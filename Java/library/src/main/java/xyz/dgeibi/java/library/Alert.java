package xyz.dgeibi.java.library;

import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Dialog;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;

public class Alert extends Dialog {

    final static int ERROR = 0;
    final static int NOTICE = 1;
    String message;
    int option;

    public Alert(Shell parentShell, String message, int option) {
        super(parentShell);
        this.message = message;
        this.option = option;
        this.go();
    }

    void go() {
        Shell parent = getParent();
        Shell shell = new Shell(parent, SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
        shell.setLayout(new GridLayout());

        String type = "";
        switch (option) {
            case ERROR:
                type = "Error";
                break;
            case NOTICE:
                type = "Notice";
                break;
        }

        shell.setText(type);

        // message
        Label label = new Label(shell, SWT.NULL);
        label.setText(message);
        label.setLayoutData(new GridData(SWT.LEFT, SWT.CENTER, true, false));

        // OK btn
        Widget.createBtn(shell, "确定", new GridData(SWT.RIGHT, SWT.CENTER, true, false), event -> {
            shell.close();
        });

        shell.pack();
        shell.open();

        Display display = parent.getDisplay();
        while (!shell.isDisposed()) {
            if (!display.readAndDispatch()) display.sleep();
        }
        System.out.println(type + ": " + message);
    }
}
