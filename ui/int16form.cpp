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

#include "int16form.h"
#include "../model/technicalattributes.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include "model/qebulimits.h"
#include <QSpinBox>
#include <QCheckBox>
#include <QTextBrowser>
#include <QEvent>
#include <QLayout>
#include <QComboBox>
#include <QLineEdit>

Int16Form::Int16Form(Int16 *int16,
                     QEbuMainWindow *mainWindow,
                     QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (int16) ? Edit : Add;
    if (!int16)
        m_int16 = new Int16;
    else
        m_int16 = int16;

    // Layout
    QVBoxLayout *l = new QVBoxLayout;

    {
        QGridLayout *gl = new QGridLayout;
        m_spinValue = new QSpinBox;
        m_spinValue->setRange(qEbuLimits::getMinInt16(), qEbuLimits::getMaxInt16());
        m_checkValue = new QCheckBox(tr("Value"));
        QObject::connect(m_spinValue, SIGNAL(valueChanged(int)),
                         this, SLOT(valueChanged()));
        gl->addWidget(m_checkValue, 0, 0);
        gl->addWidget(m_spinValue, 0, 1);
        l->addLayout(gl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(int16);
        l->addWidget(m_editTypeGroup);
    }
    this->setLayout(l);

    // Event Filter
    m_textDocumentation->setText(tr("Allows users / implementers to define their own technical parameters using the type attribute of their need."));
    m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
    m_editTypeGroup->editTypeLabel()->installEventFilter(this);
    m_editTypeGroup->editTypeLink()->installEventFilter(this);
    m_spinValue->installEventFilter(this);

    // Set data fields...
    if (m_int16->value()) {
        m_spinValue->setValue(*(m_int16->value()));
        m_checkValue->setChecked(true);
    }
}

QString Int16Form::toString()
{
    return QString(tr("Short"));
}

void Int16Form::cancelClicked()
{
    if (m_op == Add) {
        delete m_int16;
        m_int16 = 0;
    }
    emit closed(m_op, QVarPtr<Int16>::asQVariant(m_int16));
}

void Int16Form::applyClicked()
{
    if (m_checkValue->isChecked())
        m_int16->setValue(m_spinValue->value());
    else
        m_int16->clearValue();
    m_editTypeGroup->updateExistingTypeGroup(m_int16);

    emit closed(m_op, QVarPtr<Int16>::asQVariant(m_int16));
}

void Int16Form::valueChanged()
{
    m_checkValue->setChecked(true);
}

bool Int16Form::eventFilter(QObject *obj, QEvent *event)
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
