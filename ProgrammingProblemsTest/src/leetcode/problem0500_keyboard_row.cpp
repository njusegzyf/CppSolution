#include "stdafx.h"
#include "leetcode.h"

#include <vector>

namespace zyf {
namespace leetcode {

// @see https://leetcode.com/problems/keyboard-row/description/ 题目

static constexpr int ROW_LETTERS_SET_SIZE = 'z' - 'A' + 1;

static bitset<ROW_LETTERS_SET_SIZE> rowLettersSets[3];

//static constexpr int ROW1_CHARS_COUNT = 10;
//static constexpr int ROW2_CHARS_COUNT = 9;
//static constexpr int ROW3_CHARS_COUNT = 7;

static constexpr int ROWS_CHARS_COUNT[] = { 10, 9, 7 };

const char initRowLettersSet() {

  constexpr int lowerCaseCharDelta = 'a' - 2 * 'A';

  const char row1Chars[] = { 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P' };
  for (auto c : row1Chars) {
    rowLettersSets[0].set(c - 'A'); // set uppercase letter
    rowLettersSets[0].set(c + lowerCaseCharDelta); // set lowercase letter of `[c - 'A' + 'a' - 'A']`
  }

  const char row2Chars[] = { 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L' };
  for (auto c : row2Chars) {
    rowLettersSets[1].set(c - 'A'); // set uppercase letter
    rowLettersSets[1].set(c + lowerCaseCharDelta); // set lowercase letter
  }

  const char row3Chars[] = { 'Z', 'X', 'C', 'V', 'B', 'N', 'M' };
  for (auto c : row3Chars) {
    rowLettersSets[2].set(c - 'A'); // set uppercase letter
    rowLettersSets[2].set(c + lowerCaseCharDelta); // set lowercase letter
  }

  return '0';
}

static char initFlag = initRowLettersSet();

vector<string> Solution0500::findWords(const vector<string>& words) const {
  vector<string> oneRowWords;

  for (auto&& word : words) {
    int targetSetIndex = 0;
    for (int i = 0; i < 3; ++i) {
      if (rowLettersSets[i].test(word[0] - 'A')) {
        targetSetIndex = i;
        break;
      }
    }
    bitset<ROW_LETTERS_SET_SIZE> targetSet = rowLettersSets[targetSetIndex];

    bool flag = true;
    for (auto c : word) {
      if (!targetSet.test(c - 'A')) {
        flag = false;
        break;
      }
    }

    if (flag) {
      oneRowWords.push_back(word);
    }
  }

  return oneRowWords;
}

/* 效率比 `Solution0500::findWords` 差的一个实现。 */
static vector<string> findWords1(const vector<string>& words) {
  vector<string> oneRowWords;

  bitset<ROW_LETTERS_SET_SIZE> testSet;
  for (auto&& word : words) {
    testSet.reset();
    for (auto c : word) {
      testSet.set(c - 'A');
    }

    for (int i = 0; i < 3; ++i) {
      // test whether the `testSet` are contained in the row set
      if (testSet == (testSet & rowLettersSets[i])) { // testSet.count() == (testSet & rowLettersSets[i]).count()
        oneRowWords.push_back(word);
        break;
      }
    }
  }

  return oneRowWords;
}

} // end namespace leetcode
}