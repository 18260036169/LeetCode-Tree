/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode *> node_stack;
        TreeNode *cur = root;

        while ( !node_stack.empty() || cur ) {
            while ( cur ) {
                res.push_back(cur->val);
                node_stack.push(cur);
                cur = cur->left;
            }

            TreeNode *temp = node_stack.top();
            node_stack.pop();
            cur = temp->right;
        }

        return res;
    }
};
