#include "stdafx.h"
#include "leetcode.h"

#include <stack>

using std::stack;

namespace zyf {
namespace leetcode {

// @see https://leetcode.com/problems/valid-parentheses/description/ ÌâÄ¿

bool Solution0020::isValid(const string s) const {

  if (s.length() % 2 != 0) {
    return false;
  }

  stack<char> st;

  for (const char c : s) {
    switch (c) {
      case '{':
        st.push('}'); // push the excepted next char. Note: '{' == '}' - 2
        break;
      case '[':
        st.push(']'); // Note: '[' == ']' - 2
        break;
      case '(':
        st.push(')'); // Note: '(' == ')' - 1
        break;
      default:
        if (st.empty() || st.top() != c) {
          return false;
        }
        st.pop(); // pop the top element
    }
  }

  return st.empty();
}

} // end namespace leetcode
}
