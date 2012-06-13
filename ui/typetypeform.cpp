#include "typetypeform.h"
#include "../model/ebucoremaintype.h"
#include "listview.h"
#include "qvarptr.h"
#include "organisationdetailstypeform.h"
#include "contactdetailstypeform.h"
#include "typegroupform.h"
#include "elementtypeform.h"
#include <QPushButton>
#include <QLabel>
#include <QButtonGroup>
#include <QTextBrowser>
#include <QFormLayout>
#include <QDebug>
#include <QEvent>

TypeTypeForm::TypeTypeForm(TypeType *type,
                           QEbuMainWindow *mainWindow,
                           QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (type) ? Edit : Add;
    if (!type)
        m_type = new TypeType;
    else
        m_type = type;
    // Layout
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;
    {
        QFormLayout *fl = new QFormLayout;
        m_buttonType = new QPushButton(">>");
        fl->addRow(tr("Type"), m_buttonType);
        QObject::connect(m_buttonType, SIGNAL(toggled(bool)),
                         this, SLOT(typeChecked(bool)));
        m_buttonGenre = new QPushButton(">>");
        fl->addRow(tr("Genre"), m_buttonGenre);
        QObject::connect(m_buttonGenre, SIGNAL(toggled(bool)),
                         this, SLOT(genreChecked(bool)));
        m_buttonObjectType = new QPushButton(">>");
        fl->addRow(tr("Object type"), m_buttonObjectType);
        QObject::connect(m_buttonObjectType, SIGNAL(toggled(bool)),
                         this, SLOT(objectTypeChecked(bool)));
        m_buttonTargetAudience = new QPushButton(">>");
        fl->addRow(tr("Target audience"), m_buttonTargetAudience);
        QObject::connect(m_buttonTargetAudience, SIGNAL(toggled(bool)),
                         this, SLOT(targetAudienceChecked(bool)));
        l->addLayout(fl);
        QButtonGroup *group = new QButtonGroup(this);
        m_buttonType->setCheckable(true);
        group->addButton(m_buttonType);
        m_buttonGenre->setCheckable(true);
        group->addButton(m_buttonGenre);
        m_buttonObjectType->setCheckable(true);
        group->addButton(m_buttonObjectType);
        m_buttonTargetAudience->setCheckable(true);
        group->addButton(m_buttonTargetAudience);
    }
    {
        QHBoxLayout *hl = new QHBoxLayout;
        hl->addWidget(new QLabel(tr("Note")));
        m_textNote = new QTextEdit;
        hl->addWidget(m_textNote);
        l->addLayout(hl);
    }
    mainHLayout->addLayout(l);
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

    //Event filter
    m_textDocumentation->setText(tr("The nature or genre or target audience of the resource. Type includes terms describing general categories, functions, genres, or aggregation levels for content. Recommended best practice is to select a value from a controlled vocabulary or classification scheme. To describe the physical or digital manifestation of the resource, use the Format element."));
    m_textNote->installEventFilter(this);
    m_buttonType->installEventFilter(this);
    m_buttonGenre->installEventFilter(this);
    m_buttonObjectType->installEventFilter(this);
    m_buttonTargetAudience->installEventFilter(this);

    // Set data fields...
    m_textNote->setText(m_type->note());
    m_buttonType->setChecked(true);
}

QString TypeTypeForm::toString()
{
    return QString(tr("Type"));
}

void TypeTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_type;
        m_type = 0;
    }
    emit closed(m_op, QVarPtr<TypeType>::asQVariant(m_type));
}

void TypeTypeForm::applyClicked()
{
    m_type->setNote(m_textNote->toPlainText());
    emit closed(m_op, QVarPtr<TypeType>::asQVariant(m_type));
}

