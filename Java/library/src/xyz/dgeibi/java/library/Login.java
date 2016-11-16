package xyz.dgeibi.java.library;

import org.eclipse.swt.*;
import org.eclipse.swt.layout.*;
import org.eclipse.swt.widgets.*;
import java.sql.*;

public class Login {
    public void go() {
        try {
            Class.forName("org.mariadb.jdbc.Driver");
        }catch (Exception ex) {}

        System.out.println("Driver loaded");
        Display display = new Display ();
        final Shell shell = new Shell (display);
        shell.setLayout(new GridLayout());
        shell.setText("登录 - GDUT Library System");
        Composite c1 = new Composite (shell, SWT.NONE);
        GridLayout gridLayout = new GridLayout();
        gridLayout.numColumns =2;
        c1.setLayout(gridLayout);
        c1.setLayoutData(new GridData (SWT.FILL, SWT.FILL, true, true));

        Label label = new Label(c1, SWT.NULL);
        label.setLayoutData(new GridData(SWT.FILL,SWT.CENTER,true,false,2,1));
        label.setText("GDUT Library System");

        label = new Label(c1, SWT.NULL);
        label.setText("账号: ");
        Text userT = new Text (c1, SWT.SINGLE | SWT.BORDER);
        userT.addListener (SWT.Verify, e -> {
            String string = e.text;
            char [] chars = new char [string.length ()];
            string.getChars (0, chars.length, chars, 0);
            for (int i=0; i<chars.length; i++) {
                if (!('0' <= chars [i] && chars [i] <= '9')) {
                    e.doit = false;
                    return;
                }
            }
        });
        userT.setLayoutData(new GridData (SWT.FILL, SWT.CENTER, true, false,2,1));
        userT.setFocus();


        // 密码
        label = new Label(c1, SWT.NULL);
        label.setText("密码: ");
        Text pwT = new Text (c1, SWT.PASSWORD | SWT.BORDER);
        pwT.setLayoutData(new GridData (SWT.FILL, SWT.CENTER, true, false,2,1));


        Button option1 = new Button(c1,SWT.RADIO);
        option1.setText("用户");
        option1.setSelection(true);
        Button option2 = new Button(c1,SWT.RADIO);
        option2.setText("管理员");


        // 登录按钮
        Button btn1 = new Button (c1, SWT.PUSH);
        btn1.setText ("登录");
        btn1.setLayoutData(new GridData(SWT.FILL,SWT.CENTER, true, false));
        shell.setDefaultButton (btn1);
        btn1.addListener(SWT.Selection,event->{
            try {
                Connection connection = DriverManager.getConnection
                        ("jdbc:mysql://localhost/keshe", "dgeibi", "123456");
                Statement st = connection.createStatement();
                String sql;
                if (option2.getSelection()){
                    sql = "SELECT id FROM admin WHERE id = '" + userT.getText() + "' AND " + "password = '"+pwT.getText() +"';" ;
                } else if (option1.getSelection()){
                    sql = "SELECT id FROM user WHERE id = '" + userT.getText() + "' AND " + "password = '"+pwT.getText() +"';" ;
                } else {
                    sql = "";
                }
                if(!sql.equals("")) {
                    ResultSet rs = st.executeQuery(sql);
                    while(rs.next()){
                        // TODO: Client
                        new Client(rs.getString("id"),display).go();
                    }
                }
                connection.close();
            } catch (Exception ex) {}
        });

        Button btn2 = new Button (c1, SWT.PUSH);
        btn2.setText ("注册");
        btn2.setLayoutData(new GridData(SWT.FILL,SWT.CENTER, true, false));
        btn2.addListener(SWT.Selection, event->{
                try {
                    Connection connection = DriverManager.getConnection
                            ("jdbc:mysql://localhost/keshe", "dgeibi", "123456");
                    Statement st = connection.createStatement();
                    String sql;
                    if (option2.getSelection()){
                        sql = "INSERT INTO admin (id,password,registerTime) VALUES ('"+ userT.getText() + "','" + pwT.getText() + "',NOW());";
                    } else if (option1.getSelection()){
                        sql = "INSERT INTO user (id,password,registerTime) VALUES ('"+ userT.getText() + "','" + pwT.getText() + "',NOW());";
                    } else {
                        sql = "";
                    }
                    if(!sql.equals("")) st.execute(sql);
                    connection.close();
                } catch (Exception ex) {}
        });

        shell.setSize (250, 250);
        shell.open ();
        while (!shell.isDisposed()) {
            if (!display.readAndDispatch ()) display.sleep ();
        }
        display.dispose ();
    }
}
