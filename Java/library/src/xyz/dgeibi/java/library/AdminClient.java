package xyz.dgeibi.java.library;

import org.eclipse.swt.*;
import org.eclipse.swt.layout.*;
import org.eclipse.swt.widgets.*;
import java.sql.*;


public class AdminClient {
    String adminId;
    Display display;
    Connection connection;


    public AdminClient(String adminId, Display display, Connection connection) {
        this.adminId = adminId;
        this.display = display;
        this.connection = connection;
        this.go();
    }

    void reload(Shell parent) {
        Composite c1 = new Composite(parent, SWT.NONE);
        c1.setLayout(new GridLayout());
        Label label = new Label(c1, SWT.NONE);
        label.setText("已有的书籍：");
        c1.pack();
        String sql1 = "SELECT id,name,author FROM book";
        final Table table1 = Widget.createBookTable(c1, sql1, connection, SWT.MULTI | SWT.CHECK | SWT.BORDER | SWT.V_SCROLL);
        Widget.createBtn(c1, "下架", event -> {
            Confirm confirm = new Confirm(parent, "确定下架？");
            if (confirm.go()) {
                TableItem[] items = table1.getItems();
                for (TableItem item : items) {
                    if (item.getChecked()) {
                        String bookId = item.getText(0);
                        try {
                            Statement st = connection.createStatement();
                            String sql = "DELETE FROM book WHERE id = '" + bookId + "'";
                            st.executeUpdate(sql);
                        } catch (SQLException se) {
                            se.printStackTrace();
                        }
                    }
                }
                if (items.length > 0) {
                    c1.dispose();
                    reload(parent);
                }
            }
        });
        // TODO: add books
        parent.pack();
    }

    void go() {
        Shell shell = new Shell(this.display);
        shell.setLayout(new GridLayout());
        shell.setText("Admin: " + this.adminId + " - GDUT Digital Library System");
        reload(shell);
        shell.open();

        while (!shell.isDisposed()) {
            if (!display.readAndDispatch()) display.sleep();
        }
        display.dispose();
    }
}
