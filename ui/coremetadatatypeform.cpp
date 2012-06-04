#include "coremetadatatypeform.h"
#include "../model/coremetadatatype.h"
#include "ui/titletypeform.h"
#include "ui/alternativetitletypeform.h"
#include "ui/entitytypeform.h"
#include "ui/subjecttypeform.h"
#include "ui/descriptiontypeform.h"
#include "ui/datetypeform.h"
#include "ui/typetypeform.h"
/// @todo: comment
// #include "ui/formattypeform.h"
#include "ui/identifiertypeform.h"
#include "ui/elementtypeform.h"
#include "ui/languagetypeform.h"
#include "ui/relationtypeform.h"
#include "ui/coveragetypeform.h"
#include "ui/rightstypeform.h"
#include "ui/hastrackparttypeform.h"
#include "ui/publicationhistorytypeform.h"
#include "ui/ratingtypeform.h"
/// @todo: comment
// #include "ui/parttypeform.h"
#include "listview.h"
#include "qvarptr.h"
#include <QPushButton>
#include <QButtonGroup>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QTableWidget>
#include <QWidget>

CoreMetadataTypeForm::CoreMetadataTypeForm(CoreMetadataType *coreMetadata, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (coreMetadata) ? Edit : Add;
    if (!coreMetadata)
        m_coreMetadata = new CoreMetadataType;
    else
        m_coreMetadata = coreMetadata;

    // Layout
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QTabWidget *tabWidget = new QTabWidget;

    // First tab
    QWidget *firstTab = new QWidget;
    {
        QFormLayout *fl = new QFormLayout;
        {
            m_buttonTitle = new QPushButton(">>");;
            fl->addRow(tr("Title"), m_buttonTitle);
            QObject::connect(m_buttonTitle, SIGNAL(toggled(bool)),
                             this, SLOT(titleChecked(bool)));
            m_buttonAlternativeTitle = new QPushButton(">>");;
            fl->addRow(tr("Alternative Title"), m_buttonAlternativeTitle);
            QObject::connect(m_buttonAlternativeTitle, SIGNAL(toggled(bool)),
                             this, SLOT(alternativeTitleChecked(bool)));
            m_buttonCreator = new QPushButton(">>");;
            fl->addRow(tr("Creator"), m_buttonCreator);
            QObject::connect(m_buttonCreator, SIGNAL(toggled(bool)),
                             this, SLOT(creatorChecked(bool)));
            m_buttonSubject = new QPushButton(">>");;
            fl->addRow(tr("Subject"), m_buttonSubject);
            QObject::connect(m_buttonSubject, SIGNAL(toggled(bool)),
                             this, SLOT(subjectChecked(bool)));
            m_buttonDescription = new QPushButton(">>");;
            fl->addRow(tr("Description"), m_buttonDescription);
            QObject::connect(m_buttonDescription, SIGNAL(toggled(bool)),
                             this, SLOT(descriptionChecked(bool)));
            m_buttonPublisher = new QPushButton(">>");;
            fl->addRow(tr("Publisher"), m_buttonPublisher);
            QObject::connect(m_buttonPublisher, SIGNAL(toggled(bool)),
                             this, SLOT(publisherChecked(bool)));
            m_buttonContributor = new QPushButton(">>");;
            fl->addRow(tr("Contributor"), m_buttonContributor);
            QObject::connect(m_buttonContributor, SIGNAL(toggled(bool)),
                             this, SLOT(contributorChecked(bool)));
            m_buttonDate = new QPushButton(">>");;
            fl->addRow(tr("Date"), m_buttonDate);
            QObject::connect(m_buttonDate, SIGNAL(toggled(bool)),
                             this, SLOT(dateChecked(bool)));
            m_buttonType = new QPushButton(">>");;
            fl->addRow(tr("Type"), m_buttonType);
            QObject::connect(m_buttonType, SIGNAL(toggled(bool)),
                             this, SLOT(typeChecked(bool)));
            m_buttonFormat = new QPushButton(">>");;
            fl->addRow(tr("Format"), m_buttonFormat);
            QObject::connect(m_buttonFormat, SIGNAL(toggled(bool)),
                             this, SLOT(formatChecked(bool)));
            m_buttonIdentifier = new QPushButton(">>");;
            fl->addRow(tr("Identifier"), m_buttonIdentifier);
            QObject::connect(m_buttonIdentifier, SIGNAL(toggled(bool)),
                             this, SLOT(identifierChecked(bool)));
            m_buttonSource = new QPushButton(">>");;
            fl->addRow(tr("Source"), m_buttonSource);
            QObject::connect(m_buttonSource, SIGNAL(toggled(bool)),
                             this, SLOT(sourceChecked(bool)));
            m_buttonLanguage = new QPushButton(">>");;
            fl->addRow(tr("Language"), m_buttonLanguage);
            QObject::connect(m_buttonLanguage, SIGNAL(toggled(bool)),
                             this, SLOT(languageChecked(bool)));

        }
        firstTab->setLayout(fl);
    }
    tabWidget->addTab(firstTab, "Credits");

    // Second tab
    QWidget *secondTab = new QWidget;
    {
        QFormLayout *fl = new QFormLayout;
        {
            m_buttonRelation = new QPushButton(">>");;
            fl->addRow(tr("Relation"), m_buttonRelation);
            QObject::connect(m_buttonRelation, SIGNAL(toggled(bool)),
                             this, SLOT(relationChecked(bool)));
            m_buttonIsVersionOf = new QPushButton(">>");;
            fl->addRow(tr("Is Version Of"), m_buttonIsVersionOf);
            QObject::connect(m_buttonIsVersionOf, SIGNAL(toggled(bool)),
                             this, SLOT(isVersionOfChecked(bool)));
            m_buttonHasVersion = new QPushButton(">>");;
            fl->addRow(tr("Has Version"), m_buttonHasVersion);
            QObject::connect(m_buttonHasVersion, SIGNAL(toggled(bool)),
                             this, SLOT(hasVersionChecked(bool)));
            m_buttonIsReplacedBy = new QPushButton(">>");;
            fl->addRow(tr("Is Replaced By"), m_buttonIsReplacedBy);
            QObject::connect(m_buttonIsReplacedBy, SIGNAL(toggled(bool)),
                             this, SLOT(isReplacedByChecked(bool)));
            m_buttonReplaces = new QPushButton(">>");;
            fl->addRow(tr("Replaces"), m_buttonReplaces);
            QObject::connect(m_buttonReplaces, SIGNAL(toggled(bool)),
                             this, SLOT(replacesChecked(bool)));
            m_buttonIsRequiredBy = new QPushButton(">>");;
            fl->addRow(tr("Is Required By"), m_buttonIsRequiredBy);
            QObject::connect(m_buttonIsRequiredBy, SIGNAL(toggled(bool)),
                             this, SLOT(isRequiredByChecked(bool)));
            m_buttonRequires = new QPushButton(">>");;
            fl->addRow(tr("Requires"), m_buttonRequires);
            QObject::connect(m_buttonRequires, SIGNAL(toggled(bool)),
                             this, SLOT(requiresChecked(bool)));
            m_buttonIsPartOf = new QPushButton(">>");;
            fl->addRow(tr("Is Part Of"), m_buttonIsPartOf);
            QObject::connect(m_buttonIsPartOf, SIGNAL(toggled(bool)),
                             this, SLOT(isPartOfChecked(bool)));
            m_buttonHasPart = new QPushButton(">>");;
            fl->addRow(tr("Has Part"), m_buttonHasPart);
            QObject::connect(m_buttonHasPart, SIGNAL(toggled(bool)),
                             this, SLOT(hasPartChecked(bool)));
            m_buttonHasTrackPart = new QPushButton(">>");;
            fl->addRow(tr("Has Track Part"), m_buttonHasTrackPart);
            QObject::connect(m_buttonHasTrackPart, SIGNAL(toggled(bool)),
                             this, SLOT(hasTrackPartChecked(bool)));
            m_buttonIsReferencedBy = new QPushButton(">>");;
            fl->addRow(tr("Is Referenced By"), m_buttonIsReferencedBy);
            QObject::connect(m_buttonIsReferencedBy, SIGNAL(toggled(bool)),
                             this, SLOT(isReferencedByChecked(bool)));
            m_buttonReferences = new QPushButton(">>");;
            fl->addRow(tr("References"), m_buttonReferences);
            QObject::connect(m_buttonReferences, SIGNAL(toggled(bool)),
                             this, SLOT(referencesChecked(bool)));
            m_buttonIsFormatOf = new QPushButton(">>");;
            fl->addRow(tr("Is Format Of"), m_buttonIsFormatOf);
            QObject::connect(m_buttonIsFormatOf, SIGNAL(toggled(bool)),
                             this, SLOT(isFormatOfChecked(bool)));
            m_buttonHasFormat = new QPushButton(">>");;
            fl->addRow(tr("Has Format"), m_buttonHasFormat);
            QObject::connect(m_buttonHasFormat, SIGNAL(toggled(bool)),
                             this, SLOT(hasFormatChecked(bool)));
            m_buttonIsEpisodeOf = new QPushButton(">>");;
            fl->addRow(tr("Is Episod eOf"), m_buttonIsEpisodeOf);
            QObject::connect(m_buttonIsEpisodeOf, SIGNAL(toggled(bool)),
                             this, SLOT(isEpisodeOfChecked(bool)));
            m_buttonIsMemberOf = new QPushButton(">>");;
            fl->addRow(tr("Is Member Of"), m_buttonIsMemberOf);
            QObject::connect(m_buttonIsMemberOf, SIGNAL(toggled(bool)),
                             this, SLOT(isMemberOfChecked(bool)));
        }
        secondTab->setLayout(fl);
    }
    tabWidget->addTab(secondTab, "Relations");

    // Third tab
    QWidget *thirdTab = new QWidget;
    {
        QFormLayout *fl = new QFormLayout;
        {
            m_buttonCoverage = new QPushButton(">>");;
            fl->addRow(tr("Coverage"), m_buttonCoverage);
            QObject::connect(m_buttonCoverage, SIGNAL(toggled(bool)),
                             this, SLOT(coverageChecked(bool)));
            m_buttonRights = new QPushButton(">>");;
            fl->addRow(tr("Rights"), m_buttonRights);
            QObject::connect(m_buttonRights, SIGNAL(toggled(bool)),
                             this, SLOT(rightsChecked(bool)));
            m_buttonVersion = new QPushButton(">>");;
            fl->addRow(tr("Version"), m_buttonVersion);
            QObject::connect(m_buttonVersion, SIGNAL(toggled(bool)),
                             this, SLOT(versionChecked(bool)));
            m_buttonPublicationHistory = new QPushButton(">>");;
            fl->addRow(tr("Publication History"), m_buttonPublicationHistory);
            QObject::connect(m_buttonPublicationHistory, SIGNAL(toggled(bool)),
                             this, SLOT(publicationHistoryChecked(bool)));
            m_buttonRating = new QPushButton(">>");;
            fl->addRow(tr("Rating"), m_buttonRating);
            QObject::connect(m_buttonRating, SIGNAL(toggled(bool)),
                             this, SLOT(ratingChecked(bool)));
            m_buttonPart = new QPushButton(">>");;
            fl->addRow(tr("Part"), m_buttonPart);
            QObject::connect(m_buttonPart, SIGNAL(toggled(bool)),
                             this, SLOT(partChecked(bool)));

        }
        thirdTab->setLayout(fl);
    }
    tabWidget->addTab(thirdTab, "Technicals");
    QObject::connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));

    mainHLayout->addWidget(tabWidget);

    // Set button group
    QButtonGroup *group = new QButtonGroup(this);
    m_buttonTitle->setCheckable(true);
    group->addButton(m_buttonTitle);
    m_buttonAlternativeTitle->setCheckable(true);
    group->addButton(m_buttonAlternativeTitle);
    m_buttonCreator->setCheckable(true);
    group->addButton(m_buttonCreator);
    m_buttonSubject->setCheckable(true);
    group->addButton(m_buttonSubject);
    m_buttonDescription->setCheckable(true);
    group->addButton(m_buttonDescription);
    m_buttonPublisher->setCheckable(true);
    group->addButton(m_buttonPublisher);
    m_buttonContributor->setCheckable(true);
    group->addButton(m_buttonContributor);
    m_buttonDate->setCheckable(true);
    group->addButton(m_buttonDate);
    m_buttonType->setCheckable(true);
    group->addButton(m_buttonType);
    m_buttonFormat->setCheckable(true);
    group->addButton(m_buttonFormat);
    m_buttonIdentifier->setCheckable(true);
    group->addButton(m_buttonIdentifier);
    m_buttonSource->setCheckable(true);
    group->addButton(m_buttonSource);
    m_buttonLanguage->setCheckable(true);
    group->addButton(m_buttonLanguage);
    m_buttonRelation->setCheckable(true);
    group->addButton(m_buttonRelation);
    m_buttonIsVersionOf->setCheckable(true);
    group->addButton(m_buttonIsVersionOf);
    m_buttonHasVersion->setCheckable(true);
    group->addButton(m_buttonHasVersion);
    m_buttonIsReplacedBy->setCheckable(true);
    group->addButton(m_buttonIsReplacedBy);
    m_buttonReplaces->setCheckable(true);
    group->addButton(m_buttonReplaces);
    m_buttonIsRequiredBy->setCheckable(true);
    group->addButton(m_buttonIsRequiredBy);
    m_buttonRequires->setCheckable(true);
    group->addButton(m_buttonRequires);
    m_buttonIsPartOf->setCheckable(true);
    group->addButton(m_buttonIsPartOf);
    m_buttonHasPart->setCheckable(true);
    group->addButton(m_buttonHasPart);
    m_buttonHasTrackPart->setCheckable(true);
    group->addButton(m_buttonHasTrackPart);
    m_buttonIsReferencedBy->setCheckable(true);
    group->addButton(m_buttonIsReferencedBy);
    m_buttonReferences->setCheckable(true);
    group->addButton(m_buttonReferences);
    m_buttonIsFormatOf->setCheckable(true);
    group->addButton(m_buttonIsFormatOf);
    m_buttonHasFormat->setCheckable(true);
    group->addButton(m_buttonHasFormat);
    m_buttonIsEpisodeOf->setCheckable(true);
    group->addButton(m_buttonIsEpisodeOf);
    m_buttonIsMemberOf->setCheckable(true);
    group->addButton(m_buttonIsMemberOf);
    m_buttonCoverage->setCheckable(true);
    group->addButton(m_buttonCoverage);
    m_buttonRights->setCheckable(true);
    group->addButton(m_buttonRights);
    m_buttonVersion->setCheckable(true);
    group->addButton(m_buttonVersion);
    m_buttonPublicationHistory->setCheckable(true);
    group->addButton(m_buttonPublicationHistory);
    m_buttonRating->setCheckable(true);
    group->addButton(m_buttonRating);
    m_buttonPart->setCheckable(true);
    group->addButton(m_buttonPart);

    // Add list view on the right
    m_listView = new ListView();
    QObject::connect(m_listView->buttonAdd(), SIGNAL(clicked()),
                     this, SLOT(addClicked()));
    QObject::connect(m_listView->buttonEdit(), SIGNAL(clicked()),
                     this, SLOT(editClicked()));
    QObject::connect(m_listView->buttonRemove(), SIGNAL(clicked()),
                     this, SLOT(removeClicked()));
    mainHLayout->addWidget(m_listView);

    this->setLayout(mainHLayout);
    m_buttonTitle->setChecked(true);
}

