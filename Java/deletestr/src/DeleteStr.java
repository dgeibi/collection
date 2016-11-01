import java.io.*;
public class DeleteStr {
	public static void main(String[] args) {
		try {
			File output = new File("out.txt");
			output.delete();
			BufferedReader reader = new BufferedReader(new FileReader(new File(args[1])));
			BufferedWriter writer = new BufferedWriter(new FileWriter(output));
			String str = null;
			while((str = reader.readLine())!= null){
				writer.write(str.replaceAll(args[0],""));
				writer.newLine();
			}
			reader.close();
			writer.close();
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}
}
