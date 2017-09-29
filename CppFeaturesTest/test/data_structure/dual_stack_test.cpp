#include "dual_stack_test.h"

#include <cassert>

#include <string>
#include <algorithm>
#include <vector>

#include "../../data_structure/dual_stack.h"

namespace zyf {
  namespace test {

    namespace dualstack {
      void Create_IntAndStringDualStack() {
        DualStack<int> intDualStack(16);
        DualStack<std::string> stringDualStack(16);
      }

      void IsEmpty_InBothStack0AndStack1() {
        DualStack<int> intDualStack(16);
        auto& stack0 = intDualStack.getStack0();
        auto& stack1 = intDualStack.getStack1();

        assert(stack0.IsEmpty());
        assert(stack1.IsEmpty());
      }

      void IsEmpty_OnlyInStack0() {
        DualStack<int> intDualStack(16);
        auto& stack0 = intDualStack.getStack0();
        auto& stack1 = intDualStack.getStack1();

        stack0.Push(0);

        assert(!stack0.IsEmpty());
        assert(stack1.IsEmpty());
      }

      void IsEmpty_OnlyInStack1() {
        DualStack<int> intDualStack(16);
        auto& stack0 = intDualStack.getStack0();
        auto& stack1 = intDualStack.getStack1();

        stack1.Push(0);

        assert(stack0.IsEmpty());
        assert(!stack1.IsEmpty());
      }

      void PushAndPop_OnlyInStack0() {
        std::vector<int> input = { 1, 2, 3 };
        DualStack<int> intDualStack(16);
        auto& stack0 = intDualStack.getStack0();

        for (int v : input) {
          stack0.Push(v);
        }

        std::vector<int> output;
        while (!stack0.IsEmpty()) {
          int v;
          assert(stack0.Pop(v));
          output.push_back(v);
        }

        std::vector<int> reversedInput(input);
        std::reverse(reversedInput.begin(), reversedInput.end());

        assert(output == reversedInput);
      }

      void PushAndPop_OnlyInStack1() {
        std::vector<int> input = { 1, 2, 3 };
        DualStack<int> intDualStack(16);
        auto& stack1 = intDualStack.getStack1();

        for (int v : input) {
          stack1.Push(v);
        }

        std::vector<int> output;
        while (!stack1.IsEmpty()) {
          int v;
          assert(stack1.Pop(v));
          output.push_back(v);
        }

        std::vector<int> reversedInput(input);
        std::reverse(reversedInput.begin(), reversedInput.end());

        assert(output == reversedInput);
      }

      void PushAndPop_InBothStack0AndStack1() {
        std::vector<int> input = { 1, 2, 3 };
        DualStack<int> intDualStack(16);
        auto& stack0 = intDualStack.getStack0();
        auto& stack1 = intDualStack.getStack1();

        for (int v : input) {
          stack0.Push(v);
          stack1.Push(v);
        }

        std::vector<int> output0;
        while (!stack0.IsEmpty()) {
          int v;
          assert(stack0.Pop(v));
          output0.push_back(v);
        }

        std::vector<int> output1;
        while (!stack1.IsEmpty()) {
          int v;
          assert(stack1.Pop(v));
          output1.push_back(v);
        }

        std::vector<int> reversedInput(input);
        std::reverse(reversedInput.begin(), reversedInput.end());

        assert(output0 == reversedInput);
        assert(output1 == reversedInput);
      }
    }

    void DualStack_RunTests() {
      dualstack::Create_IntAndStringDualStack();
      dualstack::IsEmpty_InBothStack0AndStack1();
      dualstack::IsEmpty_OnlyInStack0();
      dualstack::IsEmpty_OnlyInStack1();
      dualstack::PushAndPop_OnlyInStack0();
      dualstack::PushAndPop_OnlyInStack1();
      dualstack::PushAndPop_InBothStack0AndStack1();
    }
  }
}
