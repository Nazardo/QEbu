#include "completereditbox.h"
#include <QStringList>
#include <QLineEdit>
#include <QCompleter>

CompleterEditBox::CompleterEditBox(FieldType fieldType, QWidget *parent):
    QLineEdit(parent)
{
    QStringList wordList;

    switch (fieldType) {
    case subjectCode:
        //ebuCoreMain.coreMetadata.subject.subjectCode
        wordList <<"urn:ebu:metadata:cs:ContentGenreCS:";
        wordList <<"urn:ebu:metadata:cs:ContentGenreCS:2007:3.1.1.10.4";
        break;

    case locationCode:
        //ebuCoreMain.coreMetadata.coverage.spatial.location.code
        wordList <<"urn:ebu:metadata:cs:ISO3166CountryCodeCS:2007:IT";

    case language:
        //ebuCoreMain.coreMetadata.language
        wordList <<"Italian";
        wordList <<"English";
        wordList <<"French";
        wordList <<"German";
        wordList <<"Spanish";
        break;

    case channel:
        //ebuCoreMain.coreMetadata.publicationHistory.firstPublicationChannel
        //ebuCoreMain.coreMetadata.publicationHistory.repeatChannel
        wordList <<"Rai Uno";
        wordList <<"Rai Due";
        wordList <<"Rai Tre";
        wordList <<"Rai Quattro";
        wordList <<"Rai Cinque";
        wordList <<"Rai Movie";
        wordList <<"Rai Premium";
        wordList <<"Rai Gulp";
        wordList <<"Rai YoYo";
        wordList <<"Rai Storia";
        wordList <<"Rai Scuola";
        wordList <<"Rai News";
        wordList <<"Rai Sport 1";
        wordList <<"Rai Sport 2";
        wordList <<"EuroNews";
        wordList <<"Rete 4";
        wordList <<"Canale 5";
        wordList <<"Italia 1";
        wordList <<"La7";
        break;



    case contactDetailsType_name_publisher:
        //ebuCoreMain.coreMetadata.publisher.contactDetails.name
        wordList <<"Rai - RadioTelevisione Italiana";
        wordList <<"Mediaset";
        wordList <<"Telecom Italia Media";
        wordList <<"Sky Italia";
        break;

    case contactDetailsType_name_metadataProvider:
        //ebuCoreMain.metadataProvider.contactDetails.name
        wordList <<"Rai Teche";
        break;

    case organisationDetailsType_organizationName:
        //ebuCoreMain.coreMetadata.creator.organisationDetails.organisationName
        //ebuCoreMain.coreMetadata.contributor.organisationDetails.organisationName
        //ebuCoreMain.metadataProvider.organisationDetails.organisationName
        wordList <<"Rai - RadioTelevisione Italiana";
        break;

    case typeGroup_typeLink_role:
        //ebuCoreMain.coreMetadata.creator.role
        //ebuCoreMain.coreMetadata.publisher.role
        //ebuCoreMain.coreMetadata.contributor.organisationDetails.role
        //ebuCoreMain.coreMetadata.contributor.contactDetails.role
        wordList <<"urn:ebu:metadata:cs:EBURoleCodeCS:2007:";
        wordList <<"urn:ebu:metadata:cs:EBURoleCodeCS:2007:20.1";
        wordList <<"urn:ebu:metadata:cs:EBURoleCodeCS:2007:10.2";
        wordList <<"urn:ebu:metadata:cs:EBURoleCodeCS:2007:10.3";
        wordList <<"urn:ebu:metadata:cs:EBURoleCodeCS:2007:20.10";
        wordList <<"urn:ebu:metadata:cs:EBURoleCodeCS:2007:25.10";
        wordList <<"urn:ebu:metadata:cs:EBURoleCodeCS:2007:20.16";
        break;

    case typeGroup_typeLabel_role:
        //ebuCoreMain.coreMetadata.creator.role
        //ebuCoreMain.coreMetadata.publisher.role
        //ebuCoreMain.coreMetadata.contributor.organisationDetails.role
        //ebuCoreMain.coreMetadata.contributor.contactDetails.role
        wordList <<"Producer";
        wordList <<"Executive Producer";
        wordList <<"Author";
        wordList <<"Presenter";
        wordList <<"Director";
        wordList <<"Writer";
        wordList <<"Distribution Company";
        break;

    case typeGroup_typeLink_identifier:
        //ebuCoreMain.coreMetadata.identifier
        wordList <<"urn:ebu:metadata:cs:IdentifierTypeCodeCS:";
        wordList <<"urn:ebu:metadata:cs:IdentifierTypeCodeCS:2007:17";
        break;

    case typeGroup_typeLabel_identifier:
        //ebuCoreMain.coreMetadata.identifier
        wordList <<"Archive Number";
        break;

    case typeGroup_typeLink_medium:
        //ebuCoreMain.coreMetadata.format.medium
        wordList <<"urn:ebu:metadata:cs:StorageMediaCodeCS:2007:IML";
        break;

    case typeGroup_typeLabel_medium:
        //ebuCoreMain.coreMetadata.format.medium
        wordList <<"Betacam IMX";
        break;

    case typeGroup_typeDefinition_locator:
        //ebuCoreMain.coreMetadata.locator
        wordList <<"RAI Internal Archive Number";
        break;



    case audioFormatType_audioEncoding:
        wordList <<"AAC";
        wordList <<"Mp3";
        break;

    case audioFormatType_audioTrackConfiguration:
        wordList <<"stereo";
        wordList <<"2+1";
        wordList <<"surround";
        wordList <<"surround (7+1)";

    case elementType_lang:
        //ebuCoreMainType
        wordList <<"en";
        wordList <<"it";
        wordList <<"fr";
        wordList <<"ger";
        wordList <<"sp";
        break;

    case formatType_mimeType:
        wordList <<"audio";
        wordList <<"video";
        wordList <<"text";
        wordList <<"application";
        break;

    case formatType_containerFormat:
        wordList <<"mp3";
        wordList <<"wave";
        wordList <<"Quicktime";
        wordList <<"ogg";
        break;

    case identifierType_typeGroup:
        wordList <<"Main";
        wordList <<"Alternative";
        break;

    case identifierType_formatGroup:
        wordList <<"SMPTE UMID";
        wordList <<"ISO ISAN";
        wordList <<"IETF URI";
        wordList <<"ISRC";
        wordList <<"custom";
        break;

    case imageFormatType_imageEncoding:
        wordList <<"jpg";
        wordList <<"png";
        break;

    case languageType_typeGroup:
        wordList <<"main original language";
        wordList <<"main dubbed language";
        wordList <<"additional original language";
        wordList <<"additional dubbed language";
        wordList <<"descriptive video information";
        wordList <<"supplemental commentary";
        wordList <<"Director's commentary";
        wordList <<"audio description";
        wordList <<"supplementary audio programme";
        wordList <<"educational notes";
        wordList <<"voice over";
        wordList <<"original commentary";
        wordList <<"dubbed commentary";
        wordList <<"original narration";
        wordList <<"dubbed narration";
        wordList <<"dubbed dialogue";
        wordList <<"interviewer language";
        wordList <<"interviewee language";
        wordList <<"text description for the hard-of-hearing";
        wordList <<"titles";
        wordList <<"subtitles";
        wordList <<"song lyrics";
        wordList <<"sign language";
        wordList <<"dubbed sign language";
        wordList <<"transcript";
        wordList <<"caption";
        wordList <<"open caption";
        wordList <<"closed caption";
        break;

    case typeType_objectType:
        wordList <<"programme";
        wordList <<"item";
        wordList <<"episode";
        break;

    case videoFormatType_aspectRatio:
        wordList <<"1:1";
        wordList <<"3:2";
        wordList <<"4:3";
        wordList <<"5:4";
        wordList <<"14:9";
        wordList <<"14:10";
        wordList <<"16:9";
        wordList <<"16:10";
        wordList <<"2.35:1";
        break;

    case videoFormatType_videoEncoding:
        wordList <<"H.264";
        wordList <<"Ogg Theora";
        wordList <<"VP8";
        break;
    }

    QCompleter *completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    setCompleter(completer);
}

