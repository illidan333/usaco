import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.URISyntaxException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Collections;
import java.util.List;

public class TestRunner {
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
            outputs.add(Long.toString(Solution.solveCase(a, b, cA, cB, fA)));
        }
        return outputs;
    }

    private static List<String> readExpected(Path file) throws IOException {
        FastScanner fs = new FastScanner(file);
        List<String> outputs = new ArrayList<>();
        String token;
        while ((token = fs.nextToken()) != null) {
            outputs.add(token);
        }
        return outputs;
    }

    private static Path getBaseDir() throws URISyntaxException {
        Path location = Paths.get(TestRunner.class.getProtectionDomain()
                .getCodeSource().getLocation().toURI());
        if (Files.isRegularFile(location)) {
            return location.getParent();
        }
        return location;
    }

    public static void main(String[] args) throws Exception {
        Path baseDir = getBaseDir();
        Path testDir = baseDir.resolve("..").resolve("testData").normalize();
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
        Collections.sort(files, new Comparator<Path>() {
            @Override
            public int compare(Path a, Path b) {
                String aName = a.getFileName().toString();
                String bName = b.getFileName().toString();
                if (aName.length() != bName.length()) {
                    return Integer.compare(aName.length(), bName.length());
                }
                return aName.compareTo(bName);
            }
        });

        PrintWriter out = new PrintWriter(System.out);
        for (Path p : files) {
            Path outPath = testDir.resolve(p.getFileName().toString().replace(".in", ".out"));
            List<String> outputs = runFile(p);
            boolean hasExpected = Files.exists(outPath);
            List<String> expected = hasExpected ? readExpected(outPath) : new ArrayList<>();

            String status;
            if (!hasExpected) {
                status = "MISSING .out";
            } else if (outputs.equals(expected)) {
                status = "PASS";
            } else {
                status = "FAIL";
            }

            out.println(p.getFileName() + ": " + status);
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

        String nextToken() throws IOException {
            int c;
            do {
                c = read();
                if (c == -1) {
                    return null;
                }
            } while (c <= ' ');
            StringBuilder sb = new StringBuilder();
            while (c > ' ') {
                sb.append((char) c);
                c = read();
            }
            return sb.toString();
        }
    }
}
