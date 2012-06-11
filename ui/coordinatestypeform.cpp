#include "coordinatestypeform.h"
#include "model/coremetadatatype.h"
#include "formatgroupeditbox.h"
#include "qvarptr.h"
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QEvent>
#include <QTextEdit>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QVBoxLayout>

CoordinatesTypeForm::CoordinatesTypeForm(CoordinatesType *coordinates, QEbuMainWindow *mainWindow, QWidget *parent)  :
    StackableWidget(mainWindow, parent)
{
    m_op = (coordinates) ? Edit : Add;
    if (!coordinates)
        m_coordinates = new CoordinatesType;
    else
        m_coordinates = coordinates;
    // Layout
    QVBoxLayout *mainVLayout = new QVBoxLayout;
    m_editFormatGroup = new FormatGroupEditBox(coordinates);
    mainVLayout->addWidget(m_editFormatGroup);
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

        mainVLayout->addLayout(gl);
    }
    this->setLayout(mainVLayout);

    // Event Filter
    m_textDocumentation->setText(tr("The spatial coordinates."));
    m_editFormatGroup->editFormatDefinition()->installEventFilter(this);
    m_editFormatGroup->editFormatLabel()->installEventFilter(this);
    m_editFormatGroup->editFormatLink()->installEventFilter(this);
    m_spinPosx->installEventFilter(this);
    m_spinPosy->installEventFilter(this);

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
    return QString(tr("Coordinates"));
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
    else
        m_coordinates->clearPosx();
    if (m_checkPosy->isChecked())
        m_coordinates->setPosy(m_spinPosy->value());
    else
        m_coordinates->clearPosy();
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

bool CoordinatesTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editFormatGroup->editFormatDefinition())
            m_textDocumentation->setText(tr("Free text for an optional definition."));
        else if (obj == (QObject*) m_editFormatGroup->editFormatLink())
            m_textDocumentation->setText(tr("Link to a classification scheme."));
        else if (obj == (QObject*) m_editFormatGroup->editFormatLabel())
            m_textDocumentation->setText(tr("Free text."));
        else if (obj == (QObject*) m_spinPosx)
            m_textDocumentation->setText(tr("The longitude of the place or location.\nExample:-015."));
        else if (obj == (QObject*) m_spinPosy)
            m_textDocumentation->setText(tr("The latitude of the place or location.\nExample: 51.49."));
    }
    return QObject::eventFilter(obj, event);
}
