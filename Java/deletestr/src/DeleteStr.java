import java.io.*;
public class DeleteStr {
	public static void main(String[] args) {
		try {
			BufferedReader reader = new BufferedReader(new FileReader(new File(args[0])));
			BufferedWriter writer = new BufferedWriter(new FileWriter(new File(args[1])));
			String str = null;
			while((str = reader.readLine())!= null){
				writer.write(str.replaceAll(args[2],""));
				writer.newLine();
			}
			reader.close();
			writer.close();
		} catch (Exception ex) {
			ex.printStackTrace();
		}
		
	}

}
