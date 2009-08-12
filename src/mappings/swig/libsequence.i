%module biolib_libsequence

%include <std_pair.i>
%include <std_string.i>
#%rename(begin_const) std::vector<Sequence::chromosome>::begin() const;
%include <std_vector.i>
%include <std_list.i>
%include <file.i>
%include <typemaps.i>
#%include <std_iostream.i>
%include <carrays.i>
%include <cpointer.i>

%array_class(double, doubleArray);
%array_class(std::string, stringArray);
%array_class(unsigned, unsignedArray);
%pointer_class(int, intPointer);
%pointer_class(unsigned, unsignedPointer);
%pointer_class(double, doublePointer);
%pointer_class(std::string, strPointer);
#%pointer_class(char, charPointer);
#%pointer_class(std::pair<int,int>, pairPointer);
%template(intPair) std::pair<int, int>;
%template(doublePair) std::pair<double, double>;

%template(intVector) std::vector<int>;
%template(doubleVector) std::vector<double>;
%template(charVector) std::vector<char*>;
%template() std::vector< std::vector<double> >;
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
  #include <Sequence/PolyTableSlice.hpp>
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
  #include <iterator>
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
  #include <Sequence/RNG/gsl_rng_wrappers.hpp>
  #include <gsl/gsl_rng.h>
  #include <Sequence/FastaExplicit.hpp>
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
#%ignore Sequence::AlignStream::UnGappedLength();
%ignore Sequence::PolyTableSlice::operator[];
#%ignore Sequence::Seq::operator[] const;
#%rename(__aref__) Sequence::Seq::operator[];
#%ignore boost::noncopyable;
#%rename(__getitem__) Sequence::PolyTable::operator[];
%template(strPair) std::pair<std::string, std::string>;
%template() std::pair<unsigned, unsigned>;
%template() std::pair<unsigned, Sequence::shortestPath::pathType>;
%template() std::pair<std::vector<double>::iterator, double>;
%template(polymorphicSites) std::pair< double, std::string >;
%template(polySiteVector) std::vector< std::pair< double, std::string > >;
%template(gametes) std::pair< std::vector<double>, std::vector<std::string> >;


/*%inline %{
std::pair< std::vector<double>, std::vector<std::string> > * new_gametes(int size) {
      return (std::pair< std::vector<double>, std::vector<std::string> > *) malloc(size*sizeof(std::pair< std::vector<double>, std::vector<std::string> > ));
}

std::pair< std::vector<double>, std::vector<std::string> > gametes_get(std::pair< std::vector<double>, std::vector<std::string> > *gametes, int i){
      return gametes[i];
}

void gametes_set(std::pair< std::vector<double>, std::vector<std::string> > *gametes, int i, std::pair< std::vector<double>, std::vector<std::string> > value){
      gametes[i] = value;
}*/

%inline %{

std::pair< std::vector<double>, std::vector<std::string> > * gametesPointer(std::pair< std::vector<double>, std::vector<std::string> > gametes){

     return &gametes;
}

%}




%rename(begin_const) Sequence::Seq::begin() const;
%rename(end_const) Sequence::Seq::end() const;
%rename(begin_const) Sequence::AlignStream< std::pair<std::string, std::string> >::begin() const;
%rename(end_const) Sequence::AlignStream< std::pair<std::string, std::string> >::end() const;
%rename(begin_const) std::list<Sequence::marginal>::begin() const;
%rename(begin_const) Sequence::marginal::begin() const;
%rename(end_const) Sequence::marginal::end() const;

%rename(_print) print;
%rename(to_std_str) Sequence::Seq::operator std::string() const;
%rename(to_polySiteVector) Sequence::PolyTable::operator Sequence::polySiteVector() const;
%rename(std_ostream) operator<<;
%rename(chr_assgin) Sequence::chromosome::operator=;
%rename(As) Sequence::Comeron95::as() const;
#%rename(__aref2__) Sequence::marginal::operator[];
%ignore Sequence::newick_stream_marginal_tree::newick_stream_marginal_tree( const marginal * m );
%ignore Sequence::newick_stream_marginal_tree_impl::newick_stream_marginal_tree_impl( const marginal * m );
%rename(sfs_assgin) Sequence::sfs_times::operator=;
%rename(sfs_ref) Sequence::sfs_times::operator[];
#%rename(AA) Sequence::Alignment::IsAlignment<std::string>;
%ignore Sequence::pick2( const uniform_generator & uni, const int & nsam);
%ignore Sequence::pick2_in_deme( const uniform_generator & uni, 
				    const std::vector<Sequence::chromosome> & sample,
				    const int & ttl_nsam,
				    const int & deme_nsam,
				    const int & deme );
