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

#include "lengthtype.h"
#include <QObject>

LengthType::LengthType()
{
    m_value= 0;
}

LengthType::~LengthType()
{
    delete m_value;
}

LengthType::LengthType(const unsigned int &value, const QString &unit)
{
    m_value = new unsigned int(value);
    m_unit = unit;
}

unsigned int *LengthType::value() const
{
    return m_value;
}

void LengthType::setValue(const unsigned int &value)
{
    delete m_value;
    m_value = new unsigned int(value);
}

void LengthType::clearValue()
{
    delete m_value;
    m_value = 0;
}

QString LengthType::unit() const
{
    return m_unit;
}

void LengthType::setUnit(const QString &unit)
{
    m_unit = unit;
}

QString LengthType::toString() const
{
    if (m_value)
        return QString::number(*m_value);
    return QObject::tr("Undefined length");
}
