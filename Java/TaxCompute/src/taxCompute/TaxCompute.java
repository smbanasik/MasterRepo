package taxCompute;


import java.util.Scanner;

enum Status {
    SINGLE,
    MARRIEDJOINT,
    MARRIEDSEP,
    HEADOFHOUSE
}

public class TaxCompute {
  
  /** This function performs the math needed in the calculateTax
  *   function. It compares to see if the income is less than or
  *   greater than the taxNumber, and calculates the partial total
  *   of the tax accordingly.
  */
  public static double[] partialTaxCalc(double income, double taxNumber, double taxRate, double previousTaxNumber) {
      double tax = 0.0;
      
      // Everything is included so just add all of the income to the tax
      
      if (income <= taxNumber - (previousTaxNumber)) {
          
          tax += income * taxRate;
          income = 0;
          
      // Total income not included, so take the amount in bracket out
      // Then add whole bracket amount to total tax
          
      } else {

          income -= (taxNumber - previousTaxNumber);
          tax += ((taxNumber - previousTaxNumber) * taxRate);
      
      } // else
      
      previousTaxNumber = taxNumber;
      
      /** We need this function so we don't have to repeat this math on every
      *   single tax bracket for every single status. However, java does not
      *   support pass by reference like C++, and we need to export both the
      *   double tax and the double income, preferably without making a class.
      *   Solution: make an array, store both values, export the array,
      *   reassign values 
      */
      
      double[] outputArray = {tax, income, previousTaxNumber};
      
      return outputArray;
      
  } // patialTaxCalc
    
  public static double calculateTax(double income, int status) {
    double tax = 0.0, previousTaxNumber = 0.0;
    double[] outputArray = new double[3];
    double[] taxRateArray = 			{0.1, 0.15, 0.25, 0.28, 0.33, 0.35};
    double[] statusSingleTaxNum = 		{8350, 33950, 82250, 171550, 372950, 372951};
    double[] statusMarriedJointTaxNum = {16700, 67900, 137050, 208850, 372950, 372951};
    double[] statusMarriedSepTaxNum =   {8350, 33950, 68525, 104425, 186475, 186476};
    double[] statusHeadOfHouse = 		{11950, 45500, 117450, 190200, 372950, 372951};
    Status taxStatus = Status.values()[status];
      
    switch(taxStatus) {
    
        case SINGLE:
               
        	for(int i = 0; i < taxRateArray.length; i++) {
	        	
	            outputArray = partialTaxCalc(income, statusSingleTaxNum[i], taxRateArray[i], previousTaxNumber);
	            tax += outputArray[0];
	            income = outputArray[1];
	            previousTaxNumber = outputArray[2];

        	}
            break;
        case MARRIEDJOINT:
        	for(int i = 0; i < taxRateArray.length; i++) {
	        	
	            outputArray = partialTaxCalc(income, statusMarriedJointTaxNum[i], taxRateArray[i], previousTaxNumber);
	            tax += outputArray[0];
	            income = outputArray[1];
	            previousTaxNumber = outputArray[2];

        	}
            break;
        case MARRIEDSEP:
        	for(int i = 0; i < taxRateArray.length; i++) {
	        	
	            outputArray = partialTaxCalc(income, statusMarriedSepTaxNum[i], taxRateArray[i], previousTaxNumber);
	            tax += outputArray[0];
	            income = outputArray[1];
	            previousTaxNumber = outputArray[2];

        	}
            break;
        case HEADOFHOUSE:
        	for(int i = 0; i < taxRateArray.length; i++) {
	        	
	            outputArray = partialTaxCalc(income, statusHeadOfHouse[i], taxRateArray[i], previousTaxNumber);
	            tax += outputArray[0];
	            income = outputArray[1];
	            previousTaxNumber = outputArray[2];

        	}
            break;
    
    }
    
    
    return tax;
  }
  public static void main(String[] args) {
    // Create a Scanner
    Scanner input = new Scanner(System.in);

    // Prompt the user to enter filing statusT
    System.out.print(
      "(0-single filer, 1-married jointly or qualifying widow(er), "
      + "\n2-married separately, 3-head of household)\n" +
      "Enter the filing status: ");
    int status = input.nextInt();

    // Prompt the user to enter taxable income
    System.out.print("Enter the taxable income: ");
    double income = input.nextDouble();

    // Compute tax
    double tax = 0;

    if (status >= 0 && status <=3 ) { // Compute tax for single filers
      tax = calculateTax(income, status);
    } else {
      System.out.println("Error: invalid status");
      System.exit(1);
    }

    // Display the result
    System.out.println("Tax is " + (int)(tax * 100) / 100.0);
    input.close();
  }
}
