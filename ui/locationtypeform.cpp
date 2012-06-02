#include "locationtypeform.h"
#include "../model/coremetadatatype.h"
#include "typegroupeditbox.h"
#include "coordinatestypeform.h"
#include "qvarptr.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
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
    fl->addRow(tr("Location ID"), m_editLocationId);
    m_textNote = new QTextEdit;
    fl->addRow(tr("Note"), m_textNote);
    m_editName = new QLineEdit;
    fl->addRow(tr("Name"), m_editName);
    m_editCode = new QLineEdit;
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
    return QString("Location Type");
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

