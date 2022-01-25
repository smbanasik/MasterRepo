package darwinAward;


/** This class contains the solution method which handles finding
*   the winner of the darwin awards
*/
public class ProblemSolution {
    
    
    /** This is the method that loops through the given votes and looks for an id
    *   that contains over half of the votes. If the first one isn't found it moves
    *   on to the next one. If none are found then it returns -1.
    */
    public int solution(int[] votes, int N) {
	           
        int result = -2,
        currentValue = votes[0],
        currentIndex = 0,
        voteCount = 0;
        
        // Loop through array, if an index matches currentIndex, increase vote count
        // If the vote count is less than set currentIndex to next number
        
        while(result == -2) {
            
            // Reset the vote count
            
            voteCount = 0;
        
            // Loop through array and gather votes of first value
            
            for(int i = 0; i < N; i++) {

                if (votes[i] == currentValue) {

                    voteCount++;

                }// if

            }// for
            
            // Check if the current id won the competition
            
            if(voteCount > (N/2)) {
            
                result = currentValue;
            
                
            // If we're on the last value and it hasn't won, return -1
                
            } else if (currentValue == votes[N - 1] && voteCount <= (N/2)) {
            
                result = -1;
                
            // If we're not on the last value and it hasn't won, move value up by one
                
            } else {
                
                currentIndex++;
                
                currentValue = votes[currentIndex];
                
            }// if
        
        }//while
        
        return result;
        
    }
    
}
