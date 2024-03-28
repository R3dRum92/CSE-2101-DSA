#include <iostream>
#include <algorithm>
using namespace std;

void selectionSort(int arr[], int n)
{
    int i, j, min_idx;

    for (i = 0; i < n; ++i)
    {
        min_idx = i;
        for (j = i + 1; j < n; ++j)
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }

        if (min_idx != i)
            swap(arr[i], arr[min_idx]);
    }
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        cout << arr[i] << ' ';
    }
    cout << '\n';
}

int main()
{
    int arr[5] = {5, 4, 3, 2, 1};

    selectionSort(arr, 5);
    printArray(arr, 5);

    return 0;
}
