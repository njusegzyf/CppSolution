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
}
