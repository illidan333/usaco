import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.PrintWriter;

public class Solution {
    private static long solveCase(long a, long b, long cA, long cB, long fA) {
        long initialA = (b / cB) * cA + a;
        if (initialA >= fA) {
            return 0L;
        }

        long needA = fA - 1 - initialA;
        long y = cB - 1 - (b % cB);

        if (cA >= cB) {
            y += needA;
        } else {
            y += (needA / cA) * cB + (needA % cA);
        }

        return y + 1;
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner();
        PrintWriter out = new PrintWriter(System.out);
        int t = fs.nextInt();
        if (t == -1) {
            out.flush();
            return;
        }
        for (int i = 0; i < t; i++) {
            long a = fs.nextLong();
            long b = fs.nextLong();
            long cA = fs.nextLong();
            long cB = fs.nextLong();
            long fA = fs.nextLong();
            out.println(solveCase(a, b, cA, cB, fA));
        }
        out.flush();
    }

    private static class FastScanner {
        private final BufferedInputStream in = new BufferedInputStream(System.in);
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0;
        private int len = 0;

        private int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) {
                    return -1;
                }
            }
            return buffer[ptr++];
        }

        int nextInt() throws IOException {
            int c;
            do {
                c = read();
                if (c == -1) {
                    return -1;
                }
            } while (c <= ' ');
            int sign = 1;
            if (c == '-') {
                sign = -1;
                c = read();
            }
            int val = 0;
            while (c > ' ') {
                val = val * 10 + (c - '0');
                c = read();
            }
            return val * sign;
        }

        long nextLong() throws IOException {
            int c;
            do {
                c = read();
                if (c == -1) {
                    return -1L;
                }
            } while (c <= ' ');
            int sign = 1;
            if (c == '-') {
                sign = -1;
                c = read();
            }
            long val = 0;
            while (c > ' ') {
                val = val * 10 + (c - '0');
                c = read();
            }
            return val * sign;
        }
    }
}
