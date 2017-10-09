#include "stdafx.h"
#include "leetcode.h"

#include <cassert>

namespace zyf {
namespace leetcode {

// @see https://leetcode.com/problems/generate-parentheses/description/ ÌâÄ¿

vector<string> Solution0022::generateParenthesis(const int pairCount) {
  this->n = pairCount * 2;
  this->solutions.clear();
  this->contentPtr = std::make_unique<char[]>(n + 1);
  this->contentPtr[this->n] = '\0';

  this->generateParenthesisRec(0, pairCount, pairCount);

  return std::move(this->solutions); // use `move` to avoid copy
}

void Solution0022::generateParenthesisRec(const int index, const int remainLeft, const int remainRight) {
  if (n != index + 1) { // if we are not handle the last index
    if (remainLeft > 0) { // we can always insert a `(` and recuse
      contentPtr[index] = '(';
      generateParenthesisRec(index + 1, remainLeft - 1, remainRight);
    }
    if (remainLeft < remainRight) { // if we can insert a `)`
      contentPtr[index] = ')';
      generateParenthesisRec(index + 1, remainLeft, remainRight - 1);
    }
  } else { // if we are handle the last index
    // we should always be a `)` at the last index
    assert(remainLeft == 0 && remainRight == 1);
    contentPtr[index] = ')';
    solutions.emplace_back(contentPtr.get(), n); // use `emplace_back` to avoid extra string allocation
  }
}

} // end namespace leetcode
}
