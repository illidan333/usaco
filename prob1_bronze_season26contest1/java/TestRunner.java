import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class TestRunner {
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

    private static List<String> runFile(Path file) throws IOException {
        FastScanner fs = new FastScanner(file);
        int t = fs.nextInt();
        List<String> outputs = new ArrayList<>();
        if (t == -1) {
            return outputs;
        }
        for (int i = 0; i < t; i++) {
            long a = fs.nextLong();
            long b = fs.nextLong();
            long cA = fs.nextLong();
            long cB = fs.nextLong();
            long fA = fs.nextLong();
            outputs.add(Long.toString(solveCase(a, b, cA, cB, fA)));
        }
        return outputs;
    }

    public static void main(String[] args) throws Exception {
        Path testDir = Paths.get("..", "testData").normalize();
        if (!Files.isDirectory(testDir)) {
            System.out.println("testData folder not found: " + testDir.toAbsolutePath());
            return;
        }

        List<Path> files = new ArrayList<>();
        try (DirectoryStream<Path> stream = Files.newDirectoryStream(testDir, "*.in")) {
            for (Path p : stream) {
                files.add(p);
            }
        }
        files.sort(Comparator.comparingInt(p -> p.getFileName().toString().length())
                .thenComparing(p -> p.getFileName().toString()));

        PrintWriter out = new PrintWriter(System.out);
        for (Path p : files) {
            out.println(p.getFileName() + ":");
            for (String line : runFile(p)) {
                out.println(line);
            }
            out.println("-");
        }
        out.flush();
    }

    private static class FastScanner {
        private final BufferedInputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0;
        private int len = 0;

        FastScanner(Path path) throws IOException {
            in = new BufferedInputStream(Files.newInputStream(path));
        }

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
