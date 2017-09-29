#include "stdafx.h"
#include "leetcode.h"

#include <bitset>

namespace zyf {
  namespace leetcode {

    // @see https://leetcode.com/problems/number-of-1-bits/description/ ÌâÄ¿
   
    int Solution0191::hammingWeight(const uint32_t n) const {
      const auto bs = std::bitset<sizeof(uint32_t) * 8>(n);
      return bs.count();
    }
  }
}