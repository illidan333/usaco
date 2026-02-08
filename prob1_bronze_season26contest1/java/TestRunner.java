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
import java.util.Scanner;

public class TestRunner {
    private static List<String> runFile(Path file) throws IOException {
        List<String> outputs = new ArrayList<>();
        Scanner sc = new Scanner(Files.newBufferedReader(file));
        if (!sc.hasNextInt()) {
            sc.close();
            return outputs;
        }
        int t = sc.nextInt();
        for (int i = 0; i < t; i++) {
            long a = sc.nextLong();
            long b = sc.nextLong();
            long cA = sc.nextLong();
            long cB = sc.nextLong();
            long fA = sc.nextLong();
            outputs.add(Long.toString(Solution.solveCase(a, b, cA, cB, fA)));
        }
        sc.close();
        return outputs;
    }

    private static List<String> readExpected(Path file) throws IOException {
        List<String> outputs = new ArrayList<>();
        Scanner sc = new Scanner(Files.newBufferedReader(file));
        while (sc.hasNext()) {
            outputs.add(sc.next());
        }
        sc.close();
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

}
