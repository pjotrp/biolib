%module biolib_libsequence
%include <std_pair.i>
%include <std_string.i>
%include <std_vector.i>
#%include <file.i>
%include <typemaps.i>
#%include <std_iostream.i>
%include <carrays.i>
%include <cpointer.i>

%array_class(double, doubleArray);
%array_class(std::string, stringArray);
%pointer_class(int, intPointer);
#%pointer_class(std::pair<int,int>, pairPointer);
%template(intPair) std::pair<int, int>;
%template(doublePair) std::pair<double, double>;

%template(intVector) std::vector<int>;
%template(doubleVector) std::vector<double>;
%template(fragVector) std::vector< std::pair<int, int> >;
%template(scaleVector) std::vector< std::pair<double, double> >;
%template(strVector) std::vector<std::string>;

%{
  #include <Sequence/Seq.hpp>
  #include <Sequence/Fasta.hpp>
  #include <Sequence/Kimura80.hpp>
  #include <Sequence/Comeron95.hpp>
  #include <Sequence/RedundancyCom95.hpp>
  #include <Sequence/SingleSub.hpp>
  #include <Sequence/Sites.hpp>
  #include <Sequence/ThreeSubs.hpp>
  #include <Sequence/TwoSubs.hpp>
  #include <Sequence/GranthamWeights.hpp>
  #include <Sequence/Unweighted.hpp>
  #include <Sequence/WeightingSchemes.hpp>
  #include <Sequence/HKA.hpp>
  #include <Sequence/Recombination.hpp>
  #include <Sequence/PolyTable.hpp>
  #include <Sequence/PolySites.hpp>
  #include <Sequence/SimData.hpp>
  #include <Sequence/SimpleSNP.hpp>
  #include <Sequence/typedefs.hpp>
  #include <Sequence/PolyTableManip.hpp>
  #include <Sequence/SeqExceptions.hpp>
  #include <Sequence/FST.hpp>
  #include <Sequence/PolySNP.hpp>
  #include <Sequence/PolySIM.hpp>
  #include <Sequence/SimData.hpp>
  #include <Sequence/SimParams.hpp>
  #include <Sequence/Coalescent/SimTypes.hpp>
  #include <Sequence/Coalescent/Mutation.hpp>
  #include <Sequence/Coalescent/FragmentsRescaling.hpp>
  #include <Sequence/Coalescent/Coalesce.hpp>
  #include <Sequence/Coalescent/Initialize.hpp>
  #include <Sequence/Coalescent/Recombination.hpp>
  #include <Sequence/Coalescent/TreeOperations.hpp>
  #include <Sequence/Coalescent/NeutralSample.hpp>
  #include <Sequence/Coalescent/DemographicModels.hpp>
  #include <Sequence/Correlations.hpp>
  #include <Sequence/Crit.hpp>
  #include <Sequence/descriptiveStats.hpp>
  #include <Sequence/shortestPath.hpp>
  #include <Sequence/SeqEnums.hpp>
  #include <Sequence/ensureFloating.hpp>
  #include <Sequence/preferFloatingTypes.hpp>
  #include <Sequence/ComplementBase.hpp>
  #include <Sequence/stateCounter.hpp>
  #include <Sequence/Portability/randomShuffleAdaptor.hpp>
  #include <Sequence/PolySNPimpl.hpp>
  #include <Sequence/SeqProperties.hpp>
  #include <Sequence/PolyFunctional.hpp>
  #include <Sequence/AlignStream.hpp>
  #include <Sequence/PathwayHelper.hpp>
  #include <Sequence/SeqRegexes.hpp>
  #include <Sequence/Translate.hpp>
  #include <Sequence/Comparisons.hpp>
  #include <boost/tuple/tuple.hpp>
  #include <boost/tuple/detail/tuple_basic.hpp>
  #include <Sequence/Alignment.hpp>
  #include <Sequence/AlignStream.hpp>
  #include <Sequence/Clustalw.hpp>
%}

#typedef unsigned int Sequence::Seq::size_type;
%apply unsigned int {Sequence::Seq::size_type};
%apply unsigned int {Sequence::PolyTable::size_type};
#%apply unsigned int {std::vector<double>::size_type};
%apply unsigned int {Sequence::AlignStream<std::pair<std::string,std::string > >::size_type};
#%apply char {Sequence::Seq::reference};
#%apply const char {Sequence::Seq::const_reference};
%constant const double CMAX = 10000;
%constant const double PRESICION = FLT_EPSILON;
%ignore Sequence::Seq::operator[];
%ignore Sequence::marginal::operator[];
%ignore Sequence::PolyTable::operator[];
%ignore Sequence::AlignStream::operator[];
%ignore Sequence::PolyTable::position();
%ignore Sequence::AlignStream::operator=;
%ignore Sequence::AlignStream::UnGappedLength();
#%ignore Sequence::Seq::operator[] const;
#%rename(__aref__) Sequence::Seq::operator[];
#%ignore boost::noncopyable;
#%rename(__getitem__) Sequence::PolyTable::operator[];
%template(strPair) std::pair<std::string, std::string>;
%template() std::pair<unsigned, unsigned>;
%template() std::pair<unsigned, Sequence::shortestPath::pathType>;
%template() std::pair<doubelVector::iterator, double>;


