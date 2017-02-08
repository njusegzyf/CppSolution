#include "stdafx.h"

#include <iostream>
#include <random>
#include <vector>
#include <chrono>

#include "../headers/PerformanceTest.h"

using namespace std;
using std::chrono::high_resolution_clock;

namespace PerformanceTest{
    vector<int> generateTargets(int seed, int inclMin, int exclMax, int length){

        typedef int (*FP) (int);

        int i = 0;

        FP p = (int (*)(int))i;

        //std::random_device rd;

        auto k = [](int z) { return z + 1 ; };
        function<int(int)> z = k;

        std::mt19937 mt(seed);
        std::uniform_int_distribution<> dis(inclMin, exclMax - 1);
        vector<int> x(length);

        for (int i = 0; i < length; ++i){
            x.push_back(dis(mt));
            }

        return std::move(x);

        }

    long long testCase2Single(int inclMin, int exclMax, vector<int>& target){

        vector<int> container = vector<int>(exclMax - inclMin);

        for (int i = inclMin; i < exclMax; ++i){
            container.push_back(i);
            }

        auto startTime = high_resolution_clock::now();

        for (const int& i : target){

            std::binary_search(container.cbegin(), container.cend(), i);
            }

        auto endTime = high_resolution_clock::now();

        auto totalTime = endTime - startTime;

        return std::chrono::duration_cast<std::chrono::microseconds>
            (totalTime).count();
        }

    long long testCase1Single(int inclMin, int exclMax, vector<int>& target){

        vector<int> container = vector<int>(exclMax - inclMin);

        for (int i = inclMin; i < exclMax; ++i){
            container.push_back(i);
            }

        auto startTime = high_resolution_clock::now();

        for (const int& i : target){

            std::find(container.cbegin(), container.cend(), i);
            }

        auto endTime = high_resolution_clock::now();

        auto totalTime = endTime.time_since_epoch() - startTime.time_since_epoch();

        return std::chrono::duration_cast<std::chrono::microseconds>
            (totalTime).count();
        }

    }

