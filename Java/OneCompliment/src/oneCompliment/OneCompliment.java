package oneCompliment;
import java.util.*;

public class OneCompliment {

	    public static void main(String[] args) {
	        // Get input of int
	        Scanner userInput = new Scanner(System.in);
	        
	        int userInt = userInput.nextInt();
	        String binaryNum;
	        int complimentInt;
	        char[] binaryArray;
	        
	        // Convert int to binary
	        // Looking at java int doc there's a toBinaryString method
	        
	        binaryNum = Integer.toBinaryString(userInt);
	        
	        // Convert string into array of characters
        	binaryArray = binaryNum.toCharArray();
	        
	        //Iterate through the binary string and if it finds a 0, convert to 1, vice versa
	        
	        for(int i = 0; i < binaryArray.length; i++) {
	            
	        	// Make sure that the char array is comparing '0's and '1's instead of integers
	        	
	            if(binaryArray[i] == '0') {
	            
	                // binaryNum.charAt(i) = 1 is what I first attempted
	                // However the left hand side of the argument must be a variable
	                // This means that this string is not changeable.
	                // I found a toCharArray function in the string docs, attempting that
	            	
	            	binaryArray[i] = '1';
	            
	            } else {
	            
	            	binaryArray[i] = '0';
	            
	            }//end if
	            
	            
	        }//end for
	        
	        String complimentNum = new String(binaryArray);
	        
	        // Convert compliment into int
	        // Looking at doc for int, parseInt might help
	        
	        complimentInt = Integer.parseInt(complimentNum, 2);
	        
	        
	        System.out.println(complimentInt);
	        userInput.close();
	    }
}
