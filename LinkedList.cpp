#include <iostream>
using namespace std;

typedef struct LinkedList
{
  typedef struct node
  {
    // Data structure for each element in the Linked List
    node *next;
    node *prev;
    int val;
  } node;

  node *head = NULL;
  node *tail = NULL;

  node *search(int x)
  {
    node *s = head;
    while (s != NULL && s->val != x)
    {
      s = s->next;
    }
    return s;
  }
  void insert_first(int x)
  {
    // Inserts x at the first position
    node *a = new node;
    a->next = NULL;
    a->prev = NULL;
    a->val = x;
    if (head == NULL)
    {
      // Linked List is empty
      head = a;
      tail = a;
    }
    else
    {
      a->next = head;
      head->prev = a;
      head = a;
    }
  }

  void insert_last(int x)
  {
    // Inserts x at the last position
    node *a = new node;
    a->next = NULL;
    a->prev = NULL;
    a->val = x;
    if (tail == NULL)
    {
      // Linked List is empty
      head = a;
      tail = a;
    }
    else
    {
      tail->next = a;
      a->prev = tail;
      tail = a;
    }
  }

  void insert_after_x(int x, int y)
  {
    node *a = new node;
    a->next = NULL;
    a->prev = NULL;
    a->val = y;

    node *s = search(x);
    if (s)
    {
      a->next = s->next;
      a->prev = s;
      if (s->next)
      {
        s->next->prev = a;
      }
      s->next = a;
    }
  }

  void print()
  {
    // Prints all the elements of the Linked List starting from head
    node *p = head;
    while (p)
    {
      cout << p->val << ' ';
      p = p->next;
    }
    cout << '\n';
  }

  int delete_first()
  {
    if (!head)
    {
      // Linked List is empty
      cout << "Linked List empty\n";
      return -1;
    }
    else if (head == tail)
    {
      // Linked list contains only one element
      int x = head->val;
      head = NULL;
      tail = NULL;
      return x;
    }
    else
    {
      // Linked List contains more than one element
      int x = head->val;
      node *d = head;
      head = head->next;
      head->prev = NULL;
      delete d;
      return x;
    }
  }

  int delete_last()
  {
    if (!tail)
    {
      // Linked List is empty
      cout << "Linked List empty\n";
      return -1;
    }
    else if (head == tail)
    {
      // Linked List contains only one element
      int x = tail->val;
      head = NULL;
      tail = NULL;
      return x;
    }
    else
    {
      // Linked List contains more than one element
      int x = tail->val;
      node *d = tail;
      tail = tail->prev;
      tail->next = NULL;
      delete d;
      return x;
    }
  }

  void delete_x(int x)
  {
    // Deletes the first occurence of x
    node *p = head;
    node *temp;
    if (head->val == x)
    {
      delete_first();
    }
    else if (tail->val == x)
    {
      delete_last();
    }
    else
    {
      while (p->next)
      {
        if (p->next->val == x)
        {
          temp = p->next;
          p->next = p->next->next;
          free(temp);
          break;
        }
        p = p->next;
      }
    }
  }

} LinkedList;

int main()
{
  LinkedList *ll = new LinkedList();
  ll->insert_first(10);
  ll->delete_last();
  if (ll->tail == NULL)
  {
    cout << "haha\n";
  }
  ll->insert_first(20);
  ll->insert_last(30);
  ll->insert_last(40);

  ll->print();
  ll->delete_first();
  ll->delete_last();
  ll->insert_last(5);
  ll->delete_x(30);
  ll->insert_after_x(11, 10);
  ll->print();
  return 0;
}
