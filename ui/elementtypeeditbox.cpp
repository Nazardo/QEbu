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

#include "elementtypeeditbox.h"
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>

ElementTypeEditBox::ElementTypeEditBox(QWidget *parent) :
    QWidget(parent)
{
    m_editValue = new QLineEdit;
    m_editLang = new QLineEdit;
    /** @todo Set size for lang */
    QGridLayout *l = new QGridLayout;
    m_label = new QLabel("call setLabel()");
    l->addWidget(m_label, 0, 0);
    l->addWidget(m_editValue, 0, 1);
    m_labelLang = new QLabel(tr("%1 Lang").arg(m_label->text()));
    l->addWidget(m_labelLang, 1, 0);
    l->addWidget(m_editLang, 1, 1);
    this->setLayout(l);
    m_editLang->setText("en");
}

QLineEdit *ElementTypeEditBox::editValue()
{
    return m_editValue;
}

QLineEdit *ElementTypeEditBox::editLang()
{
    return m_editLang;
}

void ElementTypeEditBox::setLabel(const QString &label)
{
    m_label->setText(label);
    m_labelLang->setText(tr("%1 Lang").arg(label));
}
