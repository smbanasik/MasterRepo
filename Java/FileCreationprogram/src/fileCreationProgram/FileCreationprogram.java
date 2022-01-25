package fileCreationProgram;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class FileCreationprogram {

	public static void main(String[] args) {
	
		// Try method, if error is thrown it's caught
		try {
			
			// Create output file object with name testingFile
			
			File outputFile = new File("testingFile.txt");
			
			// Check if file was created
			
			if (outputFile.createNewFile()) {
				
				// State that file was created
				
				System.out.println("Create the file: " + outputFile.getName());
				
				// Create object to write to file for the outputFile
				
				FileWriter outputFileWriter = new FileWriter(outputFile.getName());
				
				// Close the file
				
				outputFileWriter.write("This is the first line. ");
				outputFileWriter.write("Is this the second line?");
				
				outputFileWriter.write("\nIt was not the second line. This tho? Absolutely.");
				
				outputFileWriter.close();
			
			} else {
				
				// if unable to create file it must already exist
				
				System.out.println("File already exists!");
				
				Scanner outputFileReader = new Scanner(outputFile);
				
				while(outputFileReader.hasNextLine()) {
					
					String outputFileContent = outputFileReader.nextLine();
					System.out.println(outputFileContent);
				}
				
				outputFileReader.close();
				
			}
			
		// Catch method. States that there's an error and to print the stack trace
		} catch (IOException error) {
			
			System.out.println("Uh oh error! File can't be created!");
			error.printStackTrace();
			
		}
		
	}
}
