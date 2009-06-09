%module biolib_libsequence
%include <std_pair.i>
%include <std_string.i>

%{
  #include <Sequence/Seq.hpp>
%}

%ignore Sequence::Seq::operator[];
#rename(__aref__) Sequence::Seq::operator[];
%template(Pair) std::pair<std::string, std::string>;

%rename(to_string) Sequence::Seq::operator std::string() const;

%include <Sequence/Seq.hpp>


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



