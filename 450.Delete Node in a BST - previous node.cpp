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
    TreeNode* deleteNode(TreeNode* root, int key) {
        TreeNode* p;
        TreeNode* q;

        if ( root == nullptr || root->val == key && root->left == nullptr && root->right == nullptr )
            return nullptr;

        else {
            if ( key == root->val ) {
                if ( root->left == nullptr && root->right == nullptr )
                    delete root;

                if ( root->right == nullptr ) {
                    p = root;
                    root = root->left;
                    delete p;
                }
                
                else if ( root->left == nullptr ) {
                    p = root;
                    root = root->right;
                    delete p;
                }
                
                else {
                    p = root;
                    q = root->left;

                    while ( q->right ) {
                        p = q;
                        q = q->right;
                    }
                    
                    root->val = q->val;
                    
                    if ( p != root )
                        p->right = q->left;
                    else
                        p->left = q->left;

                    delete q;
                }
            }

            else if ( key < root->val )
                root->left = deleteNode(root->left, key);
            else
                root->right = deleteNode(root->right, key);

            return root;
        }
    }
};
