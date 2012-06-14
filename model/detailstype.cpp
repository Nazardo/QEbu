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

#include "detailstype.h"
#include <QStringList>

DetailsType::DetailsType()
{
    m_address = 0;
}

DetailsType::~DetailsType()
{
    delete m_address;
}

QString DetailsType::emailAddress() const
{
    return m_emailAddress;
}

void DetailsType::setEmailAddress(const QString &emailAddress)
{
    m_emailAddress = emailAddress;
}

QString DetailsType::webAddress() const
{
    return m_webAddress;
}

void DetailsType::setWebAddress(const QString &webAddress)
{
    m_webAddress = webAddress;
}

AddressType *DetailsType::address() const
{
    return m_address;
}

void DetailsType::setAddress(AddressType *address)
{
    if (address != m_address)
        delete m_address;
    m_address = address;
}

QString DetailsType::telephoneNumber() const
{
    return m_telephoneNumber;
}

void DetailsType::setTelephoneNumber(const QString &telephoneNumber)
{
    m_telephoneNumber = telephoneNumber;
}

QString DetailsType::mobileTelephoneNumber() const
{
    return m_mobileTelephoneNumber;
}

void DetailsType::setMobileTelephoneNumber(const QString &mobileTelephoneNumber)
{
    m_mobileTelephoneNumber = mobileTelephoneNumber;
}

QString DetailsType::toString() const
{
    QStringList sl;
    if (!m_emailAddress.isEmpty())
    {
        sl.append("Email Address:");
        sl.append(m_emailAddress);
        return sl.join(" ");
    }
    if (!m_webAddress.isEmpty())
    {
        sl.append("Web Address:");
        sl.append(m_webAddress);
        return sl.join(" ");
    }
    if (!m_telephoneNumber.isEmpty())
    {
        sl.append("Telephone Number:");
        sl.append(m_telephoneNumber);
        return sl.join(" ");
    }
    if (!m_mobileTelephoneNumber.isEmpty())
    {
        sl.append("Mobile Telephone Number:");
        sl.append(m_mobileTelephoneNumber);
        return sl.join(" ");
    }
    return "Unspecified Details";
}

AddressType::AddressType()
{
    m_country = 0;
}

AddressType::~AddressType()
{
    delete m_country;
}

QList<QString> &AddressType::lines()
{
    return m_lines;
}

void AddressType::lines(const QList<QString> &lines)
{
    m_lines = lines;
}

QString AddressType::townCity() const
{
    return m_townCity;
}

void AddressType::setTownCity(const QString &townCity)
{
    m_townCity = townCity;
}

QString AddressType::countyState() const
{
    return m_countyState;
}

void AddressType::setCountyState(const QString &countyState)
{
    m_countyState = countyState;
}

QString AddressType::deliveryCode() const
{
    return m_deliveryCode;
}

void AddressType::setDeliveryCode(const QString &deliveryCode)
{
    m_deliveryCode = deliveryCode;
}

TypeGroup *AddressType::country() const
{
    return m_country;
}

void AddressType::setCountry(TypeGroup *country)
{
    if (country != m_country)
        delete m_country;
    m_country = country;
}

QString AddressType::toString() const
{
    QStringList sl;
    if (m_lines.size() > 0)
    {
        sl.append("Address:");
        sl.append(m_lines.first());
        return sl.join(" ");
    }
    if (!m_townCity.isEmpty())
    {
        sl.append("Town City:");
        sl.append(m_townCity);
        return sl.join(" ");
    }
    return "Unspecified address";
}



