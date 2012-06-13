/****************************************************************************
** Copyright (C) 2012 by
**  Mauro Levra  (nazardo)     mauro@nazardo.it
**  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it
**  Denis Patti  (dextp3)      denis.patti@studenti.polito.it
**  Giovanni Pessiva           giovanni.pessiva@gmail.com
**  Stefano Ricossa            stefano.ricossa@studenti.polito.it
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

#include "durationtype.h"
#include "typeconverter.h"
#include <QObject>

DurationType::DurationType()
{
    m_time = 0;
    m_factorNumerator = 1; // default
    m_factorDenominator = 1; // default
    m_editRate = 0;
    m_editUnitNumberValue = 0;
    m_normalPlayTime = 0;
}

DurationType::DurationType(const QString &timecode)
{
    m_durationTypeRepresentation = DurationType::enumTimecode;
    m_timecode = timecode;
    m_time = 0;
    m_factorNumerator = 1; // default
    m_factorDenominator = 1; // default
    m_editRate = 0;
    m_editUnitNumberValue = 0;
    m_normalPlayTime = 0;
}

DurationType::DurationType(Duration *normalPlayTime)
{
    m_durationTypeRepresentation = DurationType::enumNormalPlayTime;
    m_normalPlayTime = normalPlayTime;
    m_time = 0;
    m_factorNumerator = 1; // default
    m_factorDenominator = 1; // default
    m_editRate = 0;
    m_editUnitNumberValue = 0;
}

DurationType::DurationType(const unsigned int &editRate, const unsigned long &editUnitNumberValue, const unsigned int &factorNumerator = 1, const unsigned int &factorDenominator = 1)
{
    m_durationTypeRepresentation = DurationType::enumEditUnitNumber;
    m_editRate = new unsigned int(editRate);
    m_factorNumerator = factorNumerator;
    m_factorDenominator = factorDenominator;
    m_editUnitNumberValue = new unsigned long(editUnitNumberValue);
    m_time = 0;
    m_normalPlayTime = 0;
}

DurationType::DurationType(const QString &timeString, FormatGroup *time)
{
    m_durationTypeRepresentation = DurationType::enumTime;
    m_timeValue = timeString;
    m_time = time;
    m_factorNumerator = 1; // default
    m_factorDenominator = 1; // default
    m_editRate = 0;
    m_editUnitNumberValue = 0;
    m_normalPlayTime = 0;
}


DurationType::~DurationType()
{
    delete m_time;
    delete m_editRate;
    delete m_editUnitNumberValue;
}

DurationType::DurationTypeRepresentation DurationType::durationTypeRepresentation() const
{
    return m_durationTypeRepresentation;
}

QString DurationType::timecode() const
{
    return m_timecode;
}

void DurationType::setTimecode(const QString &timecode)
{
    m_durationTypeRepresentation = DurationType::enumTimecode;
    m_timecode = timecode;
}

Duration *DurationType::normalPlayTime()
{
    return m_normalPlayTime;
}

void DurationType::setNormalPlayTime(Duration *normalPlayTime)
{
    m_durationTypeRepresentation = DurationType::enumNormalPlayTime;
    delete m_normalPlayTime;
    m_normalPlayTime = normalPlayTime;
}

unsigned int *DurationType::editRate() const
{
    return m_editRate;
}

void DurationType::setEditRate(unsigned int editRate)
{
    m_durationTypeRepresentation = DurationType::enumEditUnitNumber;
    delete m_editRate;
    m_editRate = new unsigned int(editRate);
}

void DurationType::clearEditRate()
{
    delete m_editRate;
    m_editRate = 0;
}

unsigned int DurationType::factorNumerator() const
{
    return m_factorNumerator;
}

void DurationType::setFactorNumerator(unsigned int factorNumerator)
{
    m_durationTypeRepresentation = DurationType::enumEditUnitNumber;
    m_factorNumerator = factorNumerator;
}

void DurationType::clearFactorNumerator()
{
    m_factorNumerator = 0;
}

unsigned int DurationType::factorDenominator() const
{
    return m_factorDenominator;
}

void DurationType::setFactorDenominator(unsigned int factorDenominator)
{
    m_durationTypeRepresentation = DurationType::enumEditUnitNumber;
    m_factorDenominator = factorDenominator;
}

void DurationType::clearFactorDenominator()
{
    m_factorDenominator = 0;
}

unsigned long *DurationType::editUnitNumberValue() const
{
    return m_editUnitNumberValue;
}

void DurationType::setEditUnitNumberValue(unsigned long editUnitNumberValue)
{
    m_durationTypeRepresentation = DurationType::enumEditUnitNumber;
    delete m_editUnitNumberValue;
    m_editUnitNumberValue = new unsigned long(editUnitNumberValue);
}

void DurationType::clearEditUnitNumberValue()
{
    delete m_editUnitNumberValue;
    m_editUnitNumberValue = 0;
}

QString DurationType::timeValue() const
{
    return m_timeValue;
}

void DurationType::setTimeValue(const QString &timeString)
{
    m_durationTypeRepresentation = DurationType::enumTime;
    m_timeValue = timeString;
}

FormatGroup *DurationType::time() const
{
    return m_time;
}

void DurationType::setTime(FormatGroup *time)
{
    m_durationTypeRepresentation = DurationType::enumTime;
    if (time != m_time)
        delete m_time;
    m_time = time;
}

QString DurationType::toString() const
{
    switch (m_durationTypeRepresentation) {
        case DurationType::enumEditUnitNumber:
            return QString::number(*m_editUnitNumberValue, 10);
        case DurationType::enumNormalPlayTime:
            //return TypeConverter::durationToString(m_normalPlayTime);
            return m_normalPlayTime->toString();
        case DurationType::enumTime:
            return m_timeValue;
        case DurationType::enumTimecode:
            return m_timecode;
    }
    return QObject::tr("Undefined duration");
}
