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

                // 重接左子树
                if ( root->right == nullptr ) {
                    p = root;
                    root = root->left;
                    delete p;
                }
                // 重接右子树
                else if ( root->left == nullptr ) {
                    p = root;
                    root = root->right;
                    delete p;
                }
                // 左右子树均不为空，利用直接前驱进行删除
                else {
                    p = root;
                    q = root->right;

                    while ( q->left ) {
                        p = q;
                        q = q->left;
                    }

                    // 原本待删除的结点的位置上的val替换为直接后继的val
                    // 真正要被删除的反而就是这个后继结点，这个后继结点做了替死鬼
                    root->val = q->val;

                    // p记录了后继结点的前一个结点，q此时已经为最左边的那个结点，不存在还有左子树这一说，将其右子树接在p的左子树上
                    if ( p != root )
                        p->left = q->right;
                    // p如果等于root说明这个最初初始化的p = root以及q = root->right的状态保持住了，即q没有左子树，此时就只要将q的右子树接上来就可以了
                    else
                        p->right = q->right;

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