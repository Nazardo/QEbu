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
