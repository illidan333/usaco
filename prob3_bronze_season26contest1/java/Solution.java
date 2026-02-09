import java.io.BufferedInputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Solution {
    public static List<Long> solveAll(int n, int k, List<Update> updates) {
        int size = n - k + 1;
        long[][] squareSum = new long[size][size];
        long[][] grid = new long[n][n];

        long maxSum = 0;
        List<Long> outputs = new ArrayList<>(updates.size());

        for (Update update : updates) {
            int r = update.r;
            int c = update.c;
            long v = update.v;
            long delta = v - grid[r][c];
            grid[r][c] = v;

            int rStart = Math.max(0, r - k + 1);
            int rEnd = Math.min(r, n - k);
            int cStart = Math.max(0, c - k + 1);
            int cEnd = Math.min(c, n - k);

            for (int i = rStart; i <= rEnd; i++) {
                for (int j = cStart; j <= cEnd; j++) {
                    long newSum = (squareSum[i][j] += delta);
                    if (newSum > maxSum) {
                        maxSum = newSum;
                    }
                }
            }
            outputs.add(maxSum);
        }

        return outputs;
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner();
        Integer nObj = fs.nextInt();
        if (nObj == null) {
            return;
        }
        int n = nObj;
        int k = fs.nextInt();
        int q = fs.nextInt();
        List<Update> updates = new ArrayList<>(q);
        for (int i = 0; i < q; i++) {
            int r = fs.nextInt() - 1;
            int c = fs.nextInt() - 1;
            long v = fs.nextLong();
            updates.add(new Update(r, c, v));
        }

        StringBuilder sb = new StringBuilder();
        for (long value : solveAll(n, k, updates)) {
            sb.append(value).append('\n');
        }
        System.out.print(sb);
    }

    public static class Update {
        public final int r;
        public final int c;
        public final long v;

        public Update(int r, int c, long v) {
            this.r = r;
            this.c = c;
            this.v = v;
        }
    }

    private static class FastScanner {
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0;
        private int len = 0;

        private int read() throws IOException {
            if (ptr >= len) {
                len = System.in.read(buffer);
                ptr = 0;
                if (len <= 0) {
                    return -1;
                }
            }
            return buffer[ptr++];
        }

        Integer nextInt() throws IOException {
            int c;
            do {
                c = read();
                if (c == -1) {
                    return null;
                }
            } while (c <= ' ');
            int sign = 1;
            if (c == '-') {
                sign = -1;
                c = read();
            }
            int value = 0;
            while (c > ' ') {
                value = value * 10 + (c - '0');
                c = read();
            }
            return value * sign;
        }

        long nextLong() throws IOException {
            int c;
            do {
                c = read();
            } while (c <= ' ');
            int sign = 1;
            if (c == '-') {
                sign = -1;
                c = read();
            }
            long value = 0;
            while (c > ' ') {
                value = value * 10 + (c - '0');
                c = read();
            }
            return value * sign;
        }
    }
}
