#include "stdafx.h"
#include "CppUnitTest.h"

#include "leetcode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace zyf {
namespace leetcode {

TEST_CLASS(Solution0682Test) {
public:

  TEST_METHOD(Solution0682TestMethod1) {
    auto ops = vector<string>{ "5" };
    auto res = this->solution.calPoints(ops);

    Assert::AreEqual(5, res);
  }

  TEST_METHOD(Solution0682TestMethod2) {
    auto ops = vector<string>{ "5", "2", "C" };
    auto res = this->solution.calPoints(ops);

    Assert::AreEqual(5, res);
  }

  TEST_METHOD(Solution0682TestMethod3) {
    auto ops = vector<string>{ "5", "D" };
    auto res = this->solution.calPoints(ops);

    Assert::AreEqual(15, res);
  }

  TEST_METHOD(Solution0682TestMethod4) {
    auto ops = vector<string>{ "5", "2", "+" };
    auto res = this->solution.calPoints(ops);

    Assert::AreEqual(14, res);
  }

  TEST_METHOD(Solution0682TestMethod5) {
    auto ops = vector<string>{ "5","2","C","D","+" };
    auto res = this->solution.calPoints(ops);

    Assert::AreEqual(30, res);
  }

  TEST_METHOD(Solution0682TestMethod6) {
    auto ops = vector<string>{ "5","-2","4","C","D","9","+","+" };
    auto res = this->solution.calPoints(ops);

    Assert::AreEqual(27, res);
  }

private:
  Solution0682 solution;
};

} // end namespace leetcode
}