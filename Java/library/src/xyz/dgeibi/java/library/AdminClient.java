package xyz.dgeibi.java.library;

import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.TableEditor;
import org.eclipse.swt.graphics.Point;
import org.eclipse.swt.graphics.Rectangle;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.layout.RowData;
import org.eclipse.swt.layout.RowLayout;
import org.eclipse.swt.widgets.*;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class AdminClient {
    String id;
    Table table;
    String sql1;

    public AdminClient(String id) {
        this.id = id;
        this.go();
    }

    void reload() {
        Widget.reloadBookTable(table, sql1, Main.connection);
        table.getParent().layout();
    }

    void go() {
        Connection connection = Main.connection;
        Display display = Main.display;
        Shell shell = new Shell(display);
        shell.setLayout(new GridLayout());
        String username = "";
        try {
            Statement st = connection.createStatement();
            ResultSet rs = st.executeQuery("SELECT username FROM admin WHERE id = '" + id + "'");
            if (rs.next()) {
                username = rs.getString("username");
            }
        } catch (SQLException se) {
        }
        if (username == null) {
            username = id;
        }
        shell.setText("Admin: " + username + "(" + this.id + ") - GDUT Digital Library System");

        /*
         * Setting
         */
        Composite setting = new Composite(shell, SWT.NONE);
        setting.setLayout(new RowLayout());
        RowData rowData = new RowData();
        Widget.createBtn(setting, "注销", event -> {
            shell.close();
            new Login();
        }, rowData);
        Widget.createBtn(setting, "修改个人信息", event -> {
            shell.setText("Admin: " + new Profile(shell, id, "admin").go() + "(" + id + ") - GDUT Digital Library System");
        }, rowData);


        /* c1: 图书管理 */
        Composite c1 = new Composite(shell, SWT.NONE);
        GridLayout gridLayout = new GridLayout();
        gridLayout.numColumns = 2;
        c1.setLayout(gridLayout);

        new Label(c1, SWT.NONE).setText("所有书籍：");
        sql1 = "SELECT id,name,author FROM book";
        table = Widget.createBookTable(c1, sql1, connection, SWT.MULTI | SWT.CHECK | SWT.BORDER | SWT.V_SCROLL);
        GridData tableGridData = new GridData(SWT.CENTER, SWT.CENTER, true, true, 2, 1);
        tableGridData.heightHint = 200;
        table.setLayoutData(tableGridData);

        final TableEditor editor = new TableEditor(table);
        editor.horizontalAlignment = SWT.LEFT;
        editor.grabHorizontal = true;
        table.addListener(SWT.MouseDown, event -> {
            Rectangle clientArea = table.getClientArea();
            Point pt = new Point(event.x, event.y);
            int index = table.getTopIndex();
            while (index < table.getItemCount()) {
                boolean visible = false;
                final TableItem item = table.getItem(index);
                for (int i = 1; i < table.getColumnCount(); i++) {
                    Rectangle rect = item.getBounds(i);
                    if (rect.contains(pt)) {
                        final int column = i;
                        final Text text = new Text(table, SWT.NONE);
                        Listener textListener = e -> {
                            switch (e.type) {
                                case SWT.FocusOut:
                                    item.setText(column, text.getText());
                                    text.dispose();
                                    break;
                                case SWT.Traverse:
                                    switch (e.detail) {
                                        case SWT.TRAVERSE_RETURN:
                                            item.setText(column, text.getText());
                                        case SWT.TRAVERSE_ESCAPE:
                                            text.dispose();
                                            e.doit = false;
                                    }
                                    break;
                            }
                        };
                        text.addListener(SWT.FocusOut, textListener);
                        text.addListener(SWT.Traverse, textListener);
                        editor.setEditor(text, item, i);
                        text.setText(item.getText(i));
                        text.selectAll();
                        text.setFocus();
                        return;
                    }
                    if (!visible && rect.intersects(clientArea)) {
                        visible = true;
                    }
                }
                if (!visible) return;
                index++;
            }
        });
        Widget.createBtn(c1, "下架已选的书籍", event -> {
            Confirm confirm = new Confirm(shell, "确定下架已选的书籍？");
            if (confirm.go()) {
                TableItem[] items = table.getItems();
                for (TableItem item : items) {
                    if (item.getChecked()) {
                        String bookId = item.getText(0);
                        try {
                            Statement st = connection.createStatement();
                            st.executeUpdate("DELETE FROM book WHERE id = '" + bookId + "'");
                            st = connection.createStatement();
                            st.executeUpdate("DELETE FROM business WHERE bookid = '" + bookId + "'");
                        } catch (SQLException se) {
                            se.printStackTrace();
                        }
                    }
                }
                if (items.length > 0) {
                    reload();
                }
            }
        }).setLayoutData(new GridData(SWT.RIGHT, SWT.CENTER, true, false, 1, 1));

        Widget.createBtn(c1, "更新书籍信息", event -> {
            Confirm confirm = new Confirm(shell, "确定更新书籍信息？");
            if (confirm.go()) {
                TableItem[] items = table.getItems();
                for (TableItem item : items) {
                    try {
                        Statement st = connection.createStatement();
                        st.execute("UPDATE book SET name = '" + item.getText(1) + "',author = '" + item.getText(2) +
                                "' WHERE id = '" + item.getText(0) + "'");
                    } catch (SQLException se) {
                        se.printStackTrace();
                    }
                }
            }
        }).setLayoutData(new GridData(SWT.RIGHT, SWT.CENTER, false, false, 1, 1));


        /* c2: 图书添加 */
        Composite c2 = new Composite(shell, SWT.NONE);
        Label label = new Label(c2, SWT.NONE);
        label.setText("添加新图书：");
        label.setLayoutData(new GridData(SWT.LEFT, SWT.CENTER, true, true, 2, 1));
        gridLayout = new GridLayout();
        gridLayout.numColumns = 2;
        c2.setLayout(gridLayout);
        new Label(c2, SWT.NONE).setText("书名：");
        final Text tx1 = new Text(c2, SWT.SINGLE | SWT.BORDER);
        GridData gridData = new GridData(SWT.FILL, SWT.CENTER, true, true, 1, 1);
        gridData.minimumWidth = 500;
        tx1.setLayoutData(gridData);
        new Label(c2, SWT.NONE).setText("作者：");
        final Text tx2 = new Text(c2, SWT.SINGLE | SWT.BORDER);
        tx2.setLayoutData(gridData);
        Widget.createBtn(c2, "提交新书", event -> {
            Confirm confirm = new Confirm(shell, "确定提交新书？");
            if (confirm.go()) {
                try {
                    String name = tx1.getText();
                    String author = tx2.getText();
                    Statement st = connection.createStatement();
                    ResultSet rs = st.executeQuery("SELECT id FROM book WHERE name = '" + name +
                            "' AND author = '" + author + "'");
                    if (rs.next()) {
                        new Alert(shell, "您添加的图书已存在！", Alert.ERROR);
                    } else {
                        st = connection.createStatement();
                        if (st.executeUpdate("INSERT INTO book (name, author, publishTime) " +
                                " VALUES ('" + name + "','" + author + "', NOW())") == 1) {
                            new Alert(shell, "提交成功！", Alert.NOTICE);
                            reload();
                            tx1.setText("");
                            tx2.setText("");
                        }
                    }
                } catch (SQLException se) {
                    se.printStackTrace();
                }
            }
        }).setLayoutData(new GridData(SWT.RIGHT, SWT.CENTER, true, false, 2, 1));

        c1.pack();
        c2.pack();
        shell.pack();
        shell.open();
        while (!shell.isDisposed()) {
            if (!display.readAndDispatch()) display.sleep();
        }
    }
}
