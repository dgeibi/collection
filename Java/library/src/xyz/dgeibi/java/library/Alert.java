package xyz.dgeibi.java.library;

import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.FormAttachment;
import org.eclipse.swt.layout.FormData;
import org.eclipse.swt.layout.FormLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;


public class Alert {

    final static int ERROR = 0;
    final static int NOTICE = 1;
    Shell parentShell;
    String message;
    int option;

    public Alert(Shell parentShell, String message, int option) {
        this.parentShell = parentShell;
        this.message = message;
        this.option = option;
        this.go();
    }

    void go() {
        Shell shell = new Shell(parentShell);
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
        System.out.println(type + ": " + message);
    }
}
