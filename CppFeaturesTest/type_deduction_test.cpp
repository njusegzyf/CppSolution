#include <initializer_list>
#include <vector>

// @see [CppCon2014]Scott Meyers - Type Deduction and Why You Care
// @see https://github.com/CppCon/CppCon2014/blob/master/Presentations/Type%20Deduction%20and%20Why%20You%20Care/C%2B%2B%20Type%20Deduction%20and%20Why%20You%20Care%20-%20Scott%20Meyers%20-%20CppCon%202014%20-%20CppCon%202014.pdf

namespace {

  // In C++98, type deduction used only for templates.
  // In C++11, scope expands :
  //    auto variables, universal references, lambda captures and returns, decltype.
  //    Six sets of rules.
  // In C++14, scope expands further :
  //    Function return types, lambda init captures.
  //    Same rule sets, but more usage contexts(and chances for confusion).

  // Rules:
  //    Template (also used by lambda auto parameter, auto return type)
  //      T&&
  //      T& / T*
  //      T (by value rule) (also used by lambda implicit return)
  //    decltype, decltype(auto)
  //    C++11 lambda capture (based on Template T& / T*)
  //    auto object, lambda init capture (base on Template)

  // (auto-related) Template type deduction
  // General problem :
  //    template<typename T>
  //    void f(ParamType param);
  //    f(expr); // deduce T and ParamType from expr
  // Given type of expr, what are these types ?
  //    T - The deduced type.
  //    ParamType - Often different from T(e.g, const T&).
  // Three general cases :
  //    ParamType is a reference or pointer, but not a universal reference.
  //    ParamType is a universal reference.
  //    ParamType is neither reference nor pointer.

  #pragma region Non-URef Reference/Pointer Parameters

  // If expr's type is a reference, ignore that
  // Pattern-match expr’s type against ParamType to determine T.
  template<typename T>
  void f1(T& param) {} // param is a reference

  void test1() {
    int x = 22; // int
    const int cx = x; // copy of int
    const int& rx = x; // ref to const view of int x
    f1(x); // T = int, param's type = int&
    f1(cx); // T = const int, param's type = const int&
    f1(rx); // T = const int, param's type = const int&
    // f(0); // Error, `0` is of type `int`(non-const rvalue), so T = int, param's type = int&, but not compile (can not bind `int&` to a rvalue)
    // Note : T is not a reference type.
  }

  // ParamType of const T& 
  // T changes, but param’s type doesn’t:
  template<typename T>
  void f2(const T& param) {} // param is a reference

  void test2() {
    int x = 22; // int
    const int cx = x; // copy of int
    const int& rx = x; // ref to const view of int
    f2(x); // T = int, param's type = const int&
    f2(cx); // T = int, param's type = const int&
    f2(rx); // T = int, param's type = const int&
    f2(0); // T = int, param's type = const int&, can bind `const int&` to a rvalue)
    // Note : T is not a reference type.
  }

  // Behavior with pointers essentially the same :
  template<typename T>
  void f3(T* param) {} // param now a pointer

  void test3() {
    int x = 22; // int
    const int *pcx = &x; // ptr to const view of int
    f3(&x); // T = int, param's type = int*
    f3(pcx); // T = const int, param's type = const int*
    // Note: T is not a pointer type.
    // Behavior of const T* parameters as you’d expect.
  }

  // auto and Non-URef Reference/Pointer Variables
  // auto plays role of T :
  void test4() {
    int x = 22; // as before
    const int cx = x; // as before
    const int& rx = x; // as before
    auto& v1 = x; // v1's type = int& (auto = int)
    auto& v2 = cx; // v2's type = const int& (auto = const int)
    auto& v3 = rx; // v3's type = const int& (auto = const int)
    const auto& v4 = x; // v4's type = const int& (auto = int)
    const auto& v5 = cx; // v5's type = const int& (auto = const int)
    const auto& v6 = rx; // v6's type = const int& (auto = const int)
  }

  #pragma endregion

  #pragma region Universal References

  // Treated like "normal" reference parameters, except:
  //    If expr is lvalue with deduced type E, T deduced as E&. (Reference-collapsing yields type E& for param.)
  // @see https://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers
  // @see http://blog.csdn.net/beyongwang/article/details/54025439

  template<typename T>
  void f4(T&& param) {}

  void test5() {
    int x = 22; // as before
    const int cx = x; // as before
    const int& rx = x; // as before
    f4(x); // x is lvalue => T = int&, param's type = int&
    f4(cx); // cx is lvalue => T = const int, param's type = const int&
    f4(rx); // rx is lvalue => T = const int&, param's type = const int&
    f4(22); // x is rvalue => no special handling; T = int, param’s type is int&&
  }

  #pragma endregion

  #pragma region By-Value Parameters

