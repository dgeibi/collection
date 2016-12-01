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

class CustomerClient {
    private String id;
    private Connection connection = Main.connection;
    private TableCreator returnTableCreator;
    private TableCreator borrowTableCreator;

    CustomerClient(String id) {
        this.id = id;
        this.go();
    }

    private void reload(Composite c) {
        returnTableCreator.reload();
        borrowTableCreator.reload();
        c.layout();
    }

    private void go() {
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

        borrowTableCreator = new TableCreator() {
            @Override
            void reload() {
                String sql = "SELECT id,name,author FROM book" +
                        " WHERE id NOT IN" +
                        "(SELECT bookID FROM history WHERE customerID = '" + id + "' AND returnTime IS NULL)";
                TableItem[] items = table.getItems();
                for (TableItem item :
                        items) {
                    item.dispose();
                }
                try {
                    Statement st = connection.createStatement();
                    ResultSet rs = st.executeQuery(sql);
                    while (rs.next()) {
                        TableItem item = new TableItem(table, SWT.NONE);
                        item.setText(0, rs.getString("id"));
                        item.setText(1, rs.getString("name"));
                        item.setText(2, rs.getString("author"));
                    }
                } catch (SQLException se) {
                    se.printStackTrace();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        };
        String[] borrowTableTitle = {"id", "书名", "作者"};
        Table borrowTable = borrowTableCreator.init(view, borrowTableTitle);
        Widget.createBtn(view, "提交", new GridData(SWT.CENTER, SWT.CENTER, true, false), event -> {
            TableItem[] items = borrowTable.getItems();
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
                reload(borrowTable.getParent());
            }
        });

        // 还书
        label = new Label(view, SWT.NONE);
        label.setText("还书：");
        String[] returnTableTitles = {"流水号", "书名", "作者"};
        returnTableCreator = new TableCreator() {
            @Override
            void reload() {
                TableItem[] items = table.getItems();
                for (TableItem item :
                        items) {
                    item.dispose();
                }

                String sql = "SELECT id,bookID FROM history WHERE customerID = '" + id + "' AND returnTime IS NULL";
                Statement st = null;
                ResultSet rs = null;
                try {
                    st = connection.createStatement();
                    rs = st.executeQuery(sql);
                    while (rs.next()) {
                        TableItem item = new TableItem(table, SWT.NONE);
                        item.setText(0, rs.getString("id"));
                        String sql2 = "SELECT name,author FROM book " +
                                "WHERE id = '" + rs.getString("bookID") + "'";

                        // 显示书名和作者
                        Statement st2 = null;
                        ResultSet rs2 = null;
                        try {
                            st2 = connection.createStatement();
                            rs2 = st2.executeQuery(sql2);

                            if (rs2.next()) {
                                String author = rs2.getString("author");
                                if (author == null) author = "";
                                item.setText(1, rs2.getString("name"));
                                item.setText(2, author);
                            }

                        } catch (SQLException se) {
                            se.printStackTrace();
                        } finally {
                            try {
                                rs2.close();
                                st2.close();
                            } catch (SQLException se) {
                            }
                        }
                    }
                } catch (SQLException se) {
                    se.printStackTrace();
                } finally {
                    try {
                        rs.close();
                        st.close();
                    } catch (SQLException se) {
                    }
                }
            }
        };
        Table returnTable = returnTableCreator.init(view, returnTableTitles);
        Widget.createBtn(view, "提交", new GridData(SWT.CENTER, SWT.CENTER, true, false), event -> {
            TableItem[] items = returnTable.getItems();
            for (TableItem item : items) {
                if (item.getChecked()) {
                    String businessID = item.getText(0);
                    Statement st = null;
                    try {
                        st = connection.createStatement();
                        String sql = "UPDATE history SET returnTime = NOW() WHERE id = '" + businessID + "'";
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
                reload(borrowTable.getParent());
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
