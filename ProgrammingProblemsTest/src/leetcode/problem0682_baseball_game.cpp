#include "stdafx.h"
#include "leetcode.h"

#include <numeric>

namespace zyf {
namespace leetcode {

// @see https://leetcode.com/problems/baseball-game/description/ ÌâÄ¿

static inline int addLastTwo(const vector<int>& container) {
  assert(container.size() >= 2);

  auto endIter = container.cend();
  --endIter;
  auto result = *endIter;
  --endIter;
  result += *endIter;

  return result;
}

int Solution0682::calPoints(const vector<string>& ops) const {

  // since '+' operator needs the get the last two operators, we use a vector instead of a stack
  vector<int> roundScores(ops.size());

  for (auto& op : ops) {
    switch (op[0]) { // can not switch on the whole string, but we can switch on the first char
      case '+': // "+" (one round's score): Represents that the points you get in this round are the sum of the last two valid round's points.
        roundScores.push_back(addLastTwo(roundScores));
        break;

      case 'D': // "D" (one round's score): Represents that the points you get in this round are the doubled data of the last valid round's points.
        roundScores.push_back(roundScores.back() * 2);
        break;

      case 'C': // "C" (an operation, which isn't a round's score): Represents the last valid round's points you get were invalid and should be removed.
        roundScores.pop_back();
        break;

      default: // Integer (one round's score): Directly represents the number of points you get in this round.
        roundScores.push_back(std::stoi(op));
        break;
    }
  }

  return std::accumulate(roundScores.cbegin(), roundScores.cend(), 0);
}

} // end namespace leetcode
}
