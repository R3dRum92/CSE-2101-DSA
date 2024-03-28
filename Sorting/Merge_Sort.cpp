#include <iostream>

using namespace std;

template <class T>
void merge(T arr[], int start, int mid, int end)
{
    int n = end - start;
    int output[n];

    int idx1 = start, idx2 = mid;
    while (idx1 < mid && idx2 < end)
    {
        if (arr[idx1] <= arr[idx2])
        {
            output[idx1 - start + idx2 - mid] = arr[idx1];
            idx1++;
        }
        else
        {
            output[idx1 - start + idx2 - mid] = arr[idx2];
            idx2++;
        }
    }
    while (idx1 < mid)
    {
        output[idx1 - start + idx2 - mid] = arr[idx1];
        idx1++;
    }
    while (idx2 < end)
    {
        output[idx1 - start + idx2 - mid] = arr[idx2];
        idx2++;
    }

    for (int i = 0; i < n; ++i)
        arr[start + i] = output[i];
}

template <class T>
void mergeSort(T arr[], int start, int end)
{
    if (end - start == 1)
    {
        return;
    }

    int mid = (start + end) / 2;
    mergeSort(arr, start, mid);
    mergeSort(arr, mid, end);

    merge(arr, start, mid, end);
}

int main(int argc, char const *argv[])
{
    // int arr[5] = {5, 4, 3, 2, 1};
    // mergeSort<int>(arr, 0, 5);

    char arr[5] = {'e', 'd', 'c', 'b', 'a'};

    mergeSort<char>(arr, 0, 5);

    for (int i = 0; i < 5; ++i)
        cout << arr[i] << '\n';

    return 0;
}
