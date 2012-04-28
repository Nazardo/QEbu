#ifndef FORMATGROUP_H
#define FORMATGROUP_H

#include <QString>

class FormatGroup
{
public:
    FormatGroup();
    FormatGroup(const FormatGroup &copy);
    QString formatLabel() const;
    void setFormatLabel(const QString &formatLabel);
    QString formatDefinition() const;
    void setFormatDefinition(const QString &formatDefinition);
    QString formatLink() const;
    void setFormatLink(const QString &formatLink);

private:
    QString m_formatLabel;
    QString m_formatDefinition;
    QString m_formatLink; // anyURI
};

#endif // FORMATGROUP_H
