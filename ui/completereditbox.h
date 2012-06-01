#ifndef COMPLETEREDITBOX_H
#define COMPLETEREDITBOX_H

#include <QLineEdit>

class CompleterEditBox : public QLineEdit
{
    Q_OBJECT
public:

    enum FieldType {
        organizationName, // organisationDetails.organisationName
        publisherName, // publisher.contactDetails.name
        providerName, // metadataProvider.contactDetails.name
        roleTypeLink, // role::typeLink
        roleTypeLabel,  // role::typeLabel
        mediumTypeLink, // medium::typeLink
        typeLabelTypeLabel, // typeLabel::typeLabel
        locatorTypeDefinition, // locator::typeDefinition
        subjectCode,
        language, // coreMetadata.language
        firstPublicationChannel // coreMetadata.firstPublicationChannel
    };

    explicit CompleterEditBox(enum FieldType fieldType, QWidget *parent = 0);

signals:

public slots:

};

#endif // COMPLETEREDITBOX_H
