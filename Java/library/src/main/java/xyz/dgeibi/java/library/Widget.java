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
        GridData tableGridData = new GridData(SWT.LEFT, SWT.FILL, true, true);
        tableGridData.heightHint = 200;
        table.setLayoutData(tableGridData);

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

    public static void reloadBookTable(Table table, String sql, Connection connection) {

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

    public static Button createBtn(Composite c, String text) {
        Button btn = new Button(c, SWT.PUSH);
        btn.setText(text);
        return btn;
    }

    public static Button createBtn(Composite c, String text, Listener listener) {
        Button btn = createBtn(c, text);
        btn.addListener(SWT.Selection, listener);
        return btn;
    }

    public static Button createBtn(Composite c, String text, Object data, Listener listener) {
        Button btn = createBtn(c, text, listener);
        btn.setLayoutData(data);
        return btn;
    }

    //http://stackoverflow.com/questions/10038570/implementing-select-on-focus-behavior-for-an-eclipse-text-control

    /**
     * This method adds select-on-focus functionality to a {@link Text} component.
     * <p>
     * Specific behavior:
     * - when the Text is already focused -> normal behavior
     * - when the Text is not focused:
     * -> focus by keyboard -> select all text
     * -> focus by mouse click -> select all text unless user manually selects text
     *
     * @param text
     */
    public static void addSelectOnFocusToText(Text text) {
        Listener listener = new Listener() {

            private boolean hasFocus = false;
            private boolean hadFocusOnMousedown = false;

            @Override
            public void handleEvent(Event e) {
                switch (e.type) {
                    case SWT.FocusIn: {
                        Text t = (Text) e.widget;

                        // Covers the case where the user focuses by keyboard.
                        t.selectAll();

                        // The case where the user focuses by mouse click is special because Eclipse,
                        // for some reason, fires SWT.FocusIn before SWT.MouseDown, and on mouse down
                        // it cancels the selection. So we set a variable to keep track of whether the
                        // control is focused (can't rely on isFocusControl() because sometimes it's wrong),
                        // and we make it asynchronous so it will get set AFTER SWT.MouseDown is fired.
                        t.getDisplay().asyncExec(new Runnable() {
                            @Override
                            public void run() {
                                hasFocus = true;
                            }
                        });

                        break;
                    }
                    case SWT.FocusOut: {
                        hasFocus = false;
                        ((Text) e.widget).clearSelection();

                        break;
                    }
                    case SWT.MouseDown: {
                        // Set the variable which is used in SWT.MouseUp.
                        hadFocusOnMousedown = hasFocus;

                        break;
                    }
                    case SWT.MouseUp: {
                        Text t = (Text) e.widget;
                        if (t.getSelectionCount() == 0 && !hadFocusOnMousedown) {
                            ((Text) e.widget).selectAll();
                        }

                        break;
                    }
                }
            }

        };

        text.addListener(SWT.FocusIn, listener);
        text.addListener(SWT.FocusOut, listener);
        text.addListener(SWT.MouseDown, listener);
        text.addListener(SWT.MouseUp, listener);
    }
}
