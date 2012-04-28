#ifndef STATUSGROUP_H
#define STATUSGROUP_H

#include <QString>

class StatusGroup
{
public:
    StatusGroup();
    StatusGroup(const StatusGroup &copy);
    QString statusLabel() const;
    void setStatusLabel(const QString &statusLabel);
    QString statusDefinition() const;
    void setStatusDefinition(const QString &statusDefinition);
    QString statusLink() const;
    void setStatusLink(const QString &statusLink);

private:
    QString m_statusLabel;
    QString m_statusDefinition;
    QString m_statusLink;
};

#endif // STATUSGROUP_H
