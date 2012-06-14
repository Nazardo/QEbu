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

#include "locationtypeform.h"
#include "../model/coremetadatatype.h"
#include "../model/typeconverter.h"
#include "typegroupeditbox.h"
#include "coordinatestypeform.h"
#include "qvarptr.h"
#include <QTextBrowser>
#include <QLineEdit>
#include <QLabel>
#include <QEvent>
#include <QPushButton>
#include <QComboBox>
#include <QFormLayout>

LocationTypeForm::LocationTypeForm(LocationType *location, QEbuMainWindow *mainWindow, QWidget *parent)  :
    StackableWidget(mainWindow, parent)
{
    m_op = (location) ? Edit : Add;
    if (!location)
        m_location = new LocationType;
    else
        m_location = location;
    // Layout
    QVBoxLayout *mainVLayout = new QVBoxLayout;
    m_editTypeGroup = new TypeGroupEditBox(location);
    mainVLayout->addWidget(m_editTypeGroup);
    QFormLayout *fl = new QFormLayout;
    m_editLocationId = new QLineEdit;
    m_editLocationId->setValidator(TypeConverter::getUriValidator());
    fl->addRow(tr("Location ID"), m_editLocationId);
    m_textNote = new QTextEdit;
    fl->addRow(tr("Note"), m_textNote);
    m_editName = new QLineEdit;
    fl->addRow(tr("Name"), m_editName);
    m_editCode = new QLineEdit;
    m_editCode->setValidator(TypeConverter::getUriValidator());
    fl->addRow(tr("Code"), m_editCode);
    mainVLayout->addLayout(fl);
    {
        QHBoxLayout *hl = new QHBoxLayout;
        hl->addWidget(new QLabel(tr("Coordinates")));
        m_editCoordinates = new QLineEdit;
        m_editCoordinates->setReadOnly(true);
        hl->addWidget(m_editCoordinates);
        QPushButton *buttonCoordinates = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttonCoordinates, SIGNAL(clicked()),
                         this, SLOT(coordinatesClicked()));
        hl->addWidget(buttonCoordinates);
        QPushButton *buttonCoordinatesRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonCoordinatesRemove, SIGNAL(clicked()),
                         this, SLOT(coordinatesRemoveClicked()));
        hl->addWidget(buttonCoordinatesRemove);
        mainVLayout->addLayout(hl);
    }
    this->setLayout(mainVLayout);

    // Event Filter
    m_textDocumentation->setText(tr("Spatial characteristics of the content of the resource."));
    m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
    m_editTypeGroup->editTypeLabel()->installEventFilter(this);
    m_editTypeGroup->editTypeLink()->installEventFilter(this);
    m_editLocationId->installEventFilter(this);
    m_editName->installEventFilter(this);
    m_editCoordinates->installEventFilter(this);
    m_editCode->installEventFilter(this);
    m_textNote->installEventFilter(this);

    // Set data fields
    m_editLocationId->setText(m_location->locationId());
    m_textNote->setText(m_location->note());
    m_editName->setText(m_location->name());
    m_editCode->setText(m_location->code());
    if (m_location->coordinates())
        m_editCoordinates->setText(m_location->coordinates()->toString());
}

QString LocationTypeForm::toString()
{
    return QString(tr("Location"));
}

void LocationTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_location;
        m_location = 0;
    }
    emit closed(m_op, QVarPtr<LocationType>::asQVariant(m_location));
}

void LocationTypeForm::applyClicked()
{
    m_location->setLocationId(m_editLocationId->text());
    m_location->setNote(m_textNote->toPlainText());
    m_location->setName(m_editName->text());
    m_location->setCode(m_editCode->text());
    m_editTypeGroup->updateExistingTypeGroup(m_location);
    emit closed(m_op, QVarPtr<LocationType>::asQVariant(m_location));
}

void LocationTypeForm::coordinatesClicked()
{
    CoordinatesTypeForm *coordinatesForm = new CoordinatesTypeForm(
                m_location->coordinates(),this->mainWindow());
    QObject::connect(coordinatesForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(coordinatesClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(coordinatesForm);
}

void LocationTypeForm::coordinatesRemoveClicked()
{
    if (!m_location->coordinates())
        return;
    m_location->setCoordinates(0);
    m_editCoordinates->setText(tr("(none)"));
}

void LocationTypeForm::coordinatesClosed(StackableWidget::Operation op, QVariant value)
{
    CoordinatesType *coordinatesType = QVarPtr<CoordinatesType>::asPointer(value);
    if (!coordinatesType)
        return;
    if (op == Add)
        m_location->setCoordinates(coordinatesType);
    m_editCoordinates->setText(coordinatesType->toString());
}

bool LocationTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_textNote )
            m_textDocumentation->setText(tr("A note for additional contextual information."));
        else if  (obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("Free text o precise the type of place and location information provided.\nExample: 'to provide a name of a city'."));
        else if  (obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("Free text.\nExample: 'city'."));
        else if  (obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setText(tr("A link to a classification scheme."));
        else if  (obj == (QObject*) m_editName)
            m_textDocumentation->setText(tr("The name of the place or location.\nExample: 'London'."));
        else if  (obj == (QObject*) m_editCoordinates)
            m_textDocumentation->setText(tr("The spatial coordinates."));
        else if  (obj == (QObject*) m_editCode)
            m_textDocumentation->setText(tr("The code under the which the place or location may be known/referenced.\nExample: 'W1AA 4WW'."));
        else if  (obj == (QObject*) m_editLocationId)
            m_textDocumentation->setText(tr("An attribute to identify the place or location."));
    }
    return QObject::eventFilter(obj, event);
}