%rename(_print) print;
%rename(to_std_str) Sequence::Seq::operator std::string() const;
%rename(to_polySiteVector) Sequence::PolyTable::operator Sequence::polySiteVector() const;
%rename(std_ostream) operator<<;
%rename(chr_assgin) Sequence::chromosome::operator=;
#%rename(__aref2__) Sequence::marginal::operator[];
%ignore Sequence::newick_stream_marginal_tree::newick_stream_marginal_tree( const marginal * m );
%ignore Sequence::newick_stream_marginal_tree_impl::newick_stream_marginal_tree_impl( const marginal * m );
%rename(sfs_assgin) Sequence::sfs_times::operator=;
%rename(sfs_ref) Sequence::sfs_times::operator[];
                                
/*#define BOOST_STATIC_ASSERT( B ) \
   typedef ::boost::static_assert_test<\
      sizeof(::boost::STATIC_ASSERTION_FAILURE< (bool)( B ) >)\
      > boost_static_assert_typedef_*/

/*namespace Sequence
{*/
typedef std::vector< std::pair<std::string,int> > CodonUsageTable;
typedef std::pair< double, std::string > polymorphicSite;
typedef std::vector< polymorphicSite > polySiteVector;
//}

%include <Sequence/Seq.hpp>
%include <Sequence/Fasta.hpp>
%include <Sequence/Kimura80.hpp>
%import <boost/noncopyable.hpp>
%include <Sequence/Comeron95.hpp>
%include <Sequence/RedundancyCom95.hpp>
%include <Sequence/SeqEnums.hpp>
%include <Sequence/SingleSub.hpp>
%include <Sequence/Sites.hpp>
%include <Sequence/ThreeSubs.hpp>
%include <Sequence/TwoSubs.hpp>
%include <Sequence/WeightingSchemes.hpp>
%include <Sequence/GranthamWeights.hpp>
%include <Sequence/Unweighted.hpp>
%include <Sequence/HKA.hpp>
%include <Sequence/Recombination.hpp>
%include <Sequence/PolyTable.hpp>
%include <Sequence/PolySites.hpp>
%include <Sequence/SimData.hpp>
%include <Sequence/SimpleSNP.hpp>
%include <Sequence/typedefs.hpp>
%include <Sequence/PolyTableManip.hpp>
%include <Sequence/SeqExceptions.hpp>
%include <Sequence/FST.hpp>
%include <Sequence/PolySNP.hpp>
%include <Sequence/PolySIM.hpp>
%include <Sequence/SimData.hpp>
%include <Sequence/SimParams.hpp>
#%import <memory>
%include <Sequence/Coalescent/SimTypes.hpp>
%include <Sequence/Coalescent/Mutation.hpp>
%include <Sequence/Coalescent/FragmentsRescaling.hpp>
%include <Sequence/Coalescent/Coalesce.hpp>
%include <Sequence/Coalescent/Initialize.hpp>
%include <Sequence/Coalescent/Recombination.hpp>
%include <Sequence/Coalescent/TreeOperations.hpp>
%include <Sequence/Coalescent/NeutralSample.hpp>
%include <Sequence/Coalescent/DemographicModels.hpp>
%include <Sequence/Correlations.hpp>
%include <Sequence/Crit.hpp>
#%include <boost/type_traits.hpp>
#%include <boost/static_assert.hpp>
#%include <boost/type_traits/is_convertible.hpp>
#%include <Sequence/descriptiveStats.hpp>
%include <Sequence/shortestPath.hpp>
%include <Sequence/SeqEnums.hpp>
#%include <Sequence/ensureFloating.hpp>
#%include <Sequence/preferFloatingTypes.hpp>
%include <Sequence/PolySNPimpl.hpp>
%include <Sequence/PathwayHelper.hpp>
#%include <Sequence/AlignStream.hpp>
%include <Sequence/Translate.hpp>
%include <Sequence/Comparisons.hpp>
#%include <boost/tuple/detail/tuple_basic.hpp>
#%include <boost/tuple/tuple.hpp>
#%include <Sequence/RNG/gsl_rng_wrappers.hpp>
%include <Sequence/bits/PolySites.tcc>
#%include <Sequence/Alignment.hpp>
%include <Sequence/bits/Alignment.tcc>
%include <Sequence/bits/AlignStream.tcc>
%include <Sequence/AlignStream.hpp>
%include <Sequence/bits/Clustalw.tcc>
%include <Sequence/Clustalw.hpp>

