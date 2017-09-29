#include "stdafx.h"

namespace Zhangyftest {
  namespace FunctionPointerTest {

    // a function pointer
    void(*p)(int);

    // an array of function pointer
    void(*pArray[10])(int);

    void m1(int i) {};

    void test1() { p = m1; };

    // http://www.cnblogs.com/zplutor/archive/2013/10/27/3391310.html
    // def signal(sig : Int, p : Int => Unit ) : Int => Unit
    void(*signal(int sig, void(*)(int)))(int) {
      return nullptr;
    }

    // define a function type of : Int => Unit
    typedef void Sigfunc1(int);
    using Sigfunc2 = void(int);

    // define the pointer type of `Sigfunc`
    typedef void(*PSigfuc1)(int);
    using PSigfuc2 = void(*)(int);
    typedef Sigfunc1* PSigfunc3;
    using PSingfunc4 = Sigfunc1*;

    // declare a function of same type as signal
    Sigfunc1 *signal2(int, Sigfunc1*) {
      return nullptr;
    }

    // the type of signal function
    using typeSignal = Sigfunc1*(int, Sigfunc1*);

    // error:
    // (void(*)(int)) signal(int i, void(*func)(int));

    void test2() {
      // an array of function pointer(of type typeSignal*)
      typeSignal* fpArray[2];
      fpArray[0] = &signal;
      fpArray[1] = &signal2;
    }
  }
}
