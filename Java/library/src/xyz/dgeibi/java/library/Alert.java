package xyz.dgeibi.java.library;

import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.FormAttachment;
import org.eclipse.swt.layout.FormData;
import org.eclipse.swt.layout.FormLayout;
import org.eclipse.swt.widgets.*;

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
        Composite parent = getParent();
        Shell shell = new Shell((Shell) parent, SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
        Label label;

        final int insetX = 4, insetY = 4;
        FormLayout formLayout = new FormLayout();
        formLayout.marginWidth = insetX;
        formLayout.marginHeight = insetY;
        formLayout.spacing = 40;
        shell.setLayout(formLayout);

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
        label = new Label(shell, SWT.NULL);
        label.setText(message);
        final FormData labelData = new FormData();
        labelData.left = new FormAttachment(0, 0);
        labelData.right = new FormAttachment(100, 0);
        label.setLayoutData(labelData);

        // OK btn
        Button btn = new Button(shell, SWT.PUSH);
        btn.setText("确定");
        final FormData btnData = new FormData();
        btnData.right = new FormAttachment(100, -insetX);
        btnData.bottom = new FormAttachment(100, 0);
        btn.setLayoutData(btnData);
        btn.addListener(SWT.Selection, event -> {
            shell.close();
        });

        shell.setSize(200, 100);
        shell.open();
        Display display = parent.getDisplay();
        while (!shell.isDisposed()) {
            if (!display.readAndDispatch()) display.sleep();
        }
        System.out.println(type + ": " + message);
    }
}
