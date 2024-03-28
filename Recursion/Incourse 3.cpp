#include <iostream>
#include <string>
using namespace std;

template <class T>
struct Stack
{
    struct node
    {
        node *next;
        T val;
    };

    node *head = NULL;
    node *tail = NULL;

    size_t length = 0;

    void push(T x)
    {
        node *a = new node();
        a->next = NULL;
        a->val = x;
        if (!head)
        {
            head = a;
            tail = a;
        }
        else
        {
            a->next = head;
            head = a;
        }
        length++;
    }

    T pop()
    {
        if (!head)
        {
            cout << "Stack empty\n";
            return -1;
        }
        else if (head == tail)
        {
            // Stack has only one element
            T x = head->val;
            head = NULL;
            tail = NULL;
            length--;
            return x;
        }
        else
        {
            node *d = head;
            head = d->next;
            T x = d->val;
            delete d;
            length--;
            return x;
        }
    }

    T peek()
    {
        if (!head)
        {
            cout << "Stack empty\n";
            return -1;
        }
        else
        {
            return head->val;
        }
    }

    void print()
    {
        node *p = head;

        while (p)
        {
            cout << p->val << ' ';
            p = p->next;
        }
        cout << '\n';
    }

    void copy(Stack<T> *newStack)
    {
        node *p = head;

        while (p)
        {
            newStack->push(p->val);
            p = p->next;
        }
    }
};

void generate(Stack<char> *stk, string s, int k)
{
    // cout << stk->length << '\n';
    if (stk->length == k)
    {
        int c = 0;
        for (Stack<char>::node *p = stk->head; p != NULL; p = p->next)
        {
            if (p->val == 'a')
                c++;
        }
        if (c == 4)
            stk->print();
        return;
    }

    for (int i = 0; i < s.length(); ++i)
    {
        Stack<char> *newStack = new Stack<char>();
        stk->copy(newStack);
        newStack->push(s[i]);
        generate(newStack, s, k);
    }
}

int main()
{
    string s = "abc";
    int k = 5;
    Stack<char> *stk = new Stack<char>();
    generate(stk, s, k);
}