#%ignore Sequence::gsl_poisson;
%ignore Sequence::bottleneck( const uniform_generator & uni,
		  const uniform01_generator & uni01,
		  const exponential_generator & expo,
		  const std::vector<chromosome> & initialized_sample, 
		  const marginal & initialized_marginal,
		  const double & tr,
		  const double & d,
		  const double & f,
		  const double & rho = 0.,
		  const bool & exponential_recovery = false,
		  const double & recovered_size = 1. );
%ignore Sequence::exponential_change( const uniform_generator & uni,
			  const uniform01_generator & uni01,
			  const exponential_generator & expo,
			  const std::vector<chromosome> & initialized_sample, 
			  const marginal & initialized_marginal,
			  const double & G,
			  const double & t_begin,
			  const double & t_end,
			  const double & rho = 0.,
			  const double & size_at_end = -1);
%ignore Sequence::infinite_sites( const uniform_generator & uni,
		      gamete_storage_type * gametes,
		      const int & nsites,
		      const arg & history,
		      const double * total_times,
		      const unsigned * segsites ); 

%ignore Sequence::infinite_sites( const poisson_generator & poiss,
		      const uniform_generator & uni,
		      gamete_storage_type * gametes,
		      const int & nsites,
		      const arg & history,
		      const double & theta );

%ignore Sequence::add_S_inf_sites( const uniform_generator & uni,
			 marginal::const_iterator history,
			 const double & tt,
			 const int & beg, const int & end,
			 const int & nsam,
			 const int & nsites,
			 const int & S ,
			 const int & first_snp_index,
			 gamete_storage_type * gametes );

%ignore Sequence::infinite_sites_sim_data( const uniform_generator & uni,
				   const int & nsites,
				   const arg & history,
				   const double * total_times,
				   const unsigned * segsites);

%ignore Sequence::infinite_sites_sim_data( const poisson_generator & poiss,
				   const uniform_generator & uni,
				   const int & nsites,
				   const arg & history,
				   const double & theta);

%ignore Sequence::pick_spot( const uniform01_generator & uni01,
				const double & total_reclen,
				const std::vector<double> & reclens,
				std::vector<chromosome>::const_iterator sample_begin,
				const unsigned & current_nsam,
				const double * rec_map);
                        
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
#%include <Sequence/Coalescent/DemographicModels.hpp>
%include <Sequence/Correlations.hpp>
%include <Sequence/Crit.hpp>
#%include <boost/type_traits.hpp>
#%include <boost/static_assert.hpp>
#%include <boost/type_traits/is_convertible.hpp>
%include <Sequence/shortestPath.hpp>
%include <Sequence/SeqEnums.hpp>
%include <Sequence/ensureFloating.hpp>
%include <Sequence/preferFloatingTypes.hpp>
%include <Sequence/PolySNPimpl.hpp>
%include <Sequence/PathwayHelper.hpp>
#%include <Sequence/AlignStream.hpp>
%include <Sequence/Translate.hpp>
%include <Sequence/Comparisons.hpp>
#%include <boost/tuple/detail/tuple_basic.hpp>
#%include <boost/tuple/tuple.hpp>
%include <Sequence/RNG/gsl_rng_wrappers.hpp>
%include <gsl/gsl_types.h>
%include <gsl/gsl_rng.h>
%include <Sequence/bits/PolySites.tcc>
#%include <Sequence/Alignment.hpp>
%include <Sequence/bits/Alignment.tcc>
%include <Sequence/bits/AlignStream.tcc>
%include <Sequence/AlignStream.hpp>
%include <Sequence/bits/Clustalw.tcc>
%include <Sequence/Clustalw.hpp>
%include <Sequence/PolyTableSlice.hpp>
%include <Sequence/bits/PolyTableSlice.tcc>
#%include <Sequence/descriptiveStats.hpp>
%include <Sequence/bits/descriptiveStats.tcc>
%include <Sequence/bits/PolyTable.tcc>
#%include <Sequence/FastaExplicit.hpp>
#%include <Sequence/Coalescent/bits/Coalesce.tcc>
%include <Sequence/Coalescent/bits/Mutation.tcc>
#%include <Sequence/bits/Correlations.tcc>
%include <Sequence/Coalescent/bits/DemographicModels.tcc>


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
%template(hkaVector) std::vector<Sequence::HKAdata>;
#%template(Polyassign) Sequence::PolyTable::assign<double, std::string>;


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
%template(PolyTableSlice_SimData) Sequence::PolyTableSlice<Sequence::SimData>;
%template(PolyTableSlice_PolySites) Sequence::PolyTableSlice<Sequence::PolySites>;


