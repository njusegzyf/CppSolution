#include "stdafx.h"

namespace Coll = System::Collections;

namespace Zhangyftest{
    namespace TemplateTest{
        //Primary Template
        //注意模板形参特化为引用类型时，匹配很贪婪
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

        //显式模板实例化
        //http://docs.oracle.com/cd/E19205-01/821-2509/bkafk/index.html
        //不能既显式专用化又显式实例化函数，原因是函数的显示专用化其实是重载实现的
        //template void TemplateFunc(int, int);

        //Default Argument Template，C++11允许在类模板和函数模板上使用，IDE尚未支持
        //template <typename T = int>
        //void TemplateFunc1(T, T){
        //	cout << "Sep template." << endl;
        //}

        void Test1(){
            TemplateFunc(static_cast<Int32*>(nullptr), static_cast<Double*>(nullptr));
            }

        //智能指针
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

            //sort()里，用的是所谓的“ strict weak ordering”，也就是说，如果a==b，则返回的应该是false，如果返回的是true，则会出"Expression : invalid operator <"。
            std::sort(container_ptr->begin(), container_ptr->end(), [](const Int32& x, const Int32& y) -> Boolean { return y - x < 0; });
            for_each(container_ptr->cbegin(), container_ptr->cend(), [](const Int32& x){cout << x << endl;});

            std::function<Void (const Int32&, const Int32&)> funct([](const Int32& x, const Int32& y) -> Void { cout << x << ',' << y << endl; });
            funct((int)1.0, (int)2.0);

            //报错，原因不是很清楚，看http://www.cnblogs.com/tracylee/archive/2012/11/15.html
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
            //定义ptr_type为类型（Int32[3]的指针）的别名
            typedef Int32 (*ptr_type)[3];

            //Raw String，IDE尚未支持，编译器已支持
            //zzz可以是任意字符，结尾加上同样字符表示结束，中间所有字符作为原始文本处理
            //C#的@"..."，仅忽略转义符和换行符
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