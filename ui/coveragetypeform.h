#ifndef COVERAGETYPEFORM_H
#define COVERAGETYPEFORM_H

#include "stackablewidget.h"

class CoverageType;
class QPushButton;
class ListView;
class ElementTypeEditBox;

class CoverageTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit CoverageTypeForm(CoverageType *coverage,
                              QEbuMainWindow *mainWindow,
                              QWidget *parent = 0);
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
    bool eventFilter(QObject *obj, QEvent *event);
    ListView *m_listView;
    ElementTypeEditBox *m_editCoverage;
    QPushButton *m_buttonTemporal;
    QPushButton *m_buttonLocation;
    CoverageType *m_coverage;
    EditMode m_currentEditMode;
};

#endif // COVERAGETYPEFORM_H
