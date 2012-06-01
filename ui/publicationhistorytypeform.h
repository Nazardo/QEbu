#ifndef PUBLICATIONHISTORYTYPEFORM_H
#define PUBLICATIONHISTORYTYPEFORM_H

#include "stackablewidget.h"

class PublicationHistoryType;
class ListView;
class QDateEdit;
class QTimeEdit;
class QComboBox;
class QPushButton;

class PublicationHistoryTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit PublicationHistoryTypeForm(PublicationHistoryType *entity,
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
    void repeatChecked(bool checked);
    // -
    void repeatFormClosed(Operation op, QVariant value);
private:
    void updateListAndButtons();

    ListView *m_listView;
    QDateEdit *m_editFirstPublicationDate;
    QTimeEdit *m_editFirstPublicationTime;
    QComboBox *m_editFirstPublicationChannel;
    QPushButton *m_buttonRepeat;
    PublicationHistoryType *m_publicationHistory;
};

#endif // PUBLICATIONHISTORYTYPEFORM_H
