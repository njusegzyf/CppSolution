#include "stdafx.h"
#include "../headers/NameSpaceTest.h"

namespace Out{

    //可以在全局namspace或者包含（enclosing）其的namespace定义函数
    Inner::NameSpaceTest::NameSpaceTest(void) {}


    /// <summary>
    /// Finalizes an instance of the <see cref="NameSpaceTest"/> class.
    /// </summary>
    Inner::NameSpaceTest::~NameSpaceTest(void) {}

    //不能在内部namespace定义函数
    //namespace Inner{
    //	namespace InnerInner{
    //		Out::Inner::NameSpaceTest::NameSpaceTest(void)
    //		{
    //		}


    //		Out::Inner::NameSpaceTest::~NameSpaceTest(void)
    //		{
    //		}
    //	}
    //}

    //namespace InnnerOther{//不能在无关的Namespace定义函数
    //	Out::Inner::NameSpaceTest::NameSpaceTest(void)
    //	{
    //	}


    //	Out::Inner::NameSpaceTest::~NameSpaceTest(void)
    //	{
    //	}
    //}
    }

//也不能在匿名名空间内定义
//namespace {
//	Out::Inner::NameSpaceTest::NameSpaceTest(void)
//	{
//	}
//
//
//	Out::Inner::NameSpaceTest::~NameSpaceTest(void)
//	{
//	}
//}

namespace OuterSpace{

    namespace InnerSpace{
        struct Cla{};

        void InnerFunction(const Cla&){}

        namespace InnerMostSpace{
            using OuterSpace::InnerSpace::Cla;

            void InnerMostFunction(const Cla&){}
            }

        using OuterSpace::InnerSpace::InnerMostSpace::InnerMostFunction;
        }

    using InnerSpace::Cla;

    void OuterFunction(const Cla&){}
    }

void f(){
    //OuterSpace::InnerSpace::Cla var;
    OuterSpace::Cla var;

    InnerFunction(var);

    //OuterFunction(var); //Error，ADL不会搜寻OuterSpace

    InnerMostFunction(var);
    }


