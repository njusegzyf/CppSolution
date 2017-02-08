#include "stdafx.h"

namespace Zhangyftest {
    namespace LambdaTest {

        class TC {
            int f1 = 0;
            double f2 = 1.0;

            void fun() {
                // generic lambdas
                auto z = f1;
                auto lambda1 = [](const auto x) { return x;};
                auto lambda2 = [](const auto& x) { return x;};
                auto lambda3 = [](const auto&& x) { return x;};
                }
            };

        }
    }
