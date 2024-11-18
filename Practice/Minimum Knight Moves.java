import java.util.Scanner;
import java.util.Queue;
import java.util.LinkedList;

class KnightMove {
    static int[][] board = new int[8][8];
    static int[] dx = {2, 2, -2, -2, 1, 1, -1, -1};
    static int[] dy = {1, -1, 1, -1, 2, -2, 2, -2};

    public static int minKnightMoves(String start, String end) {
        int sx = start.charAt(0) - 'a';
        int sy = start.charAt(1) - '1';
        int ex = end.charAt(0) - 'a';
        int ey = end.charAt(1) - '1';

        if (sx == ex && sy == ey) {
            return 0;
        }

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                board[i][j] = -1;
            }
        }

        Queue<Pair> q = new LinkedList<>();
        q.add(new Pair(sx, sy, 0));
        board[sx][sy] = 0;

        while (!q.isEmpty()) {
            Pair p = q.poll();
            int x = p.x;
            int y = p.y;
            int dist = p.dist;

            for (int i = 0; i < 8; i++) {
                int newX = x + dx[i];
                int newY = y + dy[i];
                if (isValid(newX, newY) && board[newX][newY] == -1) {
                    board[newX][newY] = dist + 1;
                    q.add(new Pair(newX, newY, dist + 1));
                }
            }
        }

        return board[ex][ey];
    }

    public static boolean isValid(int x, int y) {
        return x >= 0 && x < 8 && y >= 0 && y < 8;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();

        while (t-- > 0) {
            String start = sc.next();
            String end = sc.next();
            int minMoves = minKnightMoves(start, end);
            System.out.println(minMoves);
        }
    }

    static class Pair {
        int x, y, dist;

        public Pair(int x, int y, int dist) {
            this.x = x;
            this.y = y;
            this.dist = dist;
        }
    }
}
