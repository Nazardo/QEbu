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

#include "signingformattypeform.h"
#include "../model/ebucoremaintype.h"
#include "../model/typeconverter.h"
#include "typegroupeditbox.h"
#include "formatgroupeditbox.h"
#include "qvarptr.h"
#include <QLineEdit>
#include <QComboBox>
#include <QEvent>
#include <QTextBrowser>
#include <QFormLayout>

SigningFormatTypeForm::SigningFormatTypeForm(SigningFormatType *signingFormat, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (signingFormat) ? Edit : Add;
    if(!signingFormat)
        m_signingFormat = new SigningFormatType;
    else
        m_signingFormat = signingFormat;
    QVBoxLayout *vl = new QVBoxLayout;
    {
        QFormLayout *fl = new QFormLayout;

        m_editTrackId = new QLineEdit;
        m_editTrackId->installEventFilter(this);
        fl->addRow(tr("Track id"),m_editTrackId);

        m_editTrackName = new QLineEdit;
        m_editTrackName->installEventFilter(this);
        fl->addRow(tr("Track name"),m_editTrackName);

        m_editLanguage = new QLineEdit;
        m_editLanguage->installEventFilter(this);
        fl->addRow(tr("Language"),m_editLanguage);
        vl->addLayout(fl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(m_signingFormat);
        m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
        m_editTypeGroup->editTypeLabel()->installEventFilter(this);
        m_editTypeGroup->editTypeLink()->installEventFilter(this);
        vl->addWidget(m_editTypeGroup);
    }
    {
        m_editFormatGroup = new FormatGroupEditBox(m_signingFormat);
        m_editFormatGroup->editFormatDefinition()->installEventFilter(this);
        m_editFormatGroup->editFormatLabel()->installEventFilter(this);
        m_editFormatGroup->editFormatLink()->installEventFilter(this);
        m_editFormatGroup->addLinksMap(mainWindow->getMap("ebu_SignLanguageCodeCS"));
        vl->addWidget(m_editFormatGroup);
    }
    {
        QFormLayout *fl = new QFormLayout;

        m_editSigningSourceUri = new QLineEdit;
        m_editSigningSourceUri->installEventFilter(this);
        m_editSigningSourceUri->setValidator(TypeConverter::getUriValidator());
        fl->addRow(tr("Source uri"),m_editSigningSourceUri);

        m_editSigningFormatId = new QLineEdit;
        m_editSigningFormatId->installEventFilter(this);
        fl->addRow(tr("Format id"),m_editSigningFormatId);

        m_editSigningFormatName = new QLineEdit;
        m_editSigningFormatName->installEventFilter(this);
        fl->addRow(tr("Format name"),m_editSigningFormatName);

        m_editSigningFormatDefinition = new QLineEdit;
        m_editSigningFormatDefinition->installEventFilter(this);
        fl->addRow(tr("Format definition"),m_editSigningFormatDefinition);
        vl->addLayout(fl);
    }
    this->setLayout(vl);
    // Set text fields...
    m_textDocumentation->setText(tr("To provide information on the language, purpose and format of signing if used in the resource."));
    m_editTrackId->setText(m_signingFormat->trackId());
    m_editTrackName->setText(m_signingFormat->trackName());
    m_editLanguage->setText(m_signingFormat->language());
    m_editSigningSourceUri->setText(m_signingFormat->signingSourceUri());
    m_editSigningFormatId->setText(m_signingFormat->signingFormatId());
    m_editSigningFormatName->setText(m_signingFormat->signingFormatName());
    m_editSigningFormatDefinition->setText(m_signingFormat->signingFormatDefinition());
}

QString SigningFormatTypeForm::toString()
{
    return QString(tr("Signing Format"));
}

void SigningFormatTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_signingFormat;
        m_signingFormat = 0;
    }
    emit closed(m_op, QVarPtr<SigningFormatType>::asQVariant(m_signingFormat));
}

void SigningFormatTypeForm::applyClicked()
{
    m_signingFormat->setTrackId(m_editTrackId->text());
    m_signingFormat->setTrackName(m_editTrackName->text());
    m_signingFormat->setLanguage(m_editLanguage->text());

    m_editFormatGroup->updateExistingFormatGroup(m_signingFormat);
    m_editTypeGroup->updateExistingTypeGroup(m_signingFormat);

    m_signingFormat->setSigningSourceUri(m_editSigningSourceUri->text());
    m_signingFormat->setSigningFormatId(m_editSigningFormatId->text());
    m_signingFormat->setSigningFormatName(m_editSigningFormatName->text());
    m_signingFormat->setSigningFormatDefinition(m_editSigningFormatDefinition->text());

    emit closed(m_op, QVarPtr<SigningFormatType>::asQVariant(m_signingFormat));
}

bool SigningFormatTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if ( obj == (QObject*) m_editTrackId)
            m_textDocumentation->setText(tr("An identifier associated to the signing track."));
        if ( obj == (QObject*) m_editTrackName)
            m_textDocumentation->setText(tr("An name associated to the signing track."));
        if ( obj == (QObject*) m_editLanguage)
            m_textDocumentation->setText(tr("The language in which the signing is delivered."));
        if ( obj == (QObject*) m_editFormatGroup->editFormatDefinition())
            m_textDocumentation->setText(tr("Free text for an optional definition."));
        if ( obj == (QObject*) m_editFormatGroup->editFormatLabel())
            m_textDocumentation->setText(tr("Free text"));
        if ( obj == (QObject*) m_editFormatGroup->editFormatLink())
            m_textDocumentation->setHtml(tr("Link to a classification scheme.<br/>Reference data:<br/><a href=\"http://www.ebu.ch/metadata/cs/web/ebu_SignLanguageCodeCS_p.xml.htm\">ebu_SignLanguageCodeCS</a>"));
        if ( obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("Free text for an optional definition."));
        if ( obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("Free text"));
        if ( obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setHtml(tr("Link to a classification scheme."));
        if ( obj == (QObject*) m_editSigningSourceUri)
            m_textDocumentation->setText(tr("The address at which a signing resource can be found or accessed from"));
        if ( obj == (QObject*) m_editSigningFormatId)
            m_textDocumentation->setText(tr("An identifier associated to the signing format"));
        if ( obj == (QObject*) m_editSigningFormatName)
            m_textDocumentation->setHtml(tr("An name associated to the signing format"));
        if ( obj == (QObject*) m_editSigningFormatDefinition)
            m_textDocumentation->setHtml(tr("A definition associated to the signing format"));
    }
    return QObject::eventFilter(obj, event);
}
