package xyz.dgeibi.java.library;

import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.*;
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
        Shell parent = getParent();
        Shell shell = new Shell(parent, SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
        shell.setLayout(new GridLayout());
        Label label;

        Composite composite = new Composite(shell,SWT.NONE);
        GridData gridData = new GridData();
        gridData.heightHint = 100;
        composite.setLayoutData(gridData);

        final int insetX = 4, insetY = 4;
        FormLayout formLayout = new FormLayout();
        formLayout.marginWidth = insetX;
        formLayout.marginHeight = insetY;
        formLayout.spacing = 40;
        composite.setLayout(formLayout);

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
        label = new Label(composite, SWT.NULL);
        label.setText(message);
        final FormData labelData = new FormData();
        labelData.left = new FormAttachment(0, 0);
        labelData.right = new FormAttachment(100, 0);
        label.setLayoutData(labelData);

        // OK btn
        Button btn = new Button(composite, SWT.PUSH);
        btn.setText("确定");
        final FormData btnData = new FormData();
        btnData.right = new FormAttachment(100, -insetX);
        btnData.bottom = new FormAttachment(100, 0);
        btn.setLayoutData(btnData);
        btn.addListener(SWT.Selection, event -> {
            shell.close();
        });

        composite.pack();
        shell.pack();
        shell.open();
        Display display = parent.getDisplay();
        while (!shell.isDisposed()) {
            if (!display.readAndDispatch()) display.sleep();
        }
        System.out.println(type + ": " + message);
    }
}
