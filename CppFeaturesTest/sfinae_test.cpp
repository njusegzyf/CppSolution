#include <type_traits>
#include <iostream>

// Substitution Failure Is Not An Error
// @see http://en.cppreference.com/w/cpp/language/sfinae
// @see https://en.wikipedia.org/wiki/Substitution_failure_is_not_an_error

// SFINAE (substitution failure is not an error) rule applies during overload resolution of function templates:
// When substituting the deduced type for the template parameter fails, the specialization is discarded from the overload set instead of causing a compile error.
// This feature is used in template metaprogramming.

/*

Function template parameters are substituted (replaced by template arguments) twice:
  explicitly specified template arguments are substituted before template argument deduction
  deduced arguments and the arguments obtained from the defaults are substituted after template argument deduction

Substitution occurs in
  all types used in the function type(which includes return type and the types of all parameters)
  all types used in the template parameter declarations
  all expressions used in the function type (since C++11)
  all expressions used in a template parameter declaration (since C++11)

A substitution failure is any situation when the type or expression above would be ill-formed (with a required diagnostic), if written using the substituted arguments.

Only the failures in the types and expressions in the immediate context of the function type or its template parameter types are SFINAE errors.
If the evaluation of a substituted type/expression causes a side-effect such as instantiation of some template specialization,
generation of an implicitly-defined member function, etc, errors in those side-effects are treated as hard errors.

*/

namespace {

  #pragma region Substitution proceeds in lexical order and stops when a failure is encountered. 

  // (since C++14)
  template<typename SomeType>
  struct inner_type {
    // typedef typename SomeType::type type; 
    using type = typename SomeType::type;
  };

  template <
    class T,
    class = typename T::type,            // SFINAE failure if T has no member type
    class U = typename inner_type<T>::type // hard error (it requires a template specialization of `inner_type<T>`) if T has no member `type` (guaranteed to not occur as of C++14)
  >
    constexpr int foo(T) { return 1; }

  // the universal one
  constexpr int foo(...) { return 0; }

  static_assert(foo(0) == 0, ""); // since use `int` as the template parameter causes SFINAE failure, use the universal one
  static_assert(foo(std::true_type()) == 1, ""); // since std::true_type has member `type`, the template specialization is picked

  #pragma endregion

  #pragma region Type SFINAE

  // 1. attempting to instantiate a pack expansion containing multiple packs of different lengths (since C++11)

  // 2. attempting to create an array of void, array of reference, array of function, array of abstract class types, array of negative size, or array of size zero.

  template<int I> void div(char(*)[I % 2 == 0] = 0) {} // this overload is selected when I is even
  template<int I> void div(char(*)[I % 2 == 1] = 0) {} // this overload is selected  when I is odd

  // 3. attempting to use a type that is not a class or enumeration on the left of a scope resolution operator ::
  template <typename T>
  constexpr int f(typename T::B*) {
    return 0;
  }

  template <typename T>
  constexpr int f(T) {
    return 1;
  }

  static_assert(f<int>(0) == 1, ""); // uses second overload

  // 4. attempting to use a member of a type, where 
  //    the type does not contain the specified member
  //    the specified member is not a type where a type is required
  //    the specified member is not a template where a template is required
  //    the specified member is not a non-type where a non-type is required

  template <int I> struct X { };
  template <template <class T> class> struct Z { };
  template <class T> void f(typename T::Y*) {}
  template <class T> void g(X<T::N>*) {}
  template <class T> void h(Z<T::template TT>*) {}
  struct A {};
  struct B { int Y; };
  struct C { typedef int N; };
  struct D { typedef int TT; };
  struct B1 { typedef int Y; };
  struct C1 { static const int N = 0; };
  struct D1 {
    template <typename T>
    struct TT {};
  };

  void test1() {
    // Deduction fails in each of these cases:
    // f<A>(0); // A does not contain a member Y
    // f<B>(0); // The Y member of B is not a type
    // g<C>(0); // The N member of C is not a non-type
    // h<D>(0); // The TT member of D is not a template

    // Deduction succeeds in each of these cases:
    f<B1>(0);
    g<C1>(0);
    h<D1>(0);
  }

