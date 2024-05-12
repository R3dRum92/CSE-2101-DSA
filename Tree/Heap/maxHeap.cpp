#include <iostream>

using namespace std;

struct MaxHeap
{
    int *harr;
    int capacity;
    int heap_size;

    MaxHeap(int capacity)
    {
        this->heap_size = 0;
        this->capacity = capacity;
        this->harr = new int[capacity];
    }

    int left(int index)
    {
        return index * 2 + 1;
    }

    int right(int index)
    {
        return index * 2 + 2;
    }

    int parent(int index)
    {
        return (index - 1) / 2;
    }

    void heapify(int index)
    {
        int l = this->left(index);
        int r = this->right(index);
        int max_index = index;

        if (l < this->heap_size && harr[l] > harr[index])
        {
            max_index = l;
        }
        if (r < this->heap_size && harr[r] > harr[max_index])
        {
            max_index = r;
        }

        if (max_index != index)
        {
            swap(harr[max_index], harr[index]);
            this->heapify(max_index);
        }
    }

    void swap(int &a, int &b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

    int extract_root()
    {
        if (this->heap_size <= 0)
        {
            return INT32_MIN;
        }

        if (this->heap_size == 1)
        {
            this->heap_size--;
            return harr[0];
        }

        int root = harr[0];
        harr[0] = harr[this->heap_size - 1];
        this->heap_size--;
        this->heapify(0);

        return root;
    }

    int get_max()
    {
        if (this->heap_size <= 0)
            return INT32_MIN;

        return harr[0];
    }

    void increase_node(int index, int new_val)
    {

        if (new_val < harr[index])
            return;

        harr[index] = new_val;

        while (index != 0 && harr[this->parent(index)] < harr[index])
        {
            swap(harr[this->parent(index)], harr[index]);
            index = this->parent(index);
        }
    }

    void delete_node(int index)
    {
        this->increase_node(index, INT32_MAX);
        this->extract_root();
    }

    void insert_node(int val)
    {
        if (this->heap_size == this->capacity)
        {
            cout << "Heap Overflow\n";
            return;
        }

        int index = this->heap_size;
        this->heap_size++;
        harr[index] = val;

        while (index != 0 && harr[this->parent(index)] < harr[index])
        {
            swap(harr[this->parent(index)], harr[index]);
            index = this->parent(index);
        }
    }
};
