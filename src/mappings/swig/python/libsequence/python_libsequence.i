%module libsequence

%include <file.i>
%include ../../libsequence.i
%include <std_iostream.i>

namespace std {

 class ifstream : public istream {
   public:
     ifstream(const char *fname);
     ~ifstream();
 };

 class ofstream : public ostream {
   public:
     ofstream(const char *fname);
     ~ofstream();
 };
}


