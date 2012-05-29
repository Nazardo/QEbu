#ifndef COVERAGETYPEFORM_H
#define COVERAGETYPEFORM_H

#include "stackablewidget.h"
#include <QPushButton>
#include "listview.h"
#include "../model/coremetadatatype.h"
#include "elementtypeeditbox.h"

class CoverageTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit CoverageTypeForm(CoverageType *coverage, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
private slots:
    void cancelClicked();
    void applyClicked();
    // List view
    void addClicked();
    void editClicked();
    void removeClicked();
    // -
    void temporalChecked(bool checked);
    void locationChecked(bool checked);
    // -
    void temporalFormClosed(Operation op, QVariant value);
    void locationFormClosed(Operation op, QVariant value);
private:
    enum EditMode { Temporal, Location };
    void updateListAndButtons();

    QHBoxLayout *m_mainHLayout;
    ListView *m_listView;
    ElementTypeEditBox *m_editCoverage;
    QPushButton *m_buttonTemporal;
    QPushButton *m_buttonLocation;
    CoverageType *m_coverage;
    Operation m_op;
    EditMode m_currentEditMode;
};

#endif // COVERAGETYPEFORM_H
