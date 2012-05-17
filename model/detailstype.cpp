#include "detailstype.h"

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
    return "TODO:details";
}

AddressType::AddressType()
{
    m_country = 0;
}

AddressType::~AddressType()
{
    delete m_country;
}

QList<QString> AddressType::lines() const
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
    return "TODO:address";
}



