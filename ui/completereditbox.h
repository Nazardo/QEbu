#ifndef COMPLETEREDITBOX_H
#define COMPLETEREDITBOX_H

#include <QLineEdit>

class CompleterEditBox : public QLineEdit
{
    Q_OBJECT
public:

    enum FieldType {
        subjectCode, // coreMetadata.subject.subjectCode
        locationCode, // coreMetadata.coverage.spatial.location.code
        language, // coreMetadata.language
        channel, // coreMetadata.publicationHistory.firstPublicationChannel

        contactDetailsType_name_metadataProvider, // metadataProvider.contactDetails.name
        contactDetailsType_name_publisher, // publisher.contactDetails.name
        organisationDetailsType_organizationName, // organisationDetails.organisationName
        typeGroup_typeLink_identifier, // identifier::TypeLink
        typeGroup_typeLabel_identifier, // identifier::TypeLink
        typeGroup_typeDefinition_locator, // locator::typeDefinition
        typeGroup_typeLink_medium, // medium::typeLink
        typeGroup_typeLabel_medium, // typeLabel::typeLabel
        typeGroup_typeLink_role, // role::typeLink
        typeGroup_typeLabel_role,  // role::typeLabel

        audioFormatType_audioEncoding,
        audioFormatType_audioTrackConfiguration,
        elementType_lang,
        formatType_mimeType,
        formatType_containerFormat,
        identifierType_typeGroup,
        identifierType_formatGroup,
        imageFormatType_imageEncoding,
        languageType_typeGroup,
        typeType_objectType,
        videoFormatType_aspectRatio,
        videoFormatType_videoEncoding

    };

    explicit CompleterEditBox(enum FieldType fieldType, QWidget *parent = 0);

signals:

public slots:

};

#endif // COMPLETEREDITBOX_H