%template(IsAlignment_strPair) Sequence::Alignment::IsAlignment< std::pair< std::string, std::string > >;
%template(IsAlignment_Fasta) Sequence::Alignment::IsAlignment< Sequence::Fasta >;
%template(Gapped_strPair) Sequence::Alignment::Gapped< std::pair< std::string, std::string> >;
%template(Gapped_Fasta) Sequence::Alignment::Gapped< Sequence::Fasta >;
%template(RemoveGaps_strPair) Sequence::Alignment::RemoveGaps< std::pair< std::string, std::string> >;
%template(RemoveGaps_Fasta) Sequence::Alignment::RemoveGaps< Sequence::Fasta >;
%template(RemoveTerminalGaps_strPair) Sequence::Alignment::RemoveTerminalGaps< std::pair<std::string, std::string> >;
%template(RemoveTerminalGaps_Fasta) Sequence::Alignment::RemoveTerminalGaps< Sequence::Fasta >;
%template(UnGappedLength_strPair) Sequence::Alignment::UnGappedLength< std::pair< std::string, std::string> >;
%template(UnGappedLength_Fasta) Sequence::Alignment::UnGappedLength< Sequence::Fasta >;
%template(Trim_strPair) Sequence::Alignment::Trim< std::pair< std::string, std::string> >;
%template(Trim_Fasta) Sequence::Alignment::Trim< Sequence::Fasta >;
%template(TrimComplement_strPair) Sequence::Alignment::TrimComplement< std::pair< std::string, std::string> >;
%template(TrimComplement_Fasta) Sequence::Alignment::TrimComplement< Sequence::Fasta >;
%template(EmptyVector_strPair) Sequence::Alignment::EmptyVector< std::pair< std::string, std::string> >;
%template(EmptyVector_Fasta) Sequence::Alignment::EmptyVector< Sequence::Fasta >;
%inline %{
std::pair<std::string, std::string> * strPairPointer(std::pair<std::string, std::string> x) {
    return &x;
}
%}
%template(ppVector) std::vector< std::pair< std::string, std::string > * >;
%template(RemoveFixedOutgroupInsertions_strPair) Sequence::Alignment::RemoveFixedOutgroupInsertions< std::pair< std::string, std::string> >;
%template(RemoveFixedOutgroupInsertions_Fasta) Sequence::Alignment::RemoveFixedOutgroupInsertions< Sequence::Fasta >;
%template(validForPolyAnalysis_strPair) Sequence::Alignment::validForPolyAnalysis< std::vector< std::pair< std::string, std::string> >::iterator>; 
%template(validForPolyAnalysis_Fasta) Sequence::Alignment::validForPolyAnalysis< std::vector< Sequence::Fasta >::iterator>; 

#%template(GetData_strPair) Sequence::Alignment::GetData<  std::pair< std::string, std::string> >;







%template(mean) Sequence::mean<std::vector<double>::iterator>;
%template(variance) Sequence::variance<std::vector<double>::iterator>;
%template(meanAndVar) Sequence::meanAndVar<std::vector<double>::iterator>;

#%template(AI) Sequence::Alignment::IsAlignment< std::string >;










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
#%template(PolySites) Sequence::PolySites::PolySites< std::pair< std::string, std::string > >;
%template(PolySites) Sequence::PolySites::PolySites< Sequence::Fasta >;
#%template(PolySites) Sequence::PolySites::PolySites< std::string >;


