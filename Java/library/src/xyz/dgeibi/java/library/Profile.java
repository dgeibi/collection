package xyz.dgeibi.java.library;

import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.*;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Profile extends Dialog {
    String userId;
    String type;
    String username = getUsername();

    public Profile(Shell parent, String userId, String type) {
        super(parent);
        this.userId = userId;
        this.type = type;
    }

    public String getUsername() {
        String n = "";
        try {
            Statement st = Main.connection.createStatement();
            ResultSet rs = st.executeQuery("SELECT username FROM " + type + " WHERE id = '" + userId + "'");
            if (rs.next()) {
                n = rs.getString("username");
            }
        } catch (SQLException se) {
        }
        if (n == null) {
            n = userId;
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


        new Label(profile, SWT.NULL).setText("用户名：");
        Text usernameText = new Text(profile, SWT.SINGLE | SWT.BORDER);
        usernameText.setLayoutData(textGridData);
        usernameText.setText(username);

        new Label(profile, SWT.NULL).setText("新的密码：");
        Text newPasswordText = new Text(profile, SWT.PASSWORD | SWT.BORDER);
        newPasswordText.setLayoutData(textGridData);
        new Label(profile, SWT.NULL).setText("再次输入密码：");
        Text newPasswordCText = new Text(profile, SWT.PASSWORD | SWT.BORDER);
        newPasswordCText.setLayoutData(textGridData);

        Widget.createBtn(profile, "保存", event -> {
            String _password = newPasswordText.getText();
            String _username = usernameText.getText();
            String _passwordC = newPasswordCText.getText();

            if (!_password.equals("") && !_username.equals("")) {
                if (_password.equals(_passwordC)) {
                    try {
                        Statement st = Main.connection.createStatement();
                        if (1 == st.executeUpdate("UPDATE " + type + " SET username = '" + _username + "',password = '" +
                                _password + "' WHERE id = '" + userId + "'")) {
                            username = _username;
                            new Alert(profile, "修改成功！", Alert.NOTICE);
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
                                _password + "' WHERE id = '" + userId + "'")) {
                            new Alert(profile, "修改成功！", Alert.NOTICE);
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
                            "' WHERE id = '" + userId + "'")) {
                        username = _username;
                        new Alert(profile, "修改成功！", Alert.NOTICE);
                    } else {
                        new Alert(profile, "出错！", Alert.ERROR);
                    }
                } catch (SQLException se) {
                }
            }
        });
        profile.pack();
        profile.open();

        Display display = parent.getDisplay();
        while (!profile.isDisposed()) {
            if (!display.readAndDispatch()) display.sleep();
        }
        return username;
    }
}
