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

#include "formatgroupform.h"
#include "../model/formatgroup.h"
#include "formatgroupeditbox.h"
#include "qvarptr.h"
#include <QTextBrowser>
#include <QLayout>
#include <QString>

FormatGroupForm::FormatGroupForm(FormatGroup *formatGroup,
                                 QEbuMainWindow *mainWindow,
                                 QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (formatGroup) ? Edit : Add;
    if (!formatGroup)
        m_formatGroup = new FormatGroup;
    else
        m_formatGroup = formatGroup;
    QVBoxLayout *vl = new QVBoxLayout;
    m_title = QString(tr("Format Group"));
    m_editFormatGroup = new FormatGroupEditBox(m_formatGroup);
    m_editFormatGroup->setLabel(m_title);
    vl->addWidget(m_editFormatGroup);
    this->setLayout(vl);  
}

void FormatGroupForm::addLinksMap(QMap<QString, QString> *values) {
    m_editFormatGroup->addLinksMap(values); //Autocompletion values
}

QString FormatGroupForm::toString()
{
    return m_title;
}

void FormatGroupForm::setTitle(const QString &title)
{
    m_title = title;
}

void FormatGroupForm::applyClicked()
{
    m_editFormatGroup->updateExistingFormatGroup(m_formatGroup);
    emit closed(m_op, QVarPtr<FormatGroup>::asQVariant(m_formatGroup));
}

void FormatGroupForm::cancelClicked()
{
    emit closed(m_op, QVarPtr<FormatGroup>::asQVariant(0));
}

void FormatGroupForm::setLabelDoc(const QString &doc)
{
    m_labelDoc = doc;
}

void FormatGroupForm::setLinkDoc(const QString &doc)
{
    m_linkDoc = doc;
}

void FormatGroupForm::setGeneralDoc(const QString &doc)
{
    m_generalDoc = doc;
    m_textDocumentation->setText(doc);
}

void FormatGroupForm::setDefinitionDoc(const QString &doc)
{
    m_definitionDoc = doc;
}
