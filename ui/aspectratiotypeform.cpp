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

#include "aspectratiotypeform.h"
#include "../model/formattype.h"
#include "qvarptr.h"
#include "formatgroupeditbox.h"
#include <QPushButton>
#include <QTextBrowser>
#include <QFormLayout>
#include <QString>
#include <QLineEdit>
#include <QComboBox>
#include <QEvent>

AspectRatioTypeForm::AspectRatioTypeForm(AspectRatioType *aspectRatio,
                                         QEbuMainWindow *mainWindow,
                                         QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (aspectRatio) ? Edit : Add;
    if (!aspectRatio)
        m_aspectRatio = new AspectRatioType;
    else
        m_aspectRatio = aspectRatio;

    QVBoxLayout *vl = new QVBoxLayout;
    {
        m_editFormatGroup = new FormatGroupEditBox(aspectRatio);
        vl->addWidget(m_editFormatGroup);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_textNote = new QTextEdit;
        fl->addRow(tr("Note"), m_textNote);
        vl->addLayout(fl);
    }
    this->setLayout(vl);

    // Event Filter
    m_textDocumentation->setText(tr("The value of the ratio of the width by the height of the video expressed in the format defined by the formatGroup attributes"));
    m_textNote->installEventFilter(this);
    m_editFormatGroup->editFormatDefinition()->installEventFilter(this);
    m_editFormatGroup->editFormatLabel()->installEventFilter(this);
    m_editFormatGroup->editFormatLink()->installEventFilter(this);

    // Set text fields...
    m_textNote->setText(m_aspectRatio->note());
}

void AspectRatioTypeForm::addLinksMap(QMap<QString, QString> *values) {
    m_editFormatGroup->addLinksMap(values); //Autocompletion values
}

QString AspectRatioTypeForm::toString()
{
    return QString(tr("Aspect Ratio"));
}

void AspectRatioTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_aspectRatio;
        m_aspectRatio = 0;
    }
    emit closed(m_op, QVarPtr<AspectRatioType>::asQVariant(m_aspectRatio));
}

void AspectRatioTypeForm::applyClicked()
{
    m_aspectRatio->setNote(m_textNote->toPlainText());
    m_editFormatGroup->updateExistingFormatGroup(m_aspectRatio);
    emit closed(m_op, QVarPtr<AspectRatioType>::asQVariant(m_aspectRatio));
}

bool AspectRatioTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_textNote)
            m_textDocumentation->setText(tr("A note to add contextual additional information."));
        else if (obj == (QObject*) m_editFormatGroup->editFormatDefinition())
            m_textDocumentation->setText(tr("Free text for an optional definition.\nExample: 'the so-called “widescreen” picture format'"));
        else if (obj == (QObject*) m_editFormatGroup->editFormatLink())
            m_textDocumentation->setHtml(tr("Link to a classification scheme.<br/>Reference data: ebu_VisualAspectRatioCS<br/>Example:<a href=\"http://www.ebu.ch/metadata/cs/ebu_VisualAspectRatioCS.xml#3\">http://www.ebu.ch/metadata/cs/ebu_VisualAspectRatioCS.xml#3</a>"));
        else if (obj == (QObject*) m_editFormatGroup->editFormatLabel())
            m_textDocumentation->setText(tr("Free text\nExample: 16:9."));
    }
    return QObject::eventFilter(obj, event);
}
