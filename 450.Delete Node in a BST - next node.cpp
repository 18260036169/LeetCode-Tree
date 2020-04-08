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

        // 优化基准情形
        if ( root == nullptr || root->val == key && root->left == nullptr && root->right == nullptr )
            return nullptr;

        else {
            // 定位到目标进行删除操作...
            if ( key == root->val ) {
                // case1 : 叶子结点的删除操作
                if ( root->left == nullptr && root->right == nullptr )
                    delete root;

                // case2 : 只有左子树/只有右子树的结点
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
                // 以上都同前驱结点部分
                // case3 : 左子树右子树都存在的结点
                else {
                    // 找到当前结点root的右结点的最左边的结点
                    // p指向当前结点，q指向当前结点的右结点
                    p = root;
                    q = root->right;

                    // 假设q有左结点就不断往左推进，p随之跟进，而假设q没有左子树，p和q都滞留在原地
                    while ( q->left ) {
                        p = q;
                        q = q->left;
                    }

                    // 狸猫换太子，不难理解，我们即将要删除的并不是root，而是q
                    root->val = q->val;

                    // 情况i：直接后继为当前的结点的右结点的最左边的结点
                    // 直接后继结点是一定不会存在左子树这一说了，因为已经推到了最左边，所以右子树是他留给p的遗产(当然如果q是个叶子结点的就是一个穷光蛋，什么都不剩)，接到p的左子树上
                    if ( p != root )
                        p->left = q->right;
                    // 情况ii：当前结点的右结点就是当前结点的后继结点，将遗产接到p的右子树上
                    else
                        p->right = q->right;

                    delete q;
                }
            }

            // 若key小于当前定位到的root->val，则说明root->val应该继续往左走才有机会定位到key
            else if ( key < root->val )
                root->left = deleteNode(root->left, key);
            // 若key大于当前定位到的root->val，则说明root->val应该往右走才有机会定位到当前key
            else
                root->right = deleteNode(root->right, key);

            return root;
        }
    }
};
