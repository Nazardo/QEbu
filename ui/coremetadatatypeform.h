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

#ifndef COREMETADATATYPEFORM_H
#define COREMETADATATYPEFORM_H

#include "stackablewidget.h"

class CoreMetadataType;
class ListView;
class QButtonGroup;
class QPushButton;
class QLineEdit;

class CoreMetadataTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit CoreMetadataTypeForm(CoreMetadataType *metadata,
                            QEbuMainWindow *mainWindow,
                            QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // List view
    void addClicked();
    void editClicked();
    void removeClicked();
    // -
    void titleChecked(bool checked);
    void alternativeTitleChecked(bool checked);
    void creatorChecked(bool checked);
    void subjectChecked(bool checked);
    void descriptionChecked(bool checked);
    void publisherChecked(bool checked);
    void contributorChecked(bool checked);
    void dateChecked(bool checked);
    void typeChecked(bool checked);
    void formatChecked(bool checked);
    void identifierChecked(bool checked);
    void sourceChecked(bool checked);
    void languageChecked(bool checked);
    void relationChecked(bool checked);
    void isVersionOfChecked(bool checked);
    void hasVersionChecked(bool checked);
    void isReplacedByChecked(bool checked);
    void replacesChecked(bool checked);
    void isRequiredByChecked(bool checked);
    void requiresChecked(bool checked);
    void isPartOfChecked(bool checked);
    void hasPartChecked(bool checked);
    void hasTrackPartChecked(bool checked);
    void isReferencedByChecked(bool checked);
    void referencesChecked(bool checked);
    void isFormatOfChecked(bool checked);
    void hasFormatChecked(bool checked);
    void isEpisodeOfChecked(bool checked);
    void isMemberOfChecked(bool checked);
    void coverageChecked(bool checked);
    void rightsChecked(bool checked);
    void versionChecked(bool checked);
    void publicationHistoryChecked(bool checked);
    void ratingChecked(bool checked);
    void partChecked(bool checked);
    // -
    void titleFormClosed(Operation op, QVariant value);
    void alternativeTitleFormClosed(Operation op, QVariant value);
    void creatorFormClosed(Operation op, QVariant value);
    void subjectFormClosed(Operation op, QVariant value);
    void descriptionFormClosed(Operation op, QVariant value);
    void publisherFormClosed(Operation op, QVariant value);
    void contributorFormClosed(Operation op, QVariant value);
    void dateFormClosed(Operation op, QVariant value);
    void typeFormClosed(Operation op, QVariant value);
    void formatFormClosed(Operation op, QVariant value);
    void identifierFormClosed(Operation op, QVariant value);
    void sourceFormClosed(Operation op, QVariant value);
    void languageFormClosed(Operation op, QVariant value);
    void relationFormClosed(Operation op, QVariant value);
    void isVersionOfFormClosed(Operation op, QVariant value);
    void hasVersionFormClosed(Operation op, QVariant value);
    void isReplacedByFormClosed(Operation op, QVariant value);
    void replacesFormClosed(Operation op, QVariant value);
    void isRequiredByFormClosed(Operation op, QVariant value);
    void requiresFormClosed(Operation op, QVariant value);
    void isPartOfFormClosed(Operation op, QVariant value);
    void hasPartFormClosed(Operation op, QVariant value);
    void hasTrackPartFormClosed(Operation op, QVariant value);
    void isReferencedByFormClosed(Operation op, QVariant value);
    void referencesFormClosed(Operation op, QVariant value);
    void isFormatOfFormClosed(Operation op, QVariant value);
    void hasFormatFormClosed(Operation op, QVariant value);
    void isEpisodeOfFormClosed(Operation op, QVariant value);
    void isMemberOfFormClosed(Operation op, QVariant value);
    void coverageFormClosed(Operation op, QVariant value);
    void rightsFormClosed(Operation op, QVariant value);
    void versionFormClosed(Operation op, QVariant value);
    void publicationHistoryFormClosed(Operation op, QVariant value);
    void ratingFormClosed(Operation op, QVariant value);
    void partFormClosed(Operation op, QVariant value);
    // -
    void tabChanged(int tabIndex);

private:
    enum EditMode {
        Title, AlternativeTitle, Creator, Subject, Description, Publisher, Contributor,
        Date, Type, Format, Identifier, Source, Language, Relation, IsVersionOf, HasVersion,
        IsReplacedBy, Replaces, IsRequiredBy, Requires, IsPartOf, HasPart, HasTrackPart,
        IsReferencedBy, References, IsFormatOf, HasFormat, IsEpisodeOf, IsMemberOf, Coverage,
        Rights, Version, PublicationHistory, Rating, Part
    };
    void updateListAndButtons();
    bool eventFilter(QObject *obj, QEvent *event);
    ListView *m_listView;

    QButtonGroup* m_groupTabs[3];
    QPushButton *m_buttonTitle;
    QPushButton *m_buttonAlternativeTitle;
    QPushButton *m_buttonCreator;
    QPushButton *m_buttonSubject;
    QPushButton *m_buttonDescription;
    QPushButton *m_buttonPublisher;
    QPushButton *m_buttonContributor;
    QPushButton *m_buttonDate;
    QPushButton *m_buttonType;
    QPushButton *m_buttonFormat;
    QPushButton *m_buttonIdentifier;
    QPushButton *m_buttonSource;
    QPushButton *m_buttonLanguage;
    QPushButton *m_buttonRelation;
    QPushButton *m_buttonIsVersionOf;
    QPushButton *m_buttonHasVersion;
    QPushButton *m_buttonIsReplacedBy;
    QPushButton *m_buttonReplaces;
    QPushButton *m_buttonIsRequiredBy;
    QPushButton *m_buttonRequires;
    QPushButton *m_buttonIsPartOf;
    QPushButton *m_buttonHasPart;
    QPushButton *m_buttonHasTrackPart;
    QPushButton *m_buttonIsReferencedBy;
    QPushButton *m_buttonReferences;
    QPushButton *m_buttonIsFormatOf;
    QPushButton *m_buttonHasFormat;
    QPushButton *m_buttonIsEpisodeOf;
    QPushButton *m_buttonIsMemberOf;
    QPushButton *m_buttonCoverage;
    QPushButton *m_buttonRights;
    QPushButton *m_buttonVersion;
    QPushButton *m_buttonPublicationHistory;
    QPushButton *m_buttonRating;
    QPushButton *m_buttonPart;

    CoreMetadataType *m_coreMetadata;
    EditMode m_currentEditMode;
};

#endif // COREMETADATATYPEFORM_H
