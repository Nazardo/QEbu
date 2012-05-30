#ifndef RIGHTSTYPEFORM_H
#define RIGHTSTYPEFORM_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QTextEdit>
#include <QComboBox>
#include "stackablewidget.h"
#include "typegroupform.h"
#include "listview.h"
#include "../model/coremetadatatype.h"

class RightsTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit RightsTypeForm(RightsType *rights, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
private slots:
    void cancelClicked();
    void applyClicked();
    // List view
    void addClicked();
    void editClicked();
    void removeClicked();
    // -
    void formatIDRefsChecked(bool checked);
    void rightsChecked(bool checked);
    void rightsHolderChecked(bool checked);
    void exploitationIssuesChecked(bool checked);
    void coverageChecked(bool checked);
    void disclaimerChecked(bool checked);
    void rightsIdChecked(bool checked);
    void contactDetailsChecked(bool checked);
    // -
    void formatIDRefsFormClosed(Operation op, QVariant value);
    void rightsFormClosed(Operation op, QVariant value);
    void rightsHolderFormClosed(Operation op, QVariant value);
    void exploitationIssuesFormClosed(Operation op, QVariant value);
    void coverageFormClosed(Operation op, QVariant value);
    void disclaimerFormClosed(Operation op, QVariant value);
    void rightsIdFormClosed(Operation op, QVariant value);
    void contactDetailsFormClosed(Operation op, QVariant value);
private:
    enum EditMode { FormatIDRefs, Rights, RightsHolder, ExploitationIssues,
                  Coverage, Disclaimer, RightsId, ContactDetails };
    void updateListAndButtons();

    QVBoxLayout *m_mainVLayout;
    ListView *m_listView;
    TypeGroupEditBox *m_editTypeGroup;
    QLineEdit *m_editRightsLink;
    QCheckBox *m_checkRightsClearanceFlag;
    QTextEdit *m_textNote;
    QPushButton *m_comboFormatIDRefs;
    QPushButton *m_buttonRights;
    QPushButton *m_buttonRightsHolder;
    QPushButton *m_buttonExploitationIssues;
    QPushButton *m_buttonCoverage;
    QPushButton *m_buttonDisclaimer;
    QPushButton *m_buttonRightsId;
    QPushButton *m_buttonContactDetails;
    RightsType *m_rights;
    Operation m_op;
    EditMode m_currentEditMode;
};

#endif // RIGHTSTYPEFORM_H
