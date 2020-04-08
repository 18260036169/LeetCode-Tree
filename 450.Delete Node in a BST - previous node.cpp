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
                    // 左右子树均不为空，利用直接前驱/后继进行删除，此方法采用直接前驱
                else {
                    p = root;
                    q = root->left;

                    while ( q->right ) {
                        p = q;
                        q = q->right;
                    }

                    // 原本待删除的结点的位置上的val替换为直接前驱的val
                    // 真正要被删除的反而就是这个前驱结点，这个前驱结点做了替死鬼
                    root->val = q->val;

                    // p记录了前驱结点的前一个结点，q此时已经为最右边的那个结点，不存在还有右子树这一说，将其左子树接在p的右子树上
                    if ( p != root )
                        p->right = q->left;
                        // p如果等于root说明这个最初初始化的p = root以及q = root->left的状态保持住了，即q没有右子树，此时就只要将q的左子树接上来就可以了
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