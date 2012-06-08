#include "rightstypeform.h"
#include "typegroupeditbox.h"
#include "listview.h"
#include "../model/coremetadatatype.h"
#include "../model/ebucoremaintype.h"
#include "qvarptr.h"
#include "elementtypeform.h"
#include "entitytypeform.h"
#include "coveragetypeform.h"
#include "identifiertypeform.h"
#include "contactdetailstypeform.h"
#include <QPushButton>
#include <QButtonGroup>
#include <QLineEdit>
#include <QCheckBox>
#include <QTextEdit>
#include <QComboBox>
#include <QFormLayout>
#include <QMessageBox>
#include <QInputDialog>

RightsTypeForm::RightsTypeForm(RightsType *rights, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (rights) ? Edit : Add;
    if (!rights)
        m_rights = new RightsType;
    else
        m_rights = rights;
    // Layout
    QHBoxLayout *hl = new QHBoxLayout;
    {
        QVBoxLayout *l = new QVBoxLayout;
        m_editTypeGroup = new TypeGroupEditBox(rights);
        l->addWidget(m_editTypeGroup);
        QFormLayout *fl = new QFormLayout;
        m_editRightsLink = new QLineEdit;
        fl->addRow(tr("Rights link"), m_editRightsLink);
        m_textNote = new QTextEdit;
        fl->addRow(tr("Note"), m_textNote);
        l->addLayout(fl);
        hl->addLayout(l);
    }
    {
        QVBoxLayout *l = new QVBoxLayout;
        {
            QFormLayout *fl = new QFormLayout;
            m_comboFormatIDRefs = new QPushButton(">>");
            fl->addRow(tr("Format"), m_comboFormatIDRefs);
            QObject::connect(m_comboFormatIDRefs, SIGNAL(toggled(bool)),
                             this, SLOT(formatIDRefsChecked(bool)));
            m_buttonRights = new QPushButton(">>");
            fl->addRow(tr("Rights"), m_buttonRights);
            QObject::connect(m_buttonRights, SIGNAL(toggled(bool)),
                             this, SLOT(rightsChecked(bool)));
            m_buttonRightsHolder = new QPushButton(">>");
            fl->addRow(tr("Rights holder"), m_buttonRightsHolder);
            QObject::connect(m_buttonRightsHolder, SIGNAL(toggled(bool)),
                             this, SLOT(rightsHolderChecked(bool)));
            m_buttonExploitationIssues = new QPushButton(">>");
            fl->addRow(tr("Exploitation issues"), m_buttonExploitationIssues);
            QObject::connect(m_buttonExploitationIssues, SIGNAL(toggled(bool)),
                             this, SLOT(exploitationIssuesChecked(bool)));
            m_buttonCoverage = new QPushButton(">>");
            fl->addRow(tr("Coverage"), m_buttonCoverage);
            QObject::connect(m_buttonCoverage, SIGNAL(toggled(bool)),
                             this, SLOT(coverageChecked(bool)));
            m_buttonDisclaimer = new QPushButton(">>");
            fl->addRow(tr("Disclaimer"), m_buttonDisclaimer);
            QObject::connect(m_buttonDisclaimer, SIGNAL(toggled(bool)),
                             this, SLOT(disclaimerChecked(bool)));
            m_buttonRightsId = new QPushButton(">>");
            fl->addRow(tr("Rights ID"), m_buttonRightsId);
            QObject::connect(m_buttonRightsId, SIGNAL(toggled(bool)),
                             this, SLOT(rightsIdChecked(bool)));
            m_buttonContactDetails = new QPushButton(">>");
            fl->addRow(tr("Contact details"), m_buttonContactDetails);
            QObject::connect(m_buttonContactDetails, SIGNAL(toggled(bool)),
                             this, SLOT(contactDetailsChecked(bool)));
            m_checkRightsClearanceFlag = new QCheckBox;
            fl->addRow(tr("Rights clearance"), m_checkRightsClearanceFlag);
            l->addLayout(fl);
            QButtonGroup *group = new QButtonGroup(this);
            m_comboFormatIDRefs->setCheckable(true);
            group->addButton(m_comboFormatIDRefs);
            m_buttonRights->setCheckable(true);
            group->addButton(m_buttonRights);
            m_buttonRightsHolder->setCheckable(true);
            group->addButton(m_buttonRightsHolder);
            m_buttonExploitationIssues->setCheckable(true);
            group->addButton(m_buttonExploitationIssues);
            m_buttonCoverage->setCheckable(true);
            group->addButton(m_buttonCoverage);
            m_buttonDisclaimer->setCheckable(true);
            group->addButton(m_buttonDisclaimer);
            m_buttonRightsId->setCheckable(true);
            group->addButton(m_buttonRightsId);
            m_buttonContactDetails->setCheckable(true);
            group->addButton(m_buttonContactDetails);
        }
        hl->addLayout(l);
    }
    // Add list view on the right
    m_listView = new ListView();
    QObject::connect(m_listView->buttonAdd(), SIGNAL(clicked()),
                     this, SLOT(addClicked()));
    QObject::connect(m_listView->buttonEdit(), SIGNAL(clicked()),
                     this, SLOT(editClicked()));
    QObject::connect(m_listView->buttonRemove(), SIGNAL(clicked()),
                     this, SLOT(removeClicked()));
    hl->addWidget(m_listView);
    this->setLayout(hl);

    // Set data fields
    m_editRightsLink->setText(m_rights->rightsLink());
    m_textNote->setText(m_rights->note());
    m_checkRightsClearanceFlag->setChecked(m_rights->rightsClearanceFlag());
    m_comboFormatIDRefs->setChecked(true);
}

