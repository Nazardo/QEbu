#include "coordinatestypeform.h"
#include "qvarptr.h"
#include <QtGui>

CoordinatesTypeForm::CoordinatesTypeForm(CoordinatesType *coordinates, QEbuMainWindow *mainWindow, QWidget *parent)  :
    StackableWidget(mainWindow, parent)
{
    m_op = (coordinates) ? Edit : Add;
    if (!coordinates)
        m_coordinates = new CoordinatesType;
    else
        m_coordinates = coordinates;
    // Layout
    m_mainVLayout = new QVBoxLayout;
    m_editFormatGroup = new FormatGroupEditBox(coordinates);
    m_mainVLayout->addWidget(m_editFormatGroup);
    {
        QGridLayout *gl = new QGridLayout;

        m_spinPosx = new QDoubleSpinBox;
        m_checkPosx = new QCheckBox(tr("PosX"));
        gl->addWidget(m_checkPosx, 0, 0);
        gl->addWidget(m_spinPosx, 0, 1);
        QObject::connect(m_spinPosx, SIGNAL(valueChanged(double)),
                         this, SLOT(posxChanged()));

        m_spinPosy = new QDoubleSpinBox;
        m_checkPosy = new QCheckBox(tr("PosY"));
        gl->addWidget(m_checkPosy, 1, 0);
        gl->addWidget(m_spinPosy, 1, 1);
        QObject::connect(m_spinPosy, SIGNAL(valueChanged(double)),
                         this, SLOT(posyChanged()));

        m_mainVLayout->addLayout(gl);
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
        m_mainVLayout->addLayout(hl);
    }
    this->setLayout(m_mainVLayout);

    // Set text fields
    if (m_coordinates->posx()) {
        m_spinPosx->setValue(m_coordinates->posx());
        m_checkPosx->setChecked(true);
    }
    if (m_coordinates->posy()) {
        m_spinPosy->setValue(m_coordinates->posy());
        m_checkPosy->setChecked(true);
    }
}

QString CoordinatesTypeForm::toString()
{
    return QString("Coordinates Type");
}

void CoordinatesTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_coordinates;
        m_coordinates = 0;
    }
    emit closed(m_op, QVarPtr<CoordinatesType>::asQVariant(m_coordinates));
}

void CoordinatesTypeForm::applyClicked()
{
    if (m_checkPosx->isChecked())
        m_coordinates->setPosx(m_spinPosx->value());
    if (m_checkPosy->isChecked())
        m_coordinates->setPosy(m_spinPosy->value());
    m_editFormatGroup->updateExistingFormatGroup(m_coordinates);
    emit closed(m_op, QVarPtr<CoordinatesType>::asQVariant(m_coordinates));
}

void CoordinatesTypeForm::posxChanged()
{
    m_checkPosx->setChecked(true);
}

void CoordinatesTypeForm::posyChanged()
{
    m_checkPosy->setChecked(true);
}
