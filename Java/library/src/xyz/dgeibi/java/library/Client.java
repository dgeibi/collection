package xyz.dgeibi.java.library;

import org.eclipse.swt.*;
import org.eclipse.swt.layout.*;
import org.eclipse.swt.widgets.*;
import java.sql.*;


public class Client {

    String userId;
    Display display;
    Connection connection;
    Shell shell;

    public Client(String userId, Display display, Connection connection) {
        this.userId = userId;
        this.display = display;
        this.connection = connection;
        this.shell = new Shell(this.display);
        this.shell.setLayout(new GridLayout());
        this.shell.setText(this.userId + " - GDUT Digital Library System");
        this.go();
    }

    void go() {
        Composite c1 = new Composite(shell, SWT.NONE);
        c1.setLayout(new GridLayout());
        // 借书
        Label label = new Label(c1, SWT.NONE);
        label.setText("借书：");
        String sql1 = "SELECT id,name,author FROM book" +
                " WHERE id NOT IN" +
                "(SELECT bookid FROM business WHERE userid = '" + userId + "')" ;
        final Table table1 = createTable(c1, sql1);
        Button submit = createSubmitBtn(c1);
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
            c1.dispose();
            go();
        });

        // 还书
        label = new Label(c1, SWT.NONE);
        label.setText("还书：");
        String sql2 = "SELECT id,name,author FROM book" +
                " WHERE id IN" +
                "(SELECT bookid FROM business WHERE userid = '" + userId + "')" ;
        final Table table2 = createTable(c1, sql2);
        submit = createSubmitBtn(c1);
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
            c1.dispose();
            go();
        });

        c1.pack();
        shell.pack();
        shell.open();
        while (!shell.isDisposed()) {
            if (!display.readAndDispatch()) display.sleep();
        }
        display.dispose();
    }

    private Table createTable(Composite c, String sql) {
        final Table table = new Table(c, SWT.MULTI | SWT.CHECK | SWT.BORDER | SWT.V_SCROLL);
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

    private Button createSubmitBtn(Composite c) {
        Button submit = new Button(c,SWT.PUSH);
        submit.setLayoutData(new GridData(SWT.CENTER,SWT.CENTER,true,false));
        submit.setText("提交");
        return submit;
    }
}
