/* @source biolib_getorf
**
** Finds and extracts open reading frames (ORFs) - this is the Biolib
** extension which calls into EMBOSS and uses much of Gary Williams' 
** logic.
**
** @author Copyright (C) Gary Williams (gwilliam@hgmp.mrc.ac.uk)
** @author Pjotr Prins (C) 2009
** @@
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License
** as published by the Free Software Foundation; either version 2
** of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
******************************************************************************/

#include <biolib_getorf.h>

static void getorf_WriteORF(const AjPSeq seq, ajint len, ajint seqlen,
			    AjBool sense, ajint find, ajint *orf_no,
			    ajint start, ajint pos, const AjPStr str,
			    AjPSeqout seqout, ajint around);

static void getorf_AppORF(ajint find, AjPStr *str,
			  const char *chrseq, ajint pos,
			  char aa);

static void getorf_FindORFs(const AjPSeq seq, ajint len, const AjPTrn trnTable,
			    ajuint minsize, ajuint maxsize, AjPSeqout seqout, 
			    AjBool sense, AjBool circular, ajint find, 
			    ajint *orf_no, AjBool methionine, ajint around);

/* types of control codon */
#define START 1
#define STOP -1

/* types of ORF to find */
#define P_STOP2STOP      0
#define P_START2STOP     1
#define N_STOP2STOP      2
#define N_START2STOP     3
#define AROUND_START     4
#define AROUND_INIT_STOP 5
#define AROUND_END_STOP  6

/* @func biolib_getorf ********************************************************
******************************************************************************/

ORF *biolib_getorf(AjPSeq seq, AjPTrn table, unsigned int minsize)
{
}

/* @func getorf_acd ***********************************************************
**
** Finds and extracts open reading frames (ORFs)
**
******************************************************************************/

int getorf_acd(int argc, char **argv)
{

    AjPSeqall seqall;
    AjPSeqout seqout;
    AjPStr tablestr;
    ajint table;
    ajuint minsize;
    ajuint maxsize;
    AjPStr findstr;
    ajint find;
    AjBool methionine;
    AjBool circular;
    AjBool reverse;
    ajint around;

    AjPSeq seq = NULL;
    AjPTrn trnTable;
    AjPStr sseq = NULL;	/* sequence string */

    /* ORF number to append to name of sequence to create unique name */
    ajint orf_no;
			   

    AjBool sense;	/* ajTrue = forward sense */
    ajint len;

    embInit("getorf", argc, argv);
    
    seqout     = ajAcdGetSeqoutall("outseq");
    seqall     = ajAcdGetSeqall("sequence");
    tablestr   = ajAcdGetListSingle("table");
    minsize    = ajAcdGetInt("minsize");
    maxsize    = ajAcdGetInt("maxsize");
    findstr    = ajAcdGetListSingle("find");
    methionine = ajAcdGetBoolean("methionine");
    circular   = ajAcdGetBoolean("circular");
    reverse    = ajAcdGetBoolean("reverse");
    around     = ajAcdGetInt("flanking");
    
    
    /* initialise the translation table */
    ajStrToInt(tablestr, &table);
    trnTable = ajTrnNewI(table);
    
    /* what sort of ORF are we looking for */
    ajStrToInt(findstr, &find);
    
    /*
    ** get the minimum size converted to protein length if storing
    ** protein sequences
    */
    if(find == P_STOP2STOP || find == P_START2STOP || find == AROUND_START) 
    {
	minsize /= 3;
	maxsize /= 3;
    }
    
    while(ajSeqallNext(seqall, &seq))
    {
	orf_no = 1;		   /* number of the next ORF */
	sense = ajTrue;		   /* forward sense initially */

	/* get the length of the sequence */
	len = ajSeqGetLen(seq);

	/*
	** if the sequence is circular, append it to itself to triple its
	**  length so can deal easily with wrapped ORFs, but don't update
	** len
	*/
	if(circular)
	{
	    ajStrAssignS(&sseq, ajSeqGetSeqS(seq));
	    ajStrAppendS(&sseq, ajSeqGetSeqS(seq));
	    ajStrAppendS(&sseq, ajSeqGetSeqS(seq));
	    ajSeqAssignSeqS(seq, sseq);
	}

	/* find the ORFs */
	getorf_FindORFs(seq, len, trnTable, minsize, maxsize, seqout, sense,
			circular, find, &orf_no, methionine, around);

	/* now reverse complement the sequence and do it again */
	if(reverse)
	{
	    sense = ajFalse;
	    ajSeqReverseForce(seq);
	    getorf_FindORFs(seq, len, trnTable, minsize, maxsize, seqout, sense,
			    circular, find, &orf_no, methionine,
			    around);
	}
    }
    
    ajSeqoutClose(seqout);
    ajTrnDel(&trnTable);

    ajSeqallDel(&seqall);
    ajSeqDel(&seq);
    ajStrDel(&sseq);
    ajSeqoutDel(&seqout);
    ajStrDel(&tablestr);
    ajStrDel(&findstr);

    embExit();

    return 0;
}




