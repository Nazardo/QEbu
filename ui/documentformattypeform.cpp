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

#include "documentformattypeform.h"
#include "../model/formattype.h"
#include "typegroupeditbox.h"
#include "lengthtypeeditbox.h"
#include "formatgroupeditbox.h"
#include "technicalattributesform.h"
#include "qvarptr.h"
#include "../model/qebulimits.h"
#include "qextendedspinbox.h"
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QFormLayout>
#include <QTextBrowser>
#include <QEvent>
#include <QComboBox>

DocumentFormatTypeForm::DocumentFormatTypeForm(
        DocumentFormatType *documentFormat,
        QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (documentFormat) ? Edit : Add;
    if (!documentFormat)
        m_documentFormat = new DocumentFormatType;
    else
        m_documentFormat = documentFormat;
    // Layout
    QVBoxLayout *vl = new QVBoxLayout;
    {
        m_editTypeGroup = new TypeGroupEditBox(documentFormat);
        m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
        m_editTypeGroup->editTypeLabel()->installEventFilter(this);
        m_editTypeGroup->editTypeLink()->installEventFilter(this);
        vl->addWidget(m_editTypeGroup);
    }

    {
        m_formatTypeGroup = new FormatGroupEditBox(documentFormat);
        m_formatTypeGroup->editFormatDefinition()->installEventFilter(this);
        m_formatTypeGroup->editFormatLabel()->installEventFilter(this);
        m_formatTypeGroup->editFormatLink()->installEventFilter(this);
        vl->addWidget(m_formatTypeGroup);
    }
    {
        QFormLayout *fl = new QFormLayout;

        m_editDocumentFormatId = new QLineEdit;
        m_editDocumentFormatId->installEventFilter(this);
        fl->addRow(tr("Document Format Id:"),m_editDocumentFormatId);

        m_editDocumentFormatName = new QLineEdit;
        m_editDocumentFormatName->installEventFilter(this);
        fl->addRow(tr("Document Format Name:"),m_editDocumentFormatName);

        m_editDocumentFormatDefinition = new QLineEdit;
        m_editDocumentFormatDefinition->installEventFilter(this);
        fl->addRow(tr("Document Format Definition:"),m_editDocumentFormatDefinition);

        vl->addLayout(fl);
    }
    {
        QGridLayout *gl = new QGridLayout;

        m_spinWordCount = new QSpinBox;
        m_spinWordCount->installEventFilter(this);
        m_checkWordCount = new QCheckBox(tr("Word Count"));
        m_spinWordCount->setRange(0, qEbuLimits::getMaxInt());
        m_spinWordCount->installEventFilter(this);
        gl->addWidget(m_checkWordCount, 0, 0);
        gl->addWidget(m_spinWordCount, 0, 1);
        QObject::connect(m_spinWordCount, SIGNAL(valueChanged(int)),
                         this, SLOT(wordCountChanged()));

        m_spinRegionDelimX = new QUnsignedSpinBox;
        m_spinRegionDelimX->installEventFilter(this);
        m_checkRegionDelimX = new QCheckBox(tr("Region Delim X"));
        m_spinRegionDelimX->setRange(qEbuLimits::getMinUInt(), qEbuLimits::getMaxUInt());
        gl->addWidget(m_checkRegionDelimX, 1, 0);
        gl->addWidget(m_spinRegionDelimX, 1, 1);
        QObject::connect(m_spinRegionDelimX, SIGNAL(valueChanged()),
                         this, SLOT(regionDelimXChanged()));


        m_spinRegionDelimY = new QUnsignedSpinBox;
        m_spinRegionDelimY->installEventFilter(this);
        m_checkRegionDelimY = new QCheckBox(tr("Region Delim X"));
        m_spinRegionDelimY->setRange(qEbuLimits::getMinUInt(), qEbuLimits::getMaxUInt());
        gl->addWidget(m_checkRegionDelimY, 2, 0);
        gl->addWidget(m_spinRegionDelimY, 2, 1);
        QObject::connect(m_spinRegionDelimY, SIGNAL(valueChanged()),
                         this, SLOT(regionDelimYChanged()));

        m_editWidth = new LengthTypeEditBox(m_documentFormat->width());
        m_editWidth->editValue()->installEventFilter(this);
        m_editWidth->editUnit()->installEventFilter(this);
        m_editWidth->setLabel(tr("Width"));
        gl->addWidget(m_editWidth, 3, 0, 1, 2);

        m_editHeight = new LengthTypeEditBox(m_documentFormat->height());
        m_editHeight->editUnit()->installEventFilter(this);
        m_editHeight->editValue()->installEventFilter(this);
        m_editHeight->setLabel(tr("Height"));
        gl->addWidget(m_editHeight, 4, 0, 1, 2);

        vl->addLayout(gl);
    }
    {
        QHBoxLayout *hl = new QHBoxLayout;
        hl->addWidget(new QLabel(tr("Technical attributes")));
        m_editTechnicalAttributes = new QLineEdit;
        m_editTechnicalAttributes->installEventFilter(this);
        m_editTechnicalAttributes->setReadOnly(true);
        hl->addWidget(m_editTechnicalAttributes);
        QPushButton *buttonTechnicalAttributes = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttonTechnicalAttributes, SIGNAL(clicked()),
                         this, SLOT(technicalAttributesClicked()));
        hl->addWidget(buttonTechnicalAttributes);
        QPushButton *buttonTechnicalAttributesRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonTechnicalAttributesRemove, SIGNAL(clicked()),
                         this, SLOT(technicalAttributesRemoveClicked()));
        hl->addWidget(buttonTechnicalAttributesRemove);
        vl->addLayout(hl);
    }
    this->setLayout(vl);

    //Set data fields...
    m_textDocumentation->setText(tr("A description of characteristics of the resource if a document."));
    m_editDocumentFormatId->setText(m_documentFormat->documentFormatId());
    m_editDocumentFormatName->setText(m_documentFormat->documentFormatName());
    m_editDocumentFormatDefinition->setText(m_documentFormat->documentFormatDefinition());
    if (m_documentFormat->regionDelimX()) {
        m_spinRegionDelimX->setValue(*(m_documentFormat->regionDelimX()));
        m_checkRegionDelimX->setChecked(true);
    }
    if (m_documentFormat->regionDelimY()) {
        m_spinRegionDelimY->setValue(*(m_documentFormat->regionDelimY()));
        m_checkRegionDelimY->setChecked(true);
    }
    if (m_documentFormat->wordCount()) {
        m_spinWordCount->setValue(*(m_documentFormat->wordCount()));
        m_checkWordCount->setChecked(true);
    }
    if (m_documentFormat->technicalAttributes())
        m_editTechnicalAttributes->setText(m_documentFormat->technicalAttributes()->toString());
}

