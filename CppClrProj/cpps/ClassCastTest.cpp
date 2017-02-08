#include "stdafx.h"

namespace Zhangyftest {
    namespace ClassTest {
        namespace ClassCastTest {
            class ClassA {};

            class ClassB {
            public:
                operator ClassA() const {
                    return ClassA();
                    }
                };

            class ClassC {};

            void Test() {
                ClassB objB = ClassB();
                ClassC objC = ClassC();

                ClassA objA1 = (ClassA)objB;
                ClassA objA2 = static_cast<ClassA>(objB);
                // ClassA objA3 = dynamic_cast<ClassA>(objB); //Error

                //ClassA objA4 = (ClassA)objC; // Error
                //ClassA objA5 = static_cast<ClassA>(objC); //Error
                //ClassA objA6 = reinterpret_cast<ClassA>(objC); //Error
                }

            class C1X {
                int x = 0;

                using T = int&;
                const T y = x;

                using TC = const int&;
                TC z = x;

                void f(int& px) const {
                    // x = 10; // Error
                    y = 10; // OK
                    px = 10;
                    // z = 10; // Error, 'z' cannot be modified because it is being accessed through a const object
                    }
                };
            }
        }
    }
