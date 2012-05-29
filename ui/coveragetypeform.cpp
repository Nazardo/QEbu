#include "coveragetypeform.h"
#include "qvarptr.h"
#include "temporaltypeform.h"
#include "locationtypeform.h"
#include <QtGui>

CoverageTypeForm::CoverageTypeForm(CoverageType *coverage, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (coverage) ? Edit : Add;
    if (!coverage)
        m_coverage = new CoverageType;
    else
        m_coverage = coverage;
    // Layout
    m_mainHLayout = new QHBoxLayout;
    QVBoxLayout *vl = new QVBoxLayout;
    m_editCoverage = new ElementTypeEditBox;
    m_editCoverage->setLabel(tr("Coverage"));
    vl->addWidget(m_editCoverage);
    {
        QFormLayout *fl = new QFormLayout;
        m_buttonTemporal = new QPushButton(">>");
        fl->addRow(tr("Temporal"), m_buttonTemporal);
        QObject::connect(m_buttonTemporal, SIGNAL(toggled(bool)),
                         this, SLOT(temporalChecked(bool)));
        m_buttonLocation = new QPushButton(">>");
        fl->addRow(tr("Location"), m_buttonLocation);
        QObject::connect(m_buttonLocation, SIGNAL(toggled(bool)),
                         this, SLOT(locationChecked(bool)));
        vl->addLayout(fl);
        QButtonGroup *group = new QButtonGroup(this);
        m_buttonTemporal->setCheckable(true);
        group->addButton(m_buttonTemporal);
        m_buttonLocation->setCheckable(true);
        group->addButton(m_buttonLocation);
    }
    {
        QHBoxLayout *hl = new QHBoxLayout;
        QPushButton *buttonClose = new QPushButton(tr("Apply changes"));
        QPushButton *buttonCancel = new QPushButton(tr("Cancel"));
        QObject::connect(buttonClose, SIGNAL(clicked()),
                         this, SLOT(applyClicked()));
        QObject::connect(buttonCancel, SIGNAL(clicked()),
                         this, SLOT(cancelClicked()));
        hl->addWidget(buttonClose);
        hl->addWidget(buttonCancel);
        vl->addLayout(hl);
    }
    m_mainHLayout->addLayout(vl);
    // Add list view on the right
    m_listView = new ListView();
    QObject::connect(m_listView->buttonAdd(), SIGNAL(clicked()),
                     this, SLOT(addClicked()));
    QObject::connect(m_listView->buttonEdit(), SIGNAL(clicked()),
                     this, SLOT(editClicked()));
    QObject::connect(m_listView->buttonRemove(), SIGNAL(clicked()),
                     this, SLOT(removeClicked()));
    m_mainHLayout->addWidget(m_listView);
    this->setLayout(m_mainHLayout);

    // Set data fields
    if(m_coverage->coverage()) {
        m_editCoverage->editLang()->setText(m_coverage->coverage()->lang());
        m_editCoverage->editValue()->setText(m_coverage->coverage()->value());
    }
    m_buttonTemporal->setChecked(true);
}

QString CoverageTypeForm::toString()
{
    return QString("Coverage Type");
}

void CoverageTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_coverage;
        m_coverage = 0;
    }
    emit closed(m_op, QVarPtr<CoverageType>::asQVariant(m_coverage));
}

void CoverageTypeForm::applyClicked()
{
    m_coverage->setCoverage(new ElementType(m_editCoverage->editValue()->text(),
                                      m_editCoverage->editLang()->text()));
    emit closed(m_op, QVarPtr<CoverageType>::asQVariant(m_coverage));
}

void CoverageTypeForm::addClicked()
{
    switch (m_currentEditMode) {
    case Temporal:
    {
        TemporalTypeForm *temporalForm = new TemporalTypeForm(0, this->mainWindow());
        QObject::connect(temporalForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(temporalFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(temporalForm);
    }
        break;
    case Location:
    {
        LocationTypeForm *locationForm = new LocationTypeForm(0, this->mainWindow());
        QObject::connect(locationForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(locationFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(locationForm);
    }
        break;
    }
}

void CoverageTypeForm::editClicked()
{
    int index = m_listView->selected();
    if (index < 0)
        return;
    switch (m_currentEditMode) {
    case Temporal:
    {
        TemporalTypeForm *temporalForm = new TemporalTypeForm(
                    m_coverage->temporal(), this->mainWindow());
        QObject::connect(temporalForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(temporalFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(temporalForm);
    }
        break;
    case Location:
    {
        LocationTypeForm *locationForm = new LocationTypeForm(
                    m_coverage->location().at(index), this->mainWindow());
        QObject::connect(locationForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(locationFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(locationForm);
    }
        break;
    }
}

void CoverageTypeForm::removeClicked()
{
    int row = m_listView->selected();
    if (row < 0)
        return;
    m_listView->removeAt(row);
    switch (m_currentEditMode) {
    case Temporal:
    {
        m_coverage->setTemporal(0);
        m_listView->buttonAdd()->setEnabled(true);
    }
        break;
    case Location:
    {
        m_coverage->location().removeAt(row);
    }
        break;
    }
}

void CoverageTypeForm::temporalChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Temporal;
    updateListAndButtons();
    TemporalType *tt = m_coverage->temporal();
    if (tt) {
        m_listView->addItem(tt->toString());
        m_listView->enableAdd(false);
    }
}

void CoverageTypeForm::locationChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Location;
    updateListAndButtons();
    int s = m_coverage->location().size();
    for (int i=0; i < s; ++i) {
        LocationType *lt = m_coverage->location().at(i);
        if (!lt)
            continue;
        m_listView->addItem(lt->toString());
    }
}

void CoverageTypeForm::temporalFormClosed(StackableWidget::Operation op, QVariant value)
{
    TemporalType *temporal = QVarPtr<TemporalType>::asPointer(value);
    if(!temporal)
        return;
    if(op == Add) {
        m_listView->addItem(temporal->toString());
        m_coverage->setTemporal(temporal);
        m_listView->enableAdd(false);
    } else if(op == Edit) {
        int row = 0;
        m_listView->setItem(row, temporal->toString());
    }
}

void CoverageTypeForm::locationFormClosed(StackableWidget::Operation op, QVariant value)
{
    LocationType *location = QVarPtr<LocationType>::asPointer(value);
    if (!location)
        return;
    if (op == Add) {
        m_listView->addItem(location->toString());
        m_coverage->location().append(location);
    } else if (op == Edit) {
        int row = m_coverage->location().indexOf(location);
        m_listView->setItem(row, location->toString());
    }
}

void CoverageTypeForm::updateListAndButtons()
{
    QString title;
    if (m_currentEditMode == Temporal)
        title = tr("Temporal");
    else if (m_currentEditMode == Location)
        title = tr("Location");
    m_listView->setTitle(title);
    m_listView->clear();
}
