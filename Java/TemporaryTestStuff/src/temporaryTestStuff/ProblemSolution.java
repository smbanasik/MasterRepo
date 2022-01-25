package temporaryTestStuff;

import java.util.*;

public class ProblemSolution {
    public float solution(float N, float inputBalance, float newN) {
        float output;
        
        // Create savings account object.
        
        SavingsAccount savingsAccount = new SavingsAccount(inputBalance);
        
        // Modify interest rate with first given int
        
        SavingsAccount.modifyInterestRate(N);
        
        // Calculate the interest and print it out
        
        output = savingsAccount.calculateMonthlyInterest();
        System.out.println(output);
        
        // Set a new annual interest rate, then calculate interest and return it to print it out
        
        SavingsAccount.modifyInterestRate(newN);
        output = savingsAccount.calculateMonthlyInterest();
        
        
        return output;
    }
}
