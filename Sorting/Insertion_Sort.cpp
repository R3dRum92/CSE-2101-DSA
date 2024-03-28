#include <iostream>
using namespace std;

void insertionSort(int arr[], int n)
{
    int i, tmp, j;
    for (i = 1; i < n; ++i)
    {
        tmp = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > tmp)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = tmp;
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

    insertionSort(arr, 5);
    printArray(arr, 5);
}