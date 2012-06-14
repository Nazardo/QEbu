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

#include "elementtype.h"
#include <QObject>

ElementType::ElementType()
{
    m_lang = "en";
}

ElementType::ElementType(const QString &value, const QString &lang)
{
    m_value = value;
    m_lang = lang;
}

QString ElementType::value() const
{
    return m_value;
}

void ElementType::setValue(const QString &value)
{
    m_value = value;
}

QString ElementType::lang() const
{
    return m_lang;
}

void ElementType::setLang(const QString &lang)
{
    m_lang = lang;
}

QString ElementType::toString() const
{
    if (m_value.isEmpty())
        return QObject::tr("Unspecified element");
    return m_value;
}
