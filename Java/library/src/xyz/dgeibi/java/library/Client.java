package xyz.dgeibi.java.library;

import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.*;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Client {

    String userId;
    Display display;
    Connection connection;

    public Client(String userId, Display display, Connection connection) {
        this.userId = userId;
        this.display = display;
        this.connection = connection;
    }

    void go() {
        Shell shell = new Shell(display);
        shell.setText(userId + " - GDUT Library System");
        Table table = new Table(shell, SWT.MULTI | SWT.CHECK | SWT.BORDER | SWT.V_SCROLL);
        table.setLinesVisible(true);
        table.setHeaderVisible(true);

        String[] titles = {"id", "书名", "作者"};
        for (int i = 0; i < titles.length; i++) {
            TableColumn column = new TableColumn(table, SWT.NONE);
            column.setText(titles[i]);
        }
        try {
            Statement st = connection.createStatement();
            String sql = "SELECT id,name,author FROM book;";
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
        for (int i = 1; i < titles.length; i++) {
            table.getColumn(i).pack();
        }
        table.pack();
        table.addListener(SWT.Selection, event -> {
            String string = event.detail == SWT.CHECK ? "Checked" : "Selected";
            System.out.println(event.item + " " + string);
        });
        shell.pack();
        shell.open();
        while (!shell.isDisposed()) {
            if (!display.readAndDispatch()) display.sleep();
        }
        display.dispose();
    }
}