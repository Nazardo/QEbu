#include "completereditbox.h"
#include <QStringList>
#include <QLineEdit>
#include <QCompleter>

CompleterEditBox::CompleterEditBox(FieldType fieldType, QWidget *parent):
    QLineEdit(parent)
{
    QStringList wordList;

    switch (fieldType) {
    case organizationName:
        wordList <<"Rai - RadioTelevisione Italiana";
        break;

    case publisherName:
        wordList <<"Rai - RadioTelevisione Italiana";
        break;

    case providerName:
        wordList <<"Rai Teche";
        break;

    case roleTypeLink:
        wordList <<"urn:ebu:metadata:cs:EBURoleCodeCS:2007:";
        wordList <<"urn:ebu:metadata:cs:EBURoleCodeCS:2007:20.1";
        wordList <<"urn:ebu:metadata:cs:EBURoleCodeCS:2007:10.2";
        wordList <<"urn:ebu:metadata:cs:EBURoleCodeCS:2007:10.3";
        wordList <<"urn:ebu:metadata:cs:EBURoleCodeCS:2007:20.10";
        wordList <<"urn:ebu:metadata:cs:EBURoleCodeCS:2007:25.10";
        wordList <<"urn:ebu:metadata:cs:EBURoleCodeCS:2007:20.16";
        break;

    case roleTypeLabel:
        wordList <<"Executive Producer";
        wordList <<"Presenter";
        wordList <<"Distribution Company";
        wordList <<"Director";
        wordList <<"Writer";
        break;

    case mediumTypeLink:
        wordList <<"urn:ebu:metadata:cs:StorageMediaCodeCS:2007:IML";
        break;

    case typeLabelTypeLabel:
        wordList <<"Betacam IMX";
        break;

    case locatorTypeDefinition:
        wordList <<"RAI Internal Archive Number";
        break;

    case subjectCode:
        wordList <<"urn:ebu:metadata:cs:ContentGenreCS:";
        break;

    case language:
        wordList <<"Italian";
        wordList <<"English";
        wordList <<"French";
        wordList <<"German";
        wordList <<"Spanish";
        break;

    case firstPublicationChannel:
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
        break;
    }

    QCompleter *completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    setCompleter(completer);
}

