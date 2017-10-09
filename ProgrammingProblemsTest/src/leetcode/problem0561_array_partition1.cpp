#include "stdafx.h"
#include "leetcode.h"

#include <vector>
#include <algorithm>

namespace zyf {
namespace leetcode {

// @see https://leetcode.com/problems/array-partition-i/description/ ÌâÄ¿

int Solution0561::arrayPairSum(std::vector<int>& nums) const {
  std::sort(nums.begin(), nums.end());
  int pairSum = 0; // we may need to use `int64_t` if middle result overflow
  for (auto iter = nums.begin(); iter < nums.end(); iter += 2) {
    pairSum += *iter;
  }
  return pairSum;
}

}
}