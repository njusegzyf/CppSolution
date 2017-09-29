#include "min_heap_test.h"

#include <cassert>

#include <string>
#include <algorithm>
#include <vector>

#include "../../data_structure/min_heap.h"

namespace zyf {
  namespace test {

    namespace minheap {
      void Create_Test() {
        MinHeap<double, int> doubleMinHeap([](const double& x) { return int(x); });
        MinHeap<std::string, int> stringMinHeap([](const std::string& x) { return x.length(); });
      }

      void Insert_NoDupliates() {
        MinHeap<double, int> doubleMinHeap([](const double& x) { return int(x); });

        std::vector<double> inputs = { 1.0, 2.0, 0.0 };
        for (auto input : inputs) {
          assert(doubleMinHeap.Insert(input));
        }

        std::vector<double> results;
        while (!doubleMinHeap.IsEmpty()) {
          double v;
          assert(doubleMinHeap.RemoveMin(v));
          results.push_back(v);
        }

        std::vector<double> sortedInputs(inputs);
        std::sort(sortedInputs.begin(), sortedInputs.end());
        assert(results == sortedInputs);
      }
    }

    void MinHeap_RunTests() {
      minheap::Create_Test();
      minheap::Insert_NoDupliates();
    }
  }
}
