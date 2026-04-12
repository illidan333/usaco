import java.io.IOException;
import java.io.PrintWriter;
import java.net.URISyntaxException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Locale;
import java.util.Scanner;

public class TestRunner {
    private static List<String> runFile(Path file) throws IOException {
        List<String> outputs = new ArrayList<>();
        try (Scanner sc = new Scanner(Files.newBufferedReader(file))) {
            if (!sc.hasNextInt()) {
                return outputs;
            }
            int n = sc.nextInt();
            int k = sc.nextInt();
            int q = sc.nextInt();
            List<Solution.Update> updates = new ArrayList<>(q);
            for (int i = 0; i < q; i++) {
                int r = sc.nextInt() - 1;
                int c = sc.nextInt() - 1;
                long v = sc.nextLong();
                updates.add(new Solution.Update(r, c, v));
            }
            for (long value : Solution.solveAll(n, k, updates)) {
                outputs.add(Long.toString(value));
            }
        }
        return outputs;
    }

    private static List<String> readExpected(Path file) throws IOException {
        List<String> outputs = new ArrayList<>();
        try (Scanner sc = new Scanner(Files.newBufferedReader(file))) {
            while (sc.hasNext()) {
                outputs.add(sc.next());
            }
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

    private static Path findTestDir() throws URISyntaxException {
        Path cwd = Paths.get(System.getProperty("user.dir"));
        Path testDir = cwd.resolve("testData");
        if (Files.isDirectory(testDir)) {
            return testDir;
        }
        Path baseDir = getBaseDir();
        return baseDir.resolve("..").resolve("testData").normalize();
    }

    public static void main(String[] args) throws Exception {
        Path testDir = findTestDir();
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
        long totalStart = System.nanoTime();
        for (Path p : files) {
            Path outPath = testDir.resolve(p.getFileName().toString().replace(".in", ".out"));
            long caseStart = System.nanoTime();
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

            double elapsedMs = (System.nanoTime() - caseStart) / 1_000_000.0;
            out.println(p.getFileName() + ": " + status + String.format(Locale.US, " (%.2f ms)", elapsedMs));
        }
        double totalMs = (System.nanoTime() - totalStart) / 1_000_000.0;
        out.println(String.format(Locale.US, "Total: %.2f ms", totalMs));
        out.flush();
    }
}
