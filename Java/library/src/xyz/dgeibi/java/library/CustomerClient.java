package xyz.dgeibi.java.library;


import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridData;
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
    Table table1;
    Table table2;
    String sql1;
    String sql2;
    Connection connection = Main.connection;

    public CustomerClient(String id) {
        this.id = id;
        this.go();
    }

    void reload() {
        Widget.reloadBookTable(table1, sql1, connection);
        Widget.reloadBookTable(table2, sql2, connection);
        table1.getParent().layout();
    }

    /* TODO:
     *  delete account
     *  history
     */
    void go() {
        Display display = Main.display;
        Shell shell = new Shell(display);
        GridLayout gridLayout = new GridLayout();
        gridLayout.marginHeight = 5;
        shell.setLayout(gridLayout);
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

        /*
         * Setting
         */
        Composite setting = new Composite(shell, SWT.NONE);
        setting.setLayout(new RowLayout());
        setting.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false));
        RowData rowData = new RowData();
        Widget.createBtn(setting, "注销", event -> {
            shell.close();
            new Login();
        }, rowData);
        Widget.createBtn(setting, "修改个人信息", event -> {
            shell.setText("User: " + new Profile(shell, id, "user").go() + "(" + id + ") - GDUT Digital Library System");
        }, rowData);
        setting.pack();

        /*
         * View
         */
        Composite view = new Composite(shell, SWT.NONE);
        view.setLayout(new GridLayout());
        view.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true));

        // 借书
        Label label = new Label(view, SWT.NONE);
        label.setText("借书：");
        sql1 = "SELECT id,name,author FROM book" +
                " WHERE id NOT IN" +
                "(SELECT bookid FROM business WHERE userid = '" + id + "')";
        table1 = Widget.createBookTable(view, sql1, connection, SWT.MULTI | SWT.CHECK | SWT.BORDER | SWT.V_SCROLL);
        Widget.createBtn(view, "提交", event -> {
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
                reload();
            }
        });
        ;

        // 还书
        label = new Label(view, SWT.NONE);
        label.setText("还书：");
        sql2 = "SELECT id,name,author FROM book" +
                " WHERE id IN" +
                "(SELECT bookid FROM business WHERE userid = '" + id + "')";
        table2 = Widget.createBookTable(view, sql2, connection, SWT.MULTI | SWT.CHECK | SWT.BORDER | SWT.V_SCROLL);
        Widget.createBtn(view, "提交", event -> {
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
                reload();
            }
        });

        view.pack();

        shell.pack();
        shell.open();
        while (!shell.isDisposed()) {
            if (!display.readAndDispatch()) display.sleep();
        }
    }
}
