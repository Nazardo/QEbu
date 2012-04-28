#ifndef ELEMENTTYPE_H
#define ELEMENTTYPE_H

#include <QString>

class ElementType
{
public:
    ElementType();
    ElementType(const QString &value, const QString &lang = "en");
    QString value() const;
    void setValue(const QString &value);
    QString lang() const;
    void setLang(const QString &lang);
private:
    QString m_value;
    QString m_lang;
};

#endif // ELEMENTTYPE_H
