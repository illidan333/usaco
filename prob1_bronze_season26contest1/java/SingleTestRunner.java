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

    private static long[] parseSingleCase(List<Long> values) {
        if (values.size() == 5) {
            return new long[]{values.get(0), values.get(1), values.get(2), values.get(3), values.get(4)};
        }
        if (values.size() >= 6) {
            long t = values.get(0);
            if (t <= 0) {
                throw new IllegalArgumentException("T must be positive when provided");
            }
            return new long[]{values.get(1), values.get(2), values.get(3), values.get(4), values.get(5)};
        }
        throw new IllegalArgumentException("Expected 5 numbers or T followed by 5 numbers");
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
                System.out.println("Create it and paste numbers like: 2 3 1 1 6");
            }
            return;
        }

        List<Long> values = readNumbers(path);
        if (values.isEmpty()) {
            System.out.println("Input file is empty: " + path.toAbsolutePath());
            return;
        }

        long[] argsCase = parseSingleCase(values);
        long result = Solution.solveCase(argsCase[0], argsCase[1], argsCase[2], argsCase[3], argsCase[4]);
        System.out.println(result);
    }
}
