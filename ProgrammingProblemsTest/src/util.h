#pragma once

#include <vector>
#include <string>

namespace zyf {
namespace util {

#pragma region Joiner for container types

// @see https://stackoverflow.com/questions/1430757/c-vector-to-string

template<typename Iterable, typename Sep>
class Joiner {
  const Iterable& i_;
  const Sep& s_;
public:
  Joiner(const Iterable& i, const Sep& s) : i_(i), s_(s) {}
  std::string str() const { std::stringstream ss; ss << *this; return ss.str(); }
  template<typename I, typename S> friend std::ostream& operator<< (std::ostream& os, const Joiner<I, S>& j);
};

template<typename I, typename S>
std::ostream& operator<< (std::ostream& os, const Joiner<I, S>& j) {
  auto elem = j.i_.begin();
  if (elem != j.i_.end()) {
    os << *elem;
    ++elem;
    while (elem != j.i_.end()) {
      os << j.s_ << *elem;
      ++elem;
    }
  }
  return os;
}

template<typename I, typename S>
inline Joiner<I, S> join(const I& i, const S& s) { return Joiner<I, S>(i, s); }

// usage:
// vector<int> v{ 1,2,3 };
// string s = join(v, '+').str();

template <class Str, class It>
Str join(It begin, const It end, const Str &sep) {
  typedef typename Str::value_type     char_type;
  typedef typename Str::traits_type    traits_type;
  typedef typename Str::allocator_type allocator_type;
  typedef std::basic_ostringstream<char_type, traits_type, allocator_type>
    ostringstream_type;
  ostringstream_type result;

  if (begin != end)
    result << *begin++;
  while (begin != end) {
    result << sep;
    result << *begin++;
  }
  return result.str();
}

#pragma endregion Joiner for container types



} // end namespace util
}

namespace Microsoft {
namespace VisualStudio {
namespace CppUnitTestFramework {

#pragma region Provide specializations of ToString() template to use equality asserts in test code

// Note: Function templates cannot be partially specialised, only fully, 
// so we can not provide a specialization for all vector types (vector<T>).

template<>
inline std::wstring ToString<std::vector<int>>(const std::vector<int>& pVector) {
  return ToString("std::vector{") +
    zyf::util::join(pVector.begin(), pVector.end(), ToString(",")) +
    ToString("}");
}

#pragma endregion Provide specializations of ToString() template to use equality asserts in test code

} // end namespace Microsoft::VisualStudio::CppUnitTestFramework
}
}
