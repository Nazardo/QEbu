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

#ifndef QEBULIMITS_H
#define QEBULIMITS_H

#include <limits>

class qEbuLimits
{
public:
    qEbuLimits();

    // Generic types
    static int getMaxShort();
    static int getMinShort();
    static int getMaxInt();
    static int getMinInt();
    static long getMaxLong();
    static long getMinLong();
    static double getMaxDouble();
    static double getMinDouble();

    // qTypes sizes
    static int getMaxInt8();
    static int getMinInt8();
    static int getMaxInt16();
    static int getMinInt16();
    static int getMaxInt32();
    static int getMinInt32();
    static long long getMaxInt64();
    static long long getMinInt64();
    static unsigned int getMaxUInt();
    static unsigned int getMinUInt();
    static int getMaxUInt8();
    static int getMinUInt8();
    static int getMaxUInt16();
    static int getMinUInt16();
    static unsigned int getMaxUInt32();
    static unsigned int getMinUInt32();
    static long long unsigned getMaxUInt64();
    static long long unsigned getMinUInt64();
};

#endif // QEBULIMITS_H
