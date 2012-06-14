/****************************************************************************
** Copyright (C) 2012 by
**  Mauro Levra  (nazardo)     mauro@nazardo.it
**  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it
**  Denis Patti  (dextp3)      denis.patti@studenti.polito.it
**  Giovanni Pessiva           giovanni.pessiva@gmail.com
**  Stefano Ricossa            stefano.ricossa@gmail.com
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

#include "coveragetypeform.h"
#include "../model/coremetadatatype.h"
#include "listview.h"
#include "elementtypeeditbox.h"
#include "qvarptr.h"
#include "temporaltypeform.h"
#include "locationtypeform.h"
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QEvent>
#include <QTextBrowser>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>

CoverageTypeForm::CoverageTypeForm(CoverageType *coverage,
                                   QEbuMainWindow *mainWindow,
                                   QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (coverage) ? Edit : Add;
    if (!coverage)
        m_coverage = new CoverageType;
    else
        m_coverage = coverage;
    // Layout
    QHBoxLayout *mainHLayout = new QHBoxLayout;
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
    mainHLayout->addLayout(vl);
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

    // Event Filter
    m_textDocumentation->setText(tr("Coverage is used to show various time and place aspects of the subject of the content. Coverage will typically include spatial location (a place name or geographic coordinates), temporal period (a period label, date, or date range) or jurisdiction (such as a named administrative entity).\nRecommended best practice is to select a value from a controlled vocabulary (for example, the Thesaurus of Geographic Names) and that, where appropriate, named places or time periods be used in preference to numeric identifiers such as sets of coordinates or date ranges."));
    m_editCoverage->editLang()->installEventFilter(this);
    m_editCoverage->editValue()->installEventFilter(this);
    m_buttonTemporal->installEventFilter(this);
    m_buttonLocation->installEventFilter(this);

    // Set data fields
    if(m_coverage->coverage()) {
        m_editCoverage->editLang()->setText(m_coverage->coverage()->lang());
        m_editCoverage->editValue()->setText(m_coverage->coverage()->value());
    }
    m_buttonTemporal->setChecked(true);
}

QString CoverageTypeForm::toString()
{
    return QString(tr("Coverage"));
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
        delete(m_coverage->location().takeAt(row));
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

bool CoverageTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editCoverage->editValue())
            m_textDocumentation->setText(tr("Free text to provide temporal or spatial/geographical information about what is shown in the resource."));
        else if (obj == (QObject*) m_editCoverage->editLang())
            m_textDocumentation->setText(tr("The language the information is provided."));
        else if (obj == (QObject*) m_buttonTemporal)
            m_textDocumentation->setText(tr("Temporal characteristics of the content of the resource."));
        else if (obj == (QObject*) m_buttonLocation)
            m_textDocumentation->setText(tr("Spatial characteristics of the content of the resource."));
    }
    return QObject::eventFilter(obj, event);
}
