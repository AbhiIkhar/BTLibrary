#ifndef BTlibrary
#define BTlibrary

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> level;

class TreeNode
{
public:
    int data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int val)
    {
        data = val;
        left = NULL;
        right = NULL;
    }
};

TreeNode *createTree()
{
    int x;
    cout << "Enter the element or for no data enter -1: \n";
    cin >> x;
    TreeNode *n;
    if (x == -1)
    {
        return NULL;
    }
    else
    {
        n = new TreeNode(x);
        cout << "To enter data on left side:\n ";
        n->left = createTree();
        cout << "To enter data on right side:\n ";
        n->right = createTree();
    }
    return n;
}
// -----------------------------Traversal Algorithm------------------------------------------
/// @brief  All traversal
/// @param root
void inorderTree(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    inorderTree(root->left);
    cout << root->data << " ";
    inorderTree(root->right);
}
void preorderTree(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    cout << root->data << " ";
    preorderTree(root->left);
    preorderTree(root->right);
}
void postorderTree(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    postorderTree(root->left);
    postorderTree(root->right);
    cout << root->data << " ";
}
vector<int> levelOrder(TreeNode *root)
{
    queue<TreeNode *> q;
    q.push(root);
    q.push(NULL);
    vector<int> ans;
    int s = 0;
    while (!q.empty())
    {
        if (q.front() != NULL)
        {
            ans.push_back(q.front()->data);
            s += q.front()->data;
            if (q.front()->left != NULL)
            {
                q.push(q.front()->left);
            }
            if (q.front()->right != NULL)
            {
                q.push(q.front()->right);
            }
            q.pop();
        }
        else
        {
            level.push_back(s);
            s = 0;
            q.pop();
            if (!q.empty())
            {
                q.push(NULL);
            }
        }
    }
    return ans;
}
// -------------------------------------------------------------------------------------------------
int Height(TreeNode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int height = max(Height(root->left), Height(root->right)) + 1;
    return height;
}
int diameter(TreeNode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int lh = Height(root->left);
    int rh = Height(root->right);
    int currDia = lh + rh + 1;
    int leftDia = diameter(root->left);
    int rightDia = diameter(root->right);

    return max(currDia, max(leftDia, rightDia));
}
// -------------------------------------------------------------

/// @brief
/// @param root
/// @param h
/// @return
bool isBalance(TreeNode *root, int *h)
{
    if (root == NULL)
    {
        *h = 0;
        return true;
    }
    int lh = 0, rh = 0;
    if (isBalance(root->left, &lh) && isBalance(root->right, &rh) && abs(lh - rh) <= 1)
    {
        *h = max(lh, rh) + 1;
        return true;
    }
    else
    {
        return false;
    }
}
int countNodes(TreeNode *root, int count)
{
    if (root == NULL)
    {
        return count;
    }
    count = countNodes(root->left, count);
    count++;
    count = countNodes(root->right, count);
    return count;
}

int sumNodes(TreeNode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int sum = sumNodes(root->left) + root->data + sumNodes(root->right);
    return sum;
}
// ---------------BST functions-----------------
namespace BST
{
    TreeNode *createBST(TreeNode *root, int val)
    {
        if (root == NULL)
        {
            return new TreeNode(val);
        }

        if (val < root->data)
        {
            root->left = createBST(root->left, val);
        }
        else
        {
            root->right = createBST(root->right, val);
        }
        return root;
    }

    bool Search(TreeNode *root, int key)
    {
        // bool b;
        if (root == NULL)
        {
            // b = false;
            return false;
        }
        if (root->data == key)
        {
            // b = true;
            return true;
        }

        if (root->data > key)
        {
            return Search(root->left, key);
        }
        // else if(root->data<key){
        return Search(root->right, key);

        // return b;
    }
    TreeNode *inorderSuccesor(TreeNode *root)
    {
        TreeNode *curr = root;
        while (curr && curr->left != NULL)
        {
            curr = curr->left;
        }
        return curr;
    }

    TreeNode *deleteNode(TreeNode *root, int key)
    {
        if (root->data > key)
        {
            root->left = deleteNode(root->left, key);
        }
        else if (root->data < key)
        {
            root->right = deleteNode(root->right, key);
        }
        else
        {
            if (root->left == NULL)
            {
                TreeNode *temp = root;
                root = root->right;
                delete temp;
                return root;
            }
            else if (root->right == NULL)
            {
                TreeNode *temp = root;
                root = root->left;
                delete temp;
                return root;
            }
            TreeNode *t = inorderSuccesor(root->right);
            root->data = t->data;
            root->right = deleteNode(root->right, t->data);
        }
        return root;
    }
}
#endif