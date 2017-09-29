#include <iostream>

namespace {
  using std::cout;
  using std::endl;

  class Cla {
  public:
    class Cla(int x) :field(new int(x)) {
      cout << "Default Ctor of Cla" << endl;
    }

    class Cla(const Cla& other) {
      //Copy other的资源
      this->field = new int(*other.field);
      cout << "Copy Ctor of Cla" << endl;
    }

    class Cla(Cla&& other) {
      //偷取other的资源
      this->field = other.field;
      other.field = nullptr;
      cout << "Move Ctor of Cla" << endl;
    }

    Cla& operator=(Cla other) {
      //统一Move and Copy Assignment
      //如果调用=时，右边是右值，则局部变量other调用move ctor初始化
      //否则，other调用copy ctor初始化
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
}
