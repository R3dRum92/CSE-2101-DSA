import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Stack;
import java.util.Arrays;

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

class DIGOKEYS {
    private List<List<Integer>> adj;
    private int numVertices;
    FastIO sc;

    DIGOKEYS() {
        sc = new FastIO();
        int t = sc.nextInt();
        for (int i = 0; i < t; ++i) {
            adj = new ArrayList<>();
            this.solve();
        }
        sc.close();
    }

    private void addVertex() {
        this.adj.add(new LinkedList<Integer>());
    }

    private void addEdge(int u, int v) {
        adj.get(u).add(v);
    }

    public List<Integer> getAdjacent(int v) {
        return this.adj.get(v);
    }

    public void display() {
        for (int i = 0; i < numVertices; ++i) {
            System.out.print((i + 1) + ": ");
            for (int v : getAdjacent(i)) {
                System.out.print((v + 1) + ", ");
            }
            System.out.print("\n");
        }
    }

    public void solve() {
        this.numVertices = sc.nextInt();
        for (int i = 0; i < this.numVertices; ++i) {
            this.addVertex();
        }
        for (int i = 0; i < this.numVertices - 1; ++i) {
            int m = sc.nextInt();
            for (int j = 0; j < m; ++j) {
                int k = sc.nextInt();
                k--;
                this.addEdge(i, k);
            }
        }

        for (int i = 0; i < this.numVertices; ++i) {
            this.adj.get(i).sort(null);
        }

        int d[] = new int[this.numVertices];
        int prev[] = new int[this.numVertices];
        boolean visited[] = new boolean[this.numVertices];
        Arrays.fill(d, Integer.MAX_VALUE);
        Arrays.fill(prev, -1);
        Arrays.fill(visited, false);

        BFS(0, d, prev, visited);
        if (d[this.numVertices - 1] == Integer.MAX_VALUE) {
            sc.println(-1);
        } else {
            sc.println(d[this.numVertices - 1]);
            int cur = prev[this.numVertices - 1];
            Stack<Integer> ans = new Stack<>();
            while (cur != -1) {
                ans.push(cur);
                cur = prev[cur];
            }

            while (!ans.isEmpty()) {
                sc.print(ans.pop() + 1 + " ");
            }
            sc.println();
        }
        sc.println();
    }

    private void BFS(int source, int[] d, int[] prev, boolean[] visited) {
        d[source] = 0;
        visited[source] = true;
        Queue<Integer> q = new LinkedList<>();
        q.add(source);

        while (!q.isEmpty()) {
            int u = q.poll();

            for (int v : adj.get(u)) {
                if (!visited[v]) {
                    d[v] = d[u] + 1;
                    prev[v] = u;
                    visited[v] = true;
                    q.add(v);
                }
            }
        }
    }
}

public class Main {
    public static void main(String[] args) {
        DIGOKEYS d = new DIGOKEYS();
    }
}
