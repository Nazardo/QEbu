#ifndef PUBLICATIONTYPEFORM_H
#define PUBLICATIONTYPEFORM_H

#include "stackablewidget.h"

class PublicationType;
class QDateEdit;
class QTimeEdit;
class QComboBox;

class PublicationTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit PublicationTypeForm(PublicationType *publication,
                                 QEbuMainWindow *mainWindow,
                                 QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
private:
    void updateListAndButtons();

    QDateEdit *m_editPublicationDate;
    QTimeEdit *m_editPublicationTime;
    QComboBox *m_editPublicationChannel;
    PublicationType *m_publication;
};

#endif // PUBLICATIONTYPEFORM_H
