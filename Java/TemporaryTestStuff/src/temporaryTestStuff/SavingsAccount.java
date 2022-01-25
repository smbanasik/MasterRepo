package temporaryTestStuff;

public class SavingsAccount {

    // Two variables needed
    
    public static float annualInterestRate;
    private float savingsBalance;
    
    // Constructor to set savingsBalance to input
    
    public SavingsAccount(float inputSavingsBalance) {
    
        savingsBalance = inputSavingsBalance;
    
    }
    
    // Calculate the monthly interest using equation
    // Send output as return for displaying to console
    
    float calculateMonthlyInterest() {
        
        savingsBalance = savingsBalance + (savingsBalance * annualInterestRate / 12);
        
        float output = savingsBalance;
        
        return output;
    }
    
    // Set interest rates
    
    static void modifyInterestRate(float newInterestRate) {
        
        annualInterestRate = newInterestRate;
        
    }
    

}