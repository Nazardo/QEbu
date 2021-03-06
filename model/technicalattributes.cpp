/****************************************************************************
** Copyright (C) 2012 by
**  Mauro Levra  (nazardo)     mauro@nazardo.it
**  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it
**  Denis Patti  (dextp3)      denis.patti@studenti.polito.it
**  Giovanni Pessiva           giovanni.pessiva@gmail.com
**  Stefano Ricossa            stefano.ricossa@gmail.com
**
** This file is part of QEbu.
** QEbu is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, in the version 3 of the License.
**
** QEbu is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with QEbu.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#include "technicalattributes.h"
#include <QObject>

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

QString TechnicalAttributes::toString()
{
    if (m_technicalAttributeString.size() > 0)
         return "Technical Attributes";
    if (m_technicalAttributeByte.size() > 0)
         return "Technical Attributes";
    if (m_technicalAttributeShort.size() >0)
        return "Technical Attributes";
    if (m_technicalAttributeInteger.size() > 0)
        return "Technical Attributes";
    if (m_technicalAttributeLong.size() > 0)
        return "Technical Attributes";
    if (m_technicalAttributeUnsignedByte.size() > 0)
        return "Technical Attributes";
    if (m_technicalAttributeUnsignedShort.size() > 0)
        return "Technical Attributes";
    if (m_technicalAttributeUnsignedInteger.size() > 0)
        return "Technical Attributes";
    if (m_technicalAttributeUnsignedLong.size() > 0)
        return "Technical Attributes";
    if (m_technicalAttributeBoolean.size() > 0)
        return "Technical Attributes";
    if (m_technicalAttributeFloat.size() > 0)
        return "Technical Attributes";
    if (m_technicalAttributeRational.size() > 0)
        return "Technical Attributes";
    if (m_technicalAttributeUri.size() > 0)
        return "Technical Attributes";
    return "Technical Attributes - empty";
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
    m_value = 0;
    m_factorNumerator = 0;
    m_factorDenominator = 0;
}

TechnicalAttributeRationalType::~TechnicalAttributeRationalType()
{
    delete m_value;
    delete m_factorNumerator;
    delete m_factorDenominator;
}

long *TechnicalAttributeRationalType::value() const
{
    return m_value;
}

void TechnicalAttributeRationalType::setValue(long value)
{
    delete m_value;
    m_value = new long(value);
}

void TechnicalAttributeRationalType::clearValue()
{
    delete m_value;
    m_value = 0;
}

int *TechnicalAttributeRationalType::factorNumerator() const
{
    return m_factorNumerator;
}

void TechnicalAttributeRationalType::setFactorNumerator(int factorNumerator)
{
    delete m_factorNumerator;
    m_factorNumerator = new int(factorNumerator);
}

void TechnicalAttributeRationalType::clearFactorNumerator()
{
    delete m_factorNumerator;
    m_factorNumerator = 0;
}

int *TechnicalAttributeRationalType::factorDenominator() const
{
    return m_factorDenominator;
}

void TechnicalAttributeRationalType::setFactorDenominator(int factorDenominator)
{
    delete m_factorDenominator;
    m_factorDenominator = new int(factorDenominator);
}

void TechnicalAttributeRationalType::clearFactorDenominator()
{
    delete m_factorDenominator;
    m_factorDenominator = 0;
}

QString TechnicalAttributeRationalType::toString() const
{
    if (!m_value)
        return QObject::tr("Unspecified technical attribute");
    return QString::number(*m_value, 10);
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

QString TechnicalAttributeUriType::toString() const
{  
    if (m_value.isEmpty())
        return QObject::tr("Unspecified technical attribute");
    return m_value;
}

Float::Float()
{
    m_value = 0;
}

Float::~Float()
{
    delete m_value;
}

double *Float::value() const
{
    return m_value;
}

void Float::setValue(double value)
{
    delete m_value;
    m_value = new double(value);
}

void Float::clearValue()
{
    delete m_value;
    m_value = 0;
}

QString Float::toString() const
{
    if (!m_value)
        return QObject::tr("Undefined technical attribute");
    return QString::number(*m_value);
}

Boolean::Boolean()
{
    m_value = 0;
}

Boolean::~Boolean()
{
    delete m_value;
}

bool *Boolean::value() const
{
    return m_value;
}

void Boolean::setValue(bool value)
{
    delete m_value;
    m_value = new bool(value);
}

QString Boolean::toString() const
{
    if (!m_value)
        return QObject::tr("Unspecified technical attribute");
    return *m_value ? "true" : "false";
}

UInt64::UInt64()
{
    m_value = 0;
}

UInt64::~UInt64()
{
    delete m_value;
}

quint64 *UInt64::value() const
{
    return m_value;
}

void UInt64::setValue(quint64 value)
{
    delete m_value;
    m_value = new quint64(value);
}

void UInt64::clearValue()
{
    delete m_value;
    m_value = 0;
}

QString UInt64::toString() const
{
    if (!m_value)
        return QObject::tr("Unspecified technical attribute");
    return QString::number(*m_value, 10);
}

UInt32::UInt32()
{
    m_value = 0;
}

UInt32::~UInt32()
{
    delete m_value;
}

quint32 *UInt32::value() const
{
    return m_value;
}

void UInt32::setValue(quint32 value)
{
    delete m_value;
    m_value = new quint32(value);
}

void UInt32::clearValue()
{
    delete m_value;
    m_value = 0;
}

QString UInt32::toString() const
{
    if (!m_value)
        return QObject::tr("Unspecified technical attribute");
    return QString::number(*m_value, 10);
}

UInt16::UInt16()
{
    m_value = 0;
}

UInt16::~UInt16()
{
    delete m_value;
}

quint16 *UInt16::value() const
{
    return m_value;
}

void UInt16::setValue(quint16 value)
{
    delete m_value;
    m_value = new quint16(value);
}

void UInt16::clearValue()
{
    delete m_value;
    m_value = 0;
}

QString UInt16::toString() const
{
    if (!m_value)
        return QObject::tr("Unspecified technical attribute");
    return QString::number(*m_value, 10);
}

UInt8::UInt8()
{
    m_value = 0;
}

UInt8::~UInt8()
{
    delete m_value;
}

quint8 *UInt8::value() const
{
    return m_value;
}

void UInt8::setValue(quint8 value)
{
    delete m_value;
    m_value = new quint8(value);
}

void UInt8::clearValue()
{
    delete m_value;
    m_value = 0;
}


QString UInt8::toString() const
{
    if (!m_value)
        return QObject::tr("Unspecified technical attribute");
    return QString::number(*m_value, 10);
}

Int64::Int64()
{
    m_value = 0;
}

Int64::~Int64()
{
    delete m_value;
}

qint64 *Int64::value() const
{
    return m_value;
}

void Int64::setValue(qint64 value)
{
    delete m_value;
    m_value = new qint64(value);
}

void Int64::clearValue()
{
    delete m_value;
    m_value = 0;
}

QString Int64::toString() const
{
    if (!m_value)
        return QObject::tr("Unspecified technical attribute");
    return QString::number(*m_value, 10);
}

Int32::Int32()
{
    m_value = 0;
}

Int32::~Int32()
{
    delete m_value;
}

qint32 *Int32::value() const
{
    return m_value;
}

void Int32::setValue(qint32 value)
{
    delete m_value;
    m_value = new qint32(value);
}

void Int32::clearValue()
{
    delete m_value;
    m_value = 0;
}

QString Int32::toString() const
{
    if (!m_value)
        return QObject::tr("Unspecified technical attribute");
    return QString::number(*m_value, 10);
}

Int16::Int16()
{
    m_value = 0;
}

Int16::~Int16()
{
    delete m_value;
}

qint16 *Int16::value() const
{
    return m_value;
}

void Int16::setValue(qint16 value)
{
    delete m_value;
    m_value = new qint16(value);
}

void Int16::clearValue()
{
    delete m_value;
    m_value = 0;
}

QString Int16::toString() const
{
    if (!m_value)
        return QObject::tr("Unspecified technical attribute");
    return QString::number(*m_value, 10);
}

Int8::Int8()
{
    m_value = 0;
}

Int8::~Int8()
{
    delete m_value;
}

qint8 *Int8::value() const
{
    return m_value;
}

void Int8::setValue(qint8 value)
{
    delete m_value;
    m_value = new qint8(value);
}

void Int8::clearValue()
{
    delete m_value;
    m_value = 0;
}

QString Int8::toString() const
{
    if (!m_value)
        return QObject::tr("Unspecified technical attribute");
    return QString::number(*m_value, 10);
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

QString String::toString() const
{
    if (m_value.isEmpty())
        return QObject::tr("Unspecified technical attribute");
    return m_value;
}
