#pragma once

#include <vector>

namespace PerformanceTest{

    std::vector<int> generateTargets(int seed, int inclMin, int exclMax, int length);

    long long testCase1Single(int inclMin, int exclMax, std::vector<int>& target);

    long long testCase2Single(int inclMin, int exclMax, std::vector<int>& target);
    }