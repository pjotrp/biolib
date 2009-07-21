%module thingy

%include "std_vector.i"
%include "object.i"

using namespace std;

//%template(ObjPVector) std::vector<Object*>;
namespace xxx {
%rename(ObjPVector) std::vector<Object*>;

class Thingy:public std::vector<Object*> {
  public:
    Thingy();
    ~Thingy();
    int Func1(int a, int b);
    int Func2(int a, int b);
};
}