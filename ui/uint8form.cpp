/****************************************************************************
** Copyright (C) 2012 by
**  Mauro Levra  (nazardo)     mauro@nazardo.it
**  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it
**  Denis Patti  (dextp3)      denis.patti@studenti.polito.it
**  Giovanni Pessiva           giovanni.pessiva@gmail.com
**  Stefano Ricossa            stefano.ricossa@studenti.polito.it
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

#include "uint8form.h"
#include "../model/technicalattributes.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include "model/qebulimits.h"
#include <QSpinBox>
#include <QCheckBox>
#include <QLayout>
#include <QEvent>
#include <QTextBrowser>
#include <QComboBox>
#include "qextendedspinbox.h"

Uint8Form::Uint8Form(UInt8 *uint8,
                     QEbuMainWindow *mainWindow,
                     QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (uint8) ? Edit : Add;
    if(!uint8)
        m_uint8 = new UInt8();
    else
        m_uint8 = uint8;

    QVBoxLayout *vl = new QVBoxLayout;
    {
        QGridLayout *gl = new QGridLayout;
        m_spinValue = new QUnsignedSpinBox;
        m_spinValue->setRange(qEbuLimits::getMinUInt8(), qEbuLimits::getMaxUInt8());
        m_checkValue = new QCheckBox(tr("Value"));
        QObject::connect(m_spinValue, SIGNAL(valueChanged()),
                         this, SLOT(valueChanged()));
        gl->addWidget(m_checkValue, 0, 0);
        gl->addWidget(m_spinValue, 0, 1);
        vl->addLayout(gl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(uint8);
        vl->addWidget(m_editTypeGroup);
    }
    this->setLayout(vl);

    // Event Filter
    m_textDocumentation->setText(tr("Allows users / implementers to define their own technical parameters using the type attribute of their need."));
    m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
    m_editTypeGroup->editTypeLabel()->installEventFilter(this);
    m_editTypeGroup->editTypeLink()->installEventFilter(this);
    m_spinValue->installEventFilter(this);

    if (m_uint8->value()) {
        m_spinValue->setValue(*(m_uint8->value()));
        m_checkValue->setChecked(true);
    }
}

QString Uint8Form::toString()
{
    return QString(tr("Unsigned Byte"));
}

void Uint8Form::cancelClicked()
{
    if (m_op == Add) {
        delete m_uint8;
        m_uint8 = 0;
    }
    emit closed(m_op, QVarPtr<UInt8>::asQVariant(m_uint8));
}

void Uint8Form::applyClicked()
{
    if (m_checkValue->isChecked())
        m_uint8->setValue(m_spinValue->value());
    else
        m_uint8->clearValue();
    m_editTypeGroup->updateExistingTypeGroup(m_uint8);
    emit closed(m_op, QVarPtr<UInt8>::asQVariant(m_uint8));
}

void Uint8Form::valueChanged()
{
    m_checkValue->setChecked(true);
}

bool Uint8Form::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("Free text.\nExample: �a flag indicating that the video bitrate corresponds to an average bitrate�."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setText(tr("Link to a classification scheme."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("Free text.\nExample: averageBitrateFlag, bitrate."));
        else if (obj == (QObject*) m_spinValue)
            m_textDocumentation->setText(tr("The value of the technical attribute."));
    }
    return QObject::eventFilter(obj, event);
}
