#include "stdafx.h"
#include "leetcode.h"

namespace zyf {
namespace leetcode {

// @see https://leetcode.com/problems/valid-parentheses/description/ ÌâÄ¿

int Solution0026::removeDuplicates(vector<int>& nums) const {
  const int numsSize = nums.size();
  if (numsSize < 2) {
    return numsSize;
  }

  int lastElement = nums[0];
  auto distinctIter = nums.begin() + 1;

  for (int i : nums) { // we may skip the first element
    if (i != lastElement) {
      *distinctIter = i;
      ++distinctIter;
      lastElement = i;
    }
  }

  return distinctIter - nums.begin();
}

} // end namespace leetcode
}
