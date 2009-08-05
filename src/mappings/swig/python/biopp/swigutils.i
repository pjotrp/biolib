%module si
%include "std_deque.i"
%include "std_map.i"
%include "std_string.i"
%include "std_vector.i"

%include "cpointer.i"
%pointer_class(int,intp)
%pointer_class(unsigned int,uintp)
%pointer_class(double,doublep)
%pointer_class(std::string,strp)
//%pointer_class(std::ostream,ostreamp)

%template(intVector) std::vector<int>;
%template(uintVector) std::vector<unsigned int>;
%template(doubleVector) std::vector<double>;
%template(strVector) std::vector<std::string>;

%template(intDeque) std::deque<int>;
%template(uintDeque) std::deque<unsigned int>;
%template(doubleDeque) std::deque<double>;
%template(stringDeque) std::deque<std::string>;

%template(intMap) std::map<int,int>;
%template(strMap) std::map<std::string,std::string>;