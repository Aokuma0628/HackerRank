import java.io.*;

/**
 * @version 1.0.0
 */
class Util {

  public Util () {
    return ;
  }

  /**
   * @param void
   * @return String string from stdin
   */
  public String inputStdin() {
    String str;
    
    try {
      BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
      str = in.readLine();
    }
    catch (IOException e) {
      return null;
    }

    return str;
  }
}
