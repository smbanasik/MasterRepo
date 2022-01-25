package darwinAward;
import java.util.*;

/** This class handles creating the votes and size of array,
*   creating an object from the problemSolution class, and using
*   it to output the winner result.
*/
public class DarwinAward {

    /** This method is what carries through the classes objectives
    */
    
    public static void main(String[] args) {
        
        // Creates new scanner, assigns N to input
        
        Scanner sc = new Scanner(System.in);        
        int N = sc.nextInt();
        
        // Sets result to 0, creates a new array to size of N
        
        int result = 0;
        int[] a = new int[N];
        
        // For the size of the array, assign input to array
        
        for (int i = 0; i < N; i++) {
            a[i] = sc.nextInt();
            
        }// for
        
        // Creats object problemSolution from ProblemSolution class
        // asigns value from solution function to result variable.
        
        ProblemSolution problemSolution = new ProblemSolution();        
        result = problemSolution.solution(a, N);        
        System.out.println(result);
        
        sc.close();
        
    }// main
}