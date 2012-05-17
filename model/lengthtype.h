#ifndef LENGTHTYPE_H
#define LENGTHTYPE_H

#include <QString>

class LengthType
{
public:
    LengthType();
    ~LengthType();
    LengthType(const unsigned int &value, const QString &unit);
    unsigned int *value() const;
    void setValue(const unsigned int &value);
    QString unit() const;
    void setUnit(const QString &unit);
    QString toString() const;
private:
    unsigned int *m_value;    // nonNegativeInteger
    QString m_unit;
};

#endif // LENGTHTYPE_H
