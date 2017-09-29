// See : CppCon 2016 - [Stephan T. Lavavej]tuple What's New and How it Works

#include <tuple>

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <type_traits>

#pragma region Using

using std::tuple;
using std::make_tuple;
using std::get;
using std::tie;

using std::cout;
using std::endl;

using std::string;
using std::vector;
using std::pair;

#pragma endregion

#pragma region Multiple return values

static tuple<string, int, string> starship() {
  return make_tuple("NCC", 1701, "D");
}

static void callStarship() {
  const auto t = starship();
  cout << get<0>(t) << '-' << get<1>(t) << '-' << get<2>(t) << endl; // NCC-1701-D
}

#pragma endregion

#pragma region Data strucutres

static void useTupleInDataStructures() {
  vector<tuple<string, string, int>> v{
    { "Armstrong", "Apoll 11", 1969},
    { "Lovell", "Apoll 13", 1970 },
    { "Cernan", "Apoll 17", 1972 }
  };
  std::sort(v.begin(), v.end());
  for (const auto& t : v) {
    cout << get<0>(t) << '-' << get<1>(t) << '-' << get<2>(t) << endl;
  }
}

#pragma endregion

#pragma region Implementing comparisions

struct Point {
  int x;
  int y;
  int z;

  bool operator < (const Point& p) const {
    return tie(x, y, z) < tie(p.x, p.y, p.z);
  }
};

static void comparePoints() {
  //Point a{ 11,22,99 };
  auto a = Point{ 11, 22, 99 };
  Point b{ 11,33,0 };
  cout << std::boolalpha << (a < b) << endl; // false
}

#pragma endregion

#pragma region Piecewise construction

// See : http://en.cppreference.com/w/cpp/utility/piecewise_construct

static void testPiecewiseConstruction() {
  // use the values in tuples(as the constructor parameters) to constructor the values in the pair
  pair<vector<int>, vector<int>> p(std::piecewise_construct, std::forward_as_tuple(), std::forward_as_tuple(3, 1729));

  cout << p.first.size() << ' ' << p.second.size() << endl; // 0 3
}

// Note : There is no piecewise construction for tuples.

#pragma endregion

#pragma region Variadic data members 

// Implementing comparisons : convenient
//    Core Language deficiency : no default comparisons
// Piecewise construction : only choice for pair
//    Core Language limitation : exactly one parameter list
// Variadic data members : only good choice
//    Core Language deficiency : no variadic data members
//    Obnoxious to use without C++14's integer_sequence

#pragma endregion

#pragma region tuple Makers (template Omitted)

// tuple<VTypes...> make_tuple(Types&&...);
//    Like make_pair(), decays (array -> array pointer, function -> function pointer, remove cv-qualifier, ...) and unrefwraps
//    Don't use explicit template arguments (use `tuple<int> x{ 1 };` or `make_tuple(1)`)
// tuple<Types&...> tie(Types&...) noexcept;
//    Take l-value references and return l-value references
//    Can be used for unpacking assignment
// tuple<T&&...> forward_as_tuple(T&&...) noexcept;
//    Return l-value references or r-value references (takes r-values and return a tuple of r-value references)
//    Consume immediately, don't refrigerate
// tuple<CTypes...> tuple_cat(Tuples&&...);
//    Awesome, but impractical

static void testUnpackingAssignment() {
  string s;
  int i = 0;
  // assign through references
  // `tie(s, i, std::ignore)` construct a tuple of l-value references, and `starship()` create a temporary tuple,
  // when assigns the temporary tuple to the tuple of references, it assign through to the values it refer to. 
  tie(s, i, std::ignore) = starship();
  cout << s << '-' << i << endl; // NCC-1701
}

// tuple<T&> Is Clever, But Scary
// Core Language : reference data members inhibit compile generated copy / move assignment
// Standard Library : "We don't care, we want tie()"
// pair and tuple frequently provide additional functionality beyond the Core Language
//    Conversions, comparisons, etc.are wonderful
// Reference assignment was probably a step too far
//    vector<T&> is forbidden(`vector` requires actual data types) (good!)
//    vector<tuple<T&>> will misbehave(not reassign pointers as reference wrappers should, assign through to the values they refer to) (bad!)

#pragma endregion

#pragma region tuple type traits

// tuple_size<Tuple>::value; tuple_element<I, Tuple>::type;
//    They behave like the primary type categories
//      cv tuple<A, B, C> is acceptable
//      tuple<A, B, C>& is unacceptable
//    When taking T&&, remember to remove_reference
//      decay is less typing, but performs more transformations
//    They also accept pair and array

static int size_of_tuple = std::tuple_size<decltype(starship())>::value; // 3
using IntType = std::tuple_element<1, decltype(starship())>::type; // int, the 1th (from 0) element type of the tuple

template <typename Tuple>
decltype(auto) get_back(Tuple&& t) {
  return get<std::tuple_size<std::remove_reference_t<Tuple>>::value - 1>(std::forward<Tuple>(t));
}

