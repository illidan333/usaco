import java.io.PrintWriter;
import java.util.Scanner;

public class Solution {
    public static long solveCase(long startA, long startB, long rateA, long rateB, long targetA) {
        long aAfterExchange = (startB / rateB) * rateA + startA;
        if (aAfterExchange >=  targetA) {
            return 0L;
        }

        long remainingA = targetA - aAfterExchange;
        long remainingABeforeFinal = remainingA - 1;
        long chipsToNextBIncrease = rateB - (startB % rateB);
        long totalChipsNeeded = chipsToNextBIncrease;

        if (rateA >= rateB) {
            totalChipsNeeded += remainingABeforeFinal;
        } else {
            totalChipsNeeded += (remainingABeforeFinal / rateA) * rateB + (remainingABeforeFinal % rateA);
        }

        return totalChipsNeeded;
    }

    public static void main(String[] args) {
        try (Scanner in = new Scanner(System.in); PrintWriter out = new PrintWriter(System.out)) {
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
}
