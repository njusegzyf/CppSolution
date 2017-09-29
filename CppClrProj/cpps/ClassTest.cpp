#include "stdafx.h"

namespace Zhangyftest {
  namespace ClassTest {

    template <typename A>
    void f(A& a) {
      cout << a << endl;
    }

    template<typename A>
    void G(A &a)
    {
      F(a);
    }

    void test1() {
      //G(10);//Error, 10ΪRValue���޷��󶨵�L Ref
    }

    template<typename U>
    void forwardFunc(U&& value) {
    }

    void testForward() {
      forwardFunc(10); //forwardFunc<int>(int&&)
      forwardFunc<int&&>(10); //forwardFunc<int&&>(int&&)
      forwardFunc<const int&&>(10);

      typedef decltype(forwardFunc(0)) TReturn;

      int i1(0);
      forwardFunc(i1); //forwardFunc<int &>(int&)

      const int& i2 = 10;
      forwardFunc(i2);   //forwardFunc<const int &>(const int&)
      typedef decltype(i2) T1;

      const int&& i3 = 10;
      forwardFunc(i3);   //forwardFunc<const int &>(const int&)
      //forwardFunc<const int&&>(i3); //Error, ��Ȼi3����������const int&&, ��i3������ʽ����Ϊ��ֵ��const Lvalue����������const int&&���ܰ󶨵���ֵ��֮��Ҳ�޷���������const intת��Ϊ��������const int&&
      typedef decltype(i3) T2;     //const int&& T2
      typedef decltype(i3 + 1) T3; //int T3
      typedef decltype(std::move(i3)) T4;

      //int array[10][20];
      //typedef decltype (array[0]) T5;
    }

    template <typename T>
    struct F1Struct {
    private:
    public:
      typedef decltype (std::make_pair(T(), T())) ReturnType;
      static int staticValue;
    };

    template <typename T1, typename T2>
    void tempalteFunc(F1Struct<T1>&& val1, T2&& val2) {
    };

    //template <typename T>
    //(typename F1Struct<T>::ReturnType) f1(T x){
    //    return std::make_pair(x, x);
    //}
    template <typename T>
    std::pair<T, T> f1(T x) {
      return std::make_pair(x, x);
    }

    void test2() {
      int var = 10;
      typedef pair<int, int>(*myfunc)(int);
      myfunc a = f1<int>;

      std::unique_ptr<std::pair<int, int>> aPairPtr(new std::pair<int, int>(10, 10));
      //auto b = std::unique_ptr<std::pair<int, int>>(aPairPtr);//Error, no copy ctor for unique ptr
      auto b = std::unique_ptr<std::pair<int, int>>(std::move(aPairPtr)); //Move ctor

      //std::shared_ptr<std::pair<int, int>> aPairPtrShared = std::make_shared<std::pair<int, int>>(10, 10);
      auto aPairPtrShared = std::make_shared<decltype (std::make_pair(10, 10))>(10, 10);

      tempalteFunc(F1Struct<int>(), 10);


    }

    class Cla {
    public:
      class Cla(int x) :field(new int(x)) {
        cout << "Default Ctor of Cla" << endl;
      }

      class Cla(const Cla& other) {
        //Copy other����Դ
        this->field = new int(*other.field);
        cout << "Copy Ctor of Cla" << endl;
      }

      class Cla(Cla&& other) {
        //͵ȡother����Դ
        this->field = other.field;
        other.field = nullptr;
        cout << "Move Ctor of Cla" << endl;
      }

      Cla& operator=(Cla other) {
        //ͳһMove and Copy Assignment
        //�������=ʱ���ұ�����ֵ����ֲ�����other����move ctor��ʼ��
        //����other����copy ctor��ʼ��
        this->Swap(other);
        return *this;
      }

      //protected
      virtual ~Cla() {
        if (this->field != nullptr) {
          delete this->field;
        }
      }

      //private:

      int* field;

      void Swap(Cla& other) {
        std::swap(this->field, other.field);
      }

      void f() const {}
      void f() {}
    };

    void TestType() {
      {
        int&& x = 5;
        //int&& x1 = x; //Error
        int&& x2 = static_cast<int&&>(x); //OK
        //const int& y = x;
      }

      {
        int x = 0;
        int * p = &x;
        int & lref = x;
        int && rref = std::move(x);
        typedef decltype(x) T1;  // T1 = int
        typedef decltype(&x) T2; // T2 = int*
        typedef decltype(*p) T3; // T3 = int&
        typedef decltype(&p) T4; // T3 = int**
        typedef decltype(x + 2) T5; //T5 = int
        typedef decltype(rref + 2) T6; //T6 = int
      }
    }

    class Base
    {
    public:
      Base() {}

      virtual int func() {
        cout << "In Base Func!" << endl;
        return 1;
      }

      virtual int func1() {
        cout << "In Base Func1!" << endl;
        return 1;
      }

      virtual Base operator+(Base & other) {
        cout << "In Base Operator  +!" << endl;
        return *this;
      }

