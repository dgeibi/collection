package xyz.dgeibi.java.library;


import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.layout.RowData;
import org.eclipse.swt.layout.RowLayout;
import org.eclipse.swt.widgets.*;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class CustomerClient {
    String id;
    Connection connection = Main.connection;

    public CustomerClient(String id) {
        this.id = id;
        this.go();
    }

    void reload(Shell parent) {
        Composite c1 = new Composite(parent, SWT.NONE);
        c1.setLayout(new GridLayout());

        Composite setting = new Composite(parent, SWT.NONE);
        setting.setLayout(new RowLayout());
        RowData rowData = new RowData();
        Widget.createBtn(setting, "注销", event -> {
            parent.close();
            new Login();
        }, rowData);
        Widget.createBtn(setting, "修改个人信息", event -> {
            parent.setText("User: " + new Profile(parent, id, "user").go() + "(" + id + ") - GDUT Digital Library System");
        }, rowData);

        // 借书
        Label label = new Label(c1, SWT.NONE);
        label.setText("借书：");
        String sql1 = "SELECT id,name,author FROM book" +
                " WHERE id NOT IN" +
                "(SELECT bookid FROM business WHERE userid = '" + id + "')";
        final Table table1 = Widget.createBookTable(c1, sql1, connection, SWT.MULTI | SWT.CHECK | SWT.BORDER | SWT.V_SCROLL);
        Widget.createBtn(c1, "提交", event -> {
            TableItem[] items = table1.getItems();
            for (TableItem item : items) {
                if (item.getChecked()) {
                    String bookId = item.getText(0);
                    try {
                        Statement st = connection.createStatement();
                        String sql = "INSERT INTO business (userid,bookid,businessTime) " +
                                "VALUES ('" + id + "', '" + bookId + "', " + "NOW())";
                        st.executeUpdate(sql);
                    } catch (SQLException se) {
                        se.printStackTrace();
                    }
                }
            }
            if (items.length > 0) {
                c1.dispose();
                reload(parent);
            }
        });
        ;

        // 还书
        label = new Label(c1, SWT.NONE);
        label.setText("还书：");
        String sql2 = "SELECT id,name,author FROM book" +
                " WHERE id IN" +
                "(SELECT bookid FROM business WHERE userid = '" + id + "')";
        final Table table2 = Widget.createBookTable(c1, sql2, connection, SWT.MULTI | SWT.CHECK | SWT.BORDER | SWT.V_SCROLL);
        Widget.createBtn(c1, "提交", event -> {
            TableItem[] items = table2.getItems();
            for (TableItem item : items) {
                if (item.getChecked()) {
                    String bookId = item.getText(0);
                    try {
                        Statement st = connection.createStatement();
                        String sql = "DELETE FROM business WHERE bookid = '" + bookId + "'";
                        st.executeUpdate(sql);
                    } catch (SQLException se) {
                        se.printStackTrace();
                    }
                }
            }
            if (items.length > 0) {
                c1.dispose();
                setting.dispose();
                reload(parent);
            }
        });
        c1.pack();
        setting.pack();
        parent.pack();
    }

    /* TODO:
     *  delete account
     *  history
     */
    void go() {
        Display display = Main.display;
        Shell shell = new Shell(display);
        shell.setLayout(new GridLayout());
        String username = "";
        try {
            Statement st = connection.createStatement();
            ResultSet rs = st.executeQuery("SELECT username FROM user WHERE id = '" + id + "'");
            if (rs.next()) {
                username = rs.getString("username");
            }
        } catch (SQLException se) {
        }
        if (username == null) {
            username = id;
        }
        shell.setText("User: " + username + "(" + id + ") - GDUT Digital Library System");
        reload(shell);
        shell.open();
        while (!shell.isDisposed()) {
            if (!display.readAndDispatch()) display.sleep();
        }
    }
}
