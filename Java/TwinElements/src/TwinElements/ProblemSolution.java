package TwinElements;

import java.util.*;

public class ProblemSolution{
    public int solution(int A[]){
        // Write your code here
    	
        //A[] is our input array.
        int twinsCount = 0;
        int internalCount = 0;
        int[] previousNums = new int[A.length];
        boolean isRepeat = false; 
        
        for (int i = 0; i < A.length; i++) {
            
            internalCount = 0;
            isRepeat = false;
            
            for (int j = 0; j < A.length; j++) {
                
            	// If the current element matches any element in previous nums,
            	// the count is prevented. There should be no edge cases, but
            	// this is not certain.
            	if (A[i] == previousNums[j]) {
            		
            		isRepeat = true;
            		
            	}
            	
                if(isRepeat == false && A[i] == A[j]) {
                    // Increase internal count by one
                    internalCount++;
                    
                }// End if
                
            }// End for loop
            
            if(internalCount == 2) {
                // If internal count is 2, that means there's twins
                // and increase twins count
                twinsCount++;
                
            }// End if
            
            // Add the number into the previous number array.
            // This is used to skip previous nums
            
            previousNums[i] = A[i];
            
        }// End for loop
        
        return twinsCount;
    }
}
