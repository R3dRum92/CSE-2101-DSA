#include <iostream>

using namespace std;

template <class T>
struct binarySearchTree
{
    struct node
    {
        T val;
        node *left;
        node *right;
        node *parent;
    };

    node *root;

    void inorder(node *p)
    {
        if (!p)
            return;

        inorder(p->left);
        cout << p->val << ' ';
        inorder(p->right);
    }

    void preorder(node *p)
    {
        if (!p)
            return;

        cout << p->val << ' ';
        preorder(p->left);
        preorder(p->right);
    }

    void postorder(node *p)
    {
        if (!p)
            return;

        postorder(p->left);
        postorder(p->right);
        cout << p->val << ' ';
    }

    void insert(T val)
    {
        node *in = new node();
        in->val = val;
        in->left = NULL;
        in->right = NULL;
        in->parent = NULL;
        if (root)
            ins(root, in);
        else
            root = in;
    }

    void ins(node *p, node *in)
    {
        if (p->val > in->val && p->left == NULL)
        {
            p->left = in;
            in->parent = p;
        }
        else if (p->val < in->val && p->right == NULL)
        {
            p->right = in;
            in->parent = p;
        }
        else if (p->val > in->val)
            ins(p->left, in);
        else if (p->val < in->val)
            ins(p->right, in);
        else
            return;
    }

    bool find(node *p, T x)
    {
        if (!p)
            return false;
        if (p->val == x)
            return true;

        return find(p->left, x) || find(p->right, x);
    }

    bool binary_find(node *p, T x)
    {
        if (!p)
            return false;
        if (p->val == x)
            return true;
        if (p->val > x)
            return binary_find(p->left, x);
        if (p->val < x)
            return binary_find(p->right, x);
        return false;
    }

    void delete_value(node *p, T x)
    {
        if (!p)
            return;
        else if (p->val == x)
            delete_node(p);
        else if (p->val < x)
            delete_value(p->right, x);
        else if (p->val > x)
            delete_value(p->left, x);
        else
            return;
    }

    void delete_node(node *p)
    {
        if (p->left == NULL && p->right == NULL)
        {
            if (p->parent)
                if (p->val > p->parent->val)
                    p->parent->right = NULL;
                else
                    p->parent->left = NULL;
            p = NULL;
            delete p;
        }
        else if (p->left == NULL)
        {
            if (p->val > p->parent->val)
                p->parent->right = p->right;
            else
                p->parent->left = p->right;
            p = NULL;
            delete p;
        }
        else if (p->right == NULL)
        {
            if (p->val > p->parent->val)
                p->parent->right = p->left;
            else
                p->parent->left = p->left;
            p = NULL;
            delete p;
        }
        else
        {
            node *q = p->right;
            while (q->left)
                q = q->left;
            T temp = q->val;
            q->val = p->val;
            p->val = temp;
            delete_node(q);
        }
    }
};

int main(int argc, char const *argv[])
{
    int arr[7] = {8, 3, 10, 1, 6, 9, 14};
    binarySearchTree<int> *bst = new binarySearchTree<int>();

    for (int i = 0; i < 7; ++i)
        bst->insert(arr[i]);

    bst->inorder(bst->root);
    cout << '\n';
    bst->preorder(bst->root);
    cout << '\n';
    bst->postorder(bst->root);
    cout << '\n';

    cout << boolalpha << bst->binary_find(bst->root, 6) << '\n';

    bst->delete_value(bst->root, 6);
    bst->inorder(bst->root);
    cout << '\n';
    cout << boolalpha << bst->binary_find(bst->root, 3) << '\n';
    bst->delete_value(bst->root, 8);
    bst->inorder(bst->root);
    cout << '\n';
    return 0;
}