/* @funcstatic getorf_FindORFs ************************************************
**
** finds all orfs in the current sense and writes them out
**
** @param [r] seq [const AjPSeq] Nucleotide sequence
** @param [r] len [ajint] Sequence length
** @param [r] trnTable [const AjPTrn] Translation table
** @param [r] minsize [ajuint] Minimum size ORF to find
** @param [r] maxsize [ajuint] Maximum size ORF to find
** @param [u] seqout [AjPSeqout] Sequence output object
** @param [r] sense [AjBool] Forward (sense) strand if true, else reverse strand
** @param [r] circular [AjBool] True if sequence is circular
** @param [r] find [ajint] Find code (see main program)
** @param [w] orf_no [ajint*] ORF counter updated
** @param [r] methionine [AjBool] If true report all start codond as 'M'
** @param [r] around [ajint] Number of bases around start/stop codons
** @@
******************************************************************************/

void getorf_FindORFs(const AjPSeq seq, ajint len, const AjPTrn trnTable,
			    ajuint minsize, ajuint maxsize, AjPSeqout seqout, 
			    AjBool sense, AjBool circular, ajint find, 
			    ajint *orf_no, AjBool methionine, ajint around)
{
    AjBool ORF[3];			/* true if found an ORF */
    AjBool LASTORF[3];		 /* true if hit the end of an ORF past
				    the end on the genome in this
				    frame */
    AjBool GOTSTOP[3];		 /* true if found a STOP in a circular
				    genome's frame when
				    find = P_STOP2STOP or
				    N_STOP2STOP */
    ajint start[3];		  /* possible starting position of the
				     three frames */
    ajint pos;
    ajint codon;
    char aa;
    ajint frame;
    AjPStr newstr[3];		 /* strings of the three frames of ORF
				    sequences that we are growing */
    AjPSeq pep = NULL;
    ajint i;

    ajint seqlen;
    const char *chrseq;

    seqlen = ajSeqGetLen(seq);
    chrseq = ajSeqGetSeqC(seq);

    /* initialise the ORF sequences */
    newstr[0] = NULL;
    newstr[1] = NULL;
    newstr[2] = NULL;

    /*
    ** initialise flags for found the last ORF past the end of a circular
    ** genome
    */
    LASTORF[0] = ajFalse;
    LASTORF[1] = ajFalse;
    LASTORF[2] = ajFalse;

    /* initialise flags for found at least one STOP codon in a frame */
    GOTSTOP[0] = ajFalse;
    GOTSTOP[1] = ajFalse;
    GOTSTOP[2] = ajFalse;

    if(circular || find == P_START2STOP || find == N_START2STOP ||
       find == AROUND_START)
    {
	ORF[0] = ajFalse;
	ORF[1] = ajFalse;
	ORF[2] = ajFalse;
    }
    else
    {
	/*
	** assume already in a ORF so we get ORFs at the start of the
	** sequence
	*/
	ORF[0] = ajTrue;
	ORF[1] = ajTrue;
	ORF[2] = ajTrue;
	start[0] = 0;
	start[1] = 1;
	start[2] = 2;
    }

    for(pos=0; pos<seqlen-2; pos++)
    {
	codon = ajTrnStartStopC(trnTable, &chrseq[pos], &aa);
	frame = pos % 3;
	ajDebug("len=%d, Pos=%d, Frame=%d start/stop=%d, aa=%c",
		len, pos, frame, codon, aa);
	
	/* don't want to find extra ORFs when already been round circ */
	if(LASTORF[frame])
	    continue;
	
	if(find == P_STOP2STOP || find == N_STOP2STOP ||
	   find == AROUND_INIT_STOP || find == AROUND_END_STOP)
	{   /* look for stop codon to begin reporting ORF */
	    /* note that there was at least one STOP in a circular genome */
	    if(codon == STOP)
	    {
		GOTSTOP[frame] = ajTrue;
	    }

	    /* write details if a STOP is hit or the end of the sequence */
	    if(codon == STOP || pos >= seqlen-5)
	    {

		/*
		** End of the sequence? If so, append any
		** last codon to the sequence - otherwise, ignore the STOP
		** codon
		*/
		if(codon != STOP)
		    getorf_AppORF(find, &newstr[frame], chrseq, pos,
				  aa);

		/* Already have a sequence to write out? */
		if(ORF[frame])
		{
		    if(ajStrGetLen(newstr[frame]) >= minsize && 
		       ajStrGetLen(newstr[frame]) <= maxsize)
		    {
			/* create a new sequence */
			if(codon == STOP)
			    getorf_WriteORF(seq, len, seqlen, sense,
					    find, orf_no, start[frame],
					    pos-1, newstr[frame],
					    seqout, around);
			else
			    getorf_WriteORF(seq, len, seqlen, sense,
					    find, orf_no, start[frame],
					    pos+2, newstr[frame],
					    seqout, around);
		    }

		    ajStrSetClear(&newstr[frame]);
		}

		/*
		** if its a circular genome and the STOP codon hits past
		** the end of the genome in all frames, then break
		*/
		if(circular && pos >= len)
		{
		    ORF[frame] = ajFalse; /* past the end of the genome */
		    LASTORF[frame] = ajTrue; /* finished getting ORFs */
		    if(LASTORF[0] && LASTORF[1] && LASTORF[2])
			break;
		}
		else
		{
		    /*
		    ** hit a STOP, therefore a potential ORF to write
		    ** out next time, even if the genome is circular
		    */
		    ORF[frame]   = ajTrue;
		    start[frame] = pos+3; /* next start of the ORF */
		}

	    }
	    else if(ORF[frame])
		/* append sequence to newstr if in an ORF */
		getorf_AppORF(find, &newstr[frame], chrseq, pos, aa);
	}
	else /* Look for start: P_START2STOP N_START2STOP AROUND_START */
	{

	    if(codon == START && !ORF[frame])
	    {
		/* not in a ORF already and found a START */
		if(pos < len)
		{
		    /*
		    **  reset the newstr to zero length to enable
		    **  storing the ORF for this
		    */
		    ajStrSetClear(&newstr[frame]);
		    ORF[frame] = ajTrue; /* now in an ORF */
		    start[frame] = pos;	/* start of the ORF for this frame */
		    if(methionine)
			getorf_AppORF(find, &newstr[frame], chrseq,
				      pos, 'M');
		    else
			getorf_AppORF(find, &newstr[frame], chrseq,
				      pos, aa);
		}
	    }
	    else if(codon == STOP)
            {
		/* hit a STOP */

		/* Already have a sequence to write out? */
		if(ORF[frame])
		{
		    ORF[frame] = ajFalse; /* not in an ORF */

		    if(ajStrGetLen(newstr[frame]) >= minsize &&
		       ajStrGetLen(newstr[frame]) <= maxsize)
		    {
			/* create a new sequence */
			getorf_WriteORF(seq, len, seqlen, sense,
					    find, orf_no, start[frame],
					    pos-1, newstr[frame],
					    seqout, around);
		    }
		}

		/*
		** if a circular genome and hit the STOP past
		** the end of the genome in all frames, then break
		*/
		if(circular && pos >= len)
		{
		    LASTORF[frame] = ajTrue; /* finished getting ORFs */
		    if(LASTORF[0] && LASTORF[1] && LASTORF[2]) break;
		}

		ajStrSetClear(&newstr[frame]);
            }
            else if(pos >= seqlen-5)
            {
		/* hit the end of the sequence  without a stop */

		/* Already have a sequence to write out? */
		if(ORF[frame])
		{
		    ORF[frame] = ajFalse; /* not in an ORF */

		    /*
		    ** End of the sequence? If so, append any
		    ** last codon to the sequence - otherwise, ignore the
		    ** STOP codon
		    */
		    if(pos >= seqlen-5 && pos < seqlen-2)
			getorf_AppORF(find, &newstr[frame], chrseq,
				      pos, aa);

		    if(ajStrGetLen(newstr[frame]) >= minsize &&
		       ajStrGetLen(newstr[frame]) <= maxsize)
		    {
			/* create a new sequence */
			getorf_WriteORF(seq, len, seqlen, sense,
                                        find, orf_no, start[frame],
                                        pos+2, newstr[frame],
                                        seqout, around);
		    }
		}

		/*
		** if a circular genome and hit the STOP past
		** the end of the genome in all frames, then break
		*/
		if(circular && pos >= len)
		{
		    LASTORF[frame] = ajTrue; /* finished getting ORFs */
		    if(LASTORF[0] && LASTORF[1] && LASTORF[2]) break;
		}

		ajStrSetClear(&newstr[frame]);
	    }
	    else
		if(ORF[frame])
		    getorf_AppORF(find, &newstr[frame], chrseq, pos,
				  aa);

	}
    }

    /*
    ** Currently miss reporting a STOP-to-STOP ORF that is
    ** the full length of a circular genome when there are no STOP codons in
    ** that frame
    */
    if((find == P_STOP2STOP || find == N_STOP2STOP) && circular)
    {
	if(!GOTSTOP[0])
	{
	    /* translate frame 1 into pep */
	    pep = ajTrnSeqOrig(trnTable, seq, 1);
	    if(ajSeqGetLen(pep) >= minsize && 
	       ajSeqGetLen(pep) <= maxsize)
		getorf_WriteORF(seq, len, seqlen, sense, find, orf_no,
				0, seqlen-1, ajSeqGetSeqS(pep), seqout,
				around);
	    ajSeqDel(&pep);
	}

	if(!GOTSTOP[1])
	{
	    /* translate frame 2 into pep */
	    pep = ajTrnSeqOrig(trnTable, seq, 2);
	    if(ajSeqGetLen(pep) >= minsize &&
	       ajSeqGetLen(pep) <= maxsize)
		getorf_WriteORF(seq, len, seqlen, sense, find, orf_no,
				1, seqlen-1, ajSeqGetSeqS(pep), seqout,
				around);
	    ajSeqDel(&pep);
	}

	if(!GOTSTOP[2])
	{
	    /* translate frame 3 into pep */
	    pep = ajTrnSeqOrig(trnTable, seq, 3);
	    if(ajSeqGetLen(pep) >= minsize && 
	       ajSeqGetLen(pep) >= maxsize)
		getorf_WriteORF(seq, len, seqlen, sense, find, orf_no,
				2, seqlen-1, ajSeqGetSeqS(pep), seqout,
				around);
	    ajSeqDel(&pep);
	}
    }

    for(i=0;i<3;++i)
	ajStrDel(&newstr[i]);

    return;
}




