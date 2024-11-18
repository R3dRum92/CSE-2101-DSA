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

    public double nextDouble() {
        return Double.parseDouble(next());
    }

}

class WeightedGraph {
    private FastIO obj;
    private int n;
    private int m;
    private int k;
    private int parentI;
    private int parentJ;
    private int sum;
    Pair[][] parent;

    private static class Pair {
        int first, second;

        Pair(int first, int second) {
            this.first = first;
            this.second = second;
        }
    }

    public WeightedGraph() {
        this.obj = new FastIO();
        this.solve();
    }

    private void solve() {
        n = obj.nextInt();
        m = obj.nextInt();
        k = obj.nextInt();

        char[][] arr = new char[n][m];
        boolean[][] visited = new boolean[n][m];
        this.parent = new Pair[n][m];
        int[][] picture = new int[n][m];

        for (int i = 0; i < n; ++i) {
            String s = obj.next();
            for (int j = 0; j < m; ++j) {
                arr[i][j] = s.charAt(j);
                visited[i][j] = false;
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (arr[i][j] == '.' && !visited[i][j]) {
                    parentI = i;
                    parentJ = j;
                    sum = 0;
                    DFS(i, j, visited, arr);
                    picture[i][j] = sum;

                }
            }
        }

        for (int i = 0; i < k; ++i) {
            int x = obj.nextInt();
            int y = obj.nextInt();

            obj.println(picture[parent[x - 1][y - 1].first][parent[x - 1][y - 1].second]);
        }

    }

    private void DFS(int i, int j, boolean[][] visited, char[][] arr) {
        visited[i][j] = true;
        parent[i][j] = new Pair(parentI, parentJ);
        if (arr[i - 1][j] == '*')
            sum++;
        if (arr[i + 1][j] == '*')
            sum++;
        if (arr[i][j - 1] == '*')
            sum++;
        if (arr[i][j + 1] == '*')
            sum++;

        // right
        if (arr[i][j + 1] == '.') {
            if (!visited[i][j + 1]) {
                DFS(i, j + 1, visited, arr);
            }
        }
        // down
        if (arr[i + 1][j] == '.') {
            if (!visited[i + 1][j]) {
                DFS(i + 1, j, visited, arr);
            }
        }
        // left
        if (arr[i][j - 1] == '.' && !visited[i][j - 1]) {
            DFS(i, j - 1, visited, arr);
        }
        // up
        if (arr[i - 1][j] == '.' && !visited[i - 1][j]) {
            DFS(i - 1, j, visited, arr);
        }
    }

    public void close() {
        obj.close();
    }
}
