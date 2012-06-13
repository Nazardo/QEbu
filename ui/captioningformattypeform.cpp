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

#include "captioningformattypeform.h"
#include "../model/formattype.h"
#include "../model/typegroup.h"
#include "../model/typeconverter.h"
#include "typegroupeditbox.h"
#include "formatgroupeditbox.h"
#include "qvarptr.h"
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QTextBrowser>
#include <QEvent>
#include <QVBoxLayout>
#include <QFormLayout>

CaptioningFormatTypeForm::CaptioningFormatTypeForm(
        CaptioningFormatType *captioningFormat,
        QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (captioningFormat) ? Edit : Add;
    if (!captioningFormat)
        m_captioningFormat = new CaptioningFormatType;
    else
        m_captioningFormat = captioningFormat;

    QVBoxLayout *mainVLayout = new QVBoxLayout;
    {
        QFormLayout *fl = new QFormLayout;
        m_editTrackId = new QLineEdit;
        m_editTrackId->setValidator(TypeConverter::getUriValidator());
        fl->addRow(tr("Track ID"), m_editTrackId);
        m_editTrackName = new QLineEdit;
        fl->addRow(tr("Track name"), m_editTrackName);
        m_editLanguage = new QLineEdit;
        fl->addRow(tr("Language"), m_editLanguage);
        mainVLayout->addLayout(fl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(captioningFormat);
        mainVLayout->addWidget(m_editTypeGroup);
        m_editFormatGroup = new FormatGroupEditBox(captioningFormat);
        mainVLayout->addWidget(m_editFormatGroup);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_editCaptioningSourceUri = new QLineEdit;
        fl->addRow(tr("Captioning Source URI"), m_editCaptioningSourceUri);
        m_editCaptioningFormatId = new QLineEdit;
        fl->addRow(tr("Captioning Format ID"), m_editCaptioningFormatId);
        m_editCaptioningFormatName = new QLineEdit;
        fl->addRow(tr("Captioning Format Name"), m_editCaptioningFormatName);
        mainVLayout->addLayout(fl);
    }    
    this->setLayout(mainVLayout);

    // Event Filter
    m_textDocumentation->setText(tr("To provide information on the language, purpose and format of captoning if used in the resource."));
    m_editTrackId->installEventFilter(this);
    m_editTrackName->installEventFilter(this);
    m_editLanguage->installEventFilter(this);
    m_editCaptioningSourceUri->installEventFilter(this);
    m_editCaptioningFormatId->installEventFilter(this);
    m_editCaptioningFormatName->installEventFilter(this);
    m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
    m_editTypeGroup->editTypeLabel()->installEventFilter(this);
    m_editTypeGroup->editTypeLink()->installEventFilter(this);
    m_editFormatGroup->editFormatDefinition()->installEventFilter(this);
    m_editFormatGroup->editFormatLabel()->installEventFilter(this);
    m_editFormatGroup->editFormatLink()->installEventFilter(this);

    // Set text fields...
    m_editTrackId->setText(m_captioningFormat->trackId());
    m_editTrackName->setText(m_captioningFormat->trackName());
    m_editLanguage->setText(m_captioningFormat->trackLanguage());
    m_editCaptioningSourceUri->setText(m_captioningFormat->captioningSourceUri());
    m_editCaptioningFormatId->setText(m_captioningFormat->captioningFormatId());
    m_editCaptioningFormatName->setText(m_captioningFormat->captioningFormatName());
}

QString CaptioningFormatTypeForm::toString()
{
    return QString(tr("Captioning Format"));
}

void CaptioningFormatTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_captioningFormat;
        m_captioningFormat = 0;
    }
    emit closed(m_op, QVarPtr<CaptioningFormatType>::asQVariant(m_captioningFormat));
}

void CaptioningFormatTypeForm::applyClicked()
{
    m_captioningFormat->setTrackId(m_editTrackId->text());
    m_captioningFormat->setTrackName(m_editTrackName->text());
    m_captioningFormat->setTrackLanguage(m_editLanguage->text());
    m_captioningFormat->setCaptioningSourceUri(m_editCaptioningSourceUri->text());
    m_captioningFormat->setCaptioningFormatId(m_editCaptioningFormatId->text());
    m_captioningFormat->setCaptioningFormatName(m_editCaptioningFormatName->text());
    m_editTypeGroup->updateExistingTypeGroup(m_captioningFormat);
    m_editFormatGroup->updateExistingFormatGroup(m_captioningFormat);
    emit closed(m_op, QVarPtr<CaptioningFormatType>::asQVariant(m_captioningFormat));
}

bool CaptioningFormatTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editTrackId )
            m_textDocumentation->setText(tr("An identifier associated to the captioning track."));
        else if (obj == (QObject*) m_editTrackName )
            m_textDocumentation->setText(tr("An name associated to the captioning track."));
        else if  (obj == (QObject*) m_editLanguage)
            m_textDocumentation->setText(tr("The language in which the caption is delivered.\nExample: en-UK."));
        else if (obj == (QObject*) m_editCaptioningSourceUri)
            m_textDocumentation->setText(tr("An optional URI from which the captioning material can be accessed."));
        else if (obj == (QObject*) m_editCaptioningFormatId)
            m_textDocumentation->setText(tr("An identifier associated to the captioning format."));
        else if (obj == (QObject*) m_editCaptioningFormatName)
            m_textDocumentation->setText(tr("An name associated to the captioning format."));
        else if (obj == (QObject*) m_editFormatGroup->editFormatDefinition())
            m_textDocumentation->setText(tr("Free text for an optional definition."));
        else if (obj == (QObject*) m_editFormatGroup->editFormatLink())
            m_textDocumentation->setText(tr("Link to a classification scheme."));
        else if (obj == (QObject*) m_editFormatGroup->editFormatLabel())
            m_textDocumentation->setText(tr("Free text.\nExample: close caption."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("Free text for an optional definition."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setText(tr("Link to a classification scheme."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("Free text.\nExample: dubbing."));
    }
    return QObject::eventFilter(obj, event);
}