/* @funcstatic getorf_WriteORF ************************************************
**
** Undocumented.
**
** @param [r] seq [const AjPSeq] Undocumented
** @param [r] len [ajint] Undocumented
** @param [r] seqlen [ajint] Undocumented
** @param [r] sense [AjBool] Undocumented
** @param [r] find [ajint] Undocumented
** @param [w] orf_no [ajint*] Undocumented
** @param [r] start [ajint] Undocumented
** @param [r] pos [ajint] Undocumented
** @param [r] str [const AjPStr] Undocumented
** @param [u] seqout [AjPSeqout] Undocumented
** @param [r] around [ajint] Undocumented
** @@
******************************************************************************/

static void getorf_WriteORF(const AjPSeq seq,
			    ajint len, ajint seqlen, AjBool sense,
			    ajint find, ajint *orf_no, ajint start, ajint pos,
			    const AjPStr str, AjPSeqout seqout, ajint around)
{
    AjPSeq new;
    AjPStr name  = NULL;       		/* name of the ORF */
    AjPStr value = NULL;       		/* string value of the ORF number */
    ajint s;
    ajint e;				/* start and end positions */
    AjPStr aroundstr = NULL;		/* holds sequence string around the
					   codon of interest */
    ajint codonpos = 0;			/* holds position of start of codon
					   of interest */

    s = start+1;
    e = pos+1;

    /*
    ** it is possible for an ORF in a circular genome to appear to start
    ** past the end of the genome.
    ** Move the reported positions back to start in the range 1..len
    ** for readability.
    */
    while(s > len)
    {
	s -= len;
	e -= len;
    }

    new = ajSeqNew();
    if(find == N_STOP2STOP || find == N_START2STOP ||
	find == AROUND_INIT_STOP || find == AROUND_END_STOP ||
	find == AROUND_START)
	ajSeqSetNuc(new);
    else
	ajSeqSetProt(new);


    /*
    ** Set the start and end positions to report and get the sequence for
    ** the AROUND* sequences
    */
    if(find == AROUND_INIT_STOP)
    {
	codonpos = s-3;
	s = codonpos - around;		/* 50 before the initial STOP */
	e = codonpos + around+2;	/* 50 after the end of the STOP */
	if(s < 1)
	    return;

	if(e > seqlen)
	    return;
	ajStrAssignSubS(&aroundstr, ajSeqGetSeqS(seq), s-1, e-1);

    }
    else if(find == AROUND_START)
    {
	codonpos = s;
	s = codonpos - around;		/* 50 before the initial STOP */
	e = codonpos + around+2;	/* 50 after the end of the STOP */
	if(s < 1)
	    return;

	if(e > seqlen)
	    return;
	ajStrAssignSubS(&aroundstr, ajSeqGetSeqS(seq), s-1, e-1);

    }
    else if(find == AROUND_END_STOP)
    {
	codonpos = e+1;
	s = codonpos - around;		/* 50 before the initial STOP */
	e = codonpos + around+2;	/* 50 after the end of the STOP */
	if(s < 1)
	    return;
				
	if(e > seqlen)
	    return;
	ajStrAssignSubS(&aroundstr, ajSeqGetSeqS(seq), s-1, e-1);
    }



    /* set the name and description */
    ajStrAssignS(&name, ajSeqGetNameS(seq));
    ajStrAppendC(&name, "_");

    /* post-increment the ORF number for the next ORF */
    ajStrFromInt(&value,(*orf_no)++);
	
    ajStrAppendS(&name, value);
    ajSeqAssignNameS(new, name);

    /* set the description of the translation */
    ajStrAssignC(&name, "[");

    /* Reverse the reported positions if this is the reverse sense */
    if(!sense)
    {
	s = len-s+1;
	e = len-e+1;
    
        /*
	** shift the positions back into the range 1..len as far as possible
        ** without going into negative numbers
	*/
        while(e > len)
	{
            s -= len;	
            e -= len;	
        }

        while(e < 0 || s < 0)
	{
            s += len;	
            e += len;	
        }
    }

    /* the base before the stop codon (numbering bases from 1) */
    ajStrFromInt(&value, s);	
					   
    ajStrAppendS(&name, value);
    ajStrAppendC(&name, " - ");

    /* the base before the stop codon (numbering bases from 1) */
    ajStrFromInt(&value, e);
					   

    ajStrAppendS(&name, value);
    ajStrAppendC(&name, "] ");

    /* make it clear if this is the reverse sense */
    if(!sense)
        ajStrAppendC(&name, "(REVERSE SENSE) ");    

    
    /*
    ** make it clear if this is a circular genome and the ORF crosses
    ** the breakpoint
    */
    if(s> len || e > len)
    	ajStrAppendC(&name, "(ORF crosses the breakpoint) ");


    if(find == AROUND_INIT_STOP || find == AROUND_START ||
	find == AROUND_END_STOP)
    {
	ajStrAppendC(&name, "Around codon at ");
	ajStrFromInt(&value, codonpos);
	ajStrAppendS(&name, value);
	ajStrAppendC(&name, ". ");
    }

    ajStrAppendS(&name, ajSeqGetDescS(seq));
    ajSeqAssignDescS(new, name);


    /* replace newstr in new */
    if(find == N_STOP2STOP || find == N_START2STOP || find == P_STOP2STOP ||
	find == P_START2STOP)
	ajSeqAssignSeqS(new, str);
    else
	/* sequence to be 50 bases around the codon */
	ajSeqAssignSeqS(new, aroundstr);

    ajSeqoutWriteSeq(seqout, new);

    ajSeqDel(&new);
    ajStrDel(&value);
    ajStrDel(&name);

    return;
}




/* @funcstatic getorf_AppORF **************************************************
**
** append aa to ORF sequence string
**
** @param [r] find [ajint] Find code
** @param [u] str [AjPStr*] Sequence string
** @param [r] chrseq [const char*] Undocumented
** @param [r] pos [ajint] Codon triplet position in chrseq
** @param [r] aa [char] Undocumented
** @@
******************************************************************************/

static void getorf_AppORF(ajint find, AjPStr *str,
			  const char *chrseq, ajint pos,
			  char aa)
{

    if(find == N_STOP2STOP || find == N_START2STOP ||
	find == AROUND_INIT_STOP || find == AROUND_END_STOP)
    {
	ajStrAppendK(str, chrseq[pos]);
	ajStrAppendK(str, chrseq[pos+1]);
	ajStrAppendK(str, chrseq[pos+2]);
    }
    else if(find == P_STOP2STOP || find == P_START2STOP ||
	    find == AROUND_START)
	ajStrAppendK(str, aa);

    return;
}
