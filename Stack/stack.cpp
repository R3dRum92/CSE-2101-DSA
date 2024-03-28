#include <cstddef>
#include <iostream>
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
      return -1;
    }
    else if (head == tail)
    {
      // Stack has only one element
      T x = head->val;
      head = NULL;
      tail = NULL;
      free(head);
      return x;
    }
    else
    {
      node *d = head;
      head = d->next;
      T x = d->val;
      free(d);
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
};

int main()
{
  Stack<char> *st = new Stack<char>();
}