%template(Gapped) Sequence::Gapped<std::string::iterator>;
#%include <Sequence/SeqRegexes.hpp>
%constant char *basic_dna_alphabet = "[^AGTCN\\-]";
%constant char *full_dna_alphabet =  "[^AGCTNXMRWSKVHDB\\-]";
%constant char *pep_alphabet = "[^ARNDBCQEZGHILKMFPSTWYV\\-]";
#enum Nucleotides{A, T, G, C, N, GAP};
#enum GeneticCodes{UNIVERSAL};
#enum Mutations{Unknown, Ts, Tv};
#const std::string::const_iterator beg;
#enum pathType {S,n,SS,SN,NN,SSS,SSN,SNN,NNN,NONE,AMBIG};
#%template() Sequence::mean<doubleVector::iterator>;
%template(segVector) std::vector<Sequence::segment>;
%array_class(Sequence::segment, segArray);
#%template(chisq_tuple) boost::tuple<double, double, double, double>;
#%template(chisquareds) std::vector<chis_tuple>;
%template(nodeVector) std::vector<Sequence::node>;
%template(chroVector) std::vector<Sequence::chromosome>;

/*namespace Sequence
{
   namespace Alignment
    {
	template < typename T >
	bool IsAlignment (const std::vector < T  >&data)
     {
        BOOST_STATIC_ASSERT((boost::is_base_and_derived<std::pair<std::string,std::string>,T>::value
                             || boost::is_same<std::pair<std::string,std::string>,T>::value));
       for (int i = 0; unsigned (i) < data.size (); ++i)
         if (data[i].second.length () != data[0].second.length ())
           return 0;
 
       return 1;
     };
    };
};*/

%template(fastaVector) std::vector<Sequence::Fasta>;
%template(pVector) std::vector< std::pair< std::string, std::string > >;
%template(Align_IsAlignment) Sequence::Alignment::IsAlignment< std::pair< std::string, std::string > >;
%template(Align_Gapped) Sequence::Alignment::Gapped< std::pair< std::string, std::string> >;
%template(Align_RemoveGaps) Sequence::Alignment::RemoveGaps< std::pair< std::string, std::string> >;
%template(Align_RemoveTerminalGaps) Sequence::Alignment::RemoveTerminalGaps< std::pair<std::string, std::string> >;
#%template(Align_UnGappedLength) Sequence::Alignment::UnGappedLength< std::pair< std::string, std::string> >;
%template(Align_Trim) Sequence::Alignment::Trim< std::pair< std::string, std::string> >;
%template(Align_TrimComplement) Sequence::Alignment::TrimComplement< std::pair< std::string, std::string> >;
%template(Align_EmptyVector) Sequence::Alignment::EmptyVector< std::pair< std::string, std::string> >;
%template(Align_RemoveFixedOutgroupInsertions) Sequence::Alignment::RemoveFixedOutgroupInsertions< std::pair< std::string, std::string> >;
%template(Align_validForPolyAnalysis) Sequence::Alignment::validForPolyAnalysis< std::vector< std::pair< std::string, std::string> >::iterator>; 

/*namespace std{
class pair<string,string>;
%typemap(in) pair<string,string> * {
if ((SWIG_ConvertPtr($input, (void **) &$1, $1_descriptor, SWIG_POINTER_EXCEPTION)) == -1)
 return NULL;
} 
}*/

/*%inline %{
    void Align_EmptyVector (std::vector< std::pair< std::string, std::string> >  &seqarray)
    {
      //std::vector< std::pair< std::string, std::string> > *p = &seqarray;
      for (unsigned i=0;i<seqarray.size();++i)
	delete &(seqarray[i]);
      seqarray.resize(0);
    }
%}*/


#%template(Align_IsAlignment_str) Sequence::Alignment::IsAlignment< Sequence::Seq >;
#%template() Sequence::Alignment::GetData< Sequence::Fasta >;
#%template(PolySites) Sequence::PolySites::PolySites< std::pair< std::string, std::string > >;
%template(PolySites) Sequence::PolySites::PolySites< Sequence::Fasta >;
#%template(PolySites) Sequence::PolySites::PolySites< std::string >;


