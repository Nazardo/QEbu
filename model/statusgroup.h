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

#ifndef STATUSGROUP_H
#define STATUSGROUP_H

#include <QString>

class StatusGroup
{
public:
    StatusGroup();
    StatusGroup(const StatusGroup &copy);
    QString statusLabel() const;
    void setStatusLabel(const QString &statusLabel);
    QString statusDefinition() const;
    void setStatusDefinition(const QString &statusDefinition);
    QString statusLink() const;
    void setStatusLink(const QString &statusLink);

private:
    QString m_statusLabel;
    QString m_statusDefinition;
    QString m_statusLink;
};

#endif // STATUSGROUP_H
