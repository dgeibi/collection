import java.sql.*;

public class Main {
    public static void main(String[] args) {
        // Load the JDBC driver
        try {
            Class.forName("org.mariadb.jdbc.Driver");
            System.out.println("Driver loaded");
            // Try to connect
            Connection connection = DriverManager.getConnection
                    ("jdbc:mysql://localhost/keshe", "dgeibi", "123456");
            System.out.println("It works!");
            connection.close();
        } catch (Exception ex) {}
    }
}
