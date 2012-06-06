#ifndef TECHNICALATTRIBUTES_H
#define TECHNICALATTRIBUTES_H

#include "typegroup.h"
#include "formatgroup.h"
#include <QString>
#include <QList>

class TechnicalAttributeRationalType;
class TechnicalAttributeUriType;
class String;
class Int8;
class Int16;
class Int32;
class Int64;
class UInt8;
class UInt16;
class UInt32;
class UInt64;
class Boolean;
class Float;
class TechnicalAttributes
{
public:
    TechnicalAttributes();
    ~TechnicalAttributes();
    QString toString();
    //Elements
    QList<String *> &technicalAttributeString();
    QList<Int8 *> &technicalAttributeByte();
    QList<Int16 *> &technicalAttributeShort();
    QList<Int32 *> &technicalAttributeInteger();
    QList<Int64 *> &technicalAttributeLong();
    QList<UInt8 *> &technicalAttributeUnsignedByte();
    QList<UInt16 *> &technicalAttributeUnsignedShort();
    QList<UInt32 *> &technicalAttributeUnsignedInteger();
    QList<UInt64 *> &technicalAttributeUnsignedLong();
    QList<Boolean *> &technicalAttributeBoolean();
    QList<Float *> &technicalAttributeFloat();
    QList<TechnicalAttributeRationalType *> &technicalAttributeRational();
    QList<TechnicalAttributeUriType *> &technicalAttributeUri();
private:
    // Elements
    QList<String*> m_technicalAttributeString;
    QList<Int8*> m_technicalAttributeByte;
    QList<Int16*> m_technicalAttributeShort;
    QList<Int32*> m_technicalAttributeInteger;
    QList<Int64*> m_technicalAttributeLong;
    QList<UInt8*> m_technicalAttributeUnsignedByte;
    QList<UInt16*> m_technicalAttributeUnsignedShort;
    QList<UInt32*> m_technicalAttributeUnsignedInteger;
    QList<UInt64*> m_technicalAttributeUnsignedLong;
    QList<Boolean*> m_technicalAttributeBoolean;
    QList<Float*> m_technicalAttributeFloat;
    QList<TechnicalAttributeRationalType*> m_technicalAttributeRational;
    QList<TechnicalAttributeUriType*> m_technicalAttributeUri;
};


class String : public TypeGroup, public FormatGroup
{
public:
    String();
    //Attributes
    QString value() const;
    void setValue(const QString &value);
    QString toString() const;
private:
    QString m_value;
};

class Int8 : public TypeGroup
{
public:
    Int8();
    ~Int8();
    //Attributes
    qint8 *value() const;
    void setValue(qint8 value);
    void clearValue();
    QString toString() const;
private:
    qint8 *m_value;
};

class Int16 : public TypeGroup
{
public:
    Int16();
    ~Int16();
    //Attributes
    qint16 *value() const;
    void setValue(qint16 value);
    void clearValue();
    QString toString() const;
private:
    qint16 *m_value;
};

class Int32 : public TypeGroup
{
public:
    Int32();
    ~Int32();
    //Attributes
    qint32 *value() const;
    void setValue(qint32 value);
    void clearValue();
    QString toString() const;
private:
    qint32 *m_value;
};

class Int64 : public TypeGroup
{
public:
    Int64();
    ~Int64();
    //Attributes
    qint64 *value() const;
    void setValue(qint64 value);
    void clearValue();
    QString toString() const;
private:
    qint64 *m_value;
};

class UInt8 : public TypeGroup
{
public:
    UInt8();
    ~UInt8();
    //Attributes
    quint8 *value() const;
    void setValue(quint8 value);
    void clearValue();
    QString toString() const;
private:
    quint8 *m_value;
};

class UInt16 : public TypeGroup
{
public:
    UInt16();
    ~UInt16();
    //Attributes
    quint16 *value() const;
    void setValue(quint16 value);
    void clearValue();
    QString toString() const;
private:
    quint16 *m_value;
};

class UInt32 : public TypeGroup
{
public:
    UInt32();
    ~UInt32();
    //Attributes
    quint32 *value() const;
    void setValue(quint32 value);
    void clearValue();
    QString toString() const;
private:
    quint32 *m_value;
};

class UInt64 : public TypeGroup
{
public:
    UInt64();
    ~UInt64();
    //Attributes
    quint64 *value() const;
    void setValue(quint64 value);
    void clearValue();
    QString toString() const;
private:
    quint64 *m_value;
};

class Boolean : public TypeGroup
{
public:
    Boolean();
    ~Boolean();
    //Attributes
    bool *value() const;
    void setValue(bool value);
    QString toString() const;
private:
    bool *m_value;
};

class Float : public TypeGroup
{
public:
    Float();
    ~Float();
    //Attributes
    double *value() const;
    void setValue(double value);
    void clearValue();
    QString toString() const;
private:
    double *m_value;
};

class TechnicalAttributeUriType : public TypeGroup
{
public:
    TechnicalAttributeUriType();
    //Attributes
    QString value() const;
    void setValue (const QString &value);
    QString toString() const;
private:
    QString m_value;
};

class TechnicalAttributeRationalType : public TypeGroup
{
public:
    TechnicalAttributeRationalType();
    ~TechnicalAttributeRationalType();
    //Attributes
    long *value() const;
    void setValue(long value);
    void clearValue();
    int *factorNumerator() const;
    void setFactorNumerator (int factorNumerator);
    void clearFactorNumerator();
    int *factorDenominator() const;
    void setFactorDenominator (int factorDenominator);
    void clearFactorDenominator();
    QString toString() const;

private:
    //Attributes
    long *m_value;
    int *m_factorNumerator;
    int *m_factorDenominator;
};

#endif // TECHNICALATTRIBUTES_H

