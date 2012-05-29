#ifndef PUBLICATIONTYPEFORM_H
#define PUBLICATIONTYPEFORM_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTimeEdit>
#include <QDateEdit>
#include <QComboBox>
#include "stackablewidget.h"
#include "listview.h"
#include "../model/ebucoremaintype.h"

class PublicationTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit PublicationTypeForm(PublicationType *publication,
                                        QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
private:
    void updateListAndButtons();

    QHBoxLayout *m_mainHLayout;
    QDateEdit *m_editPublicationDate;
    QTimeEdit *m_editPublicationTime;
    QComboBox *m_editPublicationChannel;
    PublicationType *m_publication;
    Operation m_op;
};

#endif // PUBLICATIONTYPEFORM_H
