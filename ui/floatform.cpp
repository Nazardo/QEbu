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

#include "floatform.h"
#include "../model/technicalattributes.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QEvent>
#include <QTextBrowser>
#include <QLineEdit>
#include <QComboBox>


FloatForm::FloatForm(Float *p_float,
                     QEbuMainWindow *mainWindow,
                     QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    // In this case only, the variable passed to the constructor is called p_varName, because
    // either float and Float are reserved names.

    m_op = (p_float) ? Edit : Add;
    if (!p_float)
        m_float = new Float;
    else
        m_float = p_float;

    // Layout
    QVBoxLayout *l = new QVBoxLayout;
    {
        QGridLayout *gl = new QGridLayout;
        m_spinValue = new QDoubleSpinBox;
        m_checkValue = new QCheckBox(tr("Value"));
        QObject::connect(m_spinValue, SIGNAL(valueChanged(double)),
                         this, SLOT(valueChanged()));
        gl->addWidget(m_checkValue, 0, 0);
        gl->addWidget(m_spinValue, 0, 1);
        l->addLayout(gl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(p_float);
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
    if (m_float->value()) {
        m_spinValue->setValue(*(m_float->value()));
        m_checkValue->setChecked(true);
    }
}

QString FloatForm::toString()
{
    return QString(tr("Float"));
}

void FloatForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_float;
        m_float = 0;
    }
    emit closed(m_op, QVarPtr<Float>::asQVariant(m_float));
}

void FloatForm::applyClicked()
{
    if (m_checkValue->isChecked())
        m_float->setValue(m_spinValue->value());
    else
        m_float->clearValue();
    m_editTypeGroup->updateExistingTypeGroup(m_float);

    emit closed(m_op, QVarPtr<Float>::asQVariant(m_float));
}

void FloatForm::valueChanged()
{
    m_checkValue->setChecked(true);
}

bool FloatForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("Free text.\nExample: ‘a flag indicating that the video bitrate corresponds to an average bitrate’."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setText(tr("Link to a classification scheme."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("Free text.\nExample: averageBitrateFlag, bitrate."));
        else if (obj == (QObject*) m_spinValue)
            m_textDocumentation->setText(tr("The value of the technical attribute."));
    }
    return QObject::eventFilter(obj, event);
}