  // As before, if expr’s type is a reference, const or volatile, ignore that. (Since we are making a brand new object

  template<typename T>
  void f6(T param) {} // param passed by value

  void test6() {
    int x = 22; // as before
    const int cx = x; // as before
    const int& rx = x; // as before
    f6(x); // T = int, param's type = int
    f6(cx); // T = int, param's type = int
    f6(rx); // T = int, param's type = int
    // expr’s reference-/const-qualifiers always dropped in deducing T.
  }

  #pragma endregion

  #pragma region Non-Reference Non-Pointer autos

  void test7() {
    // auto again plays role of T:
    int x = 22; // as before
    const int cx = x; // as before
    const int& rx = x; // as before
    auto v1 = x; // v1's type = int (auto = int)
    auto v2 = cx; // v2's type = int (auto = int)
    auto v3 = rx; // v3's type = int (auto = int
    // Again, expr’s reference-/const-qualifiers always dropped in deducing T.
    // auto never deduced to be a reference. It must be manually added.
    // If present, use by-reference rulesets.
    auto v4 = rx; // v4's type = int
    auto& v5 = rx; // v5's type = const int&
    auto&& v6 = rx; // v6's type = const int& (rx is lvalue)
  }

  #pragma endregion

  #pragma region const exprs vs. exprs containing const

  void test8(const int * const param1, // const ptr to const
             const int * param2, // ptr to const
             int * param3) { // ptr to non-const
    auto p1 = param1; // p1's type = const int* (param1's constness ignored)
    auto p2 = param2; // p2's type = const int*
    auto p3 = param3; // p3's type = int*
  }
  // From earlier:
  //    If expr is const or volatile, ignore that.
  // More common wording:
  //    Top-level const/volatile is ignored.

  // Top-level const/volatile is ignored only when deducing types for non-reference non-pointer parameters/variables:
  void test9(const int* const param1) { // param1 is a const pointer points to a const int
    auto p1 = param1; // p1's type = const int* (param1's constness is ignored)
    auto& p2 = param1; // p2's type = const int* const& (a const reference to a pointer that points to a const int) (param1's constness is not ignored)
    const int* const& p3 = param1;

    using TConstIntPtr = const int*;
    const TConstIntPtr& p4 = param1;
  }

  #pragma endregion

  #pragma region Special Cases

  // Special treatment for exprs that are arrays or functions:
  //    When initializing a reference, array / function type deduced.
  //    Otherwise decays to a pointer before type deduction.

  #pragma endregion

  #pragma region auto Type Deduction

  // Same as template type deduction, except with braced initializers.
  //    A braced initializer has no type, so template type deduction fails.
  //    auto deduces std::initializer_list.
  template<typename T>
  void f10(T param) {}

  void test10() {
    // f10({ 1, 2, 3 }); // error! type deduction fails

    // C++17
    //    Current rules for auto + copy list initialization(with '=‘).
    //    For auto + direct list initialization(without '=').
    //        1 element in braces => auto deduces type of element.
    //        >1 element => error(ill-formed).

    // auto x1{ 1, 2, 3 }; 
    // In C++14, x's type = std::initializer_list<int>
    // Error in C++17: in a direct-list-initialization context the type for 'auto' can only be deduced from a single initializer expression

    auto x2 = { 1, 2, 3 }; // x's type = std::initializer_list<int>, as in C++14
    auto x3{ 1 }; // x's type = int, while In C++14, x's type = std::initializer_list<int>
    auto x4 = { 1 }; // x's type = std::initializer_list<int>, as in C++14
    // auto x5 = { 1, 2.0 }; // error: cannot deduce element type
  }

  #pragma endregion

  #pragma region Lambda Capture Type Deduction

  void test11() {
    // Three kinds of capture:

    // 1.By reference: uses template type deduction (for reference params).
    const int cx = 0;
    auto lambda1 = [&cx] {};
    // class lambda1Impl {
    //   const int& cx;
    // };

    // 2.By value: uses template type deduction, except cv-qualifiers are retained.
    auto lambda2 = [cx] {};
    // class lambda2Impl {
    //   const int cx; // The only place where top-level cv qualifiers is reserved when making a brand new object
    // };

    // 2.C++14’s init capture: uses auto type deduction.
    // Not equals to simple by-value capture, make a new variable and then init it.
    auto lambda3 = [x = cx] {};
    // class lambda3Impl {
    //   int x; // use auto rules, throw top-level cv qualifiers
    // };

    // const retention normally masked by default constness of operator():
    //
    // auto lambda4 = [cx] { cx = 10; }; // error!
    // class lambda4Impl {
    //   void operator()() const { cx = 10; } // a const function, which causes error
    //   int cx;
    // };
    //
    // mutable lambdas reveal the truth:
    //
    // auto lambda5 = [cx] mutable { cx = 10; }; // still error!
    // class lambda5Impl {
    //   void operator()() { cx = 10; } 
    //   const int cx; // cause error
    // };
  }

