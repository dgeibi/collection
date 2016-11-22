package xyz.dgeibi.java.library;

import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.*;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class History extends Dialog {
    final static int ALL = 1;
    String id;
    int option = 0;

    public History(Shell parent, String id) {
        super(parent);
        this.id = id;
        go();
    }

    public History(Shell parent, String id, int option) {
        super(parent);
        this.id = id;
        this.option = option;
        go();
    }

    void go() {
        Connection connection = Main.connection;
        Shell parent = getParent();
        Shell shell = new Shell(parent, SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
        shell.setLayout(new GridLayout());
        shell.setText(id + " - History");

        final Table table = new Table(shell, SWT.MULTI | SWT.BORDER | SWT.V_SCROLL);
        table.setLinesVisible(true);
        table.setHeaderVisible(true);
        GridData tableGridData = new GridData(SWT.LEFT, SWT.FILL, true, true);
        tableGridData.heightHint = 300;
        table.setLayoutData(tableGridData);
        String eSql1 = option == History.ALL ? "'" : "' AND returnTime IS NOT NULL";
        String sql1 = "SELECT bookID,businessTime,returnTime FROM history WHERE customerID = '" + id + eSql1;
        String[] titles = {"书名", "作者", "借阅时间", "归还时间"};
        for (int i = 0; i < titles.length; i++) {
            TableColumn column = new TableColumn(table, SWT.NONE);
            column.setText(titles[i]);
        }
        Statement st = null;
        ResultSet rs = null;
        try {
            st = connection.createStatement();
            rs = st.executeQuery(sql1);
            while (rs.next()) {
                TableItem item = new TableItem(table, SWT.NONE);
                String returnTime = rs.getString("returnTime");
                if (returnTime == null) {
                    returnTime = "未归还";
                }
                item.setText(2, rs.getString("businessTime"));
                item.setText(3, returnTime);
                String sql2 = "SELECT name,author FROM book " +
                        "WHERE id = '" + rs.getString("bookID") + "'";
                Statement st2 = null;
                ResultSet rs2 = null;
                try {
                    st2 = connection.createStatement();
                    rs2 = st2.executeQuery(sql2);
                    if (rs2.next()) {
                        String author = rs2.getString("author");
                        if (author == null) author = "";
                        item.setText(0, rs2.getString("name"));
                        item.setText(1, author);
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

        for (int i = 0; i < titles.length; i++) {
            table.getColumn(i).setWidth(250);
        }

        table.pack();
        shell.pack();
        shell.open();
        Display display = parent.getDisplay();
        while (!shell.isDisposed()) {
            if (!display.readAndDispatch()) display.sleep();
        }
    }
}