  // 5. attempting to create a pointer to reference
  // 6. attempting to create a reference to void
  // 7. attempting to create pointer to member of T, where T is not a class type

  template<typename T>
  class is_class {
    typedef char yes[1];
    typedef char no[2];
    template<typename C> static yes& test(int C::*); // selected if C is a class type
    // Note : `int C::*` is a pointer to member (a pointer to an int field of C).
    // @see https://msdn.microsoft.com/en-us/library/f2wbycwh.aspx
    // @see http://www.studytonight.com/cpp/pointer-to-members.php
    template<typename C> static no& test(...);      // selected otherwise
  public:
    static constexpr bool value = sizeof(test<T>(nullptr)) == sizeof(yes);
  };

  static_assert(is_class<int>::value == false, "");
  static_assert(is_class<std::true_type>::value, "");

  // 8. attempting to give an invalid type to a non-type template parameter
  //    A non-type template-parameter shall have one of the following (optionally cv-qualified) types:
  //      integral or enumeration type,
  //      pointer to object or pointer to function,
  //      lvalue reference to object or lvalue reference to function,
  //      pointer to member,
  //      std::nullptr_t.

   // template <class T, T t> struct S {};
   // template <class T> int fs(S<T, T()>*); // Error C2993 'T (void)': illegal type for non-type template parameter 't'
   // struct SX {};
   // int i0 = fs<SX>(0); // SFINAE failure
   // int i1 = fs<SX>(SX());

  // 9. attempting to perform an invalid conversion in a template argument expression or in an expression used in function declaration

  //    template <class T, T*> int f(int) { return 0; }
  //    int i2 = f<int, 1>(0); // can¡¯t conv 1 to int*

  // 10. attempting to create a function type with a parameter of type void
  // 11. attempting to create a function type which returns an array type or a function type
  // 12. attempting to create a function type with a parameter or return type that is an abstract class.(since C++11)

  #pragma endregion

  #pragma region Expression SFINAE

  // The following expression errors are SFINAE errors
  //    Ill-formed expression used in a template parameter type
  //    Ill-formed expression used in the function type

  struct X1 {};
  struct Y1 { Y1(X1) {} }; // X is convertible to Y

  template <typename T>
  auto f1(T t1, T t2) -> decltype(t1 + t2) { return t1 + t2; }  // overload #1

  X1 f1(...) { return X1(); }  // overload #2

  void test2() {
    X1 x1, x2;
    X1 x3 = f1(x1, x2);  // deduction fails on #1 (expression x1+x2 is ill-formed), only #2 is in the overload set, and is called
    double y = f1(1.0, 1.0); // overload #1 is called
  }

  #pragma endregion

  // Library support
  // The standard library component std::enable_if allows for creating a substitution failure 
  // in order to enable or disable particular overloads based on a condition evaluated at compile time.
  // The standard library component std::void_t is another utility metafunction that simplifies SFINAE applications.
  // In addition, many type traits are implemented using SFINAE.

  // Alternatives
  // Where applicable, tag dispatch, static_assert, and, if available, concepts, are usually preferred over direct use of SFINAE.

  #pragma region Examples

  // this overload is always in the set of overloads ellipsis parameter has the lowest ranking for overload resolution
  void test(...)
  {
    std::cout << "Catch-all overload called\n";
  }

  // this overload is added to the set of overloads if
  // C is a reference-to-class type and F is a member function pointer
  template<class C, class F>
  auto test(C c, F f) -> decltype((void)(c.*f)(), void()) {
    std::cout << "Reference overload called\n";
  }

  // Error, this is not allowed in VS2015.
  //// this overload is added to the set of overloads if
  //// C is a pointer-to-class type and F is a member function pointer
  //template<class C, class F>
  //auto test(C c, F f) -> decltype((void)((c->*f)()), void())
  //{
  //  std::cout << "Pointer overload called\n";
  //}

  struct X2 { void f() {} };

  void test3() {
    X2 x;
    test(x, &X2::f); // Reference overload called
    // test(&x, &X2::f); // Pointer overload called
    test(42, 1337); // Catch-all overload called
  }

  #pragma endregion
}
