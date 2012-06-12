#ifndef DATETYPEFORM_H
#define DATETYPEFORM_H

#include "stackablewidget.h"

class DateType;
class ListView;
class QPushButton;

class DateTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit DateTypeForm(DateType *date,
                          QEbuMainWindow *mainWindow,
                          QWidget *parent = 0);
    QString toString();
private slots:
    void applyClicked();
    void cancelClicked();
    // Toggle buttons:
    void dateChecked(bool checked);
    void createdChecked(bool checked);
    void issuedChecked(bool checked);
    void modifiedChecked(bool checked);
    void digitisedChecked(bool checked);
    void alternativeChecked(bool checked);
    // List view:
    void addClicked();
    void editClicked();
    void removeClicked();
    void elementTypeFormClosed(Operation op, QVariant value);
    void dateGroupFormClosed(Operation op, QVariant value);
    void alternativeTypeFormClosed(Operation op, QVariant value);
private:
    enum EditMode {
        Date,
        Created,
        Issued,
        Modified,
        Digitised,
        Alternative
    };
    void updateListTitle();
    bool eventFilter(QObject *, QEvent *);
    EditMode m_currentEditMode;
    DateType *m_date;
    QPushButton *m_buttonDate;
    QPushButton *m_buttonCreated;
    QPushButton *m_buttonIssued;
    QPushButton *m_buttonModified;
    QPushButton *m_buttonDigitised;
    QPushButton *m_buttonAlternative;
    ListView *m_listView;
};

#endif // DATETYPEFORM_H
