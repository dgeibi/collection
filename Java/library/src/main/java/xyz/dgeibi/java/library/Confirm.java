package xyz.dgeibi.java.library;

import org.eclipse.swt.SWT;
import org.eclipse.swt.graphics.Point;
import org.eclipse.swt.graphics.Rectangle;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Dialog;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;

class Confirm extends Dialog {
    private boolean result = false;
    private String message;

    Confirm(Shell parent, String message) {
        super(parent);
        this.message = message;
    }

    boolean go() {
        Shell parent = getParent();
        final Shell dialog = new Shell(parent, SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
        dialog.setText(message);
        GridLayout gridLayout = new GridLayout();
        gridLayout.numColumns = 2;
        dialog.setLayout(gridLayout);

        Label label = new Label(dialog, SWT.NONE);
        label.setText(message);
        label.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 2, 1));

        Widget.createBtn(dialog, "确定", new GridData(SWT.RIGHT, SWT.CENTER, true, false), event -> {
            result = true;
            dialog.close();
        });

        Widget.createBtn(dialog, "取消", new GridData(SWT.RIGHT, SWT.CENTER, false, false), event -> {
            dialog.close();
        });

        dialog.pack();

        Rectangle parentSize = getParent().getBounds();
        Rectangle shellSize = dialog.getBounds();
        int locationX = (parentSize.width - shellSize.width) / 2 + parentSize.x;
        int locationY = (parentSize.height - shellSize.height) / 2 + parentSize.y;
        dialog.setLocation(new Point(locationX, locationY));

        dialog.open();

        Display display = parent.getDisplay();
        while (!dialog.isDisposed()) {
            if (!display.readAndDispatch()) display.sleep();
        }
        return result;
    }
}
