package xyz.dgeibi.java.library;

import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.widgets.*;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Widget {
    public static Table createBookTable(Composite c, String sql, Connection connection, int options) {
        final Table table = new Table(c, options);
        table.setLinesVisible(true);
        table.setHeaderVisible(true);


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

    public static Button createBtn(Composite c, String text, Listener listener) {
        Button btn = new Button(c, SWT.PUSH);
        btn.setText(text);
        btn.addListener(SWT.Selection, listener);
        btn.setLayoutData(new GridData(SWT.CENTER, SWT.CENTER, true, false));
        return btn;
    }

    public static Button createBtn(Composite c, String text, Listener listener, Object data) {
        Button btn = new Button(c, SWT.PUSH);
        btn.setText(text);
        btn.addListener(SWT.Selection, listener);
        btn.setLayoutData(data);
        return btn;
    }
}
