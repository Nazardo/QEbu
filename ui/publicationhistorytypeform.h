#ifndef PUBLICATIONHISTORYTYPEFORM_H
#define PUBLICATIONHISTORYTYPEFORM_H

#include "stackablewidget.h"

class PublicationHistoryType;
class ListView;
class QDateEdit;
class QTimeEdit;
class QComboBox;
class QCheckBox;
class QLineEdit;

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
    void firstPublicationTimeChanged();
    void firstPublicationDateChanged();
    void firstPublicationChannelChanged();
    // -
    void repeatFormClosed(Operation op, QVariant value);
private:
    bool eventFilter(QObject *obj, QEvent *event);

    ListView *m_listView;
    QCheckBox *m_checkFirstPublicationDate;
    QCheckBox *m_checkFirstPublicationTime;
    QDateEdit *m_editFirstPublicationDate;
    QTimeEdit *m_editFirstPublicationTime;
    QCheckBox *m_checkFirstPublicationChannel;
    QComboBox *m_editFirstPublicationChannel;
    QLineEdit *m_editFirstPublicationChannelString;
    PublicationHistoryType *m_publicationHistory;
};

#endif // PUBLICATIONHISTORYTYPEFORM_H
