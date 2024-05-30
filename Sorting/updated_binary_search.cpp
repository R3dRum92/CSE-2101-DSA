#include <iostream>
#include <vector>

using namespace std;

int binary_search(vector<int> arr, int start, int end, int k)
{
    if (start >= end)
        return arr.size();

    int mid = (start + end) >> 1;

    if (arr[mid] == k)
    {
        // this index might not be the first occurence of k in the array
        return min(mid, binary_search(arr, start, mid - 1, k));
    }

    if (arr[mid] > k)
    {
        // discard the latter half of the search space
        return binary_search(arr, start, mid - 1, k);
    }

    if (arr[mid] < k)
    {
        // discard the first half of the search space
        return binary_search(arr, mid + 1, end, k);
    }

    else
        return -1;
}

int lower_bound(vector<int> arr, int start, int end, int k)
{
    if (start >= end)
        return arr.size();

    int mid = (start + end) >> 1; // fancy way to divide by 2;

    if (arr[mid] >= k)
    {
        return min(mid, lower_bound(arr, start, mid - 1, k));
    }

    return lower_bound(arr, mid + 1, end, k);
}

int upper_bound(vector<int> arr, int start, int end, int k)
{
    if (start >= end)
        return arr.size();

    int mid = (start + end) >> 1;

    if (arr[mid] > k)
    {
        return min(mid, upper_bound(arr, start, mid - 1, k));
    }
    return upper_bound(arr, mid + 1, end, k);
}

int main()
{
    vector<int> arr = {3, 3, 3, 3, 3};

    cout << upper_bound(arr, 0, 5, 2) << '\n';

    return 0;
}