package MinMaxExclude20;

import java.util.Random;
import java.util.stream.IntStream;
import java.util.IntSummaryStatistics;

public class MinMaxAvgOfClass {
  public static void main(String[] args) {
    Random random = new Random(12345);
    // Input into usable format
    IntStream studentScoresRaw = random.ints(72, 50, 100);
    int[] studentScoresUsable = studentScoresRaw.toArray();
      
    //Sort the list  
    for (int k = 1; k < studentScoresUsable.length; k++) {
        for(int i = 0; i < studentScoresUsable.length - k; i++) {
            
            if(studentScoresUsable[i] > studentScoresUsable[i+1]) {
                int temp = studentScoresUsable[i];
                studentScoresUsable[i] = studentScoresUsable[i+1];
                studentScoresUsable[i+1] = temp;
            }
        }
    }
    // Set top 10 to 0
    for (int i = 0; i < 10; i++) {
          
          studentScoresUsable[studentScoresUsable.length - (i+1)] = 0;
          
      }
      
    // Set bottom 10 to 0
      
      for (int i = 0; i < 10; i++) {
      
          studentScoresUsable[i] = 0;
          
      }
    
    // If element is not 0, copy to new array
      int[] studentScoresFin = new int [studentScoresUsable.length - 20];
      int studentScoresCount = 0;
      for (int i = 0; i < studentScoresUsable.length; i++) {
          if(studentScoresUsable[i] != 0) {
              
              studentScoresFin[studentScoresCount] = studentScoresUsable[i];
              studentScoresCount++;
          }
      }
          
    //Terminate with summary
    IntStream studentScoresFinal = IntStream.of(studentScoresFin);
    IntSummaryStatistics statistics = studentScoresFinal.summaryStatistics();
    
    System.out.printf("Max: %d Min: %d Avg: %.2f\n",
        statistics.getMax(),
        statistics.getMin(),
        statistics.getAverage());     
  }
}