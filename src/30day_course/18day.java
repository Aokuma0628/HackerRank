import java.io.*;
import java.util.*;

public class Solution {
    // Write your code here.
    ArrayDeque<Character> stack;
    ArrayDeque<Character> queue;

    Solution() {
      this.stack = new ArrayDeque<Character>();
      this.queue = new ArrayDeque<Character>();
    }

    public void pushCharacter(
      char c
    )
    {
      try {
        this.stack.addFirst(c);
      }
      catch (NullPointerException e) {
        e.printStackTrace();
      }
    }

    public Character popCharacter(
    )
    {
      Character c;
      try {
        c = this.stack.removeFirst();
        return c;
      }
      catch (NoSuchElementException e) {
        return '\0';
      }
    }

    public void enqueueCharacter(
      char c
    )
    {
      try {
        this.queue.addLast(c);
      }
      catch (NullPointerException e) {
        e.printStackTrace();
      }
    }

    public Character dequeueCharacter(
    )
    {
      Character c;
      try {
        c = this.queue.removeFirst();
        return c;
      }
      catch (NoSuchElementException e) {
        return '\0';
      }
    }

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        String input = scan.nextLine();
        scan.close();

        // Convert input String to an array of characters:
        char[] s = input.toCharArray();

        // Create a Solution object:
        Solution p = new Solution();

        // Enqueue/Push all chars to their respective data structures:
        for (char c : s) {
            p.pushCharacter(c);
            p.enqueueCharacter(c);
        }

        // Pop/Dequeue the chars at the head of both data structures and compare them:
        boolean isPalindrome = true;
        for (int i = 0; i < s.length/2; i++) {
            if (p.popCharacter() != p.dequeueCharacter()) {
                isPalindrome = false;
                break;
            }
        }

        //Finally, print whether string s is palindrome or not.
        System.out.println( "The word, " + input + ", is "
                           + ( (!isPalindrome) ? "not a palindrome." : "a palindrome." ) );
    }
}
