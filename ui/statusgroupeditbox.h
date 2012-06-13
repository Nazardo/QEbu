#ifndef STATUSGROUPEDITBOX_H
#define STATUSGROUPEDITBOX_H

#include <QWidget>
#include <QMap>

class StatusGroup;
class QLineEdit;
class QComboBox;
class QString;

class StatusGroupEditBox : public QWidget
{
    Q_OBJECT
public:
    explicit StatusGroupEditBox(StatusGroup *statusGroup = 0,
                                QWidget *parent = 0);
    StatusGroup *statusGroup();
    void updateExistingStatusGroup(StatusGroup *statusGroup);
    void addLinksMap(QMap<QString, QString> *values);
    QLineEdit *editStatusLabel();
    QComboBox *editStatusLink();
    QLineEdit *editStatusDefinition();
private slots:
    void onChange(int index);
    void onChange();
private:
    QLineEdit *m_editStatusLabel;
    QLineEdit *m_editStatusDefinition;
    QComboBox *m_editStatusLink;
    QList<QMap<QString, QString> *> m_linkMaps;
};

#endif // STATUSGROUPEDITBOX_H
