#include "stdafx.h"
#include "CppUnitTest.h"

#include "leetcode.h"

#include <stack>

#include "../util.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace zyf {
namespace leetcode {

TEST_CLASS(Solution0026Test) {
public:

  TEST_METHOD(Solution0026TestMethod1) {
    vector<int> inputNums = { 1, 2, 2 };
    vector<int> exceptedOutput = { 1, 2 };

    const int res = this->solution.removeDuplicates(inputNums);

    Assert::AreEqual(2, res);
    vector<int> actualOutput(inputNums.begin(), inputNums.begin() + res);
    Assert::AreEqual<vector<int>>(actualOutput, exceptedOutput);
  }

  TEST_METHOD(Solution0026TestMethod2) {
    vector<int> inputNums = { 1, 2, 2, 3, 3, 5 };
    vector<int> exceptedOutput = { 1, 2, 3, 5 };

    const int res = this->solution.removeDuplicates(inputNums);

    Assert::AreEqual(4, res);
    vector<int> actualOutput(inputNums.begin(), inputNums.begin() + res);
    Assert::AreEqual<vector<int>>(actualOutput, exceptedOutput);
  }

private:
  Solution0026 solution;
};

} // end namespace leetcode
}
