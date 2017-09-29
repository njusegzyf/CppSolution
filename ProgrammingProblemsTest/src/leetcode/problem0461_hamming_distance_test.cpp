#include "stdafx.h"
#include "CppUnitTest.h"

#include "leetcode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace zyf {
  namespace leetcode {

    TEST_CLASS(Solution0461Test) {
public:

  TEST_METHOD(Solution0461TestMethod1) {
    auto res = solution.hammingDistance(0, 0);
    Assert::AreEqual(0, res);
  }

  TEST_METHOD(Solution0461TestMethod2) {
    auto res = solution.hammingDistance(-1, 0);
    Assert::AreEqual(32, res);
  }

  TEST_METHOD(Solution0461TestMethod3) {
    auto res = solution.hammingDistance(1, 2);
    Assert::AreEqual(2, res);
  }

  TEST_METHOD(Solution0461TestMethod4) {
    auto res = solution.hammingDistance(1, 3);
    Assert::AreEqual(1, res);
  }

  TEST_METHOD(Solution0461TestMethod5) {
    auto res = solution.hammingDistance(1, 4);
    Assert::AreEqual(2, res);
  }

private:
  Solution0461 solution;

    };
  }
}