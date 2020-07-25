import java.util.*;

class Person {
	protected String firstName;
	protected String lastName;
	protected int    idNumber;

	// Constructor
	Person(String firstName, String lastName, int identification){
		this.firstName = firstName;
		this.lastName = lastName;
		this.idNumber = identification;
	}

	// Print person data
	public void printPerson(){
		 System.out.println(
				"Name: " + lastName + ", " + firstName
			+ 	"\nID: " + idNumber);
	}

}


class Student extends Person{
	private int[] testScores;

    /**
    *   Class Constructor
    *
    *   @param firstName - A string denoting the Person's first name.
    *   @param lastName - A string denoting the Person's last name.
    *   @param id - An integer denoting the Person's ID number.
    *   @param scores - An array of integers denoting the Person's test scores.
    */
    public Student(
      String firstName,
      String LastName,
      int    id,
      int[]  scores
    )
    {
      super(firstName, LastName, id);
      this.testScores = scores;
    }

    /**
    *   Method Name: calculate
    *   @return A character denoting the grade.
    */
    public char calculate () {
      int sum = 0;
      int ave;
      int cnt;
      char grade = '\0';

      for (cnt = 0; cnt < this.testScores.length; cnt++) {
        sum += this.testScores[cnt];
      }
      try {
        ave = sum / cnt;
      }
      catch (ArithmeticException e) {
        ave = 0;
      }
      if (ave < 40) {
        grade = 'T';
      }
      else if (ave < 55) {
        grade = 'D';
      }
      else if (ave < 70) {
        grade = 'P';
      }
      else if (ave < 80) {
        grade = 'A';
      }
      else if (ave < 90) {
        grade = 'E';
      }
      else if (ave <= 100) {
        grade = 'O';
      }
      else {
        System.out.println("invalid average.");
      }

      return grade;
    }

}


class Solution {
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		String firstName = scan.next();
		String lastName = scan.next();
		int id = scan.nextInt();
		int numScores = scan.nextInt();
		int[] testScores = new int[numScores];
		for(int i = 0; i < numScores; i++){
			testScores[i] = scan.nextInt();
		}
		scan.close();

		Student s = new Student(firstName, lastName, id, testScores);
		s.printPerson();
		System.out.println("Grade: " + s.calculate() );
	}
}