void TypeTypeForm::addClicked()
{
    switch (m_currentEditMode) {
    case Type:
    {
        ElementTypeForm *typeForm = new ElementTypeForm(0, this->mainWindow());
        typeForm->setTitle(tr("Type"));
        QObject::connect(typeForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(typeFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(typeForm);
    }
        break;
    case Genre:
    {
        TypeGroupForm *genreForm = new TypeGroupForm(0, this->mainWindow());
        genreForm->setTitle(tr("Genre"));
        genreForm->setGeneralDoc(tr("A group of attributes to describe the genre."));
        genreForm->setDefinitionDoc(tr("Free text for an optional definition."));
        genreForm->setLinkDoc(tr("A link to a term or only identify a classification scheme."));
        genreForm->setLabelDoc(tr("Free text field. This can be used to repeat the term name of the classification scheme term identified by a typeLink.\nExample: ‘non-fiction/information’."));
        genreForm->addLinksMap(mainWindow()->getMap("ebu_ContentAlertSchemeCodeCS"));
        genreForm->addLinksMap(mainWindow()->getMap("ebu_ContentGenreCS"));
        genreForm->addLinksMap(mainWindow()->getMap("ebu_EditorialFormatCodeCS"));
        genreForm->addLinksMap(mainWindow()->getMap("ebu_IntentionCodeCS"));
        genreForm->addLinksMap(mainWindow()->getMap("tva_ContentCommercialCS"));
        genreForm->addLinksMap(mainWindow()->getMap("tva_ContentAlertCS"));
        QObject::connect(genreForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(genreFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(genreForm);
    }
        break;
    case ObjectType:
    {
        TypeGroupForm *objectTypeForm = new TypeGroupForm(0, this->mainWindow());
        objectTypeForm->setTitle(tr("Object Type"));
        objectTypeForm->setGeneralDoc(tr("A group of attributes to describe the objectType."));
        objectTypeForm->setDefinitionDoc(tr("Free text for an optional definition.\nExample: ‘A short description of the resource’."));
        objectTypeForm->setLinkDoc(tr("A link to a term or only identify a classification scheme."));
        objectTypeForm->setLabelDoc(tr("Free text field. This can be used to repeat the term name of the classification scheme term identified by a typeLink."));
        objectTypeForm->addLinksMap(mainWindow()->getMap("ebu_ObjectTypeCS"));
        QObject::connect(objectTypeForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(objectTypeFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(objectTypeForm);
    }
        break;
    case TargetAudience:
    {
        TypeGroupForm *targetAudienceForm = new TypeGroupForm(0, this->mainWindow());
        targetAudienceForm->setTitle(tr("Target Audience"));
        targetAudienceForm->setGeneralDoc(tr("A group of attributes to describe the target audience (parental guidance, geographical or occupantional groups, etc.)."));
        targetAudienceForm->setDefinitionDoc(tr("An optional definition.\nExample: code for MPAA 'general' rating."));
        targetAudienceForm->setLinkDoc(tr("A link to a term or only identify a classification scheme."));
        targetAudienceForm->setLabelDoc(tr("Free text field. This can be used to repeat the term name of the classification scheme term identified by a typeLink.\nExample: ‘General’."));
        targetAudienceForm->addLinksMap(mainWindow()->getMap("ebu_IntendedAudienceCodeCS"));
        targetAudienceForm->addLinksMap(mainWindow()->getMap("ebu_ParentalGuidanceCodeCS"));
        QObject::connect(targetAudienceForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(targetAudienceFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(targetAudienceForm);
    }
        break;
    }
}

void TypeTypeForm::editClicked()
{
    int index = m_listView->selected();
    if (index < 0)
        return;

    switch (m_currentEditMode) {
    case Type:
    {
        ElementTypeForm *typeForm = new ElementTypeForm(m_type->type().at(index), this->mainWindow());
        typeForm->setTitle(tr("Type"));
        QObject::connect(typeForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(typeFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(typeForm);
    }
        break;
    case Genre:
    {
        TypeGroupForm *genreForm = new TypeGroupForm(m_type->genre().at(index), this->mainWindow());
        genreForm->setTitle(tr("Genre"));
        genreForm->setGeneralDoc(tr("A group of attributes to describe the genre."));
        genreForm->setDefinitionDoc(tr("Free text for an optional definition."));
        genreForm->setLinkDoc(tr("A link to a term or only identify a classification scheme."));
        genreForm->setLabelDoc(tr("Free text field. This can be used to repeat the term name of the classification scheme term identified by a typeLink.\nExample: ‘non-fiction/information’."));
        genreForm->addLinksMap(mainWindow()->getMap("ebu_ContentAlertSchemeCodeCS"));
        genreForm->addLinksMap(mainWindow()->getMap("ebu_ContentGenreCS"));
        genreForm->addLinksMap(mainWindow()->getMap("ebu_EditorialFormatCodeCS"));
        genreForm->addLinksMap(mainWindow()->getMap("ebu_IntentionCodeCS"));
        genreForm->addLinksMap(mainWindow()->getMap("tva_ContentCommercialCS"));
        genreForm->addLinksMap(mainWindow()->getMap("tva_ContentAlertCS"));
        QObject::connect(genreForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(genreFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(genreForm);
    }
        break;
    case ObjectType:
    {
        TypeGroupForm *objectTypeForm = new TypeGroupForm(m_type->objectType().at(index), this->mainWindow());
        objectTypeForm->setTitle(tr("Object Type"));
        objectTypeForm->setGeneralDoc(tr("A group of attributes to describe the objectType."));
        objectTypeForm->setDefinitionDoc(tr("Free text for an optional definition.\nExample: ‘A short description of the resource’."));
        objectTypeForm->setLinkDoc(tr("A link to a term or only identify a classification scheme."));
        objectTypeForm->setLabelDoc(tr("Free text field. This can be used to repeat the term name of the classification scheme term identified by a typeLink."));
        objectTypeForm->addLinksMap(mainWindow()->getMap("ebu_ObjectTypeCS"));
        QObject::connect(objectTypeForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(objectTypeFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(objectTypeForm);
    }
        break;
    case TargetAudience:
    {
        TypeGroupForm *targetAudienceForm = new TypeGroupForm(m_type->targetAudience().at(index), this->mainWindow());
        targetAudienceForm->setTitle(tr("Target Audience"));
        targetAudienceForm->setGeneralDoc(tr("A group of attributes to describe the target audience (parental guidance, geographical or occupantional groups, etc.)."));
        targetAudienceForm->setDefinitionDoc(tr("An optional definition.\nExample: code for MPAA 'general' rating."));
        targetAudienceForm->setLinkDoc(tr("A link to a term or only identify a classification scheme."));
        targetAudienceForm->setLabelDoc(tr("Free text field. This can be used to repeat the term name of the classification scheme term identified by a typeLink.\nExample: ‘General’."));
        targetAudienceForm->addLinksMap(mainWindow()->getMap("ebu_IntendedAudienceCodeCS"));
        targetAudienceForm->addLinksMap(mainWindow()->getMap("ebu_ParentalGuidanceCodeCS"));
        QObject::connect(targetAudienceForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(targetAudienceFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(targetAudienceForm);
    }
        break;
    }
}

void TypeTypeForm::removeClicked()
{
    int row = m_listView->selected();
    if (row < 0)
        return;
    m_listView->removeAt(row);
    switch (m_currentEditMode) {
    case Type:
    {
        delete(m_type->type().takeAt(row));
    }
        break;
    case Genre:
    {
        delete(m_type->genre().takeAt(row));
    }
        break;
    case ObjectType:
    {
        delete(m_type->objectType().takeAt(row));
    }
        break;
    case TargetAudience:
    {
        delete(m_type->targetAudience().takeAt(row));
    }
        break;
    }
}

void TypeTypeForm::typeChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Type;
    updateListAndButtons();
    int s = m_type->type().size();
    for (int i=0; i < s; ++i) {
        ElementType *et = m_type->type().at(i);
        if (!et)
            continue;
        m_listView->addItem(et->toString());
    }
}

void TypeTypeForm::genreChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Genre;
    updateListAndButtons();
    int s = m_type->genre().size();
    for (int i=0; i < s; ++i) {
        TypeGroup *g = m_type->genre().at(i);
        if (!g)
            continue;
        m_listView->addItem(g->toString());
    }
}

void TypeTypeForm::objectTypeChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = ObjectType;
    updateListAndButtons();
    int s = m_type->objectType().size();
    for (int i=0; i < s; ++i) {
        TypeGroup *ot = m_type->objectType().at(i);
        if (!ot)
            continue;
        m_listView->addItem(ot->toString());
    }
}

void TypeTypeForm::targetAudienceChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = TargetAudience;
    updateListAndButtons();
    int s = m_type->targetAudience().size();
    for (int i=0; i < s; ++i) {
        TypeGroup *ta = m_type->targetAudience().at(i);
        if (!ta)
            continue;
        m_listView->addItem(ta->toString());
    }
}

void TypeTypeForm::typeFormClosed(StackableWidget::Operation op, QVariant value)
{
    ElementType *type = QVarPtr<ElementType>::asPointer(value);
    if(!type)
        return;
    if(op == Add) {
        m_listView->addItem(type->toString());
        m_type->type().append(type);
    } else if(op == Edit) {
        int row = m_type->type().indexOf(type);
        m_listView->setItem(row, type->toString());
    }
}

void TypeTypeForm::genreFormClosed(StackableWidget::Operation op, QVariant value)
{
    TypeGroup *typeGroup = QVarPtr<TypeGroup>::asPointer(value);
    if (!typeGroup)
        return;
    if (op == Add) {
        m_listView->addItem(typeGroup->toString());
        m_type->genre().append(typeGroup);
    } else if (op == Edit) {
        int row = m_type->genre().indexOf(typeGroup);
        m_listView->setItem(row, typeGroup->toString());
    }
}

void TypeTypeForm::objectTypeFormClosed(Operation op, QVariant value)
{
    TypeGroup *typeGroup = QVarPtr<TypeGroup>::asPointer(value);
    if (!typeGroup)
        return;
    if (op == Add) {
        m_listView->addItem(typeGroup->toString());
        m_type->objectType().append(typeGroup);
    } else if (op == Edit) {
        int row = m_type->objectType().indexOf(typeGroup);
        m_listView->setItem(row, typeGroup->toString());
    }
}

void TypeTypeForm::targetAudienceFormClosed(Operation op, QVariant value)
{
    TypeGroup *typeGroup = QVarPtr<TypeGroup>::asPointer(value);
    if (!typeGroup)
        return;
    if (op == Add) {
        m_listView->addItem(typeGroup->toString());
        m_type->targetAudience().append(typeGroup);
    } else if (op == Edit) {
        int row = m_type->targetAudience().indexOf(typeGroup);
        m_listView->setItem(row, typeGroup->toString());
    }
}

bool TypeTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_textNote )
            m_textDocumentation->setText(tr("A note element to provide additional contextual information."));
        else if  (obj == (QObject*) m_buttonType )
            m_textDocumentation->setText(tr("Free text to provide ‘type’ information other than ‘genre’ or ‘objectType’, possibly in different languages."));
        else if  (obj == (QObject*) m_buttonGenre )
            m_textDocumentation->setHtml(tr("To define the ‘genre’ categorising the resource. Content genre is often described through more than one single term.<br/>Reference data:<ul><li><a href=\"http://www.ebu.ch/metadata/cs/web/ebu_ContentAlertSchemeCodeCS_p.xml.htm\">ebu_ContentAlertSchemeCodeCS</a></li><li><a href=\"http://www.ebu.ch/metadata/cs/web/ebu_ContentGenreCS_p.xml.htm\">ebu_ContentGenreCS</a></li><li><a href=\"http://www.ebu.ch/metadata/cs/web/ebu_EditorialFormatCodeCS_p.xml.htm\">ebu_EditorialFormatCodeCS</a></li><li><a href=\"http://www.ebu.ch/metadata/cs/web/ebu_IntentionCodeCS_p.xml.htm\">ebu_IntentionCodeCS</a></li><li><a href=\"http://www.ebu.ch/metadata/cs/web/tva_ContentCommercialCS_p.xml.htm\">tva_ContentCommercialCS</a></li><li><a href=\"http://www.ebu.ch/metadata/cs/web/tva_ContentAlertCS_p.xml.htm\">tva_ContentAlertCS</a></li></ul>"));
        else if (obj == (QObject*) m_buttonObjectType )
            m_textDocumentation->setHtml(tr("To define the type of real or abstract media object that the resource consists of or relates to (e.g. a programme, an item, shot, clip, scene).<br/>Reference data<br/><a href=\"http://www.ebu.ch/metadata/cs/ebu_ObjectTypeCodeCS.xml\">ebu_ObjectTypeCS</a>"));
        else if (obj == (QObject*) m_buttonTargetAudience )
            m_textDocumentation->setHtml(tr("To define the ‘target audience’ categorising the resource.<br/>Reference data<ul><li><a href=\"http://www.ebu.ch/metadata/cs/web/ebu_IntendedAudienceCodeCS_p.xml.htm\">ebu_IntendedAudienceCodeCS</a></li><li><a href=\"http://www.ebu.ch/metadata/cs/web/ebu_ParentalGuidanceCodeCS_p.xml.htm\">ebu_ParentalGuidanceCodeCS</a></li></ul>"));
    }
    return QObject::eventFilter(obj, event);
}

void TypeTypeForm::updateListAndButtons()
{
    QString title;
    if (m_currentEditMode == Type)
        title = tr("Type");
    else if (m_currentEditMode == Genre)
        title = tr("Genre");
    else if (m_currentEditMode == ObjectType)
        title = tr("Object Type");
    else if (m_currentEditMode == TargetAudience)
        title = tr("Target audience");
    m_listView->setTitle(title);
    m_listView->clear();
}



