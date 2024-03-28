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
    }

    T pop()
    {
        if (!head)
        {
            cout << "Stack empty\n";
            exit(0);
        }
        else if (head == tail)
        {
            T x = head->val;
            free(head);
            head = NULL;
            tail = NULL;
            return x;
        }
        else
        {
            node *d = head;
            head = d->next;
            T x = d->val;
            free(d);
            return x;
        }
    }

    T peek()
    {
        if (!head)
        {
            cout << "Stack empty\n";
            exit(0);
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
            cout << p->val << '\n';
            p = p->next;
        }
    }
};

template <class T>
struct Queue
{
    struct node
    {
        node *next;
        T val;
    };

    node *head = NULL;
    node *tail = NULL;

    void enqueue(T x)
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
            tail->next = a;
            tail = a;
        }
    }

    T dequeue()
    {
        if (!head)
        {
            cout << "Queue Empty" << '\n';
            exit(1);
        }
        else if (head == tail)
        {
            T x = head->val;
            free(head);
            head = NULL;
            tail = NULL;
            return x;
        }
        else
        {
            node *d = head;
            T x = d->val;
            head = d->next;
            free(d);
            return x;
        }
    }

    T peek()
    {
        if (!head)
        {
            cout << "Queue Empty\n";
            exit(1);
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
            cout << p->val << '\n';
            p = p->next;
        }
    }
};

int main()
{
    string s;
    cin >> s;

    Queue<char> *first = new Queue<char>();
    Stack<char> *last = new Stack<char>();

    size_t i = 0;
    for (; i < s.length() / 2; ++i)
    {
        first->enqueue(s[i]);
    }
    if (s.length() & 1)
        i++;
    for (; i < s.length(); ++i)
    {
        last->push(s[i]);
    }
    bool flag = true;
    while (first->head)
    {
        if (first->dequeue() != last->pop())
        {
            flag = false;
            break;
        }
    }
    if (flag)
    {
        cout << "Palindrome\n";
    }
    else
    {
        cout << "Not a Palindrome\n";
    }

    return 0;
}
