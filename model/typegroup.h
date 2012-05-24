#ifndef ATTRIBUTETYPEGROUP_H
#define ATTRIBUTETYPEGROUP_H

#include <QString>

class TypeGroup
{
public:
    TypeGroup();
    QString typeLabel() const;
    void setTypeLabel(const QString &typeLabel);
    QString typeDefinition() const;
    void setTypeDefinition(const QString &typeDefinition);
    QString typeLink() const;
    void setTypeLink(const QString &typeLink);
    QString toString() const;
private:
    QString m_typeLabel;
    QString m_typeDefinition;
    QString m_typeLink; // anyURI
};

#endif // ATTRIBUTETYPEGROUP_H
