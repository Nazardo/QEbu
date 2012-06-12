#include "datetypeform.h"
#include "../model/coremetadatatype.h"
#include "listview.h"
#include "dategroupform.h"
#include "alternativetypeform.h"
#include "elementtypeform.h"
#include "qvarptr.h"
#include <QPushButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QEvent>
#include <QTextEdit>

DateTypeForm::DateTypeForm(DateType *date,
                           QEbuMainWindow *mainWindow,
                           QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (date) ? Edit : Add;
    if (!date)
        m_date = new DateType;
    else
        m_date = date;

    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *leftVLayout = new QVBoxLayout;
    QFormLayout *formLayout = new QFormLayout;

    m_buttonDate = new QPushButton(">>");
    m_buttonDate->installEventFilter(this);
    formLayout->addRow(tr("Date"), m_buttonDate);
    QObject::connect(m_buttonDate, SIGNAL(toggled(bool)),
                     this, SLOT(dateChecked(bool)));
    m_buttonCreated = new QPushButton(">>");
    m_buttonCreated->installEventFilter(this);
    formLayout->addRow(tr("Date Created"), m_buttonCreated);
    QObject::connect(m_buttonCreated, SIGNAL(toggled(bool)),
                     this, SLOT(createdChecked(bool)));
    m_buttonIssued = new QPushButton(">>");
    m_buttonIssued->installEventFilter(this);
    formLayout->addRow(tr("Date Issued"), m_buttonIssued);
    QObject::connect(m_buttonIssued, SIGNAL(toggled(bool)),
                     this, SLOT(issuedChecked(bool)));
    m_buttonModified = new QPushButton(">>");
    m_buttonModified->installEventFilter(this);
    formLayout->addRow(tr("Date Modified"), m_buttonModified);
    QObject::connect(m_buttonModified, SIGNAL(toggled(bool)),
                     this, SLOT(modifiedChecked(bool)));
    m_buttonDigitised = new QPushButton(">>");
    m_buttonDigitised->installEventFilter(this);
    formLayout->addRow(tr("Date Digitised"), m_buttonDigitised);
    QObject::connect(m_buttonDigitised, SIGNAL(toggled(bool)),
                     this, SLOT(digitisedChecked(bool)));
    m_buttonAlternative = new QPushButton(">>");
    m_buttonAlternative->installEventFilter(this);
    formLayout->addRow(tr("Date Alternative"), m_buttonAlternative);
    QObject::connect(m_buttonAlternative, SIGNAL(toggled(bool)),
                     this, SLOT(alternativeChecked(bool)));
    leftVLayout->addLayout(formLayout);

    QButtonGroup *group = new QButtonGroup(this);
    m_buttonDate->setCheckable(true);
    group->addButton(m_buttonDate);
    m_buttonCreated->setCheckable(true);
    group->addButton(m_buttonCreated);
    m_buttonIssued->setCheckable(true);
    group->addButton(m_buttonIssued);
    m_buttonModified->setCheckable(true);
    group->addButton(m_buttonModified);
    m_buttonDigitised->setCheckable(true);
    group->addButton(m_buttonDigitised);
    m_buttonAlternative->setCheckable(true);
    group->addButton(m_buttonAlternative);

    mainHLayout->addLayout(leftVLayout);
    {
        m_listView = new ListView;
        QObject::connect(m_listView->buttonAdd(), SIGNAL(clicked()),
                         this, SLOT(addClicked()));
        QObject::connect(m_listView->buttonEdit(), SIGNAL(clicked()),
                         this, SLOT(editClicked()));
        QObject::connect(m_listView->buttonRemove(), SIGNAL(clicked()),
                         this, SLOT(removeClicked()));
        mainHLayout->addWidget(m_listView);
    }
    this->setLayout(mainHLayout);
    // Set text fields...
    m_buttonDate->setChecked(true);
    m_textDocumentation->setText(tr("Dates associated with events occurring during the life of the resource.\nTypically, Date will be associated with the creation, modification or availability of the resource."));
}

QString DateTypeForm::toString()
{
    return QString(tr("Date"));
}

void DateTypeForm::applyClicked()
{
    emit closed(m_op, QVarPtr<DateType>::asQVariant(m_date));
}

void DateTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_date;
        m_date = 0;
    }
    emit closed(m_op, QVarPtr<DateType>::asQVariant(m_date));
}

