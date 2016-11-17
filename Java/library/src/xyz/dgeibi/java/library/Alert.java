package xyz.dgeibi.java.library;

import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;


public class Alert {
    Shell parentShell;
    String info;

    public Alert(Shell parentShell, String info) {
        this.parentShell = parentShell;
        this.info = info;
        this.go();
    }

    void go() {
        Shell shell = new Shell(parentShell);
        shell.setLayout(new GridLayout());
        shell.setText("Error");
        Label label = new Label(shell, SWT.NULL);
        label.setText(info);
        label.setLayoutData(new GridData(SWT.CENTER, SWT.CENTER, true, false));
        Button btn = new Button(shell, SWT.PUSH);
        btn.setLayoutData(new GridData(SWT.CENTER, SWT.CENTER, true, false));
        btn.setText("关闭");
        btn.addListener(SWT.Selection, event -> {
            shell.close();
        });
        shell.pack();
        shell.open();
        System.out.println("Error: " + info);
    }
}
