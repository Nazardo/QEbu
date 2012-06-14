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

#include "qebulimits.h"
#include <QtGlobal>

qEbuLimits::qEbuLimits()
{

}

int qEbuLimits::getMaxInt()
{
    return std::numeric_limits<int>::max();
}

int qEbuLimits::getMinInt()
{
    return std::numeric_limits<int>::min();

}

long qEbuLimits::getMaxLong()
{
    return std::numeric_limits<long>::max();
}

long qEbuLimits::getMinLong()
{
    return std::numeric_limits<long>::min();
}

double qEbuLimits::getMaxDouble()
{
    return std::numeric_limits<double>::max();
}

double qEbuLimits::getMinDouble()
{
    return std::numeric_limits<double>::min();
}

int qEbuLimits::getMaxShort()
{
    return std::numeric_limits<short>::max();
}

int qEbuLimits::getMinShort()
{
    return std::numeric_limits<short>::min();
}

int qEbuLimits::getMaxInt8()
{
    return std::numeric_limits<qint8>::max();
}

int qEbuLimits::getMinInt8()
{
    return std::numeric_limits<qint8>::min();
}

int qEbuLimits::getMaxInt16()
{
    return std::numeric_limits<qint16>::max();
}

int qEbuLimits::getMinInt16()
{
    return std::numeric_limits<qint16>::min();
}

int qEbuLimits::getMaxInt32()
{
    return std::numeric_limits<qint32>::max();
}

int qEbuLimits::getMinInt32()
{
    return std::numeric_limits<qint32>::min();
}

long long int qEbuLimits::getMaxInt64()
{
    return std::numeric_limits<qint64>::max();
}

long long int qEbuLimits::getMinInt64()
{
    return std::numeric_limits<qint64>::min();
}

unsigned int qEbuLimits::getMaxUInt()
{
    return std::numeric_limits<unsigned int>::max();
}

unsigned int qEbuLimits::getMinUInt()
{
    return std::numeric_limits<unsigned int>::min();
}

int qEbuLimits::getMaxUInt8()
{
    return std::numeric_limits<quint8>::max();
}

int qEbuLimits::getMinUInt8()
{
    return std::numeric_limits<quint8>::min();
}

int qEbuLimits::getMaxUInt16()
{
    return std::numeric_limits<quint16>::max();
}

int qEbuLimits::getMinUInt16()
{
    return std::numeric_limits<quint16>::min();
}

unsigned int qEbuLimits::getMaxUInt32()
{
    return std::numeric_limits<quint32>::max();
}

unsigned int qEbuLimits::getMinUInt32()
{
    return std::numeric_limits<quint32>::min();
}

unsigned long long int qEbuLimits::getMaxUInt64()
{
    return std::numeric_limits<quint64>::max();
}

unsigned long long int qEbuLimits::getMinUInt64()
{
    return std::numeric_limits<quint64>::min();
}
