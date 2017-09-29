#include "stdafx.h"
#include "leetcode.h"

#include <bitset>

namespace zyf {
  namespace leetcode {

    // @see https://leetcode.com/problems/hamming-distance/description/ ��Ŀ
    // @see http://blog.csdn.net/Poison520/article/details/58603914 �ⷨ
    // @see http://blog.csdn.net/qll125596718/article/details/6901935 bitset

    int Solution0461::hammingDistance(const int x, const int y) const {
      const unsigned long xXorY = x ^ y;
      const auto bs = std::bitset<sizeof(int) * 8>(xXorY);
      return bs.count();
    }
  }
}