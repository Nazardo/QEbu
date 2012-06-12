#ifndef DETAILSTYPEFORM_H
#define DETAILSTYPEFORM_H

#include "stackablewidget.h"

class DetailsType;
class ListView;
class QPushButton;
class QLineEdit;
class TypeGroupEditBox;

class DetailsTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit DetailsTypeForm(DetailsType *details,
                             QEbuMainWindow *mainWindow,
                             QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // List view
    void addClicked();
    void editClicked();
    void removeClicked();
    // -
    void addressChecked(bool checked);
    // -
    void addressFormClosed(Operation op, QVariant value);
private:
    void updateListAndButtons();
    bool eventFilter(QObject *, QEvent *);
    ListView *m_listView;
    TypeGroupEditBox *m_editTypeGroup;
    QLineEdit *m_editEmailAddress;
    QLineEdit *m_editWebAddress;
    QLineEdit *m_editTelephoneNumber;
    QLineEdit *m_editMobileTelephoneNumber;
    QPushButton *m_buttonAddress;
    DetailsType *m_details;
};

#endif // DETAILSTYPEFORM_H
