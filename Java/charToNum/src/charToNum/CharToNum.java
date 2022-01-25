package charToNum;
import java.util.Scanner;

public class CharToNum {

	public static void main(String[] args) {
		
        // Create input object
		
		Scanner userInput = new Scanner(System.in);
		
        // Java has no method for finding characters.
        // What we need to do is find a way to get characters in
        // Using nextLine to bring in a string and then getting the 1st character of it works
        // for most things, but it does not work for new line characters.
        
        //https://docs.oracle.com/en/java/javase/16/docs/api/java.base/java/util/Scanner.html
        //https://docs.oracle.com/javase/8/docs/api/java/util/regex/Pattern.html
        
        // We can use a delimiter set to \\B to solve this
        
        userInput.useDelimiter("\\B");
        
        // Use the userInput next for a string, then get the first character
		
		char inputChar = userInput.next().charAt(0);
		
		// Cast inputChar into an integer and print value
		
		int ascii = inputChar;
		
		System.out.println(ascii);
		
		userInput.close();

	}

}