static void testGetBack() {
  tuple<string, int, string> t("NCC", 1701, "D");
  cout << get_back(t) << endl;// D
}

// See : http://en.cppreference.com/w/cpp/utility/pair/tuple_size, http://en.cppreference.com/w/cpp/utility/tuple/tuple_element

#pragma endregion

#pragma region Get by index (get<I>())

// template <size_t I, typename... Types>
//    E& get(tuple<Types...>&) noexcept;
//
// template <size_t I, typename... Types>
//    E&& get(tuple<Types...>&&) noexcept;
//
// template <size_t I, typename... Types>
//    const E& get(const tuple<Types...>&) noexcept;

// Where E is typename tuple_element<I, tuple<Types...>>::type
// get() propagates lvalueness / constness

// get is a non-member
//    In templated code, member get() would require template disambiguation: `t.template get<0>()`
//    but boost::tuple has both non-member and member `get()`

#pragma endregion

// C++ 14 tuple features

//  get<T>() (N3670)
//  integer_sequence(N3658)
//    Provided by <utility>, incredibly useful with <tuple>
//  constexpr in <tuple>(N3471, LWG 2275 / 2301)
//  tuple_element_t(N3887)

#pragma region get by type (get<T>())

void testGetByType() {
  const tuple<int, string, const char *, string> t(1729, "cute", "fluffy", "kittens");
  cout << get<int>(t) << " " << get<1>(t) << " " << get<const char *>(t) << " " << get<3>(t) << endl; // 1729 cute fluffy kittens
  // get<string>(t) would emit a compiler error
}

// get() Overloads In C++14
//  template <size_t I, typename... Types> constexpr
//    E& get(tuple<Types...>&) noexcept;
//    E&& get(tuple<Types...>&&) noexcept;
//    const E& get(const tuple<Types...>&) noexcept;
// template <typename T, typename... Types> constexpr
//    T& get(tuple<Types...>&) noexcept;
//    T&& get(tuple<Types...>&&) noexcept;
//    const T& get(const tuple<Types...>&) noexcept;
//
// get() still propagates lvalueness / constness
// More overloads for pair and array

#pragma endregion

#pragma region integer_sequence

// template <typename T, T...> struct integer_sequence;
// template <typename T, T N> using make_integer_sequence = integer_sequence<T, 0, 1, etc, N - 1>;
// template <size_t... I> using index_sequence = integer_sequence<size_t, I...>;
// template <size_t N> using make_index_sequence = make_integer_sequence<size_t, N>;
// template <typename... T> using index_sequence_for = make_index_sequence<sizeof...(T)>;

template <typename F, typename... Args>
struct MiniBinder {
  F m_f; // the function object
  tuple<Args...> m_t; // use tuple to store variadic arguments for the function object

  explicit MiniBinder(F f, Args... args) : m_f(f), m_t(args...) { }

  template <size_t... Idxs>
  decltype(auto) call(std::index_sequence<Idxs...>) const {
    // `Idxs` means `0, 1, ..., N-1` where N is the number of `Args`.
    // Thus `get<Idxs>(m_t)...` is expanded to `get<0>(m_t), get<1>(m_t), ..., get<N-1>(m_t)` 
    return m_f(get<Idxs>(m_t)...);
  }

  decltype(auto) operator()() const {
    // `std::index_sequence_for<Args...>` is expanded to `make_index_sequence<sizeof...(Args)>`,
    // and then `integer_sequence<T, 0, 1, ..., N - 1>`, where N is the number of `Args`.
    // `{}` enforces to make an instance of struct `integer_sequence`, while `()` maybe a function call.
    return call(std::index_sequence_for<Args...>{});
  }
};

template <typename F, typename... Args>
static auto mini_bind(F f, Args... args) {
  return MiniBinder<F, Args...>(f, args...);
}

static int add(int a, int b, int c, int d) {
  return a + b + c + d;
}

static int testMiniBind() {
  auto mb = mini_bind(add, 1000, 700, 20, 9);
  cout << mb() << endl;
}

#pragma endregion

// C++ 17 tuple features

// apply() (P0220R1)
// make_from_tuple() (P0209R2)
//    Logical Operator Type Traits(P0013R1)
// Provided by <type_traits>, useful in implementing <tuple>
// Improving pair And tuple(N4387)

#pragma region apply()

// `apply()` takes a callable object, a tuple and an index sequence,
// it invokes the callable object with the unpacked members of the tuple.

// apply() Implementation
//
// template <typename F, typename Tuple, size_t... I> // type `Tuple` maybe tuple, pair or array
// constexpr decltype(auto) apply_impl(
//   F&& f, Tuple&& t, index_sequence<I...>) {
//   return invoke(forward<F>(f), get<I>(forward<Tuple>(t))...);
// }
// template <typename F, typename Tuple>
// constexpr decltype(auto) apply(F&& f, Tuple&& t) {
//   return apply_impl(forward<F>(f), forward<Tuple>(t),
//                     make_index_sequence<tuple_size_v<decay_t<Tuple>>>{});
// } // ADL defenses omitted

