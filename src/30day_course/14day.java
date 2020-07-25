import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;


class Difference {
  	private int[] elements;
  	public int maximumDifference;

  /**
   * Constructor
   * @param inputs integer array entered from stdin
   */
	Difference(
    int[] inputs
  )
  {
    this.elements = inputs;
  }

  /**
   * calculate maximun ABS
   * @param void -
   * @return void -
   */
  public void computeDifference(
  )
  {
    int tmpMax = 0;

    if (this.elements.length > 0) {
      for (int i = 0; i < this.elements.length- 1; i++) {
        for (int j = i + 1; j < this.elements.length; j++) {
          int tmp = Math.abs(this.elements[i] - this.elements[j]);
          if (tmp > tmpMax) {
            tmpMax = tmp;
          }
        }
      }
      this.maximumDifference = tmpMax;
    }
    else {
      this.maximumDifference = 0;
    }

  }

}

public class Solution {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = sc.nextInt();
        }
        sc.close();

        Difference difference = new Difference(a);

        difference.computeDifference();

        System.out.print(difference.maximumDifference);
    }
}
