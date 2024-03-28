#include <iostream>
#include <algorithm>
using namespace std;

void bubbleSort(int arr[], int n)
{
    int i, j;
    bool swapped;

    for (i = 0; i < n - 1; ++i)
    {
        swapped = false;
        for (j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;
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

    bubbleSort(arr, 5);
    printArray(arr, 5);

    return 0;
}
