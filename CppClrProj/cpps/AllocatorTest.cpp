#include "stdafx.h"
#include "../headers/AllocatorTest.h"

namespace Zhangyftest {
  namespace AllocatorTest {

    int fx(int) { return 1; }
    int fx(int, int) { return 2; }
    int fx(double) { return 3; }

    void TestNew(void) {
      {
        // No overload
        //std::function<int (int)> xfunc = fx;

        std::function<int(int)> xfunc = [&](int x) -> int { return fx(x); };

        int(*p) = new int;
        cout << "未初始化的Int：" << *p << endl;
        delete p;
        p = new int();
        cout << "默认值初始化的Int：" << *p << endl;
        //C++ 语言提供一个机制以在特定的内存位置创建对象：placement new
        new(p) int(10);
        cout << "Placement New初始化的Int：" << *p << endl;
        delete p;
      }

      //Allocator分开了分配内存以及初始化工作，一般比new更高效。
      //另外可以处理无默认构造函数类型的数组的初始化
      {
        allocator<string> alloc;
        auto const p = alloc.allocate(10);//分配空间，
        for (auto q = p; q != p + 10; ++q) {//构造
          alloc.construct(q, q - p, '1');
        }

        for (auto q = p; q != p + 10; ++q) {//使用
          cout << *q << endl;
        }

        for (auto q = p; q != p + 10; ++q) {//析构，但不回收空间，可以重新构造新对象
          alloc.destroy(q);
        }

        alloc.deallocate(p, 10);//回收空间
      }
    }

    AllocatorTest::AllocatorTest(void) {}
    AllocatorTest::~AllocatorTest(void) {}
  }
}
