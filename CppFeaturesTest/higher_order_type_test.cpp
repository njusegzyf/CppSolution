// @see http://stackoverflow.com/questions/2565097/higher-kinded-types-with-c

// Higher-order Polymorphism:
// Languages such as Java and C# have first-order polymorphism because they allow us to abstract on types. 
// e.g.List<A> can have a reverse function that works on any element type(the A).
// More practical programming languages and type systems allow us to abstract on type constructors as well.
// This feature is called higher-order (or higher-kinded) polymorphism.

#pragma region Example in Scala

/*

// Key[_] means that the type `Key` is a higher order type that takes a type parameter.
final class HigherOrderMap[Key[_], Value[_]]

// `Seq` takes one type parameter, so that `Seq` can be used.
val x1: HigherOrderMap[Seq, Seq] = new HigherOrderMap[Seq, Seq]

// `V[_, _]` means that the Type `V` is a order kind type that takes two type parameters.
final class HighOrderList[V[_, _]]

// `V[A, B] <: Map[_, _]` means that the a `V[_, _]` must extends `Map[_, _]`.
final class HighOrderList1[V[A, B] <: Map[C, D]]
// It is the same as written `V[A, B] <: Map[C, D]`.
final class HighOrderList2[V[A, B] <: Map[C, D]]
// `V[X, Y] <: Map[X, Y]` means the a `V[A, B]` must extends `Map[C, D]`.
final class HighOrderList3[V[X, Y] <: Map[X, Y]]
// A high order type can also be covariant or contravariant.
final class HighOrderList4[+V[X, Y] <: Map[X, Y]]

val x2: HighOrderList[Map] = new HighOrderList[Map]

// `KH[_[_, _]]` means that the type `KH` is a higher order type that takes a high order type parameter,
// which is required to take two type parameters.
final class HigherHigherOrder[K[_], KMap <: HigherOrderMap[K, K], KH[_[_, _]]]

val x3 : HigherHigherOrder[Seq, HigherOrderMap[Seq, Seq], HighOrderList] = new HigherHigherOrder[Seq, HigherOrderMap[Seq, Seq], HighOrderList]

final class HigherHigherOrder2[K[X] <: Seq[X], KMap <: HigherOrderMap[K, K], KH[X[_, _]] <: HighOrderList[X]]

val x4 : HigherHigherOrder[Seq, HigherOrderMap[Seq, Seq], HighOrderList] = new HigherHigherOrder[Seq, HigherOrderMap[Seq, Seq], HighOrderList]

*/

#pragma endregion

// Template-template parameters (template parameters can be templates themselves)

namespace {

  // Implement Monad
  //
  // interface Transformer<X, Y> {
  //   Y transform(X x);
  // }
  //
  // interface Monad<M> { // M :: * -> *
  //   <A> M<A> pure(A a);
  //   <A, B> M<B> bind(Transformer<A, M<B>> t, M<A> a);
  // }

  template <template <typename> typename m> // of type m[_]
  struct Monad {
    template <typename a>
    static m<a> mreturn(const a&); // a -> m<a>

    template <typename a, typename b>
    static m<b> mbind(const m<a>&, m<b>(*)(const a&)); // m<a> -> (a -> m<b>) -> m<b>
  };

  template <typename a>
  struct Maybe {
    bool isNothing;
    a value;
  };

  template <>
  struct Monad<Maybe> {
    template <typename a>
    static Maybe<a> mreturn(const a& v) {
      Maybe<a> x{ false, v };
      return x;
    }

    template <typename a, typename b>
    static Maybe<b> mbind(const Maybe<a>& action, Maybe<b>(*function)(const a&)) {
      if (action.isNothing)
        return action;
      else
        return function(action.value);
    }
  };
}
