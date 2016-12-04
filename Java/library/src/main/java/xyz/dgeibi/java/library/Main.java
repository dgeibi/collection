package xyz.dgeibi.java.library;

import org.eclipse.swt.graphics.Rectangle;
import org.eclipse.swt.widgets.Display;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class Main {
    static Connection connection = DBConnection();
    static Display display = new Display();
    static Rectangle screenSize = display.getPrimaryMonitor().getBounds();

    public static void main(String[] args) {
        new Login();
        display.dispose();

        try {
            connection.close();
        } catch (SQLException se) {
            se.printStackTrace();
        }
    }


    private static Connection DBConnection() {
        Connection connection = null;
        try {
            Class.forName("org.mariadb.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/keshe", "dgeibi", "123456");
        } catch (ClassNotFoundException e) {
            System.out.println(e.getMessage());
        } catch (Exception e) {
            e.printStackTrace();
        }
        return connection;
    }
}
