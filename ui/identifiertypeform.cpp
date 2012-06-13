#include "identifiertypeform.h"
#include "../model/coremetadatatype.h"
#include "typegroupeditbox.h"
#include "formatgroupeditbox.h"
#include "elementtypeeditbox.h"
#include "qvarptr.h"
#include "entitytypeform.h"
#include <QPushButton>
#include <QLineEdit>
#include <QTextBrowser>
#include <QComboBox>
#include <QEvent>
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>

IdentifierTypeForm::IdentifierTypeForm(IdentifierType *identifier, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (identifier) ? Edit : Add;
    if (!identifier)
        m_identifier = new IdentifierType;
    else
        m_identifier = identifier;

    QVBoxLayout *vl = new QVBoxLayout;
    {
        m_editElementIdentifier = new ElementTypeEditBox;
        m_editElementIdentifier->setLabel(tr("Identifier"));
        vl->addWidget(m_editElementIdentifier);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(identifier);
        vl->addWidget(m_editTypeGroup);
        m_editFormatGroup = new FormatGroupEditBox(identifier);
        m_editFormatGroup->addLinksMap(mainWindow->getMap("ebu_IdentifierTypeCodeCS"));
        vl->addWidget(m_editFormatGroup);
    }
    {
        QHBoxLayout *hl = new QHBoxLayout;
        hl->addWidget(new QLabel(tr("Attributor")));
        m_editAttributor = new QLineEdit;
        m_editAttributor->setReadOnly(true);
        hl->addWidget(m_editAttributor);
        QPushButton *buttomAttributorAdd = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttomAttributorAdd, SIGNAL(clicked()),
                         this, SLOT(attributorClicked()));
        hl->addWidget(buttomAttributorAdd);
        QPushButton *buttonAttributorRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonAttributorRemove, SIGNAL(clicked()),
                         this, SLOT(attributorRemoveClicked()));
        hl->addWidget(buttonAttributorRemove);
        vl->addLayout(hl);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_textNote = new QTextEdit;
        fl->addRow(tr("Note"), m_textNote);
        vl->addLayout(fl);
    }
    this->setLayout(vl);

    // Event filter
    m_textDocumentation->setText(tr("A unique, unambiguous reference or identifier for a resource within a given context. Best practice is to identify the resource (whether analogue or digital) by means of a string or number corresponding to an established or formal identification system if one exists. Otherwise, use an identification method that is in use within your agency, station, production company, office, or institution.\nIt is also possible to enter more than one, different but still unique, identifier for the same resource."));
    m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
    m_editTypeGroup->editTypeLabel()->installEventFilter(this);
    m_editTypeGroup->editTypeLink()->installEventFilter(this);
    m_editFormatGroup->editFormatDefinition()->installEventFilter(this);
    m_editFormatGroup->editFormatLabel()->installEventFilter(this);
    m_editFormatGroup->editFormatLink()->installEventFilter(this);
    m_editElementIdentifier->editValue()->installEventFilter(this);
    m_editElementIdentifier->editLang()->installEventFilter(this);
    m_textNote->installEventFilter(this);
    m_editAttributor->installEventFilter(this);

    // Set text fields...
    m_textNote->setText(m_identifier->note());
    if (m_identifier->identifier()) {
        m_editElementIdentifier->editLang()->setText(m_identifier->identifier()->lang());
        m_editElementIdentifier->editValue()->setText(m_identifier->identifier()->value());
    }
    if (m_identifier->attributor()) {
        m_editAttributor->setText(m_identifier->attributor()->toString());
    }
}

QString IdentifierTypeForm::toString()
{
    return QString(tr("Identifier"));
}

bool IdentifierTypeForm::checkCompliance()
{
    bool ok = true;
    QStringList fields;
    if (m_editElementIdentifier->editValue()->text().isEmpty()) {
        ok = false;
        fields += tr("Identifier");
    }
    if(!ok) {
        QMessageBox::warning(this, this->toString(),
                             tr("<b>Required fields:</b><br>")
                             +fields.join(",<br>"),
                             QMessageBox::Ok, QMessageBox::Ok);
    }
    return ok;
}

void IdentifierTypeForm::attributorRemoveClicked()
{
    if (!m_identifier->attributor())
        return;
    m_identifier->setAttributor(0);
    m_editAttributor->setText(tr("(none)"));
}

void IdentifierTypeForm::attributorClicked()
{
    EntityTypeForm *attributorForm = new EntityTypeForm(
                m_identifier->attributor(),this->mainWindow());
    attributorForm->setTitle(tr("Attributor"));
    QObject::connect(attributorForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(attributorClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(attributorForm);
}

void IdentifierTypeForm::attributorClosed(Operation op, QVariant value)
{
    EntityType *attributor = QVarPtr<EntityType>::asPointer(value);
    if (!attributor)
        return;
    if (op == Add)
        m_identifier->setAttributor(attributor);
    m_editAttributor->setText(attributor->toString());
}

void IdentifierTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_identifier;
        m_identifier = 0;
    }
    emit closed(m_op, QVarPtr<IdentifierType>::asQVariant(m_identifier));
}

void IdentifierTypeForm::applyClicked()
{
    if (!checkCompliance())
        return;
    m_identifier->setNote(m_textNote->toPlainText());
    m_editTypeGroup->updateExistingTypeGroup(m_identifier);
    m_editFormatGroup->updateExistingFormatGroup(m_identifier);
    m_identifier->setIdentifier(new ElementType(
                                m_editElementIdentifier->editValue()->text(),
                                m_editElementIdentifier->editLang()->text()));
    emit closed(m_op, QVarPtr<IdentifierType>::asQVariant(m_identifier));
}

bool IdentifierTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_textNote )
            m_textDocumentation->setText(tr("A note element to provide additional contextual information."));
        else if  (obj == (QObject*) m_editElementIdentifier->editValue())
            m_textDocumentation->setText(tr("Free text to provide an identifier.\nExample: 06.0A.2B.34.01.01.01.01 ."));
        else if  (obj == (QObject*) m_editElementIdentifier->editLang())
            m_textDocumentation->setText("The language in which the identifier is provided.");
        else if (obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("Free text to define the type of Identifier used.\nExample: ‘main identifier attributed to the resource’."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setText(tr("A link to a classification scheme."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("Free text.\nExample: ‘main’."));
        else if (obj == (QObject*) m_editFormatGroup->editFormatDefinition())
            m_textDocumentation->setText(tr("Free text to define the format and possibly syntax of the identifier.\nExample: ‘a unique identifier as defined by SMPTE 330M’."));
        else if (obj == (QObject*) m_editFormatGroup->editFormatLink())
            m_textDocumentation->setText(tr("A link to a classification scheme."));
        else if (obj == (QObject*) m_editFormatGroup->editFormatLabel())
            m_textDocumentation->setText(tr("Free text.\nExample: SMPTE Unique Material Identifier (UMID)."));
        else if  (obj == (QObject*) m_editAttributor)
            m_textDocumentation->setText("To identify the source of attribution of the identifier, attributor is of entityType.");
    }
    return QObject::eventFilter(obj, event);
}
