#ifndef CONTACTDETAILSTYPEFORM_H
#define CONTACTDETAILSTYPEFORM_H

#include "stackablewidget.h"

class QPushButton;
class QLineEdit;
class QRadioButton;
class ListView;
class ContactDetailsType;

class ContactDetailsTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit ContactDetailsTypeForm(ContactDetailsType *contactDetails,
                                    QEbuMainWindow *mainWindow,
                                    QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // List view
    void addClicked();
    void editClicked();
    void removeClicked();
    // -
    void contactDetailsChecked(bool checked);
    void stageNameChecked(bool checked);
    void relatedContactsChecked(bool checked);
    void simpleNameChecked(bool checked);
    void complexNameChecked(bool checked);
    // -
    void detailsFormClosed(Operation op, QVariant value);
    void relatedContactsFormClosed(Operation op, QVariant value);
private:
    enum EditMode { Details, StageName, Related };
    void updateListAndButtons();
    bool eventFilter(QObject *obj, QEvent *event);
    ListView *m_listView;
    QLineEdit *m_editContactId;
    QLineEdit *m_editName;
    QLineEdit *m_editFamilyName;
    QLineEdit *m_editGivenName;
    QLineEdit *m_editUsername;
    QLineEdit *m_editOccupation;
    QRadioButton *m_radioName;
    QRadioButton *m_radioCName;
    QPushButton *m_buttonDetails;
    QPushButton *m_buttonStageName;
    QPushButton *m_buttonRelatedContacts;
    ContactDetailsType *m_contactDetails;
    EditMode m_currentEditMode;
};


#endif // CONTACTDETAILSTYPEFORM_H
