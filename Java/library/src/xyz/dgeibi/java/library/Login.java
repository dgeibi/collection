package xyz.dgeibi.java.library;

import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.*;

import java.sql.*;

public class Login {


    Connection connection = DBConnection();

    private Connection DBConnection() {
        Connection connection = null;
        try {
            Class.forName("org.mariadb.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost/keshe", "dgeibi", "123456");
        } catch (ClassNotFoundException e) {
            System.out.println(e.getMessage());
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        } catch (Exception e) {
            e.printStackTrace();
        }
        return connection;
    }

    public void go() {
        System.out.println("Driver loaded");
        Display display = new Display();
        final Shell shell = new Shell(display);
        shell.setLayout(new GridLayout());
        shell.setText("登录 - GDUT Library System");
        Composite c1 = new Composite(shell, SWT.NONE);
        GridLayout gridLayout = new GridLayout();
        gridLayout.numColumns = 2;
        c1.setLayout(gridLayout);
        c1.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true));

        Label label = new Label(c1, SWT.NULL);
        label.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 2, 1));
        label.setText("GDUT Library System");

        // Account Text
        label = new Label(c1, SWT.NULL);
        label.setText("账号: ");
        Text userT = new Text(c1, SWT.SINGLE | SWT.BORDER);
        userT.addListener(SWT.Verify, e -> {
            String string = e.text;
            char[] chars = new char[string.length()];
            string.getChars(0, chars.length, chars, 0);
            for (int i = 0; i < chars.length; i++) {
                if (!('0' <= chars[i] && chars[i] <= '9')) {
                    e.doit = false;
                    return;
                }
            }
        });
        userT.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 2, 1));
        userT.setFocus();


        // Password Text
        label = new Label(c1, SWT.NULL);
        label.setText("密码: ");
        Text pwT = new Text(c1, SWT.PASSWORD | SWT.BORDER);
        pwT.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 2, 1));

        // Account Option
        Button option1 = new Button(c1, SWT.RADIO);
        option1.setText("用户");
        option1.setSelection(true);
        Button option2 = new Button(c1, SWT.RADIO);
        option2.setText("管理员");


        // Login
        Button btn1 = new Button(c1, SWT.PUSH);
        btn1.setText("登录");
        btn1.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false));
        shell.setDefaultButton(btn1);
        btn1.addListener(SWT.Selection, event -> {
            try {
                Statement st = connection.createStatement();
                String sql = option2.getSelection() ? "admin" : "user";
                sql = "SELECT id FROM " + sql + " WHERE id = '" + userT.getText() + "' AND " + "password = '" + pwT.getText() + "'";
                ResultSet rs = st.executeQuery(sql);
                if (rs.next()) {
                    shell.close();
                    new Client(rs.getString("id"), display, connection);
                } else {
                    new Alert(shell, "登录失败", Alert.ERROR);
                }
            } catch (SQLException se) {
                se.printStackTrace();
            } catch (Exception e) {
                e.printStackTrace();
            }
        });

        // Create Account
        Button btn2 = new Button(c1, SWT.PUSH);
        btn2.setText("注册");
        btn2.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false));
        btn2.addListener(SWT.Selection, event -> {
            try {
                Statement st = connection.createStatement();
                String sql = option2.getSelection() ? "admin" : "user";
                sql = "INSERT INTO " + sql + " (id,password,registerTime) " +
                        "VALUES ('" + userT.getText() + "','" + pwT.getText() + "',NOW())";
                if (st.executeUpdate(sql) > 0) {
                    new Alert(shell, "注册成功！", Alert.NOTICE);
                }
            } catch (SQLException se) {
                new Alert(shell, "注册失败,请更换其它ID！", Alert.ERROR);
            } catch (Exception e) {
                e.printStackTrace();
            }
        });

        shell.setSize(250, 250);
        shell.open();
        while (!shell.isDisposed()) {
            if (!display.readAndDispatch()) display.sleep();
        }
        display.dispose();

        try {
            connection.close();
        } catch (SQLException se) {
            se.printStackTrace();
        }
    }
}
