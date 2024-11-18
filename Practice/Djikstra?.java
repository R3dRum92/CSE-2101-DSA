import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.InputMismatchException;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;

public class Main implements Runnable {
    public static void main(String[] args) {
        new Thread(null, new Main(), "whatever", 1 << 28).start();
    }

    public void run() {
        WeightedGraph wg = new WeightedGraph();
        wg.close();
    }
}

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

    public long nextLong() {
        int c;
        do {
            c = nextByte();
        } while (c <= ' '); // Skip whitespace

        int sgn = 1;

        if (c == '-') { // Check for negative sign
            sgn = -1;
            c = nextByte();
        }

        long res = 0;

        do {
            if (c < '0' || c > '9') { // Ensure valid digit
                throw new InputMismatchException();
            }
            res = 10 * res + c - '0'; // Construct the number
            c = nextByte();
        } while (c > ' '); // Continue until whitespace

        return res * sgn;
    }

    public double nextDouble() {
        return Double.parseDouble(next());
    }

}

class WeightedGraph {
    private List<List<Edge>> adjList;
    private int numVertices;
    private int numEdges;
    private FastIO obj;
    private List<Edge> edges;

    private static class Edge implements Comparable<Edge> {
        int from, to;
        long weight;

        Edge() {
            this.from = -1;
            this.to = -1;
            this.weight = Integer.MAX_VALUE;
        }

        Edge(int u, int v, long w) {
            this.from = u;
            this.to = v;
            this.weight = w;
        }

        @Override
        public int compareTo(WeightedGraph.Edge e) {
            if (this.weight > e.weight)
                return 1;
            else if (this.weight < e.weight)
                return -1;
            else if (this.to > e.to)
                return 1;
            else if (this.to < e.to)
                return -1;
            else
                return 0;
        }
    }

    private static class Pair implements Comparable<Pair> {
        long first;
        int second;

        Pair(long first, int second) {
            this.first = first;
            this.second = second;
        }

        @Override
        public int compareTo(WeightedGraph.Pair arg0) {
            if (this.first > this.first)
                return 1;
            else if (this.first < this.first)
                return -1;
            else if (this.second > this.second)
                return 1;
            else if (this.second < this.second)
                return -1;
            else
                return 0;
        }
    }

    public WeightedGraph() {
        this.obj = new FastIO();
        this.adjList = new ArrayList<>();
        this.numVertices = obj.nextInt();
        this.numEdges = obj.nextInt();
        this.edges = new ArrayList<>();

        // 1-based indexing
        for (int i = 0; i < this.numVertices + 1; ++i) {
            this.addVertex();
        }
        this.solve();
    }

    private void addVertex() {
        this.adjList.add(new ArrayList<Edge>());
    }

    private void addEdge(int u, int v, long w) {
        if (u == v)
            return;
        this.adjList.get(u).add(new Edge(u, v, w));
        this.adjList.get(v).add(new Edge(v, u, w));
        this.edges.add(new Edge(u, v, w));
    }

    private void prim() {
        int totalWeight = 0;
        List<Edge> minEdges = new ArrayList<Edge>(this.numVertices + 1);
        for (int i = 0; i <= this.numVertices; i++) {
            minEdges.add(new Edge());
        }
        minEdges.get(1).weight = 0;
        Queue<Edge> q = new PriorityQueue<Edge>();
        q.add(new Edge(-1, 1, 0));
        boolean[] selected = new boolean[this.numVertices + 1];
        Arrays.fill(selected, false);

        for (int i = 0; i < this.numVertices;) {
            if (q.isEmpty()) {
                obj.println("No MST");
                return;
            }

            Edge min = q.poll();
            int v = min.to;

            if (selected[v])
                continue;

            i++;

            selected[v] = true;
            totalWeight += min.weight;

            if (minEdges.get(v).to != -1)
                obj.println(v + " " + minEdges.get(v).to + " " + minEdges.get(v).weight);

            for (Edge e : this.adjList.get(v)) {
                if (!selected[e.to] && e.weight < minEdges.get(e.to).weight) {
                    q.remove(new Edge(-1, e.to, minEdges.get(e.to).weight));
                    minEdges.set(e.to, new Edge(-1, v, e.weight));
                    q.add(new Edge(-1, e.to, e.weight));
                }
            }
        }

        obj.println(totalWeight);
    }

    private void makeSet(int v, int[] parent, int[] rank) {
        parent[v] = v;
        rank[v] = 0;
    }

    private int findSet(int v, int[] parent) {
        if (v == parent[v])
            return v;
        return parent[v] = findSet(parent[v], parent);
    }

    private void unionSets(int a, int b, int[] parent, int[] rank) {
        a = findSet(a, parent);
        b = findSet(b, parent);
        if (a != b) {
            if (rank[a] < rank[b]) {
                a = a ^ b;
                b = a ^ b;
                a = a ^ b;
            }
            parent[b] = a;
            if (rank[a] == rank[b])
                rank[a]++;
        }
    }

    private void kruskal() {
        int totalWeight = 0;
        int[] parent = new int[this.numVertices + 1];
        int[] rank = new int[this.numVertices + 1];
        List<Edge> result = new ArrayList<>();

        for (int i = 0; i <= this.numVertices; ++i) {
            makeSet(i, parent, rank);
        }

        this.edges.sort(null);

        for (Edge e : edges) {
            if (findSet(e.from, parent) != findSet(e.to, parent)) {
                totalWeight += e.weight;
                result.add(e);
                unionSets(e.from, e.to, parent, rank);
            }
        }

        for (Edge e : result) {
            obj.println(e.from + " " + e.to + " " + e.weight);
        }
        obj.println(totalWeight);
    }

    private void dijkstra(int source) {
        long[] d = new long[this.numVertices + 1];
        int[] p = new int[this.numVertices + 1];
        Arrays.fill(d, Long.MAX_VALUE);
        Arrays.fill(p, -1);

        d[source] = 0;
        PriorityQueue<long[]> pq = new PriorityQueue<>(Comparator.comparingLong(a -> a[0]));
        pq.add(new long[] { 0, source });

        boolean[] visited = new boolean[this.numVertices + 1];
        Arrays.fill(visited, false);

        while (!pq.isEmpty()) {
            long[] e = pq.poll();
            int v = (int) e[1];
            long dV = e[0];

            if (dV != d[v])
                continue;

            for (Edge edge : this.adjList.get(v)) {
                if (d[v] != Long.MAX_VALUE && d[v] + edge.weight < d[edge.to]) {
                    d[edge.to] = d[v] + (long) edge.weight;
                    p[edge.to] = v;
                    pq.add(new long[] { d[edge.to], edge.to });
                }
            }
        }

        int n = this.numVertices;
        if (d[n] == Long.MAX_VALUE) {
            obj.println("-1");
        } else {
            List<Integer> path = new ArrayList<Integer>();
            int current = n;
            while (current != -1) {
                path.add(current);
                current = p[current];
            }

            for (int i = path.size() - 1; i >= 0; i--) {
                obj.print(path.get(i) + " ");
            }
            obj.println();
        }
    }

    private void solve() {
        for (int i = 0; i < this.numEdges; ++i) {
            int u = obj.nextInt();
            int v = obj.nextInt();
            long w = obj.nextLong();

            this.addEdge(u, v, w);
        }
        this.dijkstra(1);
    }

    public void close() {
        obj.close();
    }
}