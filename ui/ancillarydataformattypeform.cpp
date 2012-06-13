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

#include "ancillarydataformattypeform.h"
#include "../model/ebucoremaintype.h"
#include "../model/typeconverter.h"
#include "../model/qebulimits.h"
#include "listview.h"
#include "qvarptr.h"
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QInputDialog>
#include <QTextBrowser>
#include <QEvent>

AncillaryDataFormatTypeForm::AncillaryDataFormatTypeForm(
        AncillaryDataFormatType *ancillaryDataFormat,
        QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (ancillaryDataFormat) ? Edit : Add;
    if(!ancillaryDataFormat)
        m_ancillaryDataFormat = new AncillaryDataFormatType();
    else
        m_ancillaryDataFormat = ancillaryDataFormat;
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *vl = new QVBoxLayout;
    {
        QFormLayout *fl = new QFormLayout;

        m_editAncillaryDataFormatId = new QLineEdit;
        m_editAncillaryDataFormatId->setValidator(TypeConverter::getUriValidator());
        fl->addRow(tr("Ancillary data format id"), m_editAncillaryDataFormatId);

        m_editAncillaryDataFormatName = new QLineEdit;
        fl->addRow(tr("Ancillary data format name"), m_editAncillaryDataFormatName);
        m_buttonLineNumber = new QPushButton(">>");
        m_buttonLineNumber->setCheckable(true);
        fl->addRow(tr("Line number"), m_buttonLineNumber);
        QObject::connect(m_buttonLineNumber, SIGNAL(toggled(bool)),
                         this, SLOT(numberLineChecked(bool)));
        vl->addLayout(fl);
    }
    {
        QGridLayout *gl = new QGridLayout;

        m_spinDID = new QSpinBox;
        m_spinDID->setRange(qEbuLimits::getMinInt(), qEbuLimits::getMaxInt());
        m_checkDID = new QCheckBox(tr("DID"));
        QObject::connect(m_spinDID, SIGNAL(valueChanged(int)),
                         this, SLOT(DIDChanged()));
        gl->addWidget(m_checkDID, 0, 0);
        gl->addWidget(m_spinDID, 0, 1);

        m_spinSDID = new QSpinBox;
        m_spinSDID->setRange(qEbuLimits::getMinInt(), qEbuLimits::getMaxInt());
        m_checkSDID = new QCheckBox(tr("SDID"));
        QObject::connect(m_spinSDID, SIGNAL(valueChanged(int)),
                         this, SLOT(SDIDChanged()));
        gl->addWidget(m_checkSDID, 1, 0);
        gl->addWidget(m_spinSDID, 1, 1);

        m_spinWrappingType = new QSpinBox;
        m_spinWrappingType->setRange(qEbuLimits::getMinInt(), qEbuLimits::getMaxInt());
        m_checkWrappingType = new QCheckBox(tr("Wrapping type"));
        QObject::connect(m_spinWrappingType, SIGNAL(valueChanged(int)),
                         this, SLOT(wrappingTypeChanged()));
        gl->addWidget(m_checkWrappingType, 2, 0);
        gl->addWidget(m_spinWrappingType, 2, 1);

        vl->addLayout(gl);
    }
    mainHLayout->addLayout(vl);

    // Add list view on the right
    m_listView = new ListView();
    QObject::connect(m_listView->buttonAdd(), SIGNAL(clicked()),
                     this, SLOT(addClicked()));
    QObject::connect(m_listView->buttonEdit(), SIGNAL(clicked()),
                     this, SLOT(editClicked()));
    QObject::connect(m_listView->buttonRemove(), SIGNAL(clicked()),
                     this, SLOT(removeClicked()));
    mainHLayout->addWidget(m_listView);

    this->setLayout(mainHLayout);

    // Event filter
    m_textDocumentation->setText(tr("Used to provide information on ancillary data format and purpose. This type provides inforamtion on the Ancillary Data packet type. See SMPTE 291M, SMPTE 436M."));
    m_buttonLineNumber->installEventFilter(this);
    m_editAncillaryDataFormatId->installEventFilter(this);
    m_editAncillaryDataFormatName->installEventFilter(this);
    m_spinDID->installEventFilter(this);
    m_spinSDID->installEventFilter(this);
    m_spinWrappingType->installEventFilter(this);

    //Set Data fields
    m_editAncillaryDataFormatId->setText(m_ancillaryDataFormat->ancillaryDataFormatId());
    m_editAncillaryDataFormatName->setText(m_ancillaryDataFormat->ancillaryDataFormatName());
    if (m_ancillaryDataFormat->DID()) {
        m_spinDID->setValue(*(m_ancillaryDataFormat->DID()));
        m_checkDID->setChecked(true);
    }
    if (m_ancillaryDataFormat->SDID()) {
        m_spinSDID->setValue(*(m_ancillaryDataFormat->SDID()));
        m_checkSDID->setChecked(true);
    }
    if (m_ancillaryDataFormat->wrappingType()) {
        m_spinWrappingType->setValue(*(m_ancillaryDataFormat->wrappingType()));
        m_checkWrappingType->setChecked(true);
    }


    m_buttonLineNumber->setChecked(true);
}