// See : http://en.cppreference.com/w/cpp/utility/apply
// Not implemented in VC

//static void testApply() {
//  tuple<int, int, int, int> t(1000, 200, 30, 4);
//  cout << std::apply(add, t) << endl; // 1234
//  pair<string, string> p("me", "ow");
//  cout << std::apply(plus<>{}, p) << endl; // meow 
//}

#pragma endregion

#pragma region make_from_tuple()

// `make_from_tuple()` is similar to `apply()`, but used to construct an object

// make_from_tuple() Implementation
//
// template <typename T, typename Tuple, size_t... I>
// constexpr T make_from_tuple_impl(Tuple&& t, index_sequence<I...>) {
//   return T(get<I>(forward<Tuple>(t))...);
// }
// template <typename T, typename Tuple>
// constexpr T make_from_tuple(Tuple&& t) {
//   return make_from_tuple_impl<T>(forward<Tuple>(t), make_index_sequence<tuple_size_v<decay_t<Tuple>>>{});
// } // ADL defenses omitted

// See : http://en.cppreference.com/w/cpp/utility/make_from_tuple
// Not implemented in VC

//static void testMakeFromTuple() {
//  tuple<int, int> t(3, 1729);
//  // it invokes `vector(3, 1729)` instead of `vector{3, 1729}`, thus we get a vector of three 1729
//  auto v = std::make_from_tuple<vector<int>>(t);
//  for (const auto& e : v) {
//    cout << e << " "; 
//  } // print 1729 three times
//  cout << endl;
//}

#pragma endregion

#pragma region Logical Operators In <type_traits>

// meta type traits, work with type traits
// template <typename... B> struct conjunction : first false trait, otherwise last trait{};
//    Short-circuiting logical AND
//    true_type when empty
// template <typename... B> struct disjunction : first true trait, otherwise last trait{};
//    Short-circuiting logical OR
//    false_type when empty
// template <typename B> struct : bool_constant<!B::value> {};

// Short-Circuiting
//    conjunction<negation<is_same<A, B>>, is_constructible<A, X>>::value
// Metaprogramming doesn't usually short-circuit (all type traits are instantiated)
// conjunction and disjunction are special
// Minor benefit : possibly improves throughput
// Major benefit : sometimes avoids infinite recursion

// Improving pair And tuple(N4387)
// C++14 perfect forwarding constructor :
//    template <typename... UTypes> constexpr
//      explicit tuple(UTypes&&...);
// C++17 perfect forwarding constructor :
//    template <typename... UTypes> constexpr
//      EXPLICIT tuple(UTypes&&...);
// pair and tuple now have conditionally-constructors (like `noexcept(expr)`), implemented without Core support
// The constructor is implicit when all its arguments are implicit construable.

// Implicit Construction

static void print(const tuple<string, string, string>& t) {
  cout << get<0>(t) << get<1>(t) << get<2>(t) << endl;
}

static tuple<string, string, string> rgb() {
  //return make_tuple("Red", "Green", "Blue");
  // return tuple<string, string, string>{"Red", "Green", "Blue"};
  return{ "Red", "Green", "Blue" }; // requires implicit conversion from three arguments to a `tuple<string, string, string>`
}

// In C++17, we can brace returns a tuple (`return { "Red", "Green", "Blue" };`), or pass a brace to something expects a tuple,
// which will invoke the perfect forwarding constructor.
// This not accepted in C++14 in which the constructor of tuple is explicit.
void static testImplicitConstructionOfTuple() {
  print(rgb()); // RedGreenBlue
  print({ "One", "Two", "Three" }); // OneTwoThree
}

// Explicit Construction

static void print(const tuple<string, vector<int>>& t) {
  cout << get<string>(t) << " ";
  for (const auto& e : get<vector<int>>(t)) {
    cout << e << " ";
  }
  cout << endl;
}

static void testExplicitConstruction() {
  // constructor of `vector(int)` is explicit, thus the perfect forwarding constructor is explicit and we must construct explicitly.
  tuple<string, vector<int>> x("Good", 3); 
  print(x); // Good 0 0 0
  // print({ "Bad", 4 }) would emit a compiler error
}

#pragma endregion

#pragma region All tuple constructors

//template <typename... Types> class tuple {
//public:
//  // implicit default constructor, copy and move constructor
//  constexpr tuple();
//  tuple(const tuple&) = default;
//  tuple(tuple&&) = default;
//constexpr
//  EXPLICIT tuple(const Types&...);
//template <typename... U> constexpr
//  EXPLICIT tuple(U&&...);
//  EXPLICIT tuple(const tuple<U...>&);
//  EXPLICIT tuple(tuple<U...>&&);
//template <typename X, typename Y> constexpr
//  EXPLICIT tuple(const pair<X, Y>&);
//  EXPLICIT tuple(pair<X, Y>&&);

#pragma endregion