void DateTypeForm::addClicked()
{
    switch(m_currentEditMode) {
    case Date:
    {
        ElementTypeForm *form = new ElementTypeForm(0, mainWindow());
        form->setTitle(tr("Date"));
        form->setGenericTextDocumentation(tr("An element to provide a date in the xml:date format (NOTE: for Dublin Core compatibility purpose, dc:date is of elementType extending a string)."));
        form->setValueDocumentation(tr("Date value for this element"));
        form->setLangDocumentation(tr("Language the data is provided in"));
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(elementTypeFormClosed(Operation,QVariant)));
        mainWindow()->pushWidget(form);
        break;
    }
    case Created:
    {
        DateGroupForm *form = new DateGroupForm(0, mainWindow());
        form->setTitle(tr("Date Created"));
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(dateGroupFormClosed(Operation,QVariant)));
        mainWindow()->pushWidget(form);
        break;
    }
    case Issued:
    {
        DateGroupForm *form = new DateGroupForm(0, mainWindow());
        form->setTitle(tr("Date Created"));
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(dateGroupFormClosed(Operation,QVariant)));
        mainWindow()->pushWidget(form);
        break;
    }
    case Modified:
    {
        DateGroupForm *form = new DateGroupForm(0, mainWindow());
        form->setTitle(tr("Date Modified"));
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(dateGroupFormClosed(Operation,QVariant)));
        mainWindow()->pushWidget(form);
        break;
    }
    case Digitised:
    {
        DateGroupForm *form = new DateGroupForm(0, mainWindow());
        form->setTitle(tr("Date Digitised"));
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(dateGroupFormClosed(Operation,QVariant)));
        mainWindow()->pushWidget(form);
        break;
    }
    case Alternative:
    {
        AlternativeTypeForm *form = new AlternativeTypeForm(0, mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(alternativeTypeFormClosed(Operation,QVariant)));
        mainWindow()->pushWidget(form);
        break;
    }
    }
}

void DateTypeForm::editClicked()
{
    int index = m_listView->selected();
    if (index < 0)
        return;
    switch(m_currentEditMode) {
    case Date:
    {
        ElementTypeForm *form = new ElementTypeForm(
                    m_date->date().at(index), mainWindow());
        form->setTitle(tr("Date"));
        form->setGenericTextDocumentation(tr("An element to provide a date in the xml:date format (NOTE: for Dublin Core compatibility purpose, dc:date is of elementType extending a string)."));
        form->setValueDocumentation(tr("Date value for this element"));
        form->setLangDocumentation(tr("Language the data is provided in"));
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(elementTypeFormClosed(Operation,QVariant)));
        mainWindow()->pushWidget(form);
        break;
    }
    case Created:
    {
        DateGroupForm *form = new DateGroupForm(m_date->created(), mainWindow());
        form->setTitle(tr("Date Created"));
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(dateGroupFormClosed(Operation,QVariant)));
        mainWindow()->pushWidget(form);
        break;
    }
    case Issued:
    {
        DateGroupForm *form = new DateGroupForm(m_date->issued(), mainWindow());
        form->setTitle(tr("Date Created"));
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(dateGroupFormClosed(Operation,QVariant)));
        mainWindow()->pushWidget(form);
        break;
    }
    case Modified:
    {
        DateGroupForm *form = new DateGroupForm(m_date->modified(), mainWindow());
        form->setTitle(tr("Date Modified"));
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(dateGroupFormClosed(Operation,QVariant)));
        mainWindow()->pushWidget(form);
        break;
    }
    case Digitised:
    {
        DateGroupForm *form = new DateGroupForm(m_date->digitised(), mainWindow());
        form->setTitle(tr("Date Digitised"));
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(dateGroupFormClosed(Operation,QVariant)));
        mainWindow()->pushWidget(form);
        break;
    }
    case Alternative:
    {
        AlternativeTypeForm *form = new AlternativeTypeForm(
                    m_date->alternative().at(index), mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(alternativeTypeFormClosed(Operation,QVariant)));
        mainWindow()->pushWidget(form);
        break;
    }
    }
}

void DateTypeForm::removeClicked()
{
    int index = m_listView->selected();
    if (index < 0)
        return;
    switch (m_currentEditMode) {
    case Date:
    {
        delete(m_date->date().takeAt(index));
        m_listView->removeAt(index);
        break;
    }
    case Created:
    {
        m_date->setCreated(0);
        m_listView->clear();
        m_listView->buttonAdd()->setEnabled(true);
        break;
    }
    case Issued:
    {
        m_date->setIssued(0);
        m_listView->clear();
        m_listView->buttonAdd()->setEnabled(true);
        break;
    }
    case Modified:
    {
        m_date->setModified(0);
        m_listView->clear();
        m_listView->buttonAdd()->setEnabled(true);
        break;
    }
    case Digitised:
    {
        m_date->setDigitised(0);
        m_listView->clear();
        m_listView->buttonAdd()->setEnabled(true);
        break;
    }
    case Alternative:
    {
        delete(m_date->alternative().takeAt(index));
        m_listView->removeAt(index);
        break;
    }
    }
}

void DateTypeForm::elementTypeFormClosed(Operation op, QVariant value)
{
    ElementType *element = QVarPtr<ElementType>::asPointer(value);
    if (!element)
        return;
    if (op == Add) {
        m_listView->addItem(element->toString());
        m_date->date().append(element);
    } else if (op == Edit) {
        int row = m_date->date().indexOf(element);
        m_listView->setItem(row, element->toString());
    }
}