QString AncillaryDataFormatTypeForm::toString()
{
    return QString(tr("Ancillary Data Format"));
}

void AncillaryDataFormatTypeForm::addClicked()
{
    bool ok;
    int input = QInputDialog::getInt(this, tr("Ancillary Data Format Type > Line Number"),
                                     tr("Line Number"), 0, 0, qEbuLimits::getMaxInt(), 1, &ok);
    if (ok) {
        m_listView->addItem(QString::number(input));
        m_ancillaryDataFormat->lineNumber().append(input);
    }
}

void AncillaryDataFormatTypeForm::editClicked()
{
    int index = m_listView->selected();
    if (index < 0)
        return;

    bool ok;

    int input = QInputDialog::getInt(this, tr("Ancillary Data Format Type > Line Number"),
                                     tr("Line Number"),
                                     m_ancillaryDataFormat->lineNumber().at(index),
                                     0, qEbuLimits::getMaxInt(), 1, &ok);
    if (ok) {
        m_listView->setItem(index, QString::number(input));
        m_ancillaryDataFormat->lineNumber().removeAt(index);
        m_ancillaryDataFormat->lineNumber().insert(index, input);
    }
}

void AncillaryDataFormatTypeForm::removeClicked()
{
    int row = m_listView->selected();
    if (row < 0)
        return;
    m_listView->removeAt(row);
    m_ancillaryDataFormat->lineNumber().takeAt(row);
}

void AncillaryDataFormatTypeForm::numberLineChecked(bool checked)
{
    if (!checked)
        return;
    updateListAndButtons();
    for (int i = 0; i < m_ancillaryDataFormat->lineNumber().size(); ++i) {
        m_listView->addItem(QString::number(m_ancillaryDataFormat->lineNumber().at(i)));
    }
}

void AncillaryDataFormatTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_ancillaryDataFormat;
        m_ancillaryDataFormat = 0;
    }
    emit closed(m_op, QVarPtr<AncillaryDataFormatType>::asQVariant(m_ancillaryDataFormat));
}

void AncillaryDataFormatTypeForm::applyClicked()
{
    m_ancillaryDataFormat->setAncillaryDataFormatId(m_editAncillaryDataFormatId->text());
    m_ancillaryDataFormat->setAncillaryDataFormatName(m_editAncillaryDataFormatName->text());
    if (m_checkDID->isChecked())
        m_ancillaryDataFormat->setDID(m_spinDID->value());
    else
        m_ancillaryDataFormat->clearDID();
    if (m_checkSDID->isChecked())
        m_ancillaryDataFormat->setSDID(m_spinSDID->value());
    else
        m_ancillaryDataFormat->clearSDID();
    if (m_checkWrappingType->isChecked())
        m_ancillaryDataFormat->setWrappingType(m_spinWrappingType->value());
    else
        m_ancillaryDataFormat->clearWrappingType();
    emit closed(m_op, QVarPtr<AncillaryDataFormatType>::asQVariant(m_ancillaryDataFormat));
}

void AncillaryDataFormatTypeForm::DIDChanged()
{
    m_checkDID->setChecked(true);
}

void AncillaryDataFormatTypeForm::SDIDChanged()
{
    m_checkSDID->setChecked(true);
}

void AncillaryDataFormatTypeForm::wrappingTypeChanged()
{
    m_checkWrappingType->setChecked(true);
}

void AncillaryDataFormatTypeForm::updateListAndButtons()
{
    QString title;
    title = tr("Line number");
    m_listView->setTitle(title);
    m_listView->clear();
}

bool AncillaryDataFormatTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editAncillaryDataFormatId)
            m_textDocumentation->setText(tr("An identifier associated to the ancillary data format."));
        else if (obj == (QObject*) m_editAncillaryDataFormatName)
            m_textDocumentation->setText(tr("An name associated to the ancillary data format."));
        else if (obj == (QObject*) m_spinDID)
            m_textDocumentation->setText(tr("ANC DID value."));
        else if ( obj == (QObject*) m_spinSDID)
            m_textDocumentation->setText(tr("ANC SDID value."));
        else if ( obj ==(QObject*) m_spinWrappingType)
            m_textDocumentation->setText(tr("Indicates HANC or VANC, and what field in which packets should be stored. See SMPTE 436M for legal values."));
        else if ( obj == (QObject*) m_buttonLineNumber)
            m_textDocumentation->setText(tr("Video line number containing the ANC packets of this type."));
    }
    return QObject::eventFilter(obj, event);
}