%template(AlignStream_Fasta) Sequence::AlignStream< Sequence::Fasta>;
%template(ClustalW_Fasta) Sequence::ClustalW< Sequence::Fasta>;
%template(AlignStream_str) Sequence::AlignStream< std::pair<std::string, std::string> >;
%template(ClustalW_str) Sequence::ClustalW<std::pair<std::string, std::string> >;



%template(pick2) Sequence::pick2<Sequence::gsl_uniform>;
%template(pick2_in_deme) Sequence::pick2_in_deme<Sequence::gsl_uniform>;
%template(bottleneck) Sequence::bottleneck<Sequence::gsl_uniform, Sequence::gsl_uniform01, Sequence::gsl_exponential>;
%template(exponential_change) Sequence::exponential_change<Sequence::gsl_uniform, Sequence::gsl_uniform01, Sequence::gsl_exponential>;
%template(infinite_sites) Sequence::infinite_sites<Sequence::gsl_uniform>;
%template(infinite_sites) Sequence::infinite_sites<Sequence::gsl_poisson, Sequence::gsl_uniform>;
%template(add_S_inf_sites) Sequence::add_S_inf_sites<Sequence::gsl_uniform>;
%template(infinite_sites_sim_data) Sequence::infinite_sites_sim_data<Sequence::gsl_uniform>;
%template(infinite_sites_sim_data) Sequence::infinite_sites_sim_data<Sequence::gsl_poisson, Sequence::gsl_uniform>;
%template(pick_spot) Sequence::pick_spot<Sequence::gsl_uniform01>;
%template(neutral_sample) Sequence::neutral_sample< Sequence::gsl_uniform, Sequence::gsl_uniform01, Sequence::gsl_exponential, Sequence::gsl_poisson>;

%template(preferFloatingTypes_double) Sequence::preferFloatingTypes<int,double>;
%template(ensureFloating_double) Sequence::ensureFloating<int, double>;

/*%extend Sequence::ProductMoment {
    %template(__funcall__) operator() < std::vector<int>::iterator, std::vector<double>::iterator >;
};*/

#%template(funcall) Sequence::ProductMoment::operator()< std::vector<int>::iterator, std::vector<double>::iterator >;








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

%template() std::binary_function<int,Sequence::gsl_uniform01,int>;
%template() std::binary_function<double,polymorphicSite,double>;
%include <Sequence/Portability/randomShuffleAdaptor.hpp>
%include <Sequence/PolyFunctional.hpp>
%ignore Sequence::random_shuffle(iterator __first, iterator __last, const generator & __g);
%include <Sequence/Portability/random_shuffle.hpp>
//%template() std::unary_function <void, double>;
/*%inline %{
struct randomU : public std::unary_function<void,double> {
    gsl_rng * __r;
    explicit randomU(gsl_rng * r) : __r(r) {}
    inline double operator()(  ) const
    {
       return gsl_ran_flat(__r,0.,1.);
    }
};
%}*/

#%template(random_shuffle_gsl) Sequence::random_shuffle<std::vector<int>::iterator, Sequence::gsl_uniform01>;
%template(randomShuffleAdaptor_gsl) Sequence::randomShuffleAdaptor<Sequence::gsl_uniform01>;
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

%extend Sequence::PolyTableSlice< Sequence::SimData>{
   SimData __getitem__(const unsigned &i)
   {
     Sequence::PolyTableSlice< Sequence::SimData>::const_iterator itr = $self->begin();
     itr = itr + i;
     return $self->get_slice(itr);
   }
};
     
%extend Sequence::PolyTableSlice< Sequence::PolySites>{
   PolySites __getitem__(const unsigned &i)
   {
     Sequence::PolyTableSlice< Sequence::PolySites>::const_iterator itr = $self->begin();
     itr = itr + i;
     return $self->get_slice(itr);
   }
};
     
/*%inline %{
%template()  std::random_shuffle<std::vector<int>::iterator, Sequence::gsl_uniform01>;
     void random_shuffle_gsl(std::vector<int>::iterator beg, std::vector<int>::iterator end, Sequence::randomShuffleAdaptor<Sequence::gsl_uniform01> ru){
     std::random_shuffle<std::vector<int>::iterator, Sequence::gsl_uniform01> (beg, end, ru);
}

%}*/


