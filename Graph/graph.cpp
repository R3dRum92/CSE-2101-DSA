#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct Graph
{
    vector<vector<int>> adj; // adjacency list of the graph

    vector<bool> visited;

    Graph()
    {
        // initialize a graph of 100 nodes;
        adj.resize(100);
        visited.resize(100);
    }

    Graph(int n)
    {
        // initialize a graph of n nodes
        adj.resize(n);
        visited.resize(n);
    }

    void dfs(int v)
    {
        // recursive approach
        visited[v] = true;
        cout << "visited " << v << '\n'; // print the visited graph each time

        for (int u : adj[v])
        {
            if (!visited[u])
                dfs(u);
        }
    }

    void dfs_iterative(int v)
    {
        // iterative and rightmost approach
        stack<int> s;

        s.push(v);

        while (!s.empty())
        {
            // get the last element of the stack
            int current = s.top();
            s.pop();

            if (!visited[current])
            {
                cout << "visited " << current << '\n';
                visited[current] = true;
            }

            for (int u : adj[current])
            {
                if (!visited[u])
                    s.push(u);
            }
        }
    }

    void bfs(int v)
    {
        // queue for BFS
        queue<int> q;

        // mark the starting node as visited and enqueue it
        visited[v] = true;
        q.push(v);

        while (!q.empty())
        {
            // get the first element from the queue
            int current = q.front();
            q.pop();

            cout << "visited " << current << '\n';

            // get the neighbours of the current node
            for (int u : adj[current])
            {
                if (!visited[u])
                {
                    visited[u] = true;
                    q.push(u);
                }
            }
        }
    }

    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);

        // Considering an undirected graph
    }

    void reset()
    {
        int n = visited.size();
        visited.clear();
        visited.resize(n);
    }
};

int main()
{
    Graph *g = new Graph();

    g->add_edge(1, 3);
    g->add_edge(1, 2);
    g->add_edge(1, 13);
    g->add_edge(3, 6);
    g->add_edge(6, 4);
    g->add_edge(2, 5);
    g->add_edge(2, 11);
    g->add_edge(2, 7);

    g->dfs(1);
    cout << '\n';

    g->reset();
    g->bfs(1);
    cout << '\n';

    g->reset();
    g->dfs_iterative(1);
}