  #pragma endregion

  #pragma region Observing Deduced Types

  // During compilation: Use declared-only template with type of interest :
  template<typename T> // declaration for TD;
  class TD; // TD == "Type Displayer"
  // Instantiate the template with the type to deduce, which will fails compilation and the deduced type will be shown in the error message.

  // template<typename T> // template w/types
  // void f(T& param) // of interest
  // {
  //   TD<T> tType; // cause T to be shown
  //   TD<decltype(param)> paramType; // ditto for param's type
  // }
  // void test() {
  //   int x = 22; // as before
  //   const int& rx = x; // as before
  //   f(rx); // compiler diagnostics show types
  // }

  // For auto variables, use decltype to get type:
  // void test() 
  //   int x = 22; // as before
  //   const int& rx = x; // as before
  //   auto y = rx;
  //   TD<decltype(y)> yType; // compiler diagnostics show type
  // }

  // At runtime
  // Avoid std::type_info::name.
  //    Language rules require incorrect results in some cases!
  //    Throw reference, top-level cv qualifier.
  //
  // Given
  // template<typename T>
  // void f(const T& param) {
  //   cout << "T = " << typeid(T).name() << '\n'; // show T
  //   cout << "param = " << typeid(param).name() << '\n'; // show param's type
  // } 
  //
  // compilers report param’s type as const Widget *.
  //    Correct type is const Widget * const &.

  // Boost.TypeIndex provides accurate information :
  //
  // #include <boost/type_index.hpp>
  // template<typename T>
  // void f(const T& param)
  // {
  //   using boost::typeindex::type_id_with_cvr;
  //   cout << "T = " << type_id_with_cvr<T>().pretty_name() << '\n'; 
  //   cout << "param = " << type_id_with_cvr<decltype(param)>().pretty_name() << '\n
  // }
  //
  // gcc / Clang output (VS 2013 essentially the same.) :
  //    T = Widget const*
  //    param = Widget const* const&

  #pragma endregion

  #pragma region decltype Type Deduction

  // decltype(name) = declared type of name.
  // Unlike auto, never strips const/volatile/references.
  void test12() {
    int x = 10;
    using TX = decltype(x); // TX = int
    const auto& rx = x;
    using TRx = decltype(rx); // TRx = const int&
  }

  // decltype(lvalue expr of type T) ≡ T&
  //
  // Unsurprising. Almost all such expressions really have type T&.
  //    return type is lvalue expr and has lvalue-ref type
  //    const std::vector<Widget>& findVec(const VecHandle&); 
  // Exceptions act as if they did.
  void test13() {
    int arr[10];
    arr[0] = 5; // arr[0]'s type is int but it acts like int&
    using TIntRef = decltype(arr[0]); // int&, because arr[0] is lvalue expression
  }

  // Full rules for decltype more complex. But relevant only to hard-core library developers.
  // Rules for name and lvalue expr suffice for almost everybody almost all the time.

  // Names are lvalues, but decltype(name) rule beats decltype(expr) rule:
  void test14() {
    int x = 0;
    using TInt = decltype(x); // int, x is lvalue expression, but also a name => name rule prevails
    using TIntRef = decltype((x)); // int&, (x) is lvalue expression, but isn't a name
    // Implication of “superfluous parentheses” apparent soon.
  }

  #pragma endregion

  #pragma region Function Return Type Deduction

  // In C++11: Limited : single - statement lambdas only.
  // In C++14: Extensive : all lambdas + all functions. (Understanding type deduction more important than ever.)

  // Deduced return type specifiers:
  //    auto: Use template (not auto!) type deduction rules. (No type deduced for braced initializers.)
  //    decltype(auto): Use decltype type deduction rules.

  // returns int, wouldn't permit caller to modify std::vector.
  auto lookupValue(std::vector<int> container, int idx) {
    return container[idx];
  }

  // returns int&, would permit caller to modify std::vector.
  decltype(auto) authorizeAndIndex(std::vector<int>& v, int idx) {
    // authorizeUser();
    return v[idx];
  }

  // decltype(auto) sensitive to function implementation:
  decltype(auto) lookupValue1(std::vector<int> container, int idx) {
    auto retVal = container[idx];
    return retVal; // return int
  }

  decltype(auto) lookupValue2(std::vector<int> container, int idx) {
    auto retVal = container[idx];
    return (retVal); // return int& (to a local variable), error
  }

  // Rules of thumb :
  //    Use auto if a reference type would never be correct.
  //    Use decltype(auto) only if a reference type could be correct.

  #pragma endregion
}
