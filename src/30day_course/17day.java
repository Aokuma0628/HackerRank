import java.util.*;
import java.io.*;

//Write your code here
class Calculator {
  /**
   * Constructor(void)
   * @param void
   */
  Calculator() {
    ;
  }

  /**
   * Powering the number
   * @param number Powering target
   * @param power  Powering value
   * @return Powering the number
   */
   public int power (
    int number,
    int power
   ) throws Exception
   {
     int answer;
     if (number < 0 || power < 0) {
       throw new Exception("n and p should be non-negative");
     }

     answer = (int) Math.pow(number, power);
     return answer;
   }
}

class Solution{

    public static void main(String[] args) {

        Scanner in = new Scanner(System.in);
        int t = in.nextInt();
        while (t-- > 0) {

            int n = in.nextInt();
            int p = in.nextInt();
            Calculator myCalculator = new Calculator();
            try {
                int ans = myCalculator.power(n, p);
                System.out.println(ans);
            }
            catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }
        in.close();
    }
}
