#include <iostream>

using namespace std;

void r_permutation(int arr[], int n, int r, int idx, int c, bool flag[], int perm[])
{
    if (c == r)
    {
        for (int i = 0; i < c; ++i)
            cout << perm[i] << ' ';
        cout << '\n';
        return;
    }

    for (int i = 0; i < n; ++i)
    {
        if (!flag[i])
        {
            perm[c] = arr[i];
            flag[i] = true;
            r_permutation(arr, n, r, idx + 1, c + 1, flag, perm);
            flag[i] = false;
        }
    }
}

int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    bool flag[5];
    for (int i = 0; i < 5; ++i)
        flag[i] = false;

    int perm[5];

    r_permutation(arr, 5, 3, 0, 0, flag, perm);

    return 0;
}
