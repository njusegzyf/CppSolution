#include "stdafx.h"

namespace Zhangyftest {
    namespace LambdaTest {

        class TC {
            void fun() {
                // generic lambdas
                auto lambda1 = [](const auto x) { return x;};
                auto lambda2 = [](const auto& x) -> decltype(auto) { return x;};
                auto lambda3 = [](const auto&& x) { return x;};

                int x = lambda1(1);
                const int& xRef = lambda2(x);
                }
            };

        }
    }