#%template() Sequence::AlignStream< Sequence::Fasta>;
#%template(ClustalW_Fasta) Sequence::ClustalW< Sequence::Fasta>;
%template(AlignStream_str) Sequence::AlignStream< std::pair<std::string, std::string> >;
%template(ClustalW_str) Sequence::ClustalW<std::pair<std::string, std::string> >;








/*%extend Sequence::ClustalW<std::pair<std::string, std::string> >{
   
   ClustalW<std::pair<std::string, std::string> > (const std::vector<std::pair<std::string, std::string> > & data ):
      Sequence::AlignStream< std::pair<std::string, std::string> > (data)
   {}
  
};*/

/*%extend Sequence::ClustalW{
   ClustalW(const std::vector<T>):
      AlignStream(std::vector<T>)
   {}
};*/






/*%extend Sequence::PolySites{
    %template(temp_PolySites) PolySites< Sequence::Fasta >;
};*/

/*%extend Sequence::marginal{
  
  marginal()
   {
   }
};*/

#%ignore std::list<maginal>::list(size_type);
%include <std_list.i>
#%ignore std::list<maginal>::list(size_type);
%template(margList) std::list<Sequence::marginal>;



namespace Sequence{
template<typename Iter>
   bool validSeq(Iter beg, Iter end, const char *_pattern = Sequence::basic_dna_alphabet, const bool icase = true)
  {
     boost::regex in_alphabet(_pattern,icase);
     boost::match_results<Iter> match;
     return !(boost::regex_search(beg, end, match, in_alphabet, boost::match_default));
   };
};

%template(validSeq) Sequence::validSeq<Sequence::Seq::iterator>;


 template <class _Arg, class _Result>
    struct unary_function
    {
      typedef _Arg argument_type;                                                
      typedef _Result result_type; 
    };

%template() std::unary_function <char, void>;
%template() std::unary_function <char, bool>;

%include <Sequence/ComplementBase.hpp>
%include <Sequence/stateCounter.hpp>
%include <Sequence/SeqProperties.hpp>

 template <class _Arg1, class _Arg2, class _Result>
    struct binary_function
    {
      typedef _Arg1 first_argument_type; 
      typedef _Arg2 second_argument_type;  
      typedef _Result result_type;      
    };

%template() std::binary_function<int,uni01,int>;
%template() std::binary_function<double,polymorphicSite,double>;
%include <Sequence/Portability/randomShuffleAdaptor.hpp>
%include <Sequence/PolyFunctional.hpp>



/*%extend Sequence::newick_stream_marginal_tree_impl
{
    marginal::const_iterator mi;
    const int nsam;
    std::vector<int> left,right;
    std::vector<node> tree;
    void init();
    std::ostream & parens( const int & noden,
			   std::ostream & o) const;
    newick_stream_marginal_tree_impl(const marginal & m);
    newick_stream_marginal_tree_impl(const marginal * m);
    newick_stream_marginal_tree_impl(arg::const_iterator m);
};*/

#%template(Auto_ptr) std::auto_ptr<newick_stream_marginal_tree_impl>;



%extend Sequence::Seq {
 char __getitem__ (const int & i)
    {
    assert(i < ($self->GetSeq()).length ());
    return ($self->GetSeq())[i];
    }
};

/*%extend Sequence::GranthamWeights2 {
  double __getitem__ (const int & i)
    {
	assert(i < 2);
        return ($self->__weights)[i];
    }
};*/
/*%extend Sequence::Seq {
  char __aref__ (const size_type & i) const
    {
    assert(i < ($self->GetSeq()).length ());
    return ($self->GetSeq())[i];
    }
};*/

/*%extend Sequence::marginal{
 node __aref2__(const std::vector<node>::size_type &i)
   {
    assert(int(i) <= 2*($self->nsam) - 2);
    return ($self->tree)[i];
   }
};*/

/*%extend Sequence::marginal{
 node __aref2__(const std::vector<node>::size_type &i) const
   {
    assert(int(i) <= 2*($self->nsam) - 2);
    return ($self->tree)[i];
   }
};*/

%extend Sequence::PolyTable{
  std::string __getitem__(const unsigned &i)
   {
    assert(i < $self->size());
    return ($self->GetData())[i];
   }
};

%extend Sequence::PolyTable{
   double position( const unsigned &i)
   {
     assert(i < $self->numsites());
     return ($self->GetPositions())[i];
   }
};

%extend Sequence::marginal{
  node __getitem__(const unsigned &i)
   {
    assert(int(i) <= 2*($self->nsam) - 2);
    return ($self->tree)[i];
   }
};

%extend Sequence::AlignStream< std::pair<std::string, std::string> >{
   std::pair<std::string, std::string> __getitem__(const unsigned &i)
   {
     return ($self->Data())[i];
   }
};


   



