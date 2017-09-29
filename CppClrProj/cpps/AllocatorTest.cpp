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
        cout << "δ��ʼ����Int��" << *p << endl;
        delete p;
        p = new int();
        cout << "Ĭ��ֵ��ʼ����Int��" << *p << endl;
        //C++ �����ṩһ�����������ض����ڴ�λ�ô�������placement new
        new(p) int(10);
        cout << "Placement New��ʼ����Int��" << *p << endl;
        delete p;
      }

      //Allocator�ֿ��˷����ڴ��Լ���ʼ��������һ���new����Ч��
      //������Դ�����Ĭ�Ϲ��캯�����͵�����ĳ�ʼ��
      {
        allocator<string> alloc;
        auto const p = alloc.allocate(10);//����ռ䣬
        for (auto q = p; q != p + 10; ++q) {//����
          alloc.construct(q, q - p, '1');
        }

        for (auto q = p; q != p + 10; ++q) {//ʹ��
          cout << *q << endl;
        }

        for (auto q = p; q != p + 10; ++q) {//�������������տռ䣬�������¹����¶���
          alloc.destroy(q);
        }

        alloc.deallocate(p, 10);//���տռ�
      }
    }

    AllocatorTest::AllocatorTest(void) {}
    AllocatorTest::~AllocatorTest(void) {}
  }
}
