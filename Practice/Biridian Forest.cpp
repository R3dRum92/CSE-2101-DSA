#include <bits/stdc++.h>
#define ll long long

using namespace std;

void solve()
{
    int r, c;
    cin >> r >> c;

    vector<string> grid(r);
    pair<int, int> start;
    pair<int, int> end;
    vector<pair<int, int>> breeders;
    vector<pair<int, int>> trees;

    for (int i = 0; i < r; ++i)
    {
        cin >> grid[i];
        for (int j = 0; j < c; ++j)
        {
            if (grid[i][j] == 'S')
                start = {i, j};
            else if (grid[i][j] == 'E')
                end = {i, j};
            else if (grid[i][j] == 'T')
                trees.push_back({i, j});
            else if (grid[i][j] != '0')
                breeders.push_back({i, j});
        }
    }

    vector<vector<int>> dist(r, vector<int>(c));
    vector<vector<bool>> visited(r, vector<bool>(c));

    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            dist[i][j] = INT32_MAX;
            visited[i][j] = false;
        }
    }

    dist[end.first][end.second] = 0;
    queue<pair<int, int>> q;
    q.push(end);

    while (!q.empty())
    {
        pair<int, int> u = q.front();
        q.pop();

        int i = u.first;
        int j = u.second;
        if(visited[i][j]) continue;

        // up
        if (i != 0)
        {
            if (grid[i - 1][j] != 'T')
            {
                if (!visited[i - 1][j])
                {
                    q.push({i - 1, j});
                    dist[i - 1][j] = dist[i][j] + 1;
                }
            }
        }
        // // down
        if (i != r - 1)
        {
            if (grid[i + 1][j] != 'T')
            {
                if (!visited[i + 1][j])
                {
                    q.push({i + 1, j});
                    dist[i + 1][j] = dist[i][j] + 1;
                }
            }
        }
        // // left
        if (j != 0)
        {
            if (grid[i][j - 1] != 'T')
            {
                if (!visited[i][j - 1])
                {
                    q.push({i, j - 1});
                    dist[i][j - 1] = dist[i][j] + 1;
                }
            }
        }
        // right
        if (j != c - 1)
        {
            if (grid[i][j + 1] != 'T')
            {
                if (!visited[i][j + 1])
                {
                    q.push({i, j + 1});
                    dist[i][j + 1] = dist[i][j] + 1;
                }
            }
        }

        visited[i][j] = true;
    }
    int player_dist = dist[start.first][start.second];
    int ans = 0;

    for (pair<int, int> breeder : breeders)
    {
        // cout << dist[end] << '\n';
        if (dist[breeder.first][breeder.second] <= player_dist)
        {
            ans += grid[breeder.first][breeder.second] - '0';
        }
    }

    cout << ans << '\n';
}

int main()
{
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i)
    {
        // cout << Case << i << ": ";
        solve();
    }

    return 0;
}
