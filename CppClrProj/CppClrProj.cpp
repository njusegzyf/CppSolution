// CPPCLRProj1.cpp: 主项目文件。

#include "stdafx.h"

using namespace System;

#include "headers/ClassTest.h"
#include "headers/PerformanceTest.h"

namespace Test = Zhangyftest;

// 异步操作

typedef void NICDeviceInterface;

// 定义回调函数，两个参数，一个是启动异步操作时传入的额外参数，二是异步操作结果 
typedef void(*AsyncOperationCallback)(void *callbackParam, void *asyncOperationResult);

// 启动异步操作，返回的 bool 值仅表示异步操作是否被启动
bool AsyncOperation(void *inputParam,    // 启动异步操作的参数
  void *callbackParam, // 传递给回调的参数
  AsyncOperationCallback callback
  );

typedef void* PollingTask;

typedef int ExecutionEnvironment;

typedef void(*PollingTaskCallback)();

PollingTask RequestPoolingTask(PollingTaskCallback callback,                            // 每次轮询实际执行的回调函数
  ExecutionEnvironment executionEnvironment,               // 请求的回调执行环境，回调执行不会overlap
  bool isScheduledRepeatByInterval, int pollingInterval,   // 指定是否根据时间间隔自动调度
  bool isScheduledRepeatBySystem,                          // 是否由系统提供的机制重复调度（通常尽最大可能调度）
  bool isStarted                                           // 是否立即启动
  );

void CancelPoolingTask(PollingTask task);

bool StratPollingTask(PollingTask task);

bool StopPollingTask(PollingTask task);

// 手动调度一次任务的执行，由系统负责调度，尽最大努力执行
bool SchedulePollingTask(PollingTask task);

// 手动调度一次任务的执行，在指定延迟之后执行
bool SchedulePollingTask(PollingTask task,
  int delay);

typedef void NICDataPacket;

bool NICDevicePollingDataPacket(NICDeviceInterface *pDevice,
  bool isTakeDataPacketOwnership,
  NICDataPacket *pDataPacket
  );

void NICDeviceRXClean(NICDeviceInterface *pDevice);

void NICDeviceTXClean(NICDeviceInterface *pDevice);

struct STA {
  Byte b;
  Byte a;
  };

struct STB {
  unsigned long long b;
  };

struct STC {
  Boolean b;
  Boolean a;
  };

class Base1 {

public:
  Base1(int i1 = 0, int j1 = 0) : i(i1), j(j1) {
    }

  int(*fp)();

  //f和g是函数

  auto f() -> int { return 1; }

  auto g(int x)->int { return x; }

  auto k(int x) -> int {
    if (x >= 0) {
      return x;
      }
    else {
      return x + 1;
      }

    }

  int GetSum() {
    auto && x = 10;
    decltype(x) y = std::move(x);

    return i + j;
    }

protected:
  int i;
  int j;
  };

class Derived1 : private Base1 {

public:
  Derived1() : Base1(0, 0) {

    }

  Derived1(int i2, int j2) : Base1(i2, j2) {

    }

  Base1* GetBasePtr() {
    return this;
    //return static_cast<Base1*>(this);

    }
  };

class AC {
public:
  AC(const int x) {}

  //virtual ~AC() = 0;
private:
  AC(const AC&);
  };

int RecTail(int i) {
  if (i > 0) {
    cout << i << endl;
    return RecTail(i - 1);
    }
  else {
    return 0;
    }
  }

//Base虽然没有数据成员，但C++规范要求:
//
//If a complete object, a data member (9.2), or an array element is of class type, its type is considered the
//most derived class, to distinguish it from the class type of any base class subobject; an object of a most
//derived class type or of a non-class type is called amost derived object.
//
//Unless it is a bit-field (9.6), a most derived object shall have a non-zero size and shall occupy one or more
//bytes of storage. Base class subobjects may have zero size. An object of trivially copyable or standard-layout
//type (3.9) shall occupy contiguous bytes of storage.
//
//Unless an object is a bit-field or a base class subobject of zero size, the address of that object is the address of
//the first byte it occupies. Two objects that are not bit-fields may have the same address if one is a subobject
//of the other, or if at least one is a base class subobject of zero size and they are of different types; otherwise,
//they shall have distinct addresses.
//
//[Example:
//static const char test1 = ’x’;
//static const char test2 = ’x’;
//const bool b = &test1 != &test2; // always true
//—end example]
//
//因此实际中，如下代码显示b1和b2有不同的内存位置，但是作为基类时可能不占空间
//Base b1;
//Base b2;
//cout << (int)(&b1) << " " << (int)(&b2) << endl;

class Base {
public:
  Base() {}

  int GetID() {
    return Base::_GlobalID++;
    }

private:
  static int _GlobalID;
  };

