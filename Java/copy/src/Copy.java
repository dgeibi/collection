/**
 * Created by dgeibi on 10/23/16.
 */
import java.io.*;
public class Copy {
    public static void main(String[] args) {
        try {
            File input = new File(args[0]);
            BufferedReader reader = new BufferedReader(new FileReader(input));

            String line = null;
            File output = new File(args[1]);
            BufferedWriter writer = new BufferedWriter(new FileWriter(output));
            while((line = reader.readLine())!= null){
                writer.write(line);
                writer.newLine();
            }
            writer.close();
            reader.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
