#include <iostream>
#include <vector>

using namespace std;

void counting_sort(int arr[], int n)
{
    int mx = 0;
    for (int i = 0; i < n; ++i)
    {
        if (arr[i] > mx)
            mx = arr[i];
    }

    vector<int> hash(mx, 0);

    for (int i = 0; i < n; ++i)
    {
        hash[arr[i] - 1] += 1;
    }

    for (int i = 0, j = 0; i < mx; ++i)
    {
        while (hash[i]--)
        {
            arr[j++] = i + 1;
        }
    }
}

int main()
{
    int arr[5] = {5, 4, 3, 2, 1};

    counting_sort(arr, 5);

    for (int i = 0; i < 5; ++i)
    {
        cout << arr[i] << ' ';
    }
    cout << '\n';
}