int Base::_GlobalID = 0;

struct StructA {
  bool x;
  bool yy;
  short z;
  int y;

  };

class ClassA {
  bool x;
  int y;
  short z;
  };

int main(cli::array<System::String ^> ^args)
  {

  //RecTail(0);

  //AC varA = 10;
  ////AC varA = AC(10);

  //int varB(10);

  //int varC[] = {1, 2 ,3};

  //vector<bool> vs;
  //vs.push_back(true);
  //vs.push_back(false);
  //vs.push_back(true);
  //vs.push_back(false);

  //for (auto (& v) : vs){
  //	v = !v;
  //}

  //for (auto (& v) : vs){
  //	cout << v << endl;
  //}
  //
  //Base1 b(1,2);
  //b.f();
  //(*b.fp)();

  //int* p = new int;
  //*p = 12;

  //decltype(p) & refP(p);

  //cout << *p << endl;
  //int *q = new(p) int(20);
  //int equal = (p == q) ? 1 : 0;
  //cout << *p << ", " <<  equal << endl;

  //auto a = new int[10][10];

  ////Test::ClassTest::Test();

  //vector<std::string> v;

  //v.push_back("sss");

  //cout << sizeof(STA) << endl;
  //cout << sizeof(STB) << endl;
  //cout << sizeof(STC) << endl;

  //Derived1* d1 = new Derived1(12, 12);
  ////Base1* b1 = d1; //无法转换，因为有无法访问的成员
  //Base1* b1 = d1->GetBasePtr();
  //cout << b1->GetSum() << endl;
  //delete d1;

  //cout << bool(true) << endl;

  //cout << boolalpha;
  ////cout.operator<<(boolalpha);

  //cout << bool(true) << ", " << bool(false) <<  endl;
  //cout << bool(true) << endl;

  //Base b1;
  //Base b2;

  //cout << (int)(&b1) << " " << (int)(&b2) << endl;

  //Zhangyftest::ClassTest::TestRef();

  //typedef decltype (2147483648) T1; //long long
  //typedef decltype (-2147483648) T2; //long long
  //typedef decltype (-0x80000000) T3;//unsigned int
  //typedef decltype (2147483647) T9; //int(same as long)
  //int x1 = -0x80000000; // -> unsigned int -> 一元负操作 -> signed int ,Error, 但是-0x80000000取反后仍为-0x80000000
  //cout << x1 << endl;
  //x1 = -0x80000001; // -> unsigned int -> 一元负操作 -> signed int ,Error
  //cout << x1 << endl;
  //x1 = -2147483648LL; 
  //cout << x1 << endl ;
  //auto x2 = -0x80000000; //unsigned int
  //auto x3 = -2147483648; //long long int
  //cout << x3 << endl;

  ////false, 做无符号数比较
  //cout << boolalpha << (-2147483648 < 2147483647)  << endl;

  //signed char y1 = -1;
  //unsigned short y2 = 0xffff;
  //cout << (y1 == y2) << endl;
  //cout << (y1 == 0xffffffffU) << endl;

  //int&& x = 5;
  //int&& x2 = static_cast<int&&>(x); //OK
  //cout << (x == x2) << endl;

  //int startSize = 256;
  //int count = 16;
  //int testTargetCount = 1024;
  //int seed = 100;

  //vector<int> v;

  //int size = startSize;

  //for (int i = 0; i < count; ++i){

  //    v.push_back(size);
  //    size *= 2;
  //    }


  //for (const int& testSize : v){

  //    vector<int> targets = PerformanceTest::generateTargets(seed, 0, testSize, testTargetCount);

  //    auto result1 = PerformanceTest::testCase1Single(0, testSize, targets);

  //    auto result2 = PerformanceTest::testCase2Single(0, testSize, targets);

  //    cout << result1 << ", " << result2 << endl;

  //    }

  // 12, 12, Struct内成员强制对齐到4 Byte 自然边界
  cout << sizeof(StructA) << ", " << sizeof(ClassA) << endl;

  bool* px = new bool();

  short int* py = new short int();

  bool* pz = new bool();

  long long int* pll = new long long int();

  bool x;

  bool y;

  char localCharArray[] = { '1', '2' };
  auto pConstChars = "Hello world";

  //// 非连续，但是 4 Byte 对齐
  //cout << px << ", " << py << ", " << pz << ", " << pll << endl;

  //// 4 Byte 对齐
  //cout << &x << ", " << &y << endl;

  cout << (int)localCharArray << ", " << (int)pConstChars << endl;

  Console::ReadLine();

  return 0;
  }

template <typename T, typename U>
auto Add(T var1, U var2) -> decltype (var1 + var2) {
  return var1 + var2;
  };
