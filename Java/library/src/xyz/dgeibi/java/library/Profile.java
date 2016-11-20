package xyz.dgeibi.java.library;

import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.*;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Profile extends Dialog {
    String customerID;
    String type;
    String username;

    public Profile(Shell parent, String customerID, String type) {
        super(parent);
        this.customerID = customerID;
        this.type = type;
        this.username = getUsername();
    }

    public String getUsername() {
        String n = "";
        try {
            Statement st = Main.connection.createStatement();
            ResultSet rs = st.executeQuery("SELECT username FROM " + type + " WHERE id = '" + customerID + "'");
            if (rs.next()) {
                n = rs.getString("username");
            }
        } catch (SQLException se) {
            se.printStackTrace();
        }
        if (n == null) {
            n = customerID;
        }
        return n;
    }

    public String go() {
        Shell parent = getParent();

        GridData textGridData = new GridData(SWT.LEFT, SWT.CENTER, true, false, 2, 1);
        textGridData.widthHint = 250;

        final Shell profile = new Shell(parent, SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
        profile.setLayout(new GridLayout());
        profile.setText("修改个人信息");

        Composite c = new Composite(profile, SWT.NONE);
        c.setLayout(new GridLayout());
        c.setLayoutData(new GridData(SWT.LEFT, SWT.FILL, true, false));

        new Label(c, SWT.NULL).setText("用户名：");
        Text usernameText = new Text(c, SWT.SINGLE | SWT.BORDER);
        usernameText.setLayoutData(textGridData);
        usernameText.setText(username);

        new Label(c, SWT.NULL).setText("新的密码：");
        Text newPasswordText = new Text(c, SWT.PASSWORD | SWT.BORDER);
        newPasswordText.setLayoutData(textGridData);
        new Label(c, SWT.NULL).setText("再次输入密码：");
        Text newPasswordCText = new Text(c, SWT.PASSWORD | SWT.BORDER);
        newPasswordCText.setLayoutData(textGridData);

        Widget.createBtn(c, "保存", new GridData(SWT.CENTER, SWT.FILL, true, false), event -> {
            String _password = newPasswordText.getText();
            String _username = usernameText.getText();
            String _passwordC = newPasswordCText.getText();

            if (!_password.equals("") && !_username.equals("")) {
                if (_password.equals(_passwordC)) {
                    try {
                        Statement st = Main.connection.createStatement();
                        if (1 == st.executeUpdate("UPDATE " + type + " SET username = '" + _username + "',password = '" +
                                _password + "' WHERE id = '" + customerID + "'")) {
                            username = _username;
                            new Alert(profile, "修改成功！", Alert.NOTICE);
                            profile.close();
                        } else {
                            new Alert(profile, "出错！", Alert.ERROR);
                        }
                    } catch (SQLException se) {
                    }
                } else {
                    new Alert(profile, "密码不匹配！", Alert.ERROR);
                }
            } else if (!_password.equals("")) {
                if (_password.equals(_passwordC)) {
                    try {
                        Statement st = Main.connection.createStatement();
                        if (1 == st.executeUpdate("UPDATE " + type + " SET password = '" +
                                _password + "' WHERE id = '" + customerID + "'")) {
                            new Alert(profile, "修改成功！", Alert.NOTICE);
                            profile.close();
                        } else {
                            new Alert(profile, "出错！", Alert.ERROR);
                        }
                    } catch (SQLException se) {
                    }
                } else {
                    new Alert(profile, "密码不匹配！", Alert.ERROR);
                }
            } else if (!_username.equals("")) {
                try {
                    Statement st = Main.connection.createStatement();
                    if (1 == st.executeUpdate("UPDATE " + type + " SET username = '" + _username +
                            "' WHERE id = '" + customerID + "'")) {
                        username = _username;
                        new Alert(profile, "修改成功！", Alert.NOTICE);
                        profile.close();
                    } else {
                        new Alert(profile, "出错！", Alert.ERROR);
                    }
                } catch (SQLException se) {
                    se.printStackTrace();
                }
            }
        });
        c.pack();
        profile.pack();
        profile.open();

        Display display = parent.getDisplay();
        while (!profile.isDisposed()) {
            if (!display.readAndDispatch()) display.sleep();
        }
        return username;
    }
}
