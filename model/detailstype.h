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

#ifndef DETAILSTYPE_H
#define DETAILSTYPE_H

#include <QList>
#include <QString>
#include "typegroup.h"

class AddressType
{
public:
    AddressType();
    ~AddressType();
    QList<QString> &lines();
    void lines(const QList<QString> &lines);
    QString townCity() const;
    void setTownCity(const QString &townCity);
    QString countyState() const;
    void setCountyState(const QString &countyState);
    QString deliveryCode() const;
    void setDeliveryCode(const QString &deliveryCode);
    TypeGroup *country() const;
    void setCountry(TypeGroup *country);
    QString toString() const;
private:
    QList<QString> m_lines;
    QString m_townCity;
    QString m_countyState;
    QString m_deliveryCode;
    TypeGroup *m_country;
};

class DetailsType : public TypeGroup
{
public:
    DetailsType();
    ~DetailsType();
    QString emailAddress() const;
    void setEmailAddress(const QString &emailAddress);
    QString webAddress() const;
    void setWebAddress(const QString &webAddress);
    AddressType *address() const;
    void setAddress(AddressType *address);
    QString telephoneNumber() const;
    void setTelephoneNumber(const QString &telephoneNumber);
    QString mobileTelephoneNumber() const;
    void setMobileTelephoneNumber(const QString &mobileTelephoneNumber);
    QString toString() const;
private:
    QString m_emailAddress;
    QString m_webAddress;
    AddressType *m_address;
    QString m_telephoneNumber;
    QString m_mobileTelephoneNumber;
};

#endif // DETAILSTYPE_H
