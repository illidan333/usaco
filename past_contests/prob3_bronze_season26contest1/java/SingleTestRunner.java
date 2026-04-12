import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class SingleTestRunner {
    private static List<Long> readNumbers(Path path) throws Exception {
        List<Long> values = new ArrayList<>();
        try (Scanner sc = new Scanner(Files.newBufferedReader(path))) {
            while (sc.hasNextLong()) {
                values.add(sc.nextLong());
            }
        }
        return values;
    }

    private static Path findDefaultPath() {
        Path cwd = Paths.get(System.getProperty("user.dir"));
        Path inJavaFolder = cwd.resolve("java").resolve("single_test_input.txt");
        if (Files.isRegularFile(inJavaFolder)) {
            return inJavaFolder;
        }
        return Paths.get("single_test_input.txt");
    }

    public static void main(String[] args) throws Exception {
        Path defaultPath = findDefaultPath();
        Path path = args.length > 0 ? Paths.get(args[0]) : defaultPath;
        if (!Files.isRegularFile(path)) {
            System.out.println("Input file not found: " + path.toAbsolutePath());
            if (path.equals(defaultPath)) {
                System.out.println("Create it and paste input like: 4 2 3 2 2 11 3 4 3 3 1 100");
            }
            return;
        }

        List<Long> values = readNumbers(path);
        if (values.size() < 5) {
            System.out.println("Input file does not contain enough values: " + path.toAbsolutePath());
            return;
        }

        int n = values.get(0).intValue();
        int k = values.get(1).intValue();

        List<Solution.Update> updates = new ArrayList<>();
        if (values.size() >= 3) {
            long q = values.get(2);
            long expected = 3 + q * 3;
            if (values.size() == expected) {
                int idx = 3;
                for (long i = 0; i < q; i++) {
                    int r = values.get(idx++).intValue() - 1;
                    int c = values.get(idx++).intValue() - 1;
                    long v = values.get(idx++);
                    updates.add(new Solution.Update(r, c, v));
                }
            } else if ((values.size() - 2) % 3 == 0) {
                long inferred = (values.size() - 2) / 3;
                int idx = 2;
                for (long i = 0; i < inferred; i++) {
                    int r = values.get(idx++).intValue() - 1;
                    int c = values.get(idx++).intValue() - 1;
                    long v = values.get(idx++);
                    updates.add(new Solution.Update(r, c, v));
                }
            } else {
                System.out.println("Input does not match expected format (N K Q followed by Q updates).");
                return;
            }
        }

        List<Long> outputs = Solution.solveAll(n, k, updates);
        StringBuilder sb = new StringBuilder();
        for (long value : outputs) {
            sb.append(value).append('\n');
        }
        System.out.print(sb);
    }
}