QString RightsTypeForm::toString()
{
    return QString(tr("Rights"));
}

void RightsTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_rights;
        m_rights = 0;
    }
    emit closed(m_op, QVarPtr<RightsType>::asQVariant(m_rights));
}

void RightsTypeForm::applyClicked()
{
    m_rights->setRightsLink(m_editRightsLink->text());
    m_rights->setNote(m_textNote->toPlainText());
    m_rights->setRightsClearanceFlag(m_checkRightsClearanceFlag->isChecked());
    m_editTypeGroup->updateExistingTypeGroup(m_rights);
    emit closed(m_op, QVarPtr<RightsType>::asQVariant(m_rights));
}

void RightsTypeForm::addClicked()
{
    switch (m_currentEditMode) {
    case FormatIDRefs:
    {
        bool ok;
        QStringList sl = QStringList(mainWindow()->ebuCoreMain()->formatMap().keys());
        if (sl.size() <= 0) {
            QMessageBox::warning(this, this->toString(),
                                 tr("No format IDs available to choose from"),
                                 QMessageBox::Ok, QMessageBox::Ok);
            return;
        }
        QString text = QInputDialog::getItem(this, tr("RightsType > Format IDRef"),
                                              tr("Format ID"), sl, 0, false, &ok);
        if (ok && !text.isEmpty()) {
            QMap<QString, FormatType*>::const_iterator iter = mainWindow()->ebuCoreMain()->formatMap().find(text);
            if ( iter != mainWindow()->ebuCoreMain()->formatMap().end()) {
                m_listView->addItem(text);
                m_rights->formats().append(iter.value());
            }
        }
    }
        break;
    case Rights:
    {
        ElementTypeForm *rightsForm = new ElementTypeForm(0, this->mainWindow());
        rightsForm->setTitle(tr("Rights"));
        QObject::connect(rightsForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(rightsFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(rightsForm);
    }
        break;
    case RightsHolder:
    {
        EntityTypeForm *rightsHolderForm = new EntityTypeForm(0, this->mainWindow());
        rightsHolderForm->setTitle(tr("Rights Holder"));
        QObject::connect(rightsHolderForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(rightsHolderFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(rightsHolderForm);
    }
        break;
    case ExploitationIssues:
    {
        ElementTypeForm *exploitationIssuesForm = new ElementTypeForm(0, this->mainWindow());
        exploitationIssuesForm->setTitle(tr("Exploitation Issues"));
        QObject::connect(exploitationIssuesForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(exploitationIssuesFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(exploitationIssuesForm);
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
    case Disclaimer:
    {
        ElementTypeForm *disclaimerForm = new ElementTypeForm(0, this->mainWindow());
        disclaimerForm->setTitle(tr("Disclaimer"));
        QObject::connect(disclaimerForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(disclaimerFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(disclaimerForm);
    }
        break;
    case RightsId:
    {
        IdentifierTypeForm *rightsIdForm = new IdentifierTypeForm(0, this->mainWindow());
        QObject::connect(rightsIdForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(rightsIdFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(rightsIdForm);
    }
        break;
    case ContactDetails:
    {
        ContactDetailsTypeForm *contactDetailsForm = new ContactDetailsTypeForm(0, this->mainWindow());
        QObject::connect(contactDetailsForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(contactDetailsFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(contactDetailsForm);
    }
        break;
    }
}

void RightsTypeForm::editClicked()
{
    int index = m_listView->selected();
    if (index < 0)
        return;
    switch (m_currentEditMode) {
    case FormatIDRefs:
    {
        bool ok;
        QStringList sl = QStringList(mainWindow()->ebuCoreMain()->formatMap().keys());
        QString selected = m_listView->item(index);
        int active = sl.indexOf(selected);
        QString text = QInputDialog::getItem(this, tr("RightsType > Format IDRef"),
                                              tr("Format ID"), sl, active, false, &ok);
        if (ok && !text.isEmpty()) {
            QMap<QString, FormatType*>::const_iterator iter = mainWindow()->ebuCoreMain()->formatMap().find(text);
            if ( iter != mainWindow()->ebuCoreMain()->formatMap().end()) {
                m_listView->addItem(text);
                m_rights->formats().append(iter.value());
            }
        }
    }
        break;
    case Rights:
    {
        ElementTypeForm *rightsForm = new ElementTypeForm(
                    m_rights->rights(), this->mainWindow());
        rightsForm->setTitle(tr("Rights"));
        QObject::connect(rightsForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(rightsFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(rightsForm);
    }
        break;
    case RightsHolder:
    {
        EntityTypeForm *rightsHolderForm = new EntityTypeForm(
                    m_rights->rightsHolder(), this->mainWindow());
        rightsHolderForm->setTitle(tr("Rights Holder"));
        QObject::connect(rightsHolderForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(rightsHolderFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(rightsHolderForm);
    }
        break;
    case ExploitationIssues:
    {
        ElementTypeForm *exploitationIssuesForm = new ElementTypeForm(
                    m_rights->exploitationIssues(), this->mainWindow());
        exploitationIssuesForm->setTitle(tr("Exploitation Issues"));
        QObject::connect(exploitationIssuesForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(exploitationIssuesFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(exploitationIssuesForm);
    }
        break;
    case Coverage:
    {
        CoverageTypeForm *coverageForm = new CoverageTypeForm(
                    m_rights->coverage(), this->mainWindow());
        QObject::connect(coverageForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(coverageFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(coverageForm);
    }
        break;
    case Disclaimer:
    {
        ElementTypeForm *disclaimerForm = new ElementTypeForm(
                    m_rights->disclaimer().at(index), this->mainWindow());
        disclaimerForm->setTitle(tr("Disclaimer"));
        QObject::connect(disclaimerForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(disclaimerFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(disclaimerForm);
    }
        break;
    case RightsId:
    {
        IdentifierTypeForm *rightsIdForm = new IdentifierTypeForm(
                    m_rights->rightsID().at(index), this->mainWindow());
        QObject::connect(rightsIdForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(rightsIdFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(rightsIdForm);
    }
        break;
    case ContactDetails:
    {
        ContactDetailsTypeForm *contactDetailsForm = new ContactDetailsTypeForm(
                    m_rights->contactDetails().at(index), this->mainWindow());
        QObject::connect(contactDetailsForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(contactDetailsFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(contactDetailsForm);
    }
        break;
    }
}

void RightsTypeForm::removeClicked()
{
    {
        int row = m_listView->selected();
        if (row < 0)
            return;
        m_listView->removeAt(row);
        switch (m_currentEditMode) {
        case FormatIDRefs:
        {
            delete(m_rights->formats().takeAt(row));
        }
            break;
        case Rights:
        {
            m_rights->setRights(0);
            m_listView->buttonAdd()->setEnabled(true);
        }
            break;
        case RightsHolder:
        {
            m_rights->setRightsHolder(0);
            m_listView->buttonAdd()->setEnabled(true);
        }
            break;
        case ExploitationIssues:
        {
            m_rights->setExploitationIssues(0);
            m_listView->buttonAdd()->setEnabled(true);
        }
            break;
        case Coverage:
        {
            m_rights->setCoverage(0);
            m_listView->buttonAdd()->setEnabled(true);
        }
            break;
        case Disclaimer:
        {
            delete(m_rights->disclaimer().takeAt(row));
        }
            break;
        case RightsId:
        {
            delete(m_rights->rightsID().takeAt(row));
        }
            break;
        case ContactDetails:
        {
            delete(m_rights->contactDetails().takeAt(row));
        }
            break;
        }
    }
}

void RightsTypeForm::formatIDRefsChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = FormatIDRefs;
    updateListAndButtons();
    int s = m_rights->formats().size();
    for (int i=0; i < s; ++i) {
        FormatType *f = m_rights->formats().at(i);
        if (!f)
            continue;
        m_listView->addItem(f->toString());
    }
}

void RightsTypeForm::rightsChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Rights;
    updateListAndButtons();
    ElementType *et = m_rights->rights();
    if (et) {
        m_listView->addItem(et->toString());
        m_listView->enableAdd(false);
    }
}

void RightsTypeForm::rightsHolderChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = RightsHolder;
    updateListAndButtons();
    EntityType *et = m_rights->rightsHolder();
    if (et) {
        m_listView->addItem(et->toString());
        m_listView->enableAdd(false);
    }
}

void RightsTypeForm::exploitationIssuesChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = ExploitationIssues;
    updateListAndButtons();
    ElementType *et = m_rights->exploitationIssues();
    if (et) {
        m_listView->addItem(et->toString());
        m_listView->enableAdd(false);
    }
}

void RightsTypeForm::coverageChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Coverage;
    updateListAndButtons();
    CoverageType *ct = m_rights->coverage();
    if (ct) {
        m_listView->addItem(ct->toString());
        m_listView->enableAdd(false);
    }
}

void RightsTypeForm::disclaimerChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Disclaimer;
    updateListAndButtons();
    int s = m_rights->disclaimer().size();
    for (int i=0; i < s; ++i) {
        ElementType *et = m_rights->disclaimer().at(i);
        if (!et)
            continue;
        m_listView->addItem(et->toString());
    }
}

void RightsTypeForm::rightsIdChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = RightsId;
    updateListAndButtons();
    int s = m_rights->rightsID().size();
    for (int i=0; i < s; ++i) {
        IdentifierType *it = m_rights->rightsID().at(i);
        if (!it)
            continue;
        m_listView->addItem(it->toString());
    }
}

void RightsTypeForm::contactDetailsChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = ContactDetails;
    updateListAndButtons();
    int s = m_rights->contactDetails().size();
    for (int i=0; i < s; ++i) {
        ContactDetailsType *cdt = m_rights->contactDetails().at(i);
        if (!cdt)
            continue;
        m_listView->addItem(cdt->toString());
    }
}

void RightsTypeForm::formatIDRefsFormClosed(StackableWidget::Operation op, QVariant value)
{
    FormatType *format = QVarPtr<FormatType>::asPointer(value);
    if(!format)
        return;
    if(op == Add) {
        m_listView->addItem(format->toString());
        m_rights->formats().append(format);
    } else if(op == Edit) {
        int row = m_rights->formats().indexOf(format);
        m_listView->setItem(row, format->toString());
    }
}

void RightsTypeForm::rightsFormClosed(StackableWidget::Operation op, QVariant value)
{
    ElementType *rights = QVarPtr<ElementType>::asPointer(value);
    if(!rights)
        return;
    if(op == Add) {
        m_listView->addItem(rights->toString());
        m_rights->setRights(rights);
        m_listView->enableAdd(false);
    } else if(op == Edit) {
        int row = 0;
        m_listView->setItem(row, rights->toString());
    }
}

void RightsTypeForm::rightsHolderFormClosed(StackableWidget::Operation op, QVariant value)
{
    EntityType *rightsHolder = QVarPtr<EntityType>::asPointer(value);
    if(!rightsHolder)
        return;
    if(op == Add) {
        m_listView->addItem(rightsHolder->toString());
        m_rights->setRightsHolder(rightsHolder);
        m_listView->enableAdd(false);
    } else if(op == Edit) {
        int row = 0;
        m_listView->setItem(row, rightsHolder->toString());
    }
}

void RightsTypeForm::exploitationIssuesFormClosed(StackableWidget::Operation op, QVariant value)
{
    ElementType *exploitationIssues = QVarPtr<ElementType>::asPointer(value);
    if(!exploitationIssues)
        return;
    if(op == Add) {
        m_listView->addItem(exploitationIssues->toString());
        m_rights->setExploitationIssues(exploitationIssues);
        m_listView->enableAdd(false);
    } else if(op == Edit) {
        int row = 0;
        m_listView->setItem(row, exploitationIssues->toString());
    }
}

void RightsTypeForm::coverageFormClosed(StackableWidget::Operation op, QVariant value)
{
    CoverageType *coverage = QVarPtr<CoverageType>::asPointer(value);
    if(!coverage)
        return;
    if(op == Add) {
        m_listView->addItem(coverage->toString());
        m_rights->setCoverage(coverage);
        m_listView->enableAdd(false);
    } else if(op == Edit) {
        int row = 0;
        m_listView->setItem(row, coverage->toString());
    }
}

void RightsTypeForm::disclaimerFormClosed(StackableWidget::Operation op, QVariant value)
{
    ElementType *disclaimer = QVarPtr<ElementType>::asPointer(value);
    if(!disclaimer)
        return;
    if(op == Add) {
        m_listView->addItem(disclaimer->toString());
        m_rights->disclaimer().append(disclaimer);
    } else if(op == Edit) {
        int row = m_rights->disclaimer().indexOf(disclaimer);
        m_listView->setItem(row, disclaimer->toString());
    }
}

void RightsTypeForm::rightsIdFormClosed(StackableWidget::Operation op, QVariant value)
{
    IdentifierType *rightsId = QVarPtr<IdentifierType>::asPointer(value);
    if(!rightsId)
        return;
    if(op == Add) {
        m_listView->addItem(rightsId->toString());
        m_rights->rightsID().append(rightsId);
    } else if(op == Edit) {
        int row = m_rights->rightsID().indexOf(rightsId);
        m_listView->setItem(row, rightsId->toString());
    }
}


void RightsTypeForm::contactDetailsFormClosed(StackableWidget::Operation op, QVariant value)
{
    ContactDetailsType *contactDetails = QVarPtr<ContactDetailsType>::asPointer(value);
    if(!contactDetails)
        return;
    if(op == Add) {
        m_listView->addItem(contactDetails->toString());
        m_rights->contactDetails().append(contactDetails);
    } else if(op == Edit) {
        int row = m_rights->contactDetails().indexOf(contactDetails);
        m_listView->setItem(row, contactDetails->toString());
    }
}

void RightsTypeForm::updateListAndButtons()
{
    QString title;
    if (m_currentEditMode == FormatIDRefs)
        title = tr("Format");
    else if (m_currentEditMode == Rights)
        title = tr("Rights");
    else if (m_currentEditMode == RightsHolder)
        title = tr("Rights holder");
    else if (m_currentEditMode == ExploitationIssues)
        title = tr("Exploitation issues");
    else if (m_currentEditMode == Coverage)
        title = tr("Coverage");
    else if (m_currentEditMode == Disclaimer)
        title = tr("Disclaimer");
    else if (m_currentEditMode == RightsId)
        title = tr("RightsId");
    else if (m_currentEditMode == ContactDetails)
        title = tr("Contact Details");
    m_listView->setTitle(title);
    m_listView->clear();
}
