#include <iostream>
#include <string>

#include "ill_typed.h"

namespace illTyped1test {

  namespace test1 {
    using illTyped1::is_expr_ill_typed;
    // `1.0 + ""` is the ill typed expression.
    template<typename T>
    constexpr auto is_expr_ill_typed(T t) -> decltype(1.0 + "", t) {
      return false;
    }

    static_assert(is_expr_ill_typed(0), "");
  }

  namespace test2 {
    using illTyped1::is_expr_ill_typed;
    template<typename T>
    constexpr auto is_expr_ill_typed(T t) -> decltype(1.0 + t, true) {
      return false;
    }

    // `1.0 + 0` is not ill typed
    static_assert(is_expr_ill_typed(0) == false, "");
    // `1.0 + const char*` is ill typed 
    const char* const constCharPtr = "";
    static_assert(is_expr_ill_typed(constCharPtr), "");
  }
}

namespace illTyped2test1 {
  template <typename T>
  struct illTyped2::is_expr_ill_typed_t<T, std::void_t<decltype("" + T())>> : std::false_type {};

  // `"" + string()` is not ill typed
  // static_assert(is_expr_ill_typed_t<std::string>::value, ""); // generate compile error
  static_assert(illTyped2::is_expr_ill_typed_t<std::string>::value == false, "");

  // `"" + double()` is ill typed, pass assertion
  static_assert(illTyped2::is_expr_ill_typed_t<double>::value, "");
}

namespace illTyped2test2 {
  using illTyped2::is_expr_ill_typed_t;

  // Checks that `1.0 + ""` is ill typed.
  // We must write `decltype(1.0 + "",T())` which will causes a substitution failure.
  // If we simply write `decltype(1.0 + "")`, it is not a template and will cause a compile error.
  template <typename T>
  struct is_expr_ill_typed_t<T, std::void_t<decltype(1.0 + "", T())>> : std::false_type {};

  // pass assertion, the type argument is not used and only required to be default constructible.
  static_assert(is_expr_ill_typed_t<double>::value, "");

  // Notice : Even though we define the template specializations in different namespaces, 
  // there are considered when there are visible (in this case, the template specializations defined in namespace `illTyped2test1` is also considered).
  // Thus, even though `is_expr_ill_typed_t<int>` causes a substitution failure with the template specialization defined in this namespace,
  // it success with the template specialization defined in namespace `illTyped2test1` (`"" + int()` is well typed (char* + int)) and is picked.
  // Since the struct defined with template specialization extends `std::false_type`, it's static `value` member returns false.
  static_assert(is_expr_ill_typed_t<int>::value == false, "");
}

namespace illTyped3test {
  using illTyped3::is_templated_expr_ill_typed_t;

  template <typename T>
  using ill_expr1_t = decltype(1.0 + "", T());

  static_assert(is_templated_expr_ill_typed_t<ill_expr1_t, int>::value, "");

  template <typename T>
  using ill_expr2_t = decltype(1 + T());

  // using ill_expr2_t_with_void = ill_expr2_t<void>; // compile error
  static_assert(is_templated_expr_ill_typed_t<ill_expr2_t, void>::value, "");

  using ill_expr2_t_with_double = ill_expr2_t<double>;
  static_assert(is_templated_expr_ill_typed_t<ill_expr2_t, double>::value == false, "");
}

namespace illTyped4test {
  using illTyped4::is_expr_ill_typed_t;

  template <typename T>
  struct is_expr_ill_typed_t<0, T, std::void_t<decltype(1.0 + T())>> : std::false_type {};

  static_assert(is_expr_ill_typed_t<0, double>::value == false, "");
  static_assert(is_expr_ill_typed_t<0, std::string>::value, "");

  template <typename T>
  struct is_expr_ill_typed_t<1, T, std::void_t<decltype("" + T())>> : std::false_type {};

  static_assert(is_expr_ill_typed_t<1, std::string>::value == false, "");
  static_assert(is_expr_ill_typed_t<1, double>::value, "");
}
