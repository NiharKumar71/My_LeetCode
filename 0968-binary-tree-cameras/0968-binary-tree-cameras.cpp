/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int minCameraCover(TreeNode* root) {
        int cameras = 0;

        function<int(TreeNode*)> dfs = [&](TreeNode* node) -> int {
            if (node == nullptr) return 1;

            int left = dfs(node->left);
            int right = dfs(node->right);

            if (left == -1 || right == -1) {
                cameras++;
                return 0;
            }

            if (left == 0 || right == 0) {
                return 1;
            }

            return -1;
        };

        if (dfs(root) == -1) cameras++;
        return cameras;
    }
};