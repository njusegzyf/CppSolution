#include "stdafx.h"

namespace Coll = System::Collections;

namespace Zhangyftest{
    namespace TemplateTest{
        //Primary Template
        //ע��ģ���β��ػ�Ϊ��������ʱ��ƥ���̰��
        template <typename T, typename U>
        void TemplateFunc(T, U){
            cout << "Main template." << endl;
            }

        //Explicit and Partial Template Specialization
        template <typename T>
        void TemplateFunc(T, T){
            cout << "Sep template." << endl;
            }

        template <typename T, typename U>
        void TemplateFunc(T*, U*){
            cout << "Sep template." << endl;
            }

        template <typename T1, typename T2, typename T3, typename T4>
        void TemplateFunc(pair<T1, T2>, pair<T3, T4>){
            cout << "Pair template." << endl;
            }

        template <> void TemplateFunc(int x, int y){
            cout << "int*int template." << endl;
            }

        //��ʽģ��ʵ����
        //http://docs.oracle.com/cd/E19205-01/821-2509/bkafk/index.html
        //���ܼ���ʽר�û�����ʽʵ����������ԭ���Ǻ�������ʾר�û���ʵ������ʵ�ֵ�
        //template void TemplateFunc(int, int);

        //Default Argument Template��C++11��������ģ��ͺ���ģ����ʹ�ã�IDE��δ֧��
        //template <typename T = int>
        //void TemplateFunc1(T, T){
        //	cout << "Sep template." << endl;
        //}

        void Test1(){
            TemplateFunc(static_cast<Int32*>(nullptr), static_cast<Double*>(nullptr));
            }

        //����ָ��
        void Test2(){
            Int32 arr[] =  {1, 10, 4, 5, 5, 67};

            //shared_ptr, #include <memory>
            auto container_ptr  = std::make_shared<vector<Int32>>(); 

            typedef decltype(container_ptr->cbegin()) Itor;
            Itor it1 = container_ptr->cend();

            for each (Int32 var in arr)
                {
                container_ptr->push_back(var);
                }

            //sort()��õ�����ν�ġ� strict weak ordering����Ҳ����˵�����a==b���򷵻ص�Ӧ����false��������ص���true������"Expression : invalid operator <"��
            std::sort(container_ptr->begin(), container_ptr->end(), [](const Int32& x, const Int32& y) -> Boolean { return y - x < 0; });
            for_each(container_ptr->cbegin(), container_ptr->cend(), [](const Int32& x){cout << x << endl;});

            std::function<Void (const Int32&, const Int32&)> funct([](const Int32& x, const Int32& y) -> Void { cout << x << ',' << y << endl; });
            funct((int)1.0, (int)2.0);

            //����ԭ���Ǻ��������http://www.cnblogs.com/tracylee/archive/2012/11/15.html
            //std::function<Void (const Int32&)> funct2 = bind1st(funct, 10);

            std::function<Void (const Int32&)> funct2([&](const Int32 x){ funct(x, 10);});

            //auto list = gcnew Coll::ArrayList(64);
            //list->Add
            }

        void Test3(){

            Int32* p = new Int32[5];
            delete[] p;
            p = nullptr;
            Int32 value[] = {1, 2, 3};
            Int32 value2[3] = {1, 2, 3};
            //����ptr_typeΪ���ͣ�Int32[3]��ָ�룩�ı���
            typedef Int32 (*ptr_type)[3];

            //Raw String��IDE��δ֧�֣���������֧��
            //zzz�����������ַ�����β����ͬ���ַ���ʾ�������м������ַ���Ϊԭʼ�ı�����
            //C#��@"..."��������ת����ͻ��з�
            //std::string s = 
            //	R"xyz
            //		this is a raw string. \n  \\ ....
            //		"";
            //	xyz";
            bool x;
            bool y;
            if (x = true, y = false, x && y){
                x = false;
                }
            }
        }
    }