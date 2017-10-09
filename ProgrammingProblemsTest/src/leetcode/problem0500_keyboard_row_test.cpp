#include "stdafx.h"
#include "CppUnitTest.h"

#include "leetcode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace zyf {
namespace leetcode {

TEST_CLASS(Solution0500Test) {
public:

  TEST_METHOD(Solution0500TestMethod1) {
    auto res = solution.findWords(vector<string> { "a" });

    // Assert::AreEqual(res, vector<string> {"a"} ); // Note: Can not compare two vectors
    Assert::AreEqual(1, (int)res.size());
    Assert::AreEqual(string("a"), res[0]);
  }

  TEST_METHOD(Solution0500TestMethod2) {
    auto res = solution.findWords(vector<string> { "Hello", "Alaska", "Dad", "Peace" });

    // Assert::AreEqual(res, vector<string> {"Alaska", "Dad"});
    Assert::AreEqual(2, (int)res.size());
    Assert::AreEqual(string("Alaska"), res[0]);
    Assert::AreEqual(string("Dad"), res[1]);
  }

private:
  Solution0500 solution;
};

} // end namespace leetcode
}
