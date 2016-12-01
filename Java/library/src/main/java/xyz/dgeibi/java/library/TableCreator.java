package xyz.dgeibi.java.library;

import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableColumn;

abstract class TableCreator {
    Table table;

    Table init(Composite c, String[] titles) {
        table = new Table(c, SWT.MULTI | SWT.CHECK | SWT.BORDER | SWT.V_SCROLL);
        table.setLinesVisible(true);
        table.setHeaderVisible(true);
        GridData tableGridData = new GridData(SWT.LEFT, SWT.FILL, true, true);
        tableGridData.heightHint = 200;
        table.setLayoutData(tableGridData);
        for (int i = 0; i < titles.length; i++) {
            TableColumn column = new TableColumn(table, SWT.NONE);
            column.setText(titles[i]);
        }
        reload();
        table.getColumn(0).setWidth(60);
        table.getColumn(1).setWidth(250);
        table.getColumn(2).setWidth(250);
        table.pack();
        return table;
    }

    abstract void reload();
}
