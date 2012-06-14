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

#include "uint16form.h"
#include "../model/technicalattributes.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include "model/qebulimits.h"
#include <QSpinBox>
#include <QCheckBox>
#include <QLayout>
#include "qextendedspinbox.h"
#include <QEvent>
#include <QComboBox>
#include <QTextBrowser>

Uint16Form::Uint16Form(UInt16 *uint16,
                       QEbuMainWindow *mainWindow,
                       QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (uint16) ? Edit : Add;
    if(!uint16)
        m_uint16 = new UInt16();
    else
        m_uint16 = uint16;

    QVBoxLayout *vl = new QVBoxLayout;
    {
        QGridLayout *gl = new QGridLayout;
        m_spinValue = new QUnsignedSpinBox;
        m_spinValue->setRange(qEbuLimits::getMinUInt16(), qEbuLimits::getMaxUInt16());
        m_checkValue = new QCheckBox(tr("Value"));
        QObject::connect(m_spinValue, SIGNAL(valueChanged()),
                         this, SLOT(valueChanged()));
        gl->addWidget(m_checkValue, 0, 0);
        gl->addWidget(m_spinValue, 0, 1);
        vl->addLayout(gl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(uint16);
        vl->addWidget(m_editTypeGroup);
    }
    this->setLayout(vl);

    // Event Filter
    m_textDocumentation->setText(tr("Allows users / implementers to define their own technical parameters using the type attribute of their need."));
    m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
    m_editTypeGroup->editTypeLabel()->installEventFilter(this);
    m_editTypeGroup->editTypeLink()->installEventFilter(this);
    m_spinValue->installEventFilter(this);

    if (m_uint16->value()) {
        m_spinValue->setValue(*(m_uint16->value()));
        m_checkValue->setChecked(true);
    }
}

QString Uint16Form::toString()
{
    return QString(tr("Unsigned Short"));
}

void Uint16Form::cancelClicked()
{
    if (m_op == Add) {
        delete m_uint16;
        m_uint16 = 0;
    }
    emit closed(m_op, QVarPtr<UInt16>::asQVariant(m_uint16));
}

void Uint16Form::applyClicked()
{
    if (m_checkValue->isChecked())
        m_uint16->setValue(m_spinValue->value());
    else
        m_uint16->clearValue();
    m_editTypeGroup->updateExistingTypeGroup(m_uint16);
    emit closed(m_op, QVarPtr<UInt16>::asQVariant(m_uint16));
}

void Uint16Form::valueChanged()
{
    m_checkValue->setChecked(true);
}

bool Uint16Form::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("Free text.\nExample: 'a flag indicating that the video bitrate corresponds to an average bitrate'."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setText(tr("Link to a classification scheme."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("Free text.\nExample: averageBitrateFlag, bitrate."));
        else if (obj == (QObject*) m_spinValue)
            m_textDocumentation->setText(tr("The value of the technical attribute."));
    }
    return QObject::eventFilter(obj, event);
}
