// @see http://blog.csdn.net/x348722662/article/details/51580329

// 个人总结：
// 1. const l/rvalue reference can bind to const and non-const l/rvalue (can safely remove constness)
// 2. non-const l/rvalue reference can bind to non-const l/rvalue
// 3. const lvalue reference can bind to anything (can bind to a temporary rvalue if we do not modify it)
// 
// Usually, writes a overload of type `T&&` to make use of temporary rvalue (move the temporary),
// and writes a overload of type `const T&` for other cases.

// 左值引用和右值引用的绑定规则（函数类型对象会有所例外）：
// （1）非const左值引用只能绑定到非const左值；
// （2）const左值引用可绑定到const左值、非const左值、const右值、非const右值；
// （3）非const右值引用只能绑定到非const右值；
// （4）const右值引用可绑定到const右值和非const右值。

namespace {
  struct A { A() {} };
  A lvalue;                             // 非const左值对象
  const A const_lvalue;                 // const左值对象
  A rvalue() { return A(); }              // 返回一个非const右值对象
  const A const_rvalue() { return A(); }  // 返回一个const右值对象

  // 规则一：非const左值引用只能绑定到非const左值
  A &lvalue_reference1 = lvalue;         // ok
  // A &lvalue_reference2 = const_lvalue;   // error
  // A &lvalue_reference3 = rvalue();       // error
  // A &lvalue_reference4 = const_rvalue(); // error

  // 规则二：const左值引用可绑定到const左值、非const左值、const右值、非const右值
  const A &const_lvalue_reference1 = lvalue;         // ok
  const A &const_lvalue_reference2 = const_lvalue;   // ok
  const A &const_lvalue_reference3 = rvalue();       // ok
  const A &const_lvalue_reference4 = const_rvalue(); // ok

  // 规则三：非const右值引用只能绑定到非const右值
  // A &&rvalue_reference1 = lvalue;         // error
  // A &&rvalue_reference2 = const_lvalue;   // error
  A &&rvalue_reference3 = rvalue();       // ok
  // A &&rvalue_reference4 = const_rvalue(); // error

  // 规则四：const右值引用可绑定到const右值和非const右值，不能绑定到左值
  // const A &&const_rvalue_reference1 = lvalue;         // error
  // const A &&const_rvalue_reference2 = const_lvalue;   // error
  const A &&const_rvalue_reference3 = rvalue();       // ok
  const A &&const_rvalue_reference4 = const_rvalue(); // ok

  // 规则五：函数类型例外
  void fun() {}
  using FUN = decltype(fun); // typedef void FUN();
  FUN       &  lvalue_reference_to_fun = fun; // ok
  // const FUN &  const_lvalue_reference_to_fun = fun; // ok, but qualifier applied to function type has no meaning
  FUN       && rvalue_reference_to_fun = fun; // ok
  // const FUN && const_rvalue_reference_to_fun = fun; // ok

  // Note: 右值引用绑定到字面值常量同样符合上述规则，例如：int &&rr = 123;，
  // 这里的字面值123虽然被称为常量，可它的类型为int，而不是const int。对此C++03标准文档4.4.1节及其脚注中有如下说明：
  //    If T is a non - class type, the type of the rvalue is the cv - unqualified version of T.
  //    In C++ class rvalues can have cv-qualified types(because they are objects). This differs from ISO C, in which non-lvalues never have cv-qualified types.
  // 因此123是非const右值，int &&rr = 123;语句符合上述规则三。

  const int ci = 0;
  using ConstInt = decltype(ci); // const int
  using Int = decltype(0); // int

  // 如何判断一个value是lvalue还是rvalue呢？
  // 看两点：
  // 1，是否有名字
  // 2，是否能取到它的地址
  // 如果满足任何一点，那就是lvalue
}
