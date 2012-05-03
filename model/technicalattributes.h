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
private:
    QString m_value;
};

class Int8 : public TypeGroup
{
public:
    Int8();
    //Attributes
    qint8 value() const;
    void setValue(qint8 value);
private:
    qint8 m_value;
};

class Int16 : public TypeGroup
{
public:
    Int16();
    //Attributes
    short value() const;
    void setValue(short value);
private:
    short m_value;
};

class Int32 : public TypeGroup
{
public:
    Int32();
    //Attributes
    int value() const;
    void setValue(int value);
private:
    int m_value;
};

class Int64 : public TypeGroup
{
public:
    Int64();
    //Attributes
    double value() const;
    void setValue(double value);
private:
    long m_value;
};

class UInt8 : public TypeGroup
{
public:
    UInt8();
    //Attributes
    quint8 value() const;
    void setValue(quint8 value);
private:
    quint8 m_value;
};

class UInt16 : public TypeGroup
{
public:
    UInt16();
    //Attributes
    unsigned short value() const;
    void setValue(unsigned short value);
private:
    unsigned short m_value;
};

class UInt32 : public TypeGroup
{
public:
    UInt32();
    //Attributes
    unsigned int value() const;
    void setValue(unsigned int value);
private:
    unsigned int m_value;
};

class UInt64 : public TypeGroup
{
public:
    UInt64();
    //Attributes
    unsigned long value() const;
    void setValue(unsigned long value);
private:
    unsigned long m_value;
};

class Boolean : public TypeGroup
{
public:
    Boolean();
    //Attributes
    bool value() const;
    void setValue(bool value);
private:
    bool m_value;
};

class Float : public TypeGroup
{
public:
    Float();
    //Attributes
    double value() const;
    void setValue(double value);
private:
    double m_value;
};

class TechnicalAttributeUriType : public TypeGroup
{
public:
    TechnicalAttributeUriType();
    //Attributes
    QString value() const;
    void setValue (const QString &value);
private:
    QString m_value;
};

class TechnicalAttributeRationalType : public TypeGroup
{
public:
    TechnicalAttributeRationalType();
    //Attributes
    long value() const;
    void setValue(long value);
    int factorNumerator() const;
    void setFactorNumerator (int factorNumerator);
    int factorDenominator() const;
    void setFactorDenominator (int factorDenominator);

private:
    //Attributes
    long m_value;
    int m_factorNumerator;
    int m_factorDenominator;
};






#endif // TECHNICALATTRIBUTES_H

