package xyz.dgeibi.java.library;

import org.eclipse.swt.*;
import org.eclipse.swt.layout.*;
import org.eclipse.swt.widgets.*;
import java.sql.*;


public class Client {

    String userId;
    Display display;
    Connection connection;

    public Client(String userId, Display display, Connection connection) {
        this.userId = userId;
        this.display = display;
        this.connection = connection;
        this.go();
    }

    void go() {
        System.out.println(userId + " 登录成功");

        Shell shell = new Shell(display);
        shell.setLayout(new GridLayout());
        shell.setText(userId + " - GDUT Library System");

        // 借书
        Label label = new Label(shell, SWT.NONE);
        label.setText("借书：");
        String sql1 = "SELECT id,name,author FROM book" +
                " WHERE id NOT IN" +
                "(SELECT bookid FROM business WHERE userid = '" + userId + "')" ;
        final Table table1 = createTable(shell, sql1);
        Button submit = createSubmitBtn(shell);
        submit.addListener(SWT.Selection,event -> {
            TableItem[] Items = table1.getItems();
            for (TableItem item : Items) {
                if (item.getChecked()) {
                    String bookId = item.getText(0);
                    try {
                        Statement st = connection.createStatement();
                        String sql = "INSERT INTO business (userid,bookid,businessTime) " +
                                "VALUES ('" + userId + "', '" + bookId + "', " + "NOW())" ;
                        st.executeUpdate(sql);
                    } catch (SQLException se) {
                        se.printStackTrace();
                    }
                }
            }
            shell.close();
            go();
        });

        // 还书
        label = new Label(shell, SWT.NONE);
        label.setText("还书：");
        String sql2 = "SELECT id,name,author FROM book" +
                " WHERE id IN" +
                "(SELECT bookid FROM business WHERE userid = '" + userId + "')" ;
        final Table table2 = createTable(shell, sql2);
        submit = createSubmitBtn(shell);
        submit.addListener(SWT.Selection,event -> {
            TableItem[] Items = table2.getItems();
            for (TableItem item : Items) {
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
            shell.close();
            go();
        });

        shell.pack();
        shell.open();
        while (!shell.isDisposed()) {
            if (!display.readAndDispatch()) display.sleep();
        }
        display.dispose();
    }

    private Table createTable(Shell shell, String sql) {
        final Table table = new Table(shell, SWT.MULTI | SWT.CHECK | SWT.BORDER | SWT.V_SCROLL);
        table.setLinesVisible(true);
        table.setHeaderVisible(true);
        table.setLayoutData(new GridData(SWT.FILL,SWT.CENTER,true,false));

        String[] titles = {"id", "书名", "作者"};
        for (int i = 0; i < titles.length; i++) {
            TableColumn column = new TableColumn(table, SWT.NONE);
            column.setText(titles[i]);
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
        table.getColumn(0).setWidth(60);
        table.getColumn(1).setWidth(250);
        table.getColumn(2).setWidth(250);
        table.pack();
        return table;
    }

    private Button createSubmitBtn(Shell shell) {
        Button submit = new Button(shell,SWT.PUSH);
        submit.setLayoutData(new GridData(SWT.CENTER,SWT.CENTER,true,false));
        submit.setText("提交");
        return submit;
    }
}