    private:

    protected:

      Base(const Base&) {}
      Base& operator=(const Base&) {}

    };

    class Derived :public Base
    {
    public:
      Derived() {}

      Derived(const Derived& x) :Base(x) {}

      int func1() override {
        cout << "In Derived Func1!" << endl;
        return 2;
      }

      void ovd() {
      }

    private:
      Derived& operator=(const Derived&);

      //virtual���п���
      virtual int func() override {
        cout << "In Derived Func!" << endl;
        return 2;
      }
    };

    class MoreDerived :public Derived
    {
    public:
      MoreDerived() {}

      MoreDerived(const MoreDerived& x) :Derived(x) {}

      int func1() override final {
        cout << "In More Derived Func1!" << endl;
        return 3;
      }

      //void ovd(){}

    private:
      MoreDerived& operator=(const MoreDerived&);

      using Derived::ovd;

      int func() override final {
        cout << "In More Derived Func!" << endl;
        return 3;
      }
    };

    void Test() {

      unique_ptr<Base> base_ptr(new MoreDerived());
      //base_ptr->func();
      //base_ptr->func1();

      MoreDerived *ptr = static_cast<MoreDerived *>(base_ptr.release());

      cout << "Call ((Derived *)ptr)->func1()" << endl;
      ((Derived *)ptr)->func1();			//��̬��
      cout << endl;

      cout << "Call ((Derived *)ptr)->Derived::func1()" << endl;
      ((Derived *)ptr)->Derived::func1();	//��̬��
      cout << endl;

      delete ptr;

      MoreDerived *pmd = new MoreDerived();
      //pmd->ovd(); //Error
      //pmd->Derived::ovd();
      Derived *pd = pmd; //static_cast<Derived *>(pmd);
      //pd->ovd();

    }

    Cla GetObj(int x) {
      return Cla(x);
    }

    Cla&& Pass(Cla&& obj) {
      return std::move(obj);
    }

    /// <summary>
    /// Tests the ref.
    /// </summary>
    void TestRef() {

      const int& constInt = 10;
      //auto* addr1 = &10; //Error
      auto* addr1 = &constInt;

      auto x = 1;
      auto* addr2 = &x;
      //auto y = 2.0;
      //auto a = std::make_pair(1,2.0);
      //auto a1 = std::make_pair<int, double>(1,2.0);
      //auto b = std::make_pair(x, y);
      //auto b1 = std::make_pair<int, double>(x, y); //Error, ��Ϊtempalte��T&&�������Զ�����ʱ��ģ������ֵ����������ֵ������ֵ���ã��Դ���ʵ������ת����


      //auto* addr3 = &(std::move(10)); //
      int&& rv1 = 10;
      //int&& rv1 = std::move(int(constInt));//Error, int()û���½�һ��int��ʱ����������rv1���õĶ�����constInt
      auto* addr3 = &rv1;
      int lv1 = 10;

      //10,x,rv1,lv1��ַ���ڣ�˵��10��һ����ֵ������ֱ�Ӱ󶨵�int&&��
      cout << "Add of constInt = " << addr1 << endl;
      cout << "Add of x = " << addr2 << endl;
      cout << "Add of rv1 = " << addr3 << endl;
      cout << "Add of lv1 = " << &lv1 << endl;

      cout << "Add of addr1 = " << &addr1 << endl;
      cout << "Add of addr2 = " << &addr2 << endl;
      cout << "Add of addr3 = " << &addr3 << endl;

      cout << "rv1 = " << rv1 << endl;
      rv1 = 12;
      cout << "After, rv1 = " << rv1 << endl;
      cout << "After, constInt = " << constInt << endl;

      auto&& uref = x;

      const Cla objA(10);
      cout << "Addr of objA = " << &objA << endl;

      //Cla&& objB = objA; //Error
      Cla&& objB = Cla(objA); //Cla&& objB = Cla(10);
      cout << "Addr of objB = " << &objB << endl;

      Cla&&  objG = Pass(GetObj(30)); //GetObj������ʱ������Ϊ��������PassȻ����Ϊ&&���أ��ٰ󶨵�Cla&&�ϣ����ܻ�ʹ��ʱ��������������ڷֺŴ�����
      Cla&&  objC = GetObj(40);//����ʱ����󶨵������ϣ��ӳ�����������
      Cla&   objF = GetObj(50);

      Cla objD(1), objE(1);

      cout << *objC.field << endl;
      cout << *objF.field << endl;
      cout << *objG.field << endl;

      cout << &objG << " " << &objC << " " << &objF << endl;

    }
  }

  class A
  {
  public:

    mutable int x;

    int func() const {
      return 0;
    }

    static int Do()
    {
      return 0;
    }

  };

  class EA : public A
  {
  public:

    // ���ظ����еľ�̬������Not allowed in Java
    static double Do()
    {
      return 1.0;
    }
  };

  void Test() {
    A *pA = new EA();

    pA->Do();
    A::Do();
  }
}