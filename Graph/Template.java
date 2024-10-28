import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.InputMismatchException;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

class FastIO extends PrintWriter {

    private InputStream stream;

    private byte[] buf = new byte[1 << 16];

    private int curChar;

    private int numChars;

    // standard input

    public FastIO() {
        this(System.in, System.out);
    }

    public FastIO(InputStream i, OutputStream o) {

        super(o);

        stream = i;

    }

    // file input

    public FastIO(String i, String o) throws IOException {

        super(new FileWriter(o));

        stream = new FileInputStream(i);

    }

    // throws InputMismatchException() if previously detected end of file

    private int nextByte() {

        if (numChars == -1) {
            throw new InputMismatchException();
        }

        if (curChar >= numChars) {

            curChar = 0;

            try {

                numChars = stream.read(buf);

            } catch (IOException e) {
                throw new InputMismatchException();
            }

            if (numChars == -1) {

                return -1; // end of file

            }

        }

        return buf[curChar++];

    }

    // to read in entire lines, replace c <= ' '

    // with a function that checks whether c is a line break

    public String next() {

        int c;

        do {
            c = nextByte();
        } while (c <= ' ');

        StringBuilder res = new StringBuilder();

        do {

            res.appendCodePoint(c);

            c = nextByte();

        } while (c > ' ');

        return res.toString();

    }

    public int nextInt() { // nextLong() would be implemented similarly

        int c;

        do {
            c = nextByte();
        } while (c <= ' ');

        int sgn = 1;

        if (c == '-') {

            sgn = -1;

            c = nextByte();

        }

        int res = 0;

        do {

            if (c < '0' || c > '9') {
                throw new InputMismatchException();
            }

            res = 10 * res + c - '0';

            c = nextByte();

        } while (c > ' ');

        return res * sgn;

    }

    public double nextDouble() {
        return Double.parseDouble(next());
    }

}

class Graph {
    private List<List<Integer>> adjList;
    private int numVertices;
    private int numEdges;

    private List<List<Integer>> components; // Strongly connected components
    private List<List<Integer>> adjCond; // Adjacency list of condensation graph

    Graph(int vertices, int edges) {
        this.adjList = new ArrayList<>();
        this.numVertices = vertices;
        this.numEdges = edges;

        // 1-based indexing
        for (int i = 0; i < this.numVertices + 1; ++i) {
            this.addVertex();
        }
    }

    private void addVertex() {
        this.adjList.add(new LinkedList<Integer>());
    }

    private void addEdge(int u, int v) {
        this.adjList.get(u).add(v);
    }

    private void BFS(int vertex, int[] d, int[] prev, boolean[] visited) {
        d[vertex] = 0;
        visited[vertex] = true;
        Queue<Integer> q = new LinkedList<>();
        q.add(vertex);

        while (!q.isEmpty()) {
            int u = q.poll();

            for (int v : this.adjList.get(u)) {
                if (!visited[v]) {
                    d[v] = d[u] + 1;
                    prev[v] = u;
                    visited[v] = true;
                    q.add(v);
                }
            }
        }
    }

    private void DFS(int vertex, boolean visited[], List<List<Integer>> adj, List<Integer> output) {
        visited[vertex] = true;
        for (int v : this.adjList.get(vertex)) {
            if (!visited[v]) {
                DFS(v, visited, adj, output);
            }
        }
        output.add(vertex);
    }

    private List<Integer> topoSort() {
        boolean[] visited = new boolean[this.numVertices + 1];
        List<Integer> topOrder = new ArrayList<Integer>();
        Arrays.fill(visited, false);

        // Change to 0 for 0-based indexing
        for (int i = 1; i < this.numVertices + 1; ++i) {
            if (!visited[i]) {
                DFS(i, visited, this.adjList, topOrder);
            }
        }

        Collections.reverse(topOrder);

        return topOrder;
    }

    private void stronglyConnectedComponents() {
        this.components = new ArrayList<>();
        this.adjCond = new ArrayList<>();
        List<List<Integer>> adjRev = new ArrayList<>(); // Adjacency list of G^T

        for (int i = 0; i < this.numVertices + 1; ++i) {
            this.adjCond.add(new LinkedList<Integer>());
            adjRev.add(new LinkedList<Integer>());
        }

        List<Integer> topOrder = this.topoSort();

        for (int i = 1; i <= this.numVertices; ++i) {
            for (int u : this.adjList.get(i)) {
                adjRev.get(u).add(i);
            }
        }

        int[] roots = new int[this.numVertices + 1]; // gives the root vertex of a vertex's SCC
        boolean[] visited = new boolean[this.numVertices + 1];
        Arrays.fill(roots, 0);
        Arrays.fill(visited, false);

        // second series of depth first searches
        for (int v : topOrder) {
            if (!visited[v]) {
                List<Integer> component = new LinkedList<Integer>();
                DFS(v, visited, adjRev, component);
                this.components.add(component);
                int root = Collections.min(component);
                for (int u : component) {
                    roots[u] = root;
                }
            }
        }

        for (int i = 1; i <= this.numVertices; ++i) {
            for (int u : this.adjList.get(i)) {
                if (roots[i] != roots[u]) {
                    adjCond.get(roots[i]).add(roots[u]);
                }
            }
        }
    }
}

public class Main implements Runnable {
    public static void main(String[] args) {
        new Thread(null, new Main(), "whatever", 1 << 26).start();
    }

    public void run() {
        Graph g = new Graph();
        g.solve();
        g.close();
    }
}
