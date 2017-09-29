#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <bitset>

namespace zyf {
  namespace leetcode {

    #pragma region Using

    using std::string;
    using std::vector;
    using std::unordered_map;
    using std::bitset;

    #pragma endregion

    class Solution0191 {
    public:
      int hammingWeight(const uint32_t n) const;
    };

    class Solution0461 {
    public:
      int hammingDistance(const int x, const int y) const;
    };

    class Solution0500 {
    public:
      vector<string> findWords(const vector<string>& words) const;
    };

    class Solution0561 {
    public:
      int arrayPairSum(std::vector<int>& nums) const;
    };

    // Definition for a binary tree node.
    struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      inline TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    class Solution0617 {
    public:
      TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) const;
    };

  }
}