// @see http://blog.csdn.net/x348722662/article/details/51580329

// �����ܽ᣺
// 1. const l/rvalue reference can bind to const and non-const l/rvalue (can safely remove constness)
// 2. non-const l/rvalue reference can bind to non-const l/rvalue
// 3. const lvalue reference can bind to anything (can bind to a temporary rvalue if we do not modify it)
// 
// Usually, writes a overload of type `T&&` to make use of temporary rvalue (move the temporary),
// and writes a overload of type `const T&` for other cases.

// ��ֵ���ú���ֵ���õİ󶨹��򣨺������Ͷ�����������⣩��
// ��1����const��ֵ����ֻ�ܰ󶨵���const��ֵ��
// ��2��const��ֵ���ÿɰ󶨵�const��ֵ����const��ֵ��const��ֵ����const��ֵ��
// ��3����const��ֵ����ֻ�ܰ󶨵���const��ֵ��
// ��4��const��ֵ���ÿɰ󶨵�const��ֵ�ͷ�const��ֵ��

namespace {
  struct A { A() {} };
  A lvalue;                             // ��const��ֵ����
  const A const_lvalue;                 // const��ֵ����
  A rvalue() { return A(); }              // ����һ����const��ֵ����
  const A const_rvalue() { return A(); }  // ����һ��const��ֵ����

  // ����һ����const��ֵ����ֻ�ܰ󶨵���const��ֵ
  A &lvalue_reference1 = lvalue;         // ok
  // A &lvalue_reference2 = const_lvalue;   // error
  // A &lvalue_reference3 = rvalue();       // error
  // A &lvalue_reference4 = const_rvalue(); // error

  // �������const��ֵ���ÿɰ󶨵�const��ֵ����const��ֵ��const��ֵ����const��ֵ
  const A &const_lvalue_reference1 = lvalue;         // ok
  const A &const_lvalue_reference2 = const_lvalue;   // ok
  const A &const_lvalue_reference3 = rvalue();       // ok
  const A &const_lvalue_reference4 = const_rvalue(); // ok

  // ����������const��ֵ����ֻ�ܰ󶨵���const��ֵ
  // A &&rvalue_reference1 = lvalue;         // error
  // A &&rvalue_reference2 = const_lvalue;   // error
  A &&rvalue_reference3 = rvalue();       // ok
  // A &&rvalue_reference4 = const_rvalue(); // error

  // �����ģ�const��ֵ���ÿɰ󶨵�const��ֵ�ͷ�const��ֵ�����ܰ󶨵���ֵ
  // const A &&const_rvalue_reference1 = lvalue;         // error
  // const A &&const_rvalue_reference2 = const_lvalue;   // error
  const A &&const_rvalue_reference3 = rvalue();       // ok
  const A &&const_rvalue_reference4 = const_rvalue(); // ok

  // �����壺������������
  void fun() {}
  using FUN = decltype(fun); // typedef void FUN();
  FUN       &  lvalue_reference_to_fun = fun; // ok
  // const FUN &  const_lvalue_reference_to_fun = fun; // ok, but qualifier applied to function type has no meaning
  FUN       && rvalue_reference_to_fun = fun; // ok
  // const FUN && const_rvalue_reference_to_fun = fun; // ok

  // Note: ��ֵ���ð󶨵�����ֵ����ͬ�����������������磺int &&rr = 123;��
  // ���������ֵ123��Ȼ����Ϊ����������������Ϊint��������const int���Դ�C++03��׼�ĵ�4.4.1�ڼ����ע��������˵����
  //    If T is a non - class type, the type of the rvalue is the cv - unqualified version of T.
  //    In C++ class rvalues can have cv-qualified types(because they are objects). This differs from ISO C, in which non-lvalues never have cv-qualified types.
  // ���123�Ƿ�const��ֵ��int &&rr = 123;������������������

  const int ci = 0;
  using ConstInt = decltype(ci); // const int
  using Int = decltype(0); // int

  // ����ж�һ��value��lvalue����rvalue�أ�
  // �����㣺
  // 1���Ƿ�������
  // 2���Ƿ���ȡ�����ĵ�ַ
  // ��������κ�һ�㣬�Ǿ���lvalue
}
