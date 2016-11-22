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

    void go() {
        Display display = Main.display;
        Shell shell = new Shell(display, SWT.SHELL_TRIM & (~SWT.RESIZE));
        GridLayout gridLayout = new GridLayout();
        gridLayout.marginHeight = 5;
        shell.setLayout(gridLayout);
        String username = "";
        Statement statement = null;
        ResultSet resultSet = null;
        try {
            statement = connection.createStatement();
            resultSet = statement.executeQuery("SELECT username FROM customer WHERE id = '" + id + "'");
            if (resultSet.next()) {
                username = resultSet.getString("username");
            }
        } catch (SQLException se) {
            se.printStackTrace();
        } finally {
            try {
                resultSet.close();
                statement.close();
            } catch (SQLException se) {
            }
        }
        if (username == null) {
            username = id;
        }
        shell.setText("Customer: " + username + "(" + id + ") - GDUT Digital Library System");

        /*
         * Top
         */
        Composite top = new Composite(shell, SWT.NONE);
        top.setLayout(new RowLayout());
        top.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false));
        RowData rowData = new RowData();
        Widget.createBtn(top, "注销", rowData, event -> {
            shell.close();
            new Login();
        });
        Widget.createBtn(top, "修改个人信息", rowData, event -> {
            shell.setText("Customer: " + new Profile(shell, id, "customer").go() + "(" + id + ") - GDUT Digital Library System");
        });
        Widget.createBtn(top, "删除账号", rowData, event -> {
            Confirm confirm = new Confirm(shell, "你确定删除此账号？");
            if (confirm.go()) {
                Statement st = null;
                try {
                    st = connection.createStatement();
                    if (1 == st.executeUpdate("DELETE FROM customer WHERE id = '" + id + "'")) {
                        connection.createStatement().executeUpdate("DELETE FROM history WHERE customerID = '" + id + "'");
                        new Alert(shell, "成功删除。", Alert.NOTICE);
                        shell.close();
                        new Login();
                    } else {
                        new Alert(shell, "删除失败！", Alert.ERROR);
                    }
                } catch (SQLException se) {
                    se.printStackTrace();
                } finally {
                    try {
                        st.close();
                    } catch (SQLException se) {
                    }
                }
            }
        });
        Widget.createBtn(top, "借阅记录", event -> {
            new History(shell, id);
        });
        top.pack();

        /*
         * View
         */
        Composite view = new Composite(shell, SWT.NONE);
        view.setLayout(new GridLayout());
        view.setLayoutData(new GridData(SWT.LEFT, SWT.FILL, false, true));

        // 借书
        Label label = new Label(view, SWT.NONE);
        label.setText("借书：");
        sql1 = "SELECT id,name,author FROM book" +
                " WHERE id NOT IN" +
                "(SELECT bookID FROM history WHERE customerID = '" + id + "' AND returnTime IS NULL)";
        table1 = Widget.createBookTable(view, sql1, connection, SWT.MULTI | SWT.CHECK | SWT.BORDER | SWT.V_SCROLL);
        Widget.createBtn(view, "提交", new GridData(SWT.CENTER, SWT.CENTER, true, false), event -> {
            TableItem[] items = table1.getItems();
            for (TableItem item : items) {
                if (item.getChecked()) {
                    String bookID = item.getText(0);
                    Statement st = null;
                    try {
                        st = connection.createStatement();
                        String sql = "INSERT INTO history (customerID,bookID,businessTime) " +
                                "VALUES ('" + id + "', '" + bookID + "', " + "NOW())";
                        st.executeUpdate(sql);
                    } catch (SQLException se) {
                        se.printStackTrace();
                    } finally {
                        try {
                            st.close();
                        } catch (SQLException se) {
                        }
                    }
                }
            }
            if (items.length > 0) {
                reload();
            }
        });


        // 还书
        label = new Label(view, SWT.NONE);
        label.setText("还书：");
        sql2 = "SELECT id,name,author FROM book" +
                " WHERE id IN" +
                "(SELECT bookID FROM history WHERE customerID = '" + id + "' AND returnTime IS NULL)";
        table2 = Widget.createBookTable(view, sql2, connection, SWT.MULTI | SWT.CHECK | SWT.BORDER | SWT.V_SCROLL);
        Widget.createBtn(view, "提交", new GridData(SWT.CENTER, SWT.CENTER, true, false), event -> {
            TableItem[] items = table2.getItems();
            for (TableItem item : items) {
                if (item.getChecked()) {
                    String bookID = item.getText(0);
                    Statement st = null;
                    try {
                        st = connection.createStatement();
                        String sql = "UPDATE history SET returnTime = NOW() WHERE bookID = '" + bookID + "' AND customerID = '" + id + "'";
                        st.executeUpdate(sql);
                    } catch (SQLException se) {
                        se.printStackTrace();
                    } finally {
                        try {
                            st.close();
                        } catch (SQLException se) {
                        }
                    }
                }
            }
            if (items.length > 0) {
                reload();
            }
        });

        view.pack();
        top.pack();
        shell.pack();
        shell.open();
        while (!shell.isDisposed()) {
            if (!display.readAndDispatch()) display.sleep();
        }
    }
}