QString DocumentFormatTypeForm::toString()
{
    return QString(tr("Document Format"));
}

void DocumentFormatTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_documentFormat;
        m_documentFormat = 0;
    }
    emit closed(m_op, QVarPtr<DocumentFormatType>::asQVariant(m_documentFormat));
}

void DocumentFormatTypeForm::applyClicked()
{
    if (m_checkWordCount->isChecked())
        m_documentFormat->setWordCount(m_spinWordCount->value());
    else
        m_documentFormat->clearWordCount();
    if (m_checkRegionDelimX->isChecked())
        m_documentFormat->setRegionDelimX(m_spinRegionDelimX->value());
    else
        m_documentFormat->clearRegionDelimX();
    if (m_checkRegionDelimY->isChecked())
        m_documentFormat->setRegionDelimY(m_spinRegionDelimY->value());
    else
        m_documentFormat->clearRegionDelimY();
    m_editTypeGroup->updateExistingTypeGroup(m_documentFormat);
    m_formatTypeGroup->updateExistingFormatGroup(m_documentFormat);
    m_documentFormat->setDocumentFormatId(m_editDocumentFormatId->text());
    m_documentFormat->setDocumentFormatDefinition(m_editDocumentFormatDefinition->text());
    m_documentFormat->setDocumentFormatName(m_editDocumentFormatName->text());
    m_documentFormat->setWidth(m_editWidth->lengthType());
    m_documentFormat->setHeight(m_editHeight->lengthType());
    emit closed(m_op, QVarPtr<DocumentFormatType>::asQVariant(m_documentFormat));
}

