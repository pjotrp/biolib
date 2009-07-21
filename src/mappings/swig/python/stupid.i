%module stupid

%include "std_vector.i"

class Thingy:public vector<int> {
  public:
    Thingy();
    ~Thingy();
    int Func1(int a, int b);
    int Func2(int a, int b);
};
