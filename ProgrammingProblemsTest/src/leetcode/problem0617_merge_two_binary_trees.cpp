#include "stdafx.h"
#include "leetcode.h"

#include <bitset>

namespace zyf {
namespace leetcode {

// @see https://leetcode.com/problems/merge-two-binary-trees/description/ ÌâÄ¿

TreeNode* Solution0617::mergeTrees(TreeNode* t1, TreeNode* t2) const {
  if (t1 == nullptr) {
    return t2;
  } else if (/* t1 != nullptr && */ t2 == nullptr) {
    return t1;
  } else { // t1 != nullptr && t2 != nullptr
    // Note: we merge the trees to `t1` (modify `t1` in-place)
    t1->val += t2->val;
    t1->left = mergeTrees(t1->left, t2->left);
    t1->right = mergeTrees(t1->right, t2->right);
    return t1;
  }
}

} // end namespace leetcode
}
