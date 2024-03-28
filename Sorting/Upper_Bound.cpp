#include <iostream>

using namespace std;

int upperBound(int arr[], int start, int end, int k)
{
    if (start >= end)
        return -1;

    int mid = (start + end) / 2;
    if (arr[mid] <= k)
        return upperBound(arr, mid + 1, end, k);
    else
    {
        int idx = upperBound(arr, start, mid - 1, k);
        if (idx == -1 || arr[mid] < arr[idx])
            return mid;
        else
            return idx;
    }
}

int main()
{
    int arr[5] = {1, 1, 2, 2, 2};
    cout << upperBound(arr, 0, 5, 3) << '\n';
}