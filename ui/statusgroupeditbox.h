#ifndef STATUSGROUPEDITBOX_H
#define STATUSGROUPEDITBOX_H

#include <QWidget>
#include <QLineEdit>
#include "../model/statusgroup.h"

class StatusGroupEditBox : public QWidget
{
    Q_OBJECT
public:
    explicit StatusGroupEditBox(StatusGroup *statusGroup = 0, QWidget *parent = 0);
    StatusGroup *statusGroup();
    void updateExistingStatusGroup(StatusGroup *statusGroup);
private:
    QLineEdit *m_editStatusLabel;
    QLineEdit *m_editStatusDefinition;
    QLineEdit *m_editStatusLink;
};

#endif // STATUSGROUPEDITBOX_H
