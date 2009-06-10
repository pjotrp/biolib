%module biolib_libsequence
%include <std_pair.i>
%include <std_string.i>

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
%}

%ignore Sequence::Seq::operator[];
#rename(__aref__) Sequence::Seq::operator[];
#%ignore boost::noncopyable;
%template(Pair) std::pair<std::string, std::string>;

%rename(to_string) Sequence::Seq::operator std::string() const;

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


%extend Sequence::Seq {
 char __aref__ (const size_type & i)
    {
    assert(i < ($self->GetSeq()).length ());
    return ($self->GetSeq())[i];
    }
};

%extend Sequence::Seq {
  char __aref__ (const size_type & i) const
    {
    assert(i < ($self->GetSeq()).length ());
    return ($self->GetSeq())[i];
    }
};




