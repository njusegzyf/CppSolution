#pragma once
#include <type_traits>

// Basic idea:
// 1. Creates a template structure or overload function that has the lowest ranking.
//    It will picks if and only if other template specification or overloads fails since SFINAE (Substitution Failure Is Not An Error).
// 2. Creates a template specification or a overload function that has high ranking.
//    It should have test expressions as template parameters.
//    If some template parameter is ill typed, it causes a substitution failure and makes the template specification or overload function been discarded.
//    Otherwise, if all template parameters are not ill typed, the template specification or overload function is picked.
// 3. The template specification or overload function should extend `std::false_type` or return false, 
//    meaning that if it is picked (all template parameters are not ill typed), then the test expression is not ill typed.
//    The template structure or overload function that has the lowest ranking should extends `std::true_type` or return true,
//    meaning that if it is picked (some template parameter is ill typed), then the test expression is ill typed.

namespace illTyped1 {

  constexpr inline bool is_expr_ill_typed(...) {
    return true;
  }

  inline bool is_expr_ill_typed_nonconst(...) {
    return true;
  }
}

namespace illTyped2 {

  template <typename T, typename = void>
  struct is_expr_ill_typed_t : std::true_type {};

}

namespace illTyped3 {

  template <template <typename> class TExpr, typename T = int, typename = void>
  struct is_templated_expr_ill_typed_t : std::true_type {};

  // Note : This specification is picked when `TExpr<T>` is a legal type
  template <template <typename> class TExpr, typename T>
  struct is_templated_expr_ill_typed_t<TExpr, T, std::void_t<TExpr<T>>> : std::false_type {};

  template <template <typename> class TExpr, typename T = int>
  inline bool isTemplatedExprIllTyped() {
    return typename is_templated_expr_ill_typed_t<TExpr, T>::value;
  }
}

namespace illTyped4 {

  // `size_t N` is used as an index
  template <size_t N, typename T, typename = void>
  struct is_expr_ill_typed_t : std::true_type {};
}

