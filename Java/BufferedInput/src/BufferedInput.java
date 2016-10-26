import java.io.*;
public class BufferedInput {
    public static void main(String[] args) {
        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter(new File("myFile.txt")));
            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
            String str = null;
            System.out.print("enter your string: ");
            while(!(str = reader.readLine()).equals("quit")){
                writer.write(str);
                writer.newLine();
            }
            writer.close();
            reader.close();
        } catch (IOException e){
            e.printStackTrace();
        }
    }
}
