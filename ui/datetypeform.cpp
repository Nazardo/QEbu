#include "datetypeform.h"
#include "alternativetypeform.h"
#include "elementtypeform.h"
#include "qvarptr.h"
#include <QtGui>

DateTypeForm::DateTypeForm(DateType *date, QEbuMainWindow *mainWindow, QWidget *parent) :
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

    QPushButton *buttonDate = new QPushButton(">>");
    formLayout->addRow(tr("Date"), buttonDate);
    QObject::connect(buttonDate, SIGNAL(toggled(bool)),
                     this, SLOT(dateChecked(bool)));
    QPushButton *buttonCreated = new QPushButton(">>");
    formLayout->addRow(tr("Date Created"), buttonCreated);
    QObject::connect(buttonCreated, SIGNAL(toggled(bool)),
                     this, SLOT(createdChecked(bool)));
    QPushButton *buttonIssued = new QPushButton(">>");
    formLayout->addRow(tr("Date Issued"), buttonIssued);
    QObject::connect(buttonIssued, SIGNAL(toggled(bool)),
                     this, SLOT(issuedChecked(bool)));
    QPushButton *buttonModified = new QPushButton(">>");
    formLayout->addRow(tr("Date Modified"), buttonModified);
    QObject::connect(buttonModified, SIGNAL(toggled(bool)),
                     this, SLOT(modifiedChecked(bool)));
    QPushButton *buttonDigitised = new QPushButton(">>");
    formLayout->addRow(tr("Date Digitised"), buttonDigitised);
    QObject::connect(buttonDigitised, SIGNAL(toggled(bool)),
                     this, SLOT(digitisedChecked(bool)));
    QPushButton *buttonAlternative = new QPushButton(">>");
    formLayout->addRow(tr("Date Alternative"), buttonAlternative);
    QObject::connect(buttonAlternative, SIGNAL(toggled(bool)),
                     this, SLOT(alternativeChecked(bool)));
    leftVLayout->addLayout(formLayout);

    QButtonGroup *group = new QButtonGroup(this);
    buttonDate->setCheckable(true);
    group->addButton(buttonDate);
    buttonCreated->setCheckable(true);
    group->addButton(buttonCreated);
    buttonIssued->setCheckable(true);
    group->addButton(buttonIssued);
    buttonModified->setCheckable(true);
    group->addButton(buttonModified);
    buttonDigitised->setCheckable(true);
    group->addButton(buttonDigitised);
    buttonAlternative->setCheckable(true);
    group->addButton(buttonAlternative);

    {
        QHBoxLayout *lastRow = new QHBoxLayout;
        QPushButton *buttonApply = new QPushButton(tr("Apply changes"));
        QPushButton *buttonCancel = new QPushButton(tr("Cancel"));
        QObject::connect(buttonApply, SIGNAL(clicked()),
                         this, SLOT(applyClicked()));
        QObject::connect(buttonCancel, SIGNAL(clicked()),
                         this, SLOT(cancelClicked()));
        lastRow->addWidget(buttonApply);
        lastRow->addWidget(buttonCancel);
        leftVLayout->addLayout(lastRow);
    }
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
    buttonDate->setChecked(true);
}

QString DateTypeForm::toString()
{
    return QString(tr("DateType"));
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

void DateTypeForm::dateChecked(bool checked)
{
    m_currentEditMode = Date;
    updateListTitle();
    int s = m_date->date().size();
    for (int i=0; i < s; ++i) {
        m_listView->addItem(m_date->date().at(i)->toString());
    }
}

void DateTypeForm::createdChecked(bool checked)
{
    m_currentEditMode = Created;
    updateListTitle();
    if (m_date->created()) {
        m_listView->buttonAdd()->setEnabled(false);
        m_listView->addItem(m_date->created()->toString());
    }
}

void DateTypeForm::issuedChecked(bool checked)
{
    m_currentEditMode = Issued;
    updateListTitle();
    if (m_date->issued()) {
        m_listView->buttonAdd()->setEnabled(false);
        m_listView->addItem(m_date->issued()->toString());
    }
}

void DateTypeForm::modifiedChecked(bool checked)
{
    m_currentEditMode = Modified;
    updateListTitle();
    if (m_date->modified()) {
        m_listView->buttonAdd()->setEnabled(false);
        m_listView->addItem(m_date->modified()->toString());
    }
}

void DateTypeForm::digitisedChecked(bool checked)
{
    m_currentEditMode = Digitised;
    updateListTitle();
    if (m_date->digitised()) {
        m_listView->buttonAdd()->setEnabled(false);
        m_listView->addItem(m_date->digitised()->toString());
    }
}

void DateTypeForm::alternativeChecked(bool checked)
{
    m_currentEditMode = Alternative;
    updateListTitle();
    int s = m_date->alternative().size();
    for (int i=0; i < s; ++i) {
        m_listView->addItem(m_date->alternative().at(i)->toString());
    }
}
