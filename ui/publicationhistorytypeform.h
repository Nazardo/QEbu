#ifndef PUBLICATIONHISTORYTYPEFORM_H
#define PUBLICATIONHISTORYTYPEFORM_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTimeEdit>
#include <QDateEdit>
#include <QComboBox>
#include "stackablewidget.h"
#include "listview.h"
#include "../model/ebucoremaintype.h"

class PublicationHistoryTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit PublicationHistoryTypeForm(PublicationHistoryType *entity,
                                        QEbuMainWindow *mainWindow, QWidget *parent = 0);
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
    void repeatChecked(bool checked);
    // -
    void repeatFormClosed(Operation op, QVariant value);
private:
    void updateListAndButtons();

    QHBoxLayout *m_mainHLayout;
    ListView *m_listView;
    QDateEdit *m_editFirstPublicationDate;
    QTimeEdit *m_editFirstPublicationTime;
    QComboBox *m_editFirstPublicationChannel;
    QPushButton *m_buttonRepeat;
    PublicationHistoryType *m_publicationHistory;
    Operation m_op;
};

#endif // PUBLICATIONHISTORYTYPEFORM_H
