#include <iostream>

using namespace std;

struct AVLTree
{
    struct node
    {
        node *left;
        node *right;
        node *parent;
        int val;
        int height;
    };

    node *root;

    void update_height(node *n)
    {
        if (!n)
            return;

        int h = 1;

        if (n->left)
        {
            h = n->left->height + 1;
        }

        if (n->right)
        {
            h = max(h, n->right->height + 1);
        }

        n->height = h;
    }

    // Left Left
    node *right_rotate(node *pivot)
    {
        node *tmp = pivot->left;

        pivot->left = tmp->right;

        if (tmp->right)
        {
            tmp->right->parent = pivot;
        }

        tmp->right = pivot;

        tmp->parent = pivot->parent;

        pivot->parent = tmp;

        if (tmp->parent && pivot->val < tmp->parent->val)
        {
            tmp->parent->left = tmp;
        }
        else if (tmp->parent && pivot->val > tmp->parent->val)
        {
            tmp->parent->right = tmp;
        }

        pivot = tmp;

        this->update_height(pivot->left);
        this->update_height(pivot->right);
        this->update_height(pivot);
        this->update_height(pivot->parent);

        return pivot;
    }

    node *left_rotate(node *pivot)
    {
        node *tmp = pivot->right;

        pivot->right = tmp->left;

        if (tmp->left)
        {
            tmp->left->parent = pivot;
        }

        tmp->left = pivot;

        tmp->parent = pivot->parent;

        pivot->parent = tmp;

        if (tmp->parent && pivot->val < tmp->parent->val)
        {
            tmp->parent->left = tmp;
        }
        else if (tmp->parent && pivot->val > tmp->parent->val)
        {
            tmp->parent->right = tmp;
        }

        if (pivot == root)
            root = tmp;
        pivot = tmp;

        this->update_height(pivot->left);
        this->update_height(pivot->right);
        this->update_height(pivot);
        this->update_height(pivot->parent);

        return pivot;
    }

    node *insert(int val)
    {
        node *in = new node();
        in->val = val;
        in->left = NULL;
        in->right = NULL;
        in->height = 1;
        in->parent = NULL;

        if (root)
        {
            return ins(root, in);
        }
        root = in;
        return root;
    }

    node *ins(node *p, node *in)
    {
        if (p->val > in->val)
        {
            if (p->left == NULL)
            {
                p->left = in;
                in->parent = p;
            }
            else
            {
                ins(p->left, in);
            }

            int left_height = 0;
            int right_height = 0;

            if (p->left)
            {
                left_height = p->left->height;
            }

            if (p->right)
            {
                right_height = p->right->height;
            }

            if (abs(left_height - right_height) >= 2)
            {
                // left left
                if (p->left && in->val < p->left->val)
                {
                    p = right_rotate(p);
                }
                // left right
                else if (p->left && in->val > p->left->val)
                {
                    p->left = left_rotate(p->left);
                    p = right_rotate(p);
                }
            }
        }

        else if (p->val < in->val)
        {
            if (p->right == NULL)
            {
                // cout << "haha\n";
                p->right = in;
                in->parent = p;
            }
            else
            {
                ins(p->right, in);
            }

            int left_height = 0;
            int right_height = 0;

            if (p->left)
            {
                left_height = p->left->height;
            }

            if (p->right)
            {
                right_height = p->right->height;
            }

            if (abs(left_height - right_height) >= 2)
            {
                // right left
                if (p->right && in->val < p->right->val)
                {
                    p->right = right_rotate(p->right);
                    p = left_rotate(p);
                }
                // right right
                else if (p->right && in->val > p->right->val)
                {
                    p = left_rotate(p);
                }
            }
        }

        this->update_height(p);

        return p;
    }

    void preorder(node *p)
    {
        cout << "Node: " << p->val << ", Parent Node: ";

        if (p->parent)
        {
            cout << p->parent->val << '\n';
        }
        else
        {
            cout << "NULL\n";
        }

        if (p->left)
            preorder(p->left);

        if (p->right)
            preorder(p->right);
    }

    node *min_value_node(node *n)
    {
        node *current = n;

        while (current->left)
            current = current->left;

        return current;
    }

    node *deleteNode(node *p, int val)
    {
        if (p == NULL)
            return p;

        if (val < p->val)
        {
            p->left = deleteNode(p->left, val);
        }
        else if (val > p->val)
        {
            p->right = deleteNode(p->right, val);
        }
        else
        {
            // one child or no child
            if ((p->left == NULL) || (p->right == NULL))
            {
                node *tmp = p->left ? p->left : p->right;

                // no child
                if (tmp == NULL)
                {
                    tmp = p;
                    p = NULL;
                    delete p;
                }
                // one child
                else
                {
                    *p = *tmp;
                }

                delete tmp;
            }
            else
            {
                node *tmp = min_value_node(p->right);

                p->val = tmp->val;

                p->right = deleteNode(p->right, val);
            }
        }

        if (p == NULL)
            return p;

        update_height(p);

        int balance = get_balance(p);

        // left left
        if (balance > 1 && get_balance(p->left) >= 0)
        {
            return right_rotate(p);
        }
        // left right
        if (balance > 1 && get_balance(p->left) < 0)
        {
            p->left = left_rotate(p->left);
            return right_rotate(p);
        }
        // right left
        if (balance < -1 && get_balance(p->right) > 0)
        {
            p->right = right_rotate(p->right);
            return left_rotate(p);
        }
        // right right
        if (balance < -1 && get_balance(p->right) <= 0)
        {
            return left_rotate(p);
        }

        return p;
    }

    int get_height(node *n)
    {
        if (n == NULL)
            return 0;

        return n->height;
    }

    int get_balance(node *n)
    {
        if (n == NULL)
            return 0;

        return get_height(n->left) - get_height(n->right);
    }
};

int main()
{
    AVLTree *tree = new AVLTree();

    int arr[9] = {9, 5, 10, 0, 6, 11, -1, 1, 2};

    for (int i = 0; i < 9; ++i)
    {
        tree->insert(arr[i]);
        tree->preorder(tree->root);

        cout << '\n';
    }

    tree->root = tree->deleteNode(tree->root, 10);
    tree->preorder(tree->root);
}