void DocumentFormatTypeForm::wordCountChanged()
{
    m_checkWordCount->setChecked(true);
}

void DocumentFormatTypeForm::regionDelimXChanged()
{
    m_checkRegionDelimX->setChecked(true);
}

void DocumentFormatTypeForm::regionDelimYChanged()
{
    m_checkRegionDelimY->setChecked(true);
}

void DocumentFormatTypeForm::technicalAttributesRemoveClicked()
{
    if (!m_documentFormat->technicalAttributes())
        return;
    m_documentFormat->setTechnicalAttributes(0);
    m_editTechnicalAttributes->setText(tr("(none)"));
}

void DocumentFormatTypeForm::technicalAttributesClicked()
{
    TechnicalAttributesForm *technicalAttributesForm = new TechnicalAttributesForm(
                m_documentFormat->technicalAttributes(),this->mainWindow());
    QObject::connect(technicalAttributesForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(technicalAttributesFormClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(technicalAttributesForm);
}

void DocumentFormatTypeForm::technicalAttributesFormClosed(StackableWidget::Operation op, QVariant value)
{
    TechnicalAttributes *technicalAttributes = QVarPtr<TechnicalAttributes>::asPointer(value);
    if (!technicalAttributes)
        return;
    if (op == Add)
        m_documentFormat->setTechnicalAttributes(technicalAttributes);
    m_editTechnicalAttributes->setText(technicalAttributes->toString());
}

bool DocumentFormatTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if ( obj == (QObject*) m_formatTypeGroup->editFormatDefinition())
            m_textDocumentation->setText(tr("Free text for an optional definition."));
        else if ( obj == (QObject*) m_formatTypeGroup->editFormatLabel() )
            m_textDocumentation->setText(tr("Free text."));
        else if  (obj == (QObject*) m_formatTypeGroup->editFormatLink())
            m_textDocumentation->setText(tr("Link to a classification scheme."));
        else if  (obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("Free text."));
        else if  (obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("Free text."));
        else if  (obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setText(tr("Link to a Classification Scheme,"));
        else if  (obj == (QObject*) m_editDocumentFormatId)
            m_textDocumentation->setText(tr("An identifier associated to the document format"));
        else if  (obj == (QObject*) m_editDocumentFormatDefinition)
            m_textDocumentation->setText(tr("A definition associated to the signing format"));
        else if  (obj == (QObject*) m_editDocumentFormatName)
            m_textDocumentation->setText(tr("An name associated to the document format"));
        else if  (obj == (QObject*) m_editTechnicalAttributes)
            m_textDocumentation->setText(tr("To provide a user defined technical attribute. See Technical Attributes below."));
        else if  (obj == (QObject*) m_spinWordCount)
            m_textDocumentation->setText(tr("To provide a word count for the document"));
        else if  (obj == (QObject*) m_spinRegionDelimX)
            m_textDocumentation->setText(tr("The identification of a region in a document, an image or a video\nis done by defining the coordinates of the bottom left corner of the region\nThe region is defined from this point of reference using the width and\nheight properties. regionDelimX uses the same unit as width."));
        else if  (obj == (QObject*) m_spinRegionDelimY)
            m_textDocumentation->setText(tr("The identification of a region in a document, an image or a video\nis done by defining the coordinates of the bottom left corner of the region.\nThe region is defined from this point of reference using the width and\nheight properties. regionDelimY uses the same unit as\nheight."));
        else if  (obj == (QObject*) m_editWidth->editUnit())
            m_textDocumentation->setText(tr("The width of an image, video or document."));
        else if  (obj == (QObject*) m_editWidth->editValue())
            m_textDocumentation->setText(tr("The width of an image, video or document."));
        else if  (obj == (QObject*) m_editHeight->editUnit())
            m_textDocumentation->setText(tr("The height of an image, video or document."));
        else if  (obj == (QObject*) m_editHeight->editValue())
            m_textDocumentation->setText(tr("The height of an image, video or document."));
    }
    return QObject::eventFilter(obj, event);
}




