package TwinElements;

import java.util.*;

public class DriverMain {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int N = s.nextInt();
        int A[] = new int[N];
        for (int i = 0; i < N; i++) {
            A[i] = s.nextInt();
        }
        ProblemSolution problemSolution = new ProblemSolution();
        System.out.print(problemSolution.solution(A));
    }
}