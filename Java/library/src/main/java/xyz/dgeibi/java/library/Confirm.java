package xyz.dgeibi.java.library;

import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Dialog;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;

public class Confirm extends Dialog {
    boolean result = false;
    String message;

    public Confirm(Shell parent, String message) {
        super(parent);
        this.message = message;
    }

    public boolean go() {
        Shell parent = getParent();
        final Shell dialog = new Shell(parent, SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
        dialog.setText(message);
        GridLayout gridLayout = new GridLayout();
        gridLayout.numColumns = 2;
        dialog.setLayout(gridLayout);

        Label label = new Label(dialog, SWT.NONE);
        label.setText(message);
        label.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 2, 1));

        Widget.createBtn(dialog, "确定", event -> {
            result = true;
            dialog.close();
        });

        Widget.createBtn(dialog, "取消", event -> {
            dialog.close();
        });

        dialog.pack();
        dialog.open();

        Display display = parent.getDisplay();
        while (!dialog.isDisposed()) {
            if (!display.readAndDispatch()) display.sleep();
        }
        return result;
    }
}