void DateTypeForm::dateGroupFormClosed(StackableWidget::Operation op, QVariant value)
{
    DateGroup *dateGroup = QVarPtr<DateGroup>::asPointer(value);
    if (!dateGroup)
        return;
    switch(m_currentEditMode) {
    case Date:
    case Alternative:
        break;
    case Created:
    {
        if (op == Add) {
            m_listView->addItem(dateGroup->toString());
            m_date->setCreated(dateGroup);
            m_listView->buttonAdd()->setEnabled(false);
        } else if (op == Edit) {
            m_listView->setItem(0, dateGroup->toString());
        }
        break;
    }
    case Issued:
    {
        if (op == Add) {
            m_listView->addItem(dateGroup->toString());
            m_date->setIssued(dateGroup);
            m_listView->buttonAdd()->setEnabled(false);
        } else if (op == Edit) {
            m_listView->setItem(0, dateGroup->toString());
        }
        break;
    }
    case Modified:
    {
        if (op == Add) {
            m_listView->addItem(dateGroup->toString());
            m_date->setModified(dateGroup);
            m_listView->buttonAdd()->setEnabled(false);
        } else if (op == Edit) {
            m_listView->setItem(0, dateGroup->toString());
        }
        break;
    }
    case Digitised:
    {
        if (op == Add) {
            m_listView->addItem(dateGroup->toString());
            m_date->setDigitised(dateGroup);
            m_listView->buttonAdd()->setEnabled(false);
        } else if (op == Edit) {
            m_listView->setItem(0, dateGroup->toString());
        }
        break;
    }
    }
}

void DateTypeForm::alternativeTypeFormClosed(StackableWidget::Operation op, QVariant value)
{
    AlternativeType *alternative = QVarPtr<AlternativeType>::asPointer(value);
    if (!alternative)
        return;
    if (op == Add) {
        m_listView->addItem(alternative->toString());
        m_date->alternative().append(alternative);
    } else if (op == Edit) {
        int index = m_date->alternative().indexOf(alternative);
        m_listView->setItem(index, alternative->toString());
    }
}

void DateTypeForm::updateListTitle()
{
    QString title;
    if (m_currentEditMode == Date)
        title = tr("Date");
    else if (m_currentEditMode == Created)
        title = tr("Date Created");
    else if (m_currentEditMode == Issued)
        title = tr("Date Issued");
    else if (m_currentEditMode == Modified)
        title = tr("Date Modified");
    else if (m_currentEditMode == Digitised)
        title = tr("Date Digitised");
    else if (m_currentEditMode == Alternative)
        title = tr("Alternative Date");
    m_listView->setTitle(title);
    m_listView->clear();
}

bool DateTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if ( obj == (QObject*) m_buttonDate)
            m_textDocumentation->setText(tr("An element to provide a date in the xml:date format"));
        else if ( obj == (QObject*) m_buttonCreated )
            m_textDocumentation->setText(tr("An element to specify the creation date for a particular version or rendition of a resource across its life cycle. It is the moment in time that the media item was finalized during its production process and is forwarded to other divisions or agencies to make it ready for publication or distribution."));
        else if  (obj == (QObject*) m_buttonIssued)
            m_textDocumentation->setText(tr("Date of formal issuance (e.g. publication) of the resource.\nSpecifies the formal date for a particular version or rendition of a resource has been made ready or officially released for distribution, publication or consumption, e.g. the broadcasting date of a radio programme.\nA specific time may also be associated with the date."));
        else if  (obj == (QObject*) m_buttonModified)
            m_textDocumentation->setText(tr("Date on which the resource was last changed."));
        else if  (obj == (QObject*) m_buttonDigitised)
            m_textDocumentation->setText(tr("Date on which the resource was digitised."));
        else if  (obj == (QObject*) m_buttonAlternative)
            m_textDocumentation->setText(tr("To define an alternative date important to qualify the resource."));
    }
    return QObject::eventFilter(obj, event);
}

void DateTypeForm::dateChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Date;
    updateListTitle();
    int s = m_date->date().size();
    for (int i=0; i < s; ++i) {
        m_listView->addItem(m_date->date().at(i)->toString());
    }
}

void DateTypeForm::createdChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Created;
    updateListTitle();
    if (m_date->created()) {
        m_listView->buttonAdd()->setEnabled(false);
        m_listView->addItem(m_date->created()->toString());
    }
}

void DateTypeForm::issuedChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Issued;
    updateListTitle();
    if (m_date->issued()) {
        m_listView->buttonAdd()->setEnabled(false);
        m_listView->addItem(m_date->issued()->toString());
    }
}

void DateTypeForm::modifiedChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Modified;
    updateListTitle();
    if (m_date->modified()) {
        m_listView->buttonAdd()->setEnabled(false);
        m_listView->addItem(m_date->modified()->toString());
    }
}

void DateTypeForm::digitisedChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Digitised;
    updateListTitle();
    if (m_date->digitised()) {
        m_listView->buttonAdd()->setEnabled(false);
        m_listView->addItem(m_date->digitised()->toString());
    }
}

void DateTypeForm::alternativeChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Alternative;
    updateListTitle();
    int s = m_date->alternative().size();
    for (int i=0; i < s; ++i) {
        m_listView->addItem(m_date->alternative().at(i)->toString());
    }
}
