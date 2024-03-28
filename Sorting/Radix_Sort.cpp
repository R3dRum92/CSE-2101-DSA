#include <iostream>
using namespace std;

int getMax(int arr[], int n)
{
    int mx = INT32_MIN;
    for (int i = 0; i < n; ++i)
    {
        if (arr[i] > mx)
            mx = arr[i];
    }
    return mx;
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        cout << arr[i] << ' ';
    }
    cout << '\n';
}

void countSort(int arr[], int n, int exp)
{
    int output[n];
    int i, count[10] = {0};

    for (i = 0; i < n; ++i)
        count[(arr[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (i = 0; i < n; ++i)
    {
        arr[i] = output[i];
    }
}

void radixSort(int arr[], int n)
{
    int mx = getMax(arr, n);

    int exp = 1;
    while (mx / exp > 0)
    {
        countSort(arr, n, exp);
        exp *= 10;
    }
}

int main()
{
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);

    radixSort(arr, n);
    printArray(arr, n);
}