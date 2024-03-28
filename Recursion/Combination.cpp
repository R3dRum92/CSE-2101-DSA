#include <iostream>
using namespace std;

void r_combination(int arr[], int n, int r, int idx, int c, int comb[])
{
    if (c == r)
    {
        for (int i = 0; i < c; ++i)
            cout << comb[i] << ' ';
        cout << '\n';
        return;
    }

    for (int i = idx; i < n; ++i)
    {
        comb[c] = arr[i];
        r_combination(arr, n, r, i + 1, c + 1, comb);
    }
}

int main()
{
    int arr[5] = {1, 2, 3, 4, 5};

    int comb[5];

    r_combination(arr, 5, 3, 0, 0, comb);

    return 0;
}