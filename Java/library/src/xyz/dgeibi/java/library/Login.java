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

    private void toggleComposite(Composite c, GridData d){
        d.exclude = !d.exclude;
        c.setVisible(!d.exclude);
        c.getParent().pack();
    }


    public void go() {
        Display display = new Display();
        final Shell shell = new Shell(display);
        shell.setLayout(new GridLayout());
        shell.setText("登录 - GDUT Digital Library System");

        GridLayout gridLayout = new GridLayout();
        gridLayout.numColumns = 2;

        Composite c1 = new Composite(shell, SWT.NONE);
        c1.setLayout(gridLayout);
        c1.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false));

        Composite c5 = new Composite(shell, SWT.NONE);
        c5.setLayout(gridLayout);
        c5.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false));

        Composite c2 = new Composite(shell, SWT.NONE);
        c2.setLayout(gridLayout);
        GridData c2Data = new GridData(SWT.FILL, SWT.CENTER, true, false);
        c2.setLayoutData(c2Data);

        Composite c3 = new Composite(shell, SWT.NONE);
        c3.setLayout(gridLayout);
        GridData c3Data = new GridData(SWT.FILL, SWT.CENTER, true, false);
        c3.setLayoutData(c3Data);
        toggleComposite(c3,c3Data);

        Label label = new Label(c1, SWT.NULL);
        label.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 2, 1));
        label.setText("GDUT Digital Library System");

        GridData textGridData = new GridData(SWT.LEFT, SWT.CENTER, true, false, 2, 1);
        textGridData.widthHint = 250;

        // Account Text
        new Label(c1, SWT.NULL).setText("账号: ");
        Text accountText = new Text(c1, SWT.SINGLE | SWT.BORDER);
        accountText.addListener(SWT.Verify, e -> {
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
        accountText.setLayoutData(textGridData);
        accountText.setFocus();

        // Password Text
        new Label(c1, SWT.NULL).setText("密码: ");
        Text passwordText = new Text(c1, SWT.PASSWORD | SWT.BORDER);
        passwordText.setLayoutData(textGridData);

        // Extra Text
        Composite c11 = new Composite(c1, SWT.NONE);
        GridData c11Data = new GridData(SWT.LEFT,SWT.CENTER,true,false,2,1);
        c11.setLayoutData(c11Data);
        GridLayout c11Layout = new GridLayout();
        c11Layout.numColumns = 2;
        c11Layout.marginHeight = 0;
        c11Layout.marginWidth = 0;
        c11.setLayout(c11Layout);
        // Password Confirm
        new Label(c11,SWT.NULL).setText("确认密码：");
        Text passwordCText = new Text(c11,SWT.PASSWORD | SWT.BORDER);
        passwordCText.setLayoutData(textGridData);
        // Username Text
        new Label(c11,SWT.NULL).setText("用户名：");
        Text usernameText = new Text(c11,SWT.SINGLE | SWT.BORDER);
        usernameText.setLayoutData(textGridData);
        toggleComposite(c11,c11Data);

        // Account Option
        Button option1 = new Button(c5, SWT.RADIO);
        option1.setText("用户");
        option1.setSelection(true);
        option1.setLayoutData(new GridData(SWT.LEFT,SWT.CENTER,false,false,1,1));
        Button option2 = new Button(c5, SWT.RADIO);
        option2.setText("管理员");
        option2.setLayoutData(new GridData(SWT.LEFT,SWT.CENTER,true,false,1,1));

        // Login Button
        GridData gridDataLeft = new GridData(SWT.LEFT, SWT.CENTER, false, false);
        gridDataLeft.widthHint = 130;

        Button btn1 = new Button(c2, SWT.PUSH);
        btn1.setText("登录");
        btn1.setLayoutData(gridDataLeft);
        shell.setDefaultButton(btn1);
        btn1.addListener(SWT.Selection, event -> {
            try {
                Statement st = connection.createStatement();
                String kind = option2.getSelection() ? "admin" : "user";
                String sql = "SELECT id FROM " + kind + " WHERE id = '" + accountText.getText() +
                        "' AND " + "password = '" + passwordText.getText() + "'";
                ResultSet rs = st.executeQuery(sql);
                if (rs.next()) {
                    String id = rs.getString("id");
                    shell.close();
                    switch (kind) {
                        case "admin":
                            new AdminClient(id, display, connection);
                            break;
                        case "user":
                            new CustomerClient(id, display, connection);
                            break;
                    }
                } else {
                    new Alert(shell, "登录失败！", Alert.ERROR);
                }
            } catch (SQLException se) {
                se.printStackTrace();
            } catch (Exception e) {
                e.printStackTrace();
            }
        });

        // Create Account Button
        GridData gridDataRight = new GridData(SWT.LEFT, SWT.CENTER, true, false);
        gridDataRight.minimumWidth = 130;
        Button btn2 = new Button(c2, SWT.PUSH);
        btn2.setText("注册");
        btn2.setLayoutData(gridDataRight);
        btn2.addListener(SWT.Selection, event -> {
            toggleComposite(c11,c11Data);
            toggleComposite(c2,c2Data);
            toggleComposite(c3,c3Data);
        });

        // Composite 3: extra buttons
        Widget.createBtn(c3,"返回",event -> {
            toggleComposite(c11,c11Data);
            toggleComposite(c2,c2Data);
            toggleComposite(c3,c3Data);
        }).setLayoutData(gridDataLeft);

        Widget.createBtn(c3,"确定注册",event -> {
                String account = accountText.getText();
                String username = usernameText.getText();
                String password = passwordText.getText();
                String passwordC = passwordCText.getText();
                if (username.equals("")) {
                    username = account;
                }
                if (passwordC.equals(password)) {
                    try {
                        Statement st = connection.createStatement();
                        String sql = option2.getSelection() ? "admin" : "user";
                        sql = "INSERT INTO " + sql + " (id,password,username,registerTime) " +
                                "VALUES ('" + account + "','" + password + "','" +
                                username + "',NOW())";
                        if (st.executeUpdate(sql) > 0) {
                            new Alert(shell, "注册成功！", Alert.NOTICE);
                            toggleComposite(c11, c11Data);
                            toggleComposite(c2, c2Data);
                            toggleComposite(c3, c3Data);
                        }
                    } catch (SQLException se) {
                        new Alert(shell, "注册失败！请更换ID后再试", Alert.ERROR);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                } else {
                    new Alert(shell,"你输入的密码不一致！",SWT.ERROR);
                }
        }).setLayoutData(gridDataRight);


        shell.pack();
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
