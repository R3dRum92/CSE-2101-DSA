import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.InputMismatchException;
import java.util.LinkedList;
import java.util.List;
import java.util.Stack;
 
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
    private List<List<Integer>> adj;
    private List<List<Integer>> backEdge;
    private int numVertices;
    private int numEdges;
    FastIO sc;
    private int[] in;
 
    Graph() throws IOException {
        adj = new ArrayList<>();
        backEdge = new ArrayList<>();
        sc = new FastIO();
        this.numVertices = sc.nextInt();
        this.numEdges = sc.nextInt();
        in = new int[this.numVertices];
 
        for (int i = 0; i < this.numVertices; ++i) {
            this.addVertex();
            backEdge.add(new LinkedList<Integer>());
            in[i] = 0;
        }
 
        for (int i = 0; i < this.numEdges; ++i) {
            int u = sc.nextInt();
            int v = sc.nextInt();
 
            u--;
            v--;
 
            this.addEdge(u, v);
            this.backEdge.get(v).add(u);
        }
 
        this.DFSInitialization(0);
 
        sc.close();
    }
 
    private void addVertex() {
        this.adj.add(new LinkedList<Integer>());
    }
 
    private void addEdge(int u, int v) {
        this.adj.get(u).add(v);
    }
 
    public void DFSInitialization(int source) {
        boolean[] visited = new boolean[this.numVertices];
        List<Integer> topo = new ArrayList<Integer>();
        Arrays.fill(visited, false);
        for (int i = 0; i < this.numVertices; ++i) {
            if (!visited[i])
                DFSVisit(i, visited, topo);
        }
 
        int[] dist = new int[this.numVertices];
        int[] prev = new int[this.numVertices];
 
        Arrays.fill(dist, Integer.MIN_VALUE);
        Arrays.fill(prev, -1);
 
        dist[0] = 1;
 
        for (int i = topo.size() - 1; i >= 0; --i) {
            int b = topo.get(i);
            for (int par : backEdge.get(b)) {
                if (dist[par] + 1 > dist[b]) {
                    dist[b] = dist[par] + 1;
                    prev[b] = par;
                }
            }
        }
 
        if (dist[this.numVertices - 1] < 0) {
            sc.println("IMPOSSIBLE");
        } else {
            sc.println(dist[this.numVertices - 1]);
            Stack<Integer> ans = new Stack<>();
            int cur = this.numVertices - 1;
            while (cur != -1) {
                ans.push(cur);
                cur = prev[cur];
            }
 
            while (!ans.isEmpty()) {
                sc.print(ans.pop() + 1 + " ");
            }
            sc.println();
        }
    }
 
    private void DFSVisit(int vertex, boolean[] visited, List<Integer> topo) {
        visited[vertex] = true;
        for (int v : adj.get(vertex)) {
            if (!visited[v]) {
                DFSVisit(v, visited, topo);
            }
        }
 
        topo.add(vertex);
    }
}
 
public class Main {
    public static void main(String[] args) throws IOException {
        Graph g = new Graph();
    }
}
