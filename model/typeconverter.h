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

#ifndef TYPECONVERTER_H
#define TYPECONVERTER_H

#include <QDateTime>
#include <QUrl>
#include "model/duration.h"

class QValidator;

class TypeConverter
{
public:
    static QDateTime stringToDate(const QString &date);
    static QString dateToString(const QDateTime &date);

    static Duration *stringToDuration(const QString &duration);
    static QString durationToString(const Duration *duration);

    static QDateTime stringToTime(const QString &time);
    static QString timeToString(const QDateTime &time);
    static QDateTime timeToDateTime(const QTime &time, Qt::TimeSpec timeSpec = Qt::LocalTime, int minutesUTCOffset=0);

    static QValidator *getUriValidator();

    static QString errorMsg();

private:
    TypeConverter();

    static QString m_errorMsg;
    static QValidator *m_uriValidator;
};

#endif // TYPECONVERTER_H
