#include "stdafx.h"
#include "../headers/NameSpaceTest.h"

namespace Out{

    //������ȫ��namspace���߰�����enclosing�����namespace���庯��
    Inner::NameSpaceTest::NameSpaceTest(void) {}


    /// <summary>
    /// Finalizes an instance of the <see cref="NameSpaceTest"/> class.
    /// </summary>
    Inner::NameSpaceTest::~NameSpaceTest(void) {}

    //�������ڲ�namespace���庯��
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

    //namespace InnnerOther{//�������޹ص�Namespace���庯��
    //	Out::Inner::NameSpaceTest::NameSpaceTest(void)
    //	{
    //	}


    //	Out::Inner::NameSpaceTest::~NameSpaceTest(void)
    //	{
    //	}
    //}
    }

//Ҳ�������������ռ��ڶ���
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

    //OuterFunction(var); //Error��ADL������ѰOuterSpace

    InnerMostFunction(var);
    }


