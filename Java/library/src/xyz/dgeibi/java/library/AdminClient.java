package xyz.dgeibi.java.library;

import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.*;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

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
    /* TODO:
     *  support password update
     *  editable table
     */
    void reload(Shell parent) {
        Composite c1 = new Composite(parent, SWT.NONE);
        GridLayout gridLayout = new GridLayout();
        gridLayout.numColumns = 2;
        c1.setLayout(gridLayout);

        Label label = new Label(c1, SWT.NONE);
        label.setText("所有书籍：");
        String sql1 = "SELECT id,name,author FROM book";
        final Table table1 = Widget.createBookTable(c1, sql1, connection, SWT.MULTI | SWT.CHECK | SWT.BORDER | SWT.V_SCROLL);
        table1.setLayoutData(new GridData(SWT.CENTER, SWT.CENTER, true, true, 2, 1));


        Composite c2 = new Composite(parent, SWT.NONE);
        label = new Label(c2, SWT.NONE);
        label.setText("添加新图书：");
        label.setLayoutData(new GridData(SWT.LEFT, SWT.CENTER, true, true, 2, 1));
        gridLayout = new GridLayout();
        gridLayout.numColumns = 2;
        c2.setLayout(gridLayout);
        new Label(c2, SWT.NONE).setText("书名：");
        final Text tx1 = new Text(c2, SWT.SINGLE);
        GridData gridData = new GridData(SWT.FILL, SWT.CENTER, true, true, 1, 1);
        gridData.minimumWidth = 500;
        tx1.setLayoutData(gridData);
        new Label(c2, SWT.NONE).setText("作者：");
        final Text tx2 = new Text(c2, SWT.SINGLE);
        tx2.setLayoutData(gridData);

        Widget.createBtn(c2, "提交新书", event -> {
            Confirm confirm = new Confirm(parent, "确定提交新书？");
            if (confirm.go()) {
                try {
                    String name = tx1.getText();
                    String author = tx2.getText();
                    Statement st = connection.createStatement();
                    ResultSet rs = st.executeQuery("SELECT id FROM book WHERE name = '" + name +
                            "' AND author = '" + author + "'");
                    if (rs.next()) {
                        new Alert(parent, "您添加的图书已存在！", Alert.ERROR);
                    } else {
                        st = connection.createStatement();
                        if (st.executeUpdate("INSERT INTO book (name, author, publishTime) " +
                                " VALUES (' " + name + "','" + author + "', NOW())") == 1) {
                            new Alert(parent, "提交成功！", Alert.NOTICE);
                        }
                        c1.dispose();
                        c2.dispose();
                        reload(parent);
                    }
                } catch (SQLException se) {
                    se.printStackTrace();
                }
            }
        }).setLayoutData(new GridData(SWT.CENTER, SWT.CENTER, true, false, 2, 1));

        Widget.createBtn(c1, "下架已选的书籍", event -> {
            Confirm confirm = new Confirm(parent, "确定下架已选的书籍？");
            if (confirm.go()) {
                TableItem[] items = table1.getItems();
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
                    c1.dispose();
                    c2.dispose();
                    reload(parent);
                }
            }
        }).setLayoutData(new GridData(SWT.CENTER, SWT.CENTER, true, false, 2, 1));

        c1.pack();
        c2.pack();
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
    }
}
