import java.io.PrintWriter;
import java.util.Scanner;

public class Solution {
    public static long solveCase(long startA, long startB, long rateA, long rateB, long targetA) {
        long initialA = (startB / rateB) * rateA + startA;
        if (initialA >= targetA) {
            return 0L;
        }

        long needA = targetA - 1 - initialA;
        long y = rateB - 1 - (startB % rateB);

        if (rateA >= rateB) {
            y += needA;
        } else {
            y += (needA / rateA) * rateB + (needA % rateA);
        }

        return y + 1;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);
        if (!in.hasNextInt()) {
            out.flush();
            return;
        }
        int testCases = in.nextInt();
        for (int i = 0; i < testCases; i++) {
            long startA = in.nextLong();
            long startB = in.nextLong();
            long rateA = in.nextLong();
            long rateB = in.nextLong();
            long targetA = in.nextLong();
            out.println(solveCase(startA, startB, rateA, rateB, targetA));
        }
        out.flush();
    }
}
