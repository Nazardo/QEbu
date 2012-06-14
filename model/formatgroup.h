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

#ifndef FORMATGROUP_H
#define FORMATGROUP_H

#include <QString>

class FormatGroup
{
public:
    FormatGroup();
    FormatGroup(const FormatGroup &copy);
    QString formatLabel() const;
    void setFormatLabel(const QString &formatLabel);
    QString formatDefinition() const;
    void setFormatDefinition(const QString &formatDefinition);
    QString formatLink() const;
    void setFormatLink(const QString &formatLink);
    QString toString() const;
private:
    QString m_formatLabel;
    QString m_formatDefinition;
    QString m_formatLink; // anyURI
};

#endif // FORMATGROUP_H
