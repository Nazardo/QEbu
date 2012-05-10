#include "technicalattributes.h"

TechnicalAttributes::TechnicalAttributes()
{
}

TechnicalAttributes::~TechnicalAttributes()
{
    int s = m_technicalAttributeString.size();
    for (int i=0; i < s; ++i) {
        delete (m_technicalAttributeString.takeAt(0));
    }
    s = m_technicalAttributeByte.size();
    for (int i=0; i < s; ++i) {
        delete (m_technicalAttributeByte.takeAt(0));
    }
    s = m_technicalAttributeShort.size();
    for (int i=0; i < s; ++i) {
        delete (m_technicalAttributeShort.takeAt(0));
    }
    s = m_technicalAttributeInteger.size();
    for (int i=0; i < s; ++i) {
        delete (m_technicalAttributeInteger.takeAt(0));
    }
    s = m_technicalAttributeLong.size();
    for (int i=0; i < s; ++i) {
        delete (m_technicalAttributeLong.takeAt(0));
    }
    s = m_technicalAttributeUnsignedByte.size();
    for (int i=0; i < s; ++i) {
        delete (m_technicalAttributeUnsignedByte.takeAt(0));
    }
    s = m_technicalAttributeUnsignedShort.size();
    for (int i=0; i < s; ++i) {
        delete (m_technicalAttributeUnsignedShort.takeAt(0));
    }
    s = m_technicalAttributeUnsignedInteger.size();
    for (int i=0; i < s; ++i) {
        delete (m_technicalAttributeUnsignedInteger.takeAt(0));
    }
    s = m_technicalAttributeUnsignedLong.size();
    for (int i=0; i < s; ++i) {
        delete (m_technicalAttributeUnsignedLong.takeAt(0));
    }
    s = m_technicalAttributeBoolean.size();
    for (int i=0; i < s; ++i) {
        delete (m_technicalAttributeBoolean.takeAt(0));
    }
    s = m_technicalAttributeFloat.size();
    for (int i=0; i < s; ++i) {
        delete (m_technicalAttributeFloat.takeAt(0));
    }
    s = m_technicalAttributeRational.size();
    for (int i=0; i < s; ++i) {
        delete (m_technicalAttributeRational.takeAt(0));
    }
    s = m_technicalAttributeUri.size();
    for (int i=0; i < s; ++i) {
        delete (m_technicalAttributeUri.takeAt(0));
    }
}

QList<String *> &TechnicalAttributes::technicalAttributeString()
{
    return m_technicalAttributeString;
}

QList<Int8 *> &TechnicalAttributes::technicalAttributeByte()
{
    return m_technicalAttributeByte;
}

QList<Int16 *> &TechnicalAttributes::technicalAttributeShort()
{
    return m_technicalAttributeShort;
}

QList<Int32 *> &TechnicalAttributes::technicalAttributeInteger()
{
    return m_technicalAttributeInteger;
}

QList<Int64 *> &TechnicalAttributes::technicalAttributeLong()
{
    return m_technicalAttributeLong;
}

QList<UInt8 *> &TechnicalAttributes::technicalAttributeUnsignedByte()
{
    return m_technicalAttributeUnsignedByte;
}

QList<UInt16 *> &TechnicalAttributes::technicalAttributeUnsignedShort()
{
    return m_technicalAttributeUnsignedShort;
}

QList<UInt32 *> &TechnicalAttributes::technicalAttributeUnsignedInteger()
{
    return m_technicalAttributeUnsignedInteger;
}

QList<UInt64 *> &TechnicalAttributes::technicalAttributeUnsignedLong()
{
    return m_technicalAttributeUnsignedLong;
}

QList<Boolean *> &TechnicalAttributes::technicalAttributeBoolean()
{
    return m_technicalAttributeBoolean;
}

QList<Float *> &TechnicalAttributes::technicalAttributeFloat()
{
    return m_technicalAttributeFloat;
}

QList<TechnicalAttributeRationalType *> &TechnicalAttributes::technicalAttributeRational()
{
    return m_technicalAttributeRational;
}

QList<TechnicalAttributeUriType *> &TechnicalAttributes::technicalAttributeUri()
{
    return m_technicalAttributeUri;
}

TechnicalAttributeRationalType::TechnicalAttributeRationalType()
{
}

long TechnicalAttributeRationalType::value() const
{
    return m_value;
}

void TechnicalAttributeRationalType::setValue(long value)
{
    m_value = value;
}

int TechnicalAttributeRationalType::factorNumerator() const
{
    return m_factorNumerator;
}

void TechnicalAttributeRationalType::setFactorNumerator(int factorNumerator)
{
    m_factorNumerator = factorNumerator;
}

int TechnicalAttributeRationalType::factorDenominator() const
{
    return m_factorDenominator;
}

void TechnicalAttributeRationalType::setFactorDenominator(int factorDenominator)
{
    m_factorDenominator = factorDenominator;
}

TechnicalAttributeUriType::TechnicalAttributeUriType()
{
}

QString TechnicalAttributeUriType::value() const
{
    return m_value;
}

void TechnicalAttributeUriType::setValue(const QString &value)
{
    m_value = value;
}

Float::Float()
{
}

double Float::value() const
{
    return m_value;
}

void Float::setValue(double value)
{
    m_value = value;
}

Boolean::Boolean()
{
}

bool Boolean::value() const
{
    return m_value;
}

void Boolean::setValue(bool value)
{
    m_value = value;
}

UInt64::UInt64()
{
}

quint64 UInt64::value() const
{
    return m_value;
}

void UInt64::setValue(quint64 value)
{
    m_value = value;
}

UInt32::UInt32()
{
}

quint32 UInt32::value() const
{
    return m_value;
}

void UInt32::setValue(quint32 value)
{
    m_value = value;
}

UInt16::UInt16()
{
}

quint16 UInt16::value() const
{
    return m_value;
}

void UInt16::setValue(quint16 value)
{
    m_value = value;
}

UInt8::UInt8()
{
}

quint8 UInt8::value() const
{
    return m_value;
}

void UInt8::setValue(quint8 value)
{
    m_value = value;
}

Int64::Int64()
{
}

qint64 Int64::value() const
{
    return m_value;
}

void Int64::setValue(qint64 value)
{
    m_value = value;
}

Int32::Int32()
{
}

qint32 Int32::value() const
{
    return m_value;
}

void Int32::setValue(qint32 value)
{
    m_value = value;
}

Int16::Int16()
{
}

qint16 Int16::value() const
{
    return m_value;
}

void Int16::setValue(qint16 value)
{
    m_value = value;
}

Int8::Int8()
{
}

qint8 Int8::value() const
{
    return m_value;
}

void Int8::setValue(qint8 value)
{
    m_value = value;
}

String::String()
{
}

QString String::value() const
{
    return m_value;
}

void String::setValue(const QString &value)
{
    m_value = value;
}























