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
    QFormLayout *fl = new QFormLayout;
    m_spinPosx = new QDoubleSpinBox;
    fl->addRow(tr("Posx"), m_spinPosx);
    m_spinPosy = new QDoubleSpinBox;
    fl->addRow(tr("Posy"), m_spinPosy);
    m_mainVLayout->addLayout(fl);
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
    m_spinPosx->setValue(m_coordinates->posx());
    m_spinPosy->setValue(m_coordinates->posy());
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
    m_coordinates->setPosx(m_spinPosx->value());
    m_coordinates->setPosy(m_spinPosy->value());
    m_editFormatGroup->updateExistingFormatGroup(m_coordinates);
    emit closed(m_op, QVarPtr<CoordinatesType>::asQVariant(m_coordinates));
}