QString CoreMetadataTypeForm::toString()
{
    return QString("CoreMetadata Type");
}

void CoreMetadataTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_coreMetadata;
        m_coreMetadata = 0;
    }
    emit closed(m_op, QVarPtr<CoreMetadataType>::asQVariant(m_coreMetadata));
}

void CoreMetadataTypeForm::applyClicked()
{
    emit closed(m_op, QVarPtr<CoreMetadataType>::asQVariant(m_coreMetadata));
}

void CoreMetadataTypeForm::addClicked()
{
    switch (m_currentEditMode) {
    case Title:
    {
        TitleTypeForm *titleForm = new TitleTypeForm(0, this->mainWindow());
        QObject::connect(titleForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(titleFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(titleForm);
    }
        break;
    case AlternativeTitle:
    {
        AlternativeTitleTypeForm *alternativeTitleForm = new AlternativeTitleTypeForm(0, this->mainWindow());
        QObject::connect(alternativeTitleForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(alternativeTitleFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(alternativeTitleForm);
    }
        break;
    case Creator:
    {
        EntityTypeForm *creatorForm = new EntityTypeForm(0, this->mainWindow());
        QObject::connect(creatorForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(creatorFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(creatorForm);
    }
        break;
    case Subject:
    {
        SubjectTypeForm *subjectForm = new SubjectTypeForm(0, this->mainWindow());
        QObject::connect(subjectForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(subjectFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(subjectForm);
    }
        break;
    case Description:
    {
        DescriptionTypeForm *descriptionForm = new DescriptionTypeForm(0, this->mainWindow());
        QObject::connect(descriptionForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(descriptionFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(descriptionForm);
    }
        break;
    case Publisher:
    {
        EntityTypeForm *publisherForm = new EntityTypeForm(0, this->mainWindow());
        QObject::connect(publisherForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(publisherFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(publisherForm);
    }
        break;
    case Contributor:
    {
        EntityTypeForm *contributorForm = new EntityTypeForm(0, this->mainWindow());
        QObject::connect(contributorForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(contributorFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(contributorForm);
    }
        break;
    case Date:
    {
        DateTypeForm *dateForm = new DateTypeForm(0, this->mainWindow());
        QObject::connect(dateForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(dateFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(dateForm);
    }
        break;
    case Type:
    {
        TypeTypeForm *typeForm = new TypeTypeForm(0, this->mainWindow());
        QObject::connect(typeForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(typeFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(typeForm);
    }
        break;
    case Format:
    {
        /// @todo: comment
//        FormatTypeForm *formatForm = new FormatTypeForm(0, this->mainWindow());
//        QObject::connect(formatForm, SIGNAL(closed(Operation,QVariant)),
//                         this, SLOT(formatFormClosed(Operation,QVariant)));
//        this->mainWindow()->pushWidget(formatForm);
    }
        break;
    case Identifier:
    {
        IdentifierTypeForm *identifierForm = new IdentifierTypeForm(0, this->mainWindow());
        QObject::connect(identifierForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(identifierFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(identifierForm);
    }
        break;
    case Source:
    {
        ElementTypeForm *sourceForm = new ElementTypeForm(0, this->mainWindow());
        sourceForm->setTitle(tr("Source"));
        QObject::connect(sourceForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(sourceFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(sourceForm);
    }
        break;
    case Language:
    {
        LanguageTypeForm *languageForm = new LanguageTypeForm(0, this->mainWindow());
        QObject::connect(languageForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(languageFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(languageForm);
    }
        break;
    case Relation:
    {
        RelationTypeForm *relationForm = new RelationTypeForm(0, this->mainWindow());
        QObject::connect(relationForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(relationFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(relationForm);
    }
        break;
    case IsVersionOf:
    {
        RelationTypeForm *isVersionOfForm = new RelationTypeForm(0, this->mainWindow());
        QObject::connect(isVersionOfForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(isVersionOfFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(isVersionOfForm);
    }
        break;
    case HasVersion:
    {
        RelationTypeForm *hasVersionForm = new RelationTypeForm(0, this->mainWindow());
        QObject::connect(hasVersionForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(hasVersionFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(hasVersionForm);
    }
        break;
    case IsReplacedBy:
    {
        RelationTypeForm *isReplacedByForm = new RelationTypeForm(0, this->mainWindow());
        QObject::connect(isReplacedByForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(isReplacedByFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(isReplacedByForm);
    }
        break;
    case Replaces:
    {
        RelationTypeForm *replacesForm = new RelationTypeForm(0, this->mainWindow());
        QObject::connect(replacesForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(replacesFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(replacesForm);
    }
        break;
    case IsRequiredBy:
    {
        RelationTypeForm *isRequiredByForm = new RelationTypeForm(0, this->mainWindow());
        QObject::connect(isRequiredByForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(isRequiredByFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(isRequiredByForm);
    }
        break;
    case Requires:
    {
        RelationTypeForm *requiresForm = new RelationTypeForm(0, this->mainWindow());
        QObject::connect(requiresForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(requiresFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(requiresForm);
    }
        break;
    case IsPartOf:
    {
        RelationTypeForm *isPartOfForm = new RelationTypeForm(0, this->mainWindow());
        QObject::connect(isPartOfForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(isPartOfFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(isPartOfForm);
    }
        break;
    case HasPart:
    {
        RelationTypeForm *hasPartForm = new RelationTypeForm(0, this->mainWindow());
        QObject::connect(hasPartForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(hasPartFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(hasPartForm);
    }
        break;
    case HasTrackPart:
    {
        HasTrackPartTypeForm *hasTrackPartForm = new HasTrackPartTypeForm(0, this->mainWindow());
        QObject::connect(hasTrackPartForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(hasTrackPartFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(hasTrackPartForm);
    }
        break;
    case IsReferencedBy:
    {
        RelationTypeForm *isReferencedByForm = new RelationTypeForm(0, this->mainWindow());
        QObject::connect(isReferencedByForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(isReferencedByFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(isReferencedByForm);
    }
        break;
    case References:
    {
        RelationTypeForm *referencesForm = new RelationTypeForm(0, this->mainWindow());
        QObject::connect(referencesForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(referencesFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(referencesForm);
    }
        break;
    case IsFormatOf:
    {
        RelationTypeForm *isFormatOfForm = new RelationTypeForm(0, this->mainWindow());
        QObject::connect(isFormatOfForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(isFormatOfFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(isFormatOfForm);
    }
        break;
    case HasFormat:
    {
        RelationTypeForm *hasFormatForm = new RelationTypeForm(0, this->mainWindow());
        QObject::connect(hasFormatForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(hasFormatFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(hasFormatForm);
    }
        break;
    case IsEpisodeOf:
    {
        RelationTypeForm *isEpisodeOfForm = new RelationTypeForm(0, this->mainWindow());
        QObject::connect(isEpisodeOfForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(isEpisodeOfFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(isEpisodeOfForm);
    }
        break;
    case IsMemberOf:
    {
        RelationTypeForm *isMemberOfForm = new RelationTypeForm(0, this->mainWindow());
        QObject::connect(isMemberOfForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(isMemberOfFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(isMemberOfForm);
    }
        break;
    case Coverage:
    {
        CoverageTypeForm *coverageForm = new CoverageTypeForm(0, this->mainWindow());
        QObject::connect(coverageForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(coverageFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(coverageForm);
    }
        break;
    case Rights:
    {
        RightsTypeForm *rightsForm = new RightsTypeForm(0, this->mainWindow());
        QObject::connect(rightsForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(rightsFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(rightsForm);
    }
        break;
    case Version:
    {
        ElementTypeForm *versionForm = new ElementTypeForm(0, this->mainWindow());
        versionForm->setTitle(tr("Version"));
        QObject::connect(versionForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(versionFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(versionForm);
    }
        break;
    case PublicationHistory:
    {
        PublicationHistoryTypeForm *publicationHistoryForm = new PublicationHistoryTypeForm(0, this->mainWindow());
        QObject::connect(publicationHistoryForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(publicationHistoryFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(publicationHistoryForm);
    }
        break;
    case Rating:
    {
        RatingTypeForm *ratingForm = new RatingTypeForm(0, this->mainWindow());
        QObject::connect(ratingForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(ratingFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(ratingForm);
    }
        break;
    case Part:
    {
        /// @todo: comment
//        PartTypeForm *partForm = new PartTypeForm(0, this->mainWindow());
//        QObject::connect(partForm, SIGNAL(closed(Operation,QVariant)),
//                         this, SLOT(partFormClosed(Operation,QVariant)));
//        this->mainWindow()->pushWidget(partForm);
    }
        break;
    }
}

void CoreMetadataTypeForm::editClicked()
{
    int index = m_listView->selected();
    if (index < 0)
        return;
    switch (m_currentEditMode) {
    case Title:
    {
        TitleTypeForm *titleForm = new TitleTypeForm(m_coreMetadata->title().at(index), this->mainWindow());
        QObject::connect(titleForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(titleFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(titleForm);
    }
        break;
    case AlternativeTitle:
    {
        AlternativeTitleTypeForm *alternativeTitleForm = new AlternativeTitleTypeForm(m_coreMetadata->alternativeTitle().at(index), this->mainWindow());
        QObject::connect(alternativeTitleForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(alternativeTitleFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(alternativeTitleForm);
    }
        break;
    case Creator:
    {
        EntityTypeForm *creatorForm = new EntityTypeForm(m_coreMetadata->creator().at(index), this->mainWindow());
        QObject::connect(creatorForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(creatorFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(creatorForm);
    }
        break;
    case Subject:
    {
        SubjectTypeForm *subjectForm = new SubjectTypeForm(m_coreMetadata->subject().at(index), this->mainWindow());
        QObject::connect(subjectForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(subjectFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(subjectForm);
    }
        break;
    case Description:
    {
        DescriptionTypeForm *descriptionForm = new DescriptionTypeForm(m_coreMetadata->description().at(index), this->mainWindow());
        QObject::connect(descriptionForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(descriptionFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(descriptionForm);
    }
        break;
    case Publisher:
    {
        EntityTypeForm *publisherForm = new EntityTypeForm(m_coreMetadata->publisher().at(index), this->mainWindow());
        QObject::connect(publisherForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(publisherFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(publisherForm);
    }
        break;
    case Contributor:
    {
        EntityTypeForm *contributorForm = new EntityTypeForm(m_coreMetadata->contributor().at(index), this->mainWindow());
        QObject::connect(contributorForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(contributorFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(contributorForm);
    }
        break;
    case Date:
    {
        DateTypeForm *dateForm = new DateTypeForm(m_coreMetadata->date().at(index), this->mainWindow());
        QObject::connect(dateForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(dateFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(dateForm);
    }
        break;
    case Type:
    {
        TypeTypeForm *typeForm = new TypeTypeForm(m_coreMetadata->type().at(index), this->mainWindow());
        QObject::connect(typeForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(typeFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(typeForm);
    }
        break;
    case Format:
    {
        /// @todo: comment
//        FormatTypeForm *formatForm = new FormatTypeForm(m_coreMetadata->format().at(index), this->mainWindow());
//        QObject::connect(formatForm, SIGNAL(closed(Operation,QVariant)),
//                         this, SLOT(formatFormClosed(Operation,QVariant)));
//        this->mainWindow()->pushWidget(formatForm);
    }
        break;
    case Identifier:
    {
        IdentifierTypeForm *identifierForm = new IdentifierTypeForm(m_coreMetadata->identifier().at(index), this->mainWindow());
        QObject::connect(identifierForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(identifierFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(identifierForm);
    }
        break;
    case Source:
    {
        ElementTypeForm *sourceForm = new ElementTypeForm(m_coreMetadata->source().at(index), this->mainWindow());
        sourceForm->setTitle(tr("Source"));
        QObject::connect(sourceForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(sourceFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(sourceForm);
    }
        break;
    case Language:
    {
        LanguageTypeForm *languageForm = new LanguageTypeForm(m_coreMetadata->language().at(index), this->mainWindow());
        QObject::connect(languageForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(languageFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(languageForm);
    }
        break;
    case Relation:
    {
        RelationTypeForm *relationForm = new RelationTypeForm(m_coreMetadata->relation().at(index), this->mainWindow());
        QObject::connect(relationForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(relationFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(relationForm);
    }
        break;
    case IsVersionOf:
    {
        RelationTypeForm *isVersionOfForm = new RelationTypeForm(m_coreMetadata->isVersionOf().at(index), this->mainWindow());
        QObject::connect(isVersionOfForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(isVersionOfFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(isVersionOfForm);
    }
        break;
    case HasVersion:
    {
        RelationTypeForm *hasVersionForm = new RelationTypeForm(m_coreMetadata->hasVersion().at(index), this->mainWindow());
        QObject::connect(hasVersionForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(hasVersionFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(hasVersionForm);
    }
        break;
    case IsReplacedBy:
    {
        RelationTypeForm *isReplacedByForm = new RelationTypeForm(m_coreMetadata->isReplacedBy().at(index), this->mainWindow());
        QObject::connect(isReplacedByForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(isReplacedByFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(isReplacedByForm);
    }
        break;
    case Replaces:
    {
        RelationTypeForm *replacesForm = new RelationTypeForm(m_coreMetadata->replaces().at(index), this->mainWindow());
        QObject::connect(replacesForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(replacesFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(replacesForm);
    }
        break;
    case IsRequiredBy:
    {
        RelationTypeForm *isRequiredByForm = new RelationTypeForm(m_coreMetadata->isRequiredBy().at(index), this->mainWindow());
        QObject::connect(isRequiredByForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(isRequiredByFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(isRequiredByForm);
    }
        break;
    case Requires:
    {
        RelationTypeForm *requiresForm = new RelationTypeForm(m_coreMetadata->requires().at(index), this->mainWindow());
        QObject::connect(requiresForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(requiresFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(requiresForm);
    }
        break;
    case IsPartOf:
    {
        RelationTypeForm *isPartOfForm = new RelationTypeForm(m_coreMetadata->isPartOf().at(index), this->mainWindow());
        QObject::connect(isPartOfForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(isPartOfFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(isPartOfForm);
    }
        break;
    case HasPart:
    {
        RelationTypeForm *hasPartForm = new RelationTypeForm(m_coreMetadata->hasPart().at(index), this->mainWindow());
        QObject::connect(hasPartForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(hasPartFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(hasPartForm);
    }
        break;
    case HasTrackPart:
    {
        HasTrackPartTypeForm *hasTrackPartForm = new HasTrackPartTypeForm(m_coreMetadata->hasTrackPart().at(index), this->mainWindow());
        QObject::connect(hasTrackPartForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(hasTrackPartFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(hasTrackPartForm);
    }
        break;
    case IsReferencedBy:
    {
        RelationTypeForm *isReferencedByForm = new RelationTypeForm(m_coreMetadata->isReferencedBy().at(index), this->mainWindow());
        QObject::connect(isReferencedByForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(isReferencedByFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(isReferencedByForm);
    }
        break;
    case References:
    {
        RelationTypeForm *referencesForm = new RelationTypeForm(m_coreMetadata->references().at(index), this->mainWindow());
        QObject::connect(referencesForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(referencesFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(referencesForm);
    }
        break;
    case IsFormatOf:
    {
        RelationTypeForm *isFormatOfForm = new RelationTypeForm(m_coreMetadata->isFormatOf().at(index), this->mainWindow());
        QObject::connect(isFormatOfForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(isFormatOfFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(isFormatOfForm);
    }
        break;
    case HasFormat:
    {
        RelationTypeForm *hasFormatForm = new RelationTypeForm(m_coreMetadata->hasFormat().at(index), this->mainWindow());
        QObject::connect(hasFormatForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(hasFormatFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(hasFormatForm);
    }
        break;
    case IsEpisodeOf:
    {
        RelationTypeForm *isEpisodeOfForm = new RelationTypeForm(m_coreMetadata->isEpisodeOf().at(index), this->mainWindow());
        QObject::connect(isEpisodeOfForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(isEpisodeOfFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(isEpisodeOfForm);
    }
        break;
    case IsMemberOf:
    {
        RelationTypeForm *isMemberOfForm = new RelationTypeForm(m_coreMetadata->isMemberOf().at(index), this->mainWindow());
        QObject::connect(isMemberOfForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(isMemberOfFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(isMemberOfForm);
    }
        break;
    case Coverage:
    {
        CoverageTypeForm *coverageForm = new CoverageTypeForm(m_coreMetadata->coverage().at(index), this->mainWindow());
        QObject::connect(coverageForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(coverageFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(coverageForm);
    }
        break;
    case Rights:
    {
        RightsTypeForm *rightsForm = new RightsTypeForm(m_coreMetadata->rights().at(index), this->mainWindow());
        QObject::connect(rightsForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(rightsFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(rightsForm);
    }
        break;
    case Version:
    {
        ElementTypeForm *versionForm = new ElementTypeForm(m_coreMetadata->version(), this->mainWindow());
        versionForm->setTitle(tr("Version"));
        QObject::connect(versionForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(versionFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(versionForm);
    }
        break;
    case PublicationHistory:
    {
        PublicationHistoryTypeForm *publicationHistoryForm = new PublicationHistoryTypeForm(m_coreMetadata->publicationHistory(), this->mainWindow());
        QObject::connect(publicationHistoryForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(publicationHistoryFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(publicationHistoryForm);
    }
        break;
    case Rating:
    {
        RatingTypeForm *ratingForm = new RatingTypeForm(m_coreMetadata->rating().at(index), this->mainWindow());
        QObject::connect(ratingForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(ratingFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(ratingForm);
    }
        break;
    case Part:
    {
        /// @todo: comment
//        PartTypeForm *partForm = new PartTypeForm(m_coreMetadata->part().at(index), this->mainWindow());
//        QObject::connect(partForm, SIGNAL(closed(Operation,QVariant)),
//                         this, SLOT(partFormClosed(Operation,QVariant)));
//        this->mainWindow()->pushWidget(partForm);
    }
        break;
    }
}

void CoreMetadataTypeForm::removeClicked()
{
    int row = m_listView->selected();
    if (row < 0)
        return;
    m_listView->removeAt(row);
    switch (m_currentEditMode) {
    case Title:
    {
        delete(m_coreMetadata->title().takeAt(row));
    }
        break;
    case AlternativeTitle:
    {
        delete(m_coreMetadata->alternativeTitle().takeAt(row));
    }
        break;
    case Creator:
    {
        delete(m_coreMetadata->creator().takeAt(row));
    }
        break;
    case Subject:
    {
        delete(m_coreMetadata->subject().takeAt(row));
    }
        break;
    case Description:
    {
        delete(m_coreMetadata->description().takeAt(row));
    }
        break;
    case Publisher:
    {
        delete(m_coreMetadata->publisher().takeAt(row));
    }
        break;
    case Contributor:
    {
        delete(m_coreMetadata->contributor().takeAt(row));
    }
        break;
    case Date:
    {
        delete(m_coreMetadata->date().takeAt(row));
    }
        break;
    case Type:
    {
        delete(m_coreMetadata->type().takeAt(row));
    }
        break;
    case Format:
    {
        delete(m_coreMetadata->format().takeAt(row));
    }
        break;
    case Identifier:
    {
        delete(m_coreMetadata->identifier().takeAt(row));
    }
        break;
    case Source:
    {
        delete(m_coreMetadata->source().takeAt(row));
    }
        break;
    case Language:
    {
        delete(m_coreMetadata->language().takeAt(row));
    }
        break;
    case Relation:
    {
        delete(m_coreMetadata->relation().takeAt(row));
    }
        break;
    case IsVersionOf:
    {
        delete(m_coreMetadata->isVersionOf().takeAt(row));
    }
        break;
    case HasVersion:
    {
        delete(m_coreMetadata->hasVersion().takeAt(row));
    }
        break;
    case IsReplacedBy:
    {
        delete(m_coreMetadata->isReplacedBy().takeAt(row));
    }
        break;
    case Replaces:
    {
        delete(m_coreMetadata->replaces().takeAt(row));
    }
        break;
    case IsRequiredBy:
    {
        delete(m_coreMetadata->isRequiredBy().takeAt(row));
    }
        break;
    case Requires:
    {
        delete(m_coreMetadata->requires().takeAt(row));
    }
        break;
    case IsPartOf:
    {
        delete(m_coreMetadata->isPartOf().takeAt(row));
    }
        break;
    case HasPart:
    {
        delete(m_coreMetadata->hasPart().takeAt(row));
    }
        break;
    case HasTrackPart:
    {
        delete(m_coreMetadata->hasTrackPart().takeAt(row));
    }
        break;
    case IsReferencedBy:
    {
        delete(m_coreMetadata->isReferencedBy().takeAt(row));
    }
        break;
    case References:
    {
        delete(m_coreMetadata->references().takeAt(row));
    }
        break;
    case IsFormatOf:
    {
        delete(m_coreMetadata->isFormatOf().takeAt(row));
    }
        break;
    case HasFormat:
    {
        delete(m_coreMetadata->hasFormat().takeAt(row));
    }
        break;
    case IsEpisodeOf:
    {
        delete(m_coreMetadata->isEpisodeOf().takeAt(row));
    }
        break;
    case IsMemberOf:
    {
        delete(m_coreMetadata->isMemberOf().takeAt(row));
    }
        break;
    case Coverage:
    {
        delete(m_coreMetadata->coverage().takeAt(row));
    }
        break;
    case Rights:
    {
        delete(m_coreMetadata->rights().takeAt(row));
    }
        break;
    case Version:
    {
        delete(m_coreMetadata->version());
        m_listView->enableAdd(true);
    }
        break;
    case PublicationHistory:
    {
        delete(m_coreMetadata->publicationHistory());
        m_listView->enableAdd(true);
    }
        break;
    case Rating:
    {
        delete(m_coreMetadata->rating().takeAt(row));
    }
        break;
    case Part:
    {
        delete(m_coreMetadata->part().takeAt(row));
    }
        break;

    }
}

void CoreMetadataTypeForm::titleChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Title;
    updateListAndButtons();
    int s = m_coreMetadata->title().size();
    for (int i=0; i < s; ++i) {
        TitleType *coreItem = m_coreMetadata->title().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::alternativeTitleChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = AlternativeTitle;
    updateListAndButtons();
    int s = m_coreMetadata->alternativeTitle().size();
    for (int i=0; i < s; ++i) {
        AlternativeTitleType *coreItem = m_coreMetadata->alternativeTitle().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::creatorChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Creator;
    updateListAndButtons();
    int s = m_coreMetadata->creator().size();
    for (int i=0; i < s; ++i) {
        EntityType *coreItem = m_coreMetadata->creator().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::subjectChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Subject;
    updateListAndButtons();
    int s = m_coreMetadata->subject().size();
    for (int i=0; i < s; ++i) {
        SubjectType *coreItem = m_coreMetadata->subject().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::descriptionChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Description;
    updateListAndButtons();
    int s = m_coreMetadata->description().size();
    for (int i=0; i < s; ++i) {
        DescriptionType *coreItem = m_coreMetadata->description().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::publisherChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Publisher;
    updateListAndButtons();
    int s = m_coreMetadata->publisher().size();
    for (int i=0; i < s; ++i) {
        EntityType *coreItem = m_coreMetadata->publisher().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::contributorChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Contributor;
    updateListAndButtons();
    int s = m_coreMetadata->contributor().size();
    for (int i=0; i < s; ++i) {
        EntityType *coreItem = m_coreMetadata->contributor().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::dateChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Date;
    updateListAndButtons();
    int s = m_coreMetadata->date().size();
    for (int i=0; i < s; ++i) {
        DateType *coreItem = m_coreMetadata->date().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::typeChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Type;
    updateListAndButtons();
    int s = m_coreMetadata->type().size();
    for (int i=0; i < s; ++i) {
        TypeType *coreItem = m_coreMetadata->type().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::formatChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Format;
    updateListAndButtons();
    int s = m_coreMetadata->format().size();
    for (int i=0; i < s; ++i) {
        FormatType *coreItem = m_coreMetadata->format().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::identifierChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Identifier;
    updateListAndButtons();
    int s = m_coreMetadata->identifier().size();
    for (int i=0; i < s; ++i) {
        IdentifierType *coreItem = m_coreMetadata->identifier().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::sourceChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Source;
    updateListAndButtons();
    int s = m_coreMetadata->source().size();
    for (int i=0; i < s; ++i) {
        ElementType *coreItem = m_coreMetadata->source().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::languageChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Language;
    updateListAndButtons();
    int s = m_coreMetadata->language().size();
    for (int i=0; i < s; ++i) {
        LanguageType *coreItem = m_coreMetadata->language().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::relationChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Relation;
    updateListAndButtons();
    int s = m_coreMetadata->relation().size();
    for (int i=0; i < s; ++i) {
        RelationType *coreItem = m_coreMetadata->relation().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::isVersionOfChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = IsVersionOf;
    updateListAndButtons();
    int s = m_coreMetadata->isVersionOf().size();
    for (int i=0; i < s; ++i) {
        RelationType *coreItem = m_coreMetadata->isVersionOf().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::hasVersionChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = HasVersion;
    updateListAndButtons();
    int s = m_coreMetadata->hasVersion().size();
    for (int i=0; i < s; ++i) {
        RelationType *coreItem = m_coreMetadata->hasVersion().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::isReplacedByChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = IsReplacedBy;
    updateListAndButtons();
    int s = m_coreMetadata->isReplacedBy().size();
    for (int i=0; i < s; ++i) {
        RelationType *coreItem = m_coreMetadata->isReplacedBy().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::replacesChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Replaces;
    updateListAndButtons();
    int s = m_coreMetadata->replaces().size();
    for (int i=0; i < s; ++i) {
        RelationType *coreItem = m_coreMetadata->replaces().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::isRequiredByChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = IsRequiredBy;
    updateListAndButtons();
    int s = m_coreMetadata->isRequiredBy().size();
    for (int i=0; i < s; ++i) {
        RelationType *coreItem = m_coreMetadata->isRequiredBy().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::requiresChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Requires;
    updateListAndButtons();
    int s = m_coreMetadata->requires().size();
    for (int i=0; i < s; ++i) {
        RelationType *coreItem = m_coreMetadata->requires().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::isPartOfChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = IsPartOf;
    updateListAndButtons();
    int s = m_coreMetadata->isPartOf().size();
    for (int i=0; i < s; ++i) {
        RelationType *coreItem = m_coreMetadata->isPartOf().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::hasPartChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = HasPart;
    updateListAndButtons();
    int s = m_coreMetadata->hasPart().size();
    for (int i=0; i < s; ++i) {
        RelationType *coreItem = m_coreMetadata->hasPart().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::hasTrackPartChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = HasTrackPart;
    updateListAndButtons();
    int s = m_coreMetadata->hasTrackPart().size();
    for (int i=0; i < s; ++i) {
        HasTrackPartType *coreItem = m_coreMetadata->hasTrackPart().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::isReferencedByChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = IsReferencedBy;
    updateListAndButtons();
    int s = m_coreMetadata->isReferencedBy().size();
    for (int i=0; i < s; ++i) {
        RelationType *coreItem = m_coreMetadata->isReferencedBy().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::referencesChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = References;
    updateListAndButtons();
    int s = m_coreMetadata->references().size();
    for (int i=0; i < s; ++i) {
        RelationType *coreItem = m_coreMetadata->references().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::isFormatOfChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = IsFormatOf;
    updateListAndButtons();
    int s = m_coreMetadata->isFormatOf().size();
    for (int i=0; i < s; ++i) {
        RelationType *coreItem = m_coreMetadata->isFormatOf().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::hasFormatChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = HasFormat;
    updateListAndButtons();
    int s = m_coreMetadata->hasFormat().size();
    for (int i=0; i < s; ++i) {
        RelationType *coreItem = m_coreMetadata->hasFormat().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::isEpisodeOfChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = IsEpisodeOf;
    updateListAndButtons();
    int s = m_coreMetadata->isEpisodeOf().size();
    for (int i=0; i < s; ++i) {
        RelationType *coreItem = m_coreMetadata->isEpisodeOf().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::isMemberOfChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = IsMemberOf;
    updateListAndButtons();
    int s = m_coreMetadata->isMemberOf().size();
    for (int i=0; i < s; ++i) {
        RelationType *coreItem = m_coreMetadata->isMemberOf().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::coverageChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Coverage;
    updateListAndButtons();
    int s = m_coreMetadata->coverage().size();
    for (int i=0; i < s; ++i) {
        CoverageType *coreItem = m_coreMetadata->coverage().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::rightsChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Rights;
    updateListAndButtons();
    int s = m_coreMetadata->rights().size();
    for (int i=0; i < s; ++i) {
        RightsType *coreItem = m_coreMetadata->rights().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::versionChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Version;
    updateListAndButtons();
    ElementType *coreItem = m_coreMetadata->version();
    if (!coreItem)
        return;
    m_listView->addItem(coreItem->toString());
    m_listView->enableAdd(false);
}

void CoreMetadataTypeForm::publicationHistoryChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = PublicationHistory;
    updateListAndButtons();
    PublicationHistoryType *coreItem = m_coreMetadata->publicationHistory();
    if (!coreItem)
        return;
    m_listView->addItem(coreItem->toString());
    m_listView->enableAdd(false);
}

void CoreMetadataTypeForm::ratingChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Rating;
    updateListAndButtons();
    int s = m_coreMetadata->rating().size();
    for (int i=0; i < s; ++i) {
        RatingType *coreItem = m_coreMetadata->rating().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::partChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Part;
    updateListAndButtons();
    int s = m_coreMetadata->part().size();
    for (int i=0; i < s; ++i) {
        PartType *coreItem = m_coreMetadata->part().at(i);
        if (!coreItem)
            continue;
        m_listView->addItem(coreItem->toString());
    }
}

void CoreMetadataTypeForm::titleFormClosed(Operation op, QVariant value)
{
    TitleType *coreItem = QVarPtr<TitleType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->title().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->title().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::alternativeTitleFormClosed(Operation op, QVariant value)
{
    AlternativeTitleType *coreItem = QVarPtr<AlternativeTitleType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->alternativeTitle().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->alternativeTitle().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::creatorFormClosed(Operation op, QVariant value)
{
    EntityType *coreItem = QVarPtr<EntityType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->creator().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->creator().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::subjectFormClosed(Operation op, QVariant value)
{
    SubjectType *coreItem = QVarPtr<SubjectType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->subject().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->subject().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::descriptionFormClosed(Operation op, QVariant value)
{
    DescriptionType *coreItem = QVarPtr<DescriptionType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->description().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->description().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::publisherFormClosed(Operation op, QVariant value)
{
    EntityType *coreItem = QVarPtr<EntityType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->publisher().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->publisher().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::contributorFormClosed(Operation op, QVariant value)
{
    EntityType *coreItem = QVarPtr<EntityType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->contributor().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->contributor().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::dateFormClosed(Operation op, QVariant value)
{
    DateType *coreItem = QVarPtr<DateType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->date().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->date().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::typeFormClosed(Operation op, QVariant value)
{
    TypeType *coreItem = QVarPtr<TypeType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->type().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->type().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::formatFormClosed(Operation op, QVariant value)
{
    FormatType *coreItem = QVarPtr<FormatType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->format().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->format().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::identifierFormClosed(Operation op, QVariant value)
{
    IdentifierType *coreItem = QVarPtr<IdentifierType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->identifier().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->identifier().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::sourceFormClosed(Operation op, QVariant value)
{
    ElementType *coreItem = QVarPtr<ElementType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->source().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->source().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::languageFormClosed(Operation op, QVariant value)
{
    LanguageType *coreItem = QVarPtr<LanguageType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->language().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->language().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::relationFormClosed(Operation op, QVariant value)
{
    RelationType *coreItem = QVarPtr<RelationType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->relation().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->relation().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::isVersionOfFormClosed(Operation op, QVariant value)
{
    RelationType *coreItem = QVarPtr<RelationType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->isVersionOf().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->isVersionOf().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::hasVersionFormClosed(Operation op, QVariant value)
{
    RelationType *coreItem = QVarPtr<RelationType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->hasVersion().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->hasVersion().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::isReplacedByFormClosed(Operation op, QVariant value)
{
    RelationType *coreItem = QVarPtr<RelationType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->isReplacedBy().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->isReplacedBy().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::replacesFormClosed(Operation op, QVariant value)
{
    RelationType *coreItem = QVarPtr<RelationType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->replaces().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->replaces().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::isRequiredByFormClosed(Operation op, QVariant value)
{
    RelationType *coreItem = QVarPtr<RelationType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->isRequiredBy().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->isRequiredBy().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::requiresFormClosed(Operation op, QVariant value)
{
    RelationType *coreItem = QVarPtr<RelationType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->requires().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->requires().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::isPartOfFormClosed(Operation op, QVariant value)
{
    RelationType *coreItem = QVarPtr<RelationType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->isPartOf().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->isPartOf().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::hasPartFormClosed(Operation op, QVariant value)
{
    RelationType *coreItem = QVarPtr<RelationType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->hasPart().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->hasPart().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::hasTrackPartFormClosed(Operation op, QVariant value)
{
    HasTrackPartType *coreItem = QVarPtr<HasTrackPartType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->hasTrackPart().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->hasTrackPart().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::isReferencedByFormClosed(Operation op, QVariant value)
{
    RelationType *coreItem = QVarPtr<RelationType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->isReferencedBy().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->isReferencedBy().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::referencesFormClosed(Operation op, QVariant value)
{
    RelationType *coreItem = QVarPtr<RelationType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->references().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->references().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::isFormatOfFormClosed(Operation op, QVariant value)
{
    RelationType *coreItem = QVarPtr<RelationType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->isFormatOf().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->isFormatOf().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::hasFormatFormClosed(Operation op, QVariant value)
{
    RelationType *coreItem = QVarPtr<RelationType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->hasFormat().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->hasFormat().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::isEpisodeOfFormClosed(Operation op, QVariant value)
{
    RelationType *coreItem = QVarPtr<RelationType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->isEpisodeOf().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->isEpisodeOf().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::isMemberOfFormClosed(Operation op, QVariant value)
{
    RelationType *coreItem = QVarPtr<RelationType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->isMemberOf().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->isMemberOf().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::coverageFormClosed(Operation op, QVariant value)
{
    CoverageType *coreItem = QVarPtr<CoverageType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->coverage().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->coverage().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::rightsFormClosed(Operation op, QVariant value)
{
    RightsType *coreItem = QVarPtr<RightsType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->rights().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->rights().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::versionFormClosed(Operation op, QVariant value)
{
    ElementType *coreItem = QVarPtr<ElementType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->setVersion(coreItem);
        m_listView->enableAdd(false);
    } else if (op == Edit) {
        int row = 0;
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::publicationHistoryFormClosed(Operation op, QVariant value)
{
    PublicationHistoryType *coreItem = QVarPtr<PublicationHistoryType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->setPubblicationHistory(coreItem);
    } else if (op == Edit) {
        int row = 0;
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::ratingFormClosed(Operation op, QVariant value)
{
    RatingType *coreItem = QVarPtr<RatingType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->rating().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->rating().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::partFormClosed(Operation op, QVariant value)
{
    PartType *coreItem = QVarPtr<PartType>::asPointer(value);
    if (!coreItem)
        return;
    if (op == Add) {
        m_listView->addItem(coreItem->toString());
        m_coreMetadata->part().append(coreItem);
    } else if (op == Edit) {
        int row = m_coreMetadata->part().indexOf(coreItem);
        m_listView->setItem(row, coreItem->toString());
    }
}

void CoreMetadataTypeForm::tabChanged(int tabIndex)
{
    switch(tabIndex) {
    case 0:
        m_buttonTitle->setChecked(true);
        break;
    case 1:
        m_buttonRelation->setChecked(true);
        break;
    case 2:
        m_buttonCoverage->setChecked(true);
        break;
    default:
        // If you're here, something dreadful happened.
        break;
    }
}

void CoreMetadataTypeForm::updateListAndButtons()
{
    QString title;
    switch(m_currentEditMode) {
    case Title:
    {
        title = tr("Title");
    }
        break;
    case AlternativeTitle:
    {
        title = tr("Alternative Title");
    }
        break;
    case Creator:
    {
        title = tr("Creator");
    }
        break;
    case Subject:
    {
        title = tr("Subject");
    }
        break;
    case Description:
    {
        title = tr("Description");
    }
        break;
    case Publisher:
    {
        title = tr("Publisher");
    }
        break;
    case Contributor:
    {
        title = tr("Contributor");
    }
        break;
    case Date:
    {
        title = tr("Date");
    }
        break;
    case Type:
    {
        title = tr("Type");
    }
        break;
    case Format:
    {
        title = tr("Format");
    }
        break;
    case Identifier:
    {
        title = tr("Identifier");
    }
        break;
    case Source:
    {
        title = tr("Source");
    }
        break;
    case Language:
    {
        title = tr("Language");
    }
        break;
    case Relation:
    {
        title = tr("Relation");
    }
        break;
    case IsVersionOf:
    {
        title = tr("Is Version Of");
    }
        break;
    case HasVersion:
    {
        title = tr("Has Version");
    }
        break;
    case IsReplacedBy:
    {
        title = tr("Is Replaced By");
    }
        break;
    case Replaces:
    {
        title = tr("Replaces");
    }
        break;
    case IsRequiredBy:
    {
        title = tr("Is Required By");
    }
        break;
    case Requires:
    {
        title = tr("Requires");
    }
        break;
    case IsPartOf:
    {
        title = tr("Is Part Of");
    }
        break;
    case HasPart:
    {
        title = tr("Has Part");
    }
        break;
    case HasTrackPart:
    {
        title = tr("Has Track Part");
    }
        break;
    case IsReferencedBy:
    {
        title = tr("Is Referenced By");
    }
        break;
    case References:
    {
        title = tr("References");
    }
        break;
    case IsFormatOf:
    {
        title = tr("Is Format Of");
    }
        break;
    case HasFormat:
    {
        title = tr("Has Format");
    }
        break;
    case IsEpisodeOf:
    {
        title = tr("Is Episode Of");
    }
        break;
    case IsMemberOf:
    {
        title = tr("Is Member Of");
    }
        break;
    case Coverage:
    {
        title = tr("Coverage");
    }
        break;
    case Rights:
    {
        title = tr("Rights");
    }
        break;
    case Version:
    {
        title = tr("Version");
    }
        break;
    case PublicationHistory:
    {
        title = tr("Publication History");
    }
        break;
    case Rating:
    {
        title = tr("Rating");
    }
        break;
    case Part:
    {
        title = tr("Part");
    }
        break;

    }
    m_listView->setTitle(title);
    m_listView->clear();
}

