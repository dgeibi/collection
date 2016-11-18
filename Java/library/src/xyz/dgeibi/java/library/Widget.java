package xyz.dgeibi.java.library;

import org.eclipse.swt.*;
import org.eclipse.swt.layout.*;
import org.eclipse.swt.widgets.*;
import java.sql.*;

/**
 * Created by dgeibi on 11/18/16.
 */
public class Widget {
    public static Table createBookTable(Composite c, String sql, Connection connection, int options) {
        final Table table = new Table(c, options);
        table.setLinesVisible(true);
        table.setHeaderVisible(true);
        table.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false));

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

    public static Button createBtn(Composite c, String text) {
        Button btn = new Button(c, SWT.PUSH);
        btn.setLayoutData(new GridData(SWT.CENTER, SWT.CENTER, true, false));
        btn.setText(text);
        return btn;
    }

    public static Button createBtn(Composite c, String text, Listener listener) {
        Button btn = new Button(c, SWT.PUSH);
        btn.setLayoutData(new GridData(SWT.CENTER, SWT.CENTER, true, false));
        btn.setText(text);
        btn.addListener(SWT.Selection, listener);
        return btn;
    }
}
