#include <iostream>

using namespace std;

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
            head = NULL;
            tail = NULL;
            return x;
        }
        else
        {
            node *d = head;
            T x = d->val;
            head = d->next;
            delete d;
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
    Queue<int> *q = new Queue<int>();

    q->enqueue(5);
    q->enqueue(10);
    q->enqueue(12);
    q->print();
    cout << q->peek() << '\n';
    cout << q->dequeue() << '\n';
    q->print();
}
