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
