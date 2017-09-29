#include <utility>

// @see http://en.cppreference.com/w/cpp/language/auto
// @see http://www.cnblogs.com/QG-whz/p/4951177.html C++11ÌØÐÔ£ºauto ¹Ø¼ü×Ö

namespace {

  #pragma region auto variable initializer

  // When declaring variables in block scope, in namespace scope, in initialization statements of for loops, etc., the keyword auto may be used as the type specifier.
  // Once the type of the initializer has been determined, the compiler determines the type that will replace the keyword auto 
  // the rules for template argument deduction from a function call(see template argument deduction#Other contexts for details).
  // The keyword auto may be accompanied by modifiers, such as const or &, which will participate in the type deduction.
  //
  // For example, given 
  //    `const auto& i = expr;`,
  // the type of i is exactly the type of the argument u in an imaginary template 
  //    `template<class U> void f(const U& u)`
  // if the function call f(expr) was compiled.

  void test1() {
    //auto         => will copy the value
    //auto&        => will only bind to modifiable lvalues
    //const auto&  => will bind to anything but make it const
    //const auto&& => will bind only to rvalues

    int i = 0;
    const int ci = 0;

    auto x1 = i; // int
    auto x2 = ci; // int, auto ordinarily ignores top-level consts
    const auto x3 = i; // const int

    auto& x4 = ci; // const int&, `auto` is deduced to be `const int`

    // auto& x4 = 0; 
    // Error, since `0`'s type is `int`, `auto` is deduced to be `int` (not `const int`, `const int&` can be bind to `0`),
    const int& cRef = 0;
    // but `0` is a non-const rvalue (`decltype(0)` is `int`, not `const int`), so it can not be bind to `int&`.
    // This forbids modification to a temporary variable (non-const rvalue).

    auto&& x5 = 0; // int&&
    const auto&& x6 = 0; // const int&&
    const auto& x7 = 0; // const int&

    // const auto&& x8 = i; // Error, const T&& can only bind to rvalue (const or non-const)
    const auto&& x9 = 0; // const int&&
    const auto&& x10 = std::move(i); // const int&&

    // Therefore, `auto&&` may be deduced either as an lvalue reference or rvalue reference (`auto&&` will bind to anything)
    // according to the initializer, which is used in range-based for loop.
    auto&& x11 = 0; // int&&
    auto&& x12 = i; // int&
    auto&& x13 = ci; // const int&

    // If auto is used to declare multiple variables, the deduced types must match.
    // For example, the declaration 
    //    `auto i = 0, d = 0.0;`
    // is ill-formed, 
    // while the declaration 
    auto multiAutoVarI = 0, *pMultiAutoVarI = &multiAutoVarI;
    // is well-formed and the auto is deduced as int.
  }

  // `auto& x = 0` fails as:
  template<typename U>
  U& func1(U& u) { return u; }
  // auto x = func1(0); // Error, `U` is deduced to be `int`

  #pragma endregion

  #pragma region auto function -> return type

  // In a function declaration that uses the trailing return type syntax, the keyword auto does not perform automatic type detection. It only serves as a part of the syntax.

  auto test2(int x) -> decltype(x) { // return int
    return x;
  }

  template <typename T, typename U>
  auto test3(T x, U y) -> decltype(x + y) {
    return x + y;
  }

  auto test3Result = test3(1, 1.0); // double

  #pragma endregion

  #pragma region auto function

  // In a function declaration that does not use the trailing return type syntax, 
  // the keyword auto indicates that the return type will be deduced from the operand of its return statement using the rules for template argument deduction.

  auto test4_1(int x) { // return int
    return x;
  }

  auto& test4_2(const int& x) { // return const int&
    return x;
  }

  auto&& test4_3(const int& x) { // return const int&
    return x;
  }

  auto&& test4_4(int&& x) { // return int&, since `x` is a lvalue
    return x;
  }

  auto&& test4_5(int&& x) { // return int&&
    return std::move(x);
  }

  decltype(auto) test4_6(int x) { // return int (use decltype rules) 
    return x;
  }

  decltype(auto) test4_7(int x) { // return int& (use decltype rules, add reference to a lvalue expression) 
    return (x);
  }

  template <typename T, typename U>
  auto test5(T x, U y) {
    return x + y;
  }

  auto test5Result = test5(1, 1.0); // double

  #pragma endregion

  #pragma region decltype(auto)

  // decltype(auto) variable initializer
  // If the declared type of the variable is decltype(auto), the keyword auto is replaced with the expression(or expression list) of its initializer, 
  // and the actual type is deduced using the rules for decltype.
  decltype(auto) value1 = 1 + 1.0; // double
  decltype(1 + 1.0) value2 = 1 + 1.0;

  // decltype(auto) function
  // If the return type of the function is declared decltype(auto), the keyword auto is replaced with the operand of its return statement,
  // and the actual return type is deduced using the rules for decltype.
  decltype(auto) test6(const int& x) { // return `const int&`
    return x;
  }

  #pragma endregion

  // auto :: (concepts TS)
  // A nested-name-specifier of the form auto:: is a placeholder that is replaced by a class or enumeration type following the rules for constrained type placeholder deduction.

  // cv(optional) auto ref(optional) parameter
  // A parameter declaration in a lambda expression. A function parameter declaration. (concepts TS)
  // @see http://en.cppreference.com/w/cpp/language/constraints

  // template < auto Parameter >	(since C++17)
  // If a template parameter is declared auto, its type is deduced from the corresponding argument.

  // cv(optional) auto ref(optional)[identifier - list] initializer (since C++17)
  // A structured binding declaration
  // @see http://en.cppreference.com/w/cpp/language/declarations#Structured_binding_declaration
}
