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

#include "formattypeform.h"
#include "documentformattypeform.h"
#include "typegroupform.h"
#include "dategroupform.h"
#include "technicalattributesform.h"
#include "timetypeform.h"
#include "formatgroupform.h"
#include "signingformattypeform.h"
#include "audioformattypeform.h"
#include "videoformattypeform.h"
#include "imageformattypeform.h"
#include "dataformattypeform.h"
#include "durationtypeform.h"
#include "locatortypeform.h"
#include "lengthtypeeditbox.h"
#include "../model/ebucoremaintype.h"
#include "../model/typegroup.h"
#include "../model/formattype.h"
#include "../model/formatgroup.h"
#include "../model/dategroup.h"
#include "../model/technicalattributes.h"
#include "../model/timetype.h"
#include "elementtypeeditbox.h"
#include "../model/qebulimits.h"
#include "qvarptr.h"
#include "listview.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QButtonGroup>
#include <QMessageBox>
#include <QEvent>
#include <QTextBrowser>
#include "qextendedspinbox.h"

FormatTypeForm::FormatTypeForm(FormatType *format, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (format) ? Edit : Add;
    if (!format)
        m_format = new FormatType;
    else
        m_format = format;

    m_tabFormat = new QTabWidget;
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    mainHLayout->addWidget(m_tabFormat);
    {
        QWidget *m_widgetCredits = new QWidget();
        QVBoxLayout *m_vTab = new QVBoxLayout;

        QFormLayout *fl = new QFormLayout;
        m_editFormatId = new QLineEdit;
        m_editFormatId->installEventFilter(this);
        m_editFormatName = new QLineEdit;
        m_editFormatName->installEventFilter(this);
        m_editFormatDefinition = new QLineEdit;
        m_editFormatDefinition->installEventFilter(this);
        fl->addRow(tr("Format Id"), m_editFormatId);
        fl->addRow(tr("Format Name"), m_editFormatName);
        fl->addRow(tr("Format Definition"), m_editFormatDefinition);
        m_vTab->addLayout(fl);

        m_editElementFormat = new ElementTypeEditBox;
        m_editElementFormat->editLang()->installEventFilter(this);
        m_editElementFormat->editValue()->installEventFilter(this);
        m_editElementFormat->setLabel(tr("Format"));
        m_vTab->addWidget(m_editElementFormat);

        QGridLayout *gl = new QGridLayout;
        m_spinFileSize = new QSignedSpinBox;
        m_spinFileSize->installEventFilter(this);
        m_spinFileSize->setRange(0, qEbuLimits::getMaxInt64());
        m_checkFileSize = new QCheckBox(tr("File Size"));
        gl->addWidget(m_checkFileSize, 0, 0, 1, 1);
        gl->addWidget(m_spinFileSize, 0, 1, 1, 3);
        QObject::connect(m_spinFileSize, SIGNAL(valueChanged()),
                         this, SLOT(fileSizeChanged()));


        m_editFileName = new QLineEdit;
        m_editFileName->installEventFilter(this);
        gl->addWidget(new QLabel(tr("File Name")), 1, 0, 1, 1);
        gl->addWidget(m_editFileName, 1, 1, 1, 3);


        gl->addWidget(new QLabel(tr("Document Format")),2,0);
        m_editDocumentFormat = new QLineEdit;
        m_editDocumentFormat->installEventFilter(this);
        m_editDocumentFormat->setReadOnly(true);
        gl->addWidget(m_editDocumentFormat,2,1);
        QPushButton *buttonDocumentFormat = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttonDocumentFormat, SIGNAL(clicked()),
                         this, SLOT(documentFormatClicked()));
        gl->addWidget(buttonDocumentFormat,2,2);
        QPushButton *buttonDocumentFormatRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonDocumentFormatRemove, SIGNAL(clicked()),
                         this, SLOT(documentFormatRemoveClicked()));
        gl->addWidget(buttonDocumentFormatRemove,2,3);


        gl->addWidget(new QLabel(tr("Locator")),3,0);
        m_editLocator = new QLineEdit;
        m_editLocator->installEventFilter(this);
        m_editLocator->setReadOnly(true);
        gl->addWidget(m_editLocator,3,1);
        QPushButton *buttonLocator = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttonLocator, SIGNAL(clicked()),
                         this, SLOT(locatorClicked()));
        gl->addWidget(buttonLocator,3,2);
        QPushButton *buttonLocatorRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonLocatorRemove, SIGNAL(clicked()),
                         this, SLOT(locatorRemoveClicked()));
        gl->addWidget(buttonLocatorRemove,3,3);


        gl->addWidget(new QLabel(tr("Date Created")),4,0);
        m_editDateCreated = new QLineEdit;
        m_editDateCreated->installEventFilter(this);
        m_editDateCreated->setReadOnly(true);
        gl->addWidget(m_editDateCreated,4,1);
        QPushButton *buttonDateCreated = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttonDateCreated, SIGNAL(clicked()),
                         this, SLOT(dateCreatedClicked()));
        gl->addWidget(buttonDateCreated,4,2);
        QPushButton *buttonDateCreatedRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonDateCreatedRemove, SIGNAL(clicked()),
                         this, SLOT(dateCreatedRemoveClicked()));
        gl->addWidget(buttonDateCreatedRemove,4,3);


        gl->addWidget(new QLabel(tr("Date Modified")),5,0);
        m_editDateModified = new QLineEdit;
        m_editDateModified->installEventFilter(this);
        m_editDateModified->setReadOnly(true);
        gl->addWidget(m_editDateModified,5,1);
        QPushButton *buttonDateModified = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttonDateModified, SIGNAL(clicked()),
                         this, SLOT(dateModifiedClicked()));
        gl->addWidget(buttonDateModified,5,2);
        QPushButton *buttonDateModifiedRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonDateModifiedRemove, SIGNAL(clicked()),
                         this, SLOT(dateModifiedRemoveClicked()));
        gl->addWidget(buttonDateModifiedRemove,5,3);

        m_vTab->addLayout(gl);


        m_widgetCredits->setLayout(m_vTab);
        m_tabFormat->addTab(m_widgetCredits,"Credits");
    }
    {
        QWidget *m_attributes = new QWidget();
        QVBoxLayout *m_vTab = new QVBoxLayout;

        QVBoxLayout *vlGeneral = new QVBoxLayout;
        QHBoxLayout *hlTechnicalAttributes = new QHBoxLayout;
        hlTechnicalAttributes->addWidget(new QLabel(tr("Technical Attributes")));
        m_editTechnicalAttributes = new QLineEdit;
        m_editTechnicalAttributes->installEventFilter(this);
        m_editTechnicalAttributes->setReadOnly(true);
        hlTechnicalAttributes->addWidget(m_editTechnicalAttributes);
        QPushButton *buttonTechnicalAttributes = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttonTechnicalAttributes, SIGNAL(clicked()),
                         this, SLOT(technicalAttributesClicked()));
        hlTechnicalAttributes->addWidget(buttonTechnicalAttributes);
        QPushButton *buttonTechnicalAttributesRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonTechnicalAttributesRemove, SIGNAL(clicked()),
                         this, SLOT(technicalAttributesRemoveClicked()));
        hlTechnicalAttributes->addWidget(buttonTechnicalAttributesRemove);
        vlGeneral->addLayout(hlTechnicalAttributes);
        m_vTab->addLayout(vlGeneral);

        QGridLayout *gl = new QGridLayout;
        m_spinRegionDelimX = new QUnsignedSpinBox;
        m_spinRegionDelimX->installEventFilter(this);
        m_spinRegionDelimX->setRange(qEbuLimits::getMinUInt(), qEbuLimits::getMaxUInt());
        m_checkRegionDelimX = new QCheckBox(tr("Region Delim X"));
        gl->addWidget(m_checkRegionDelimX, 0, 0, 1, 2);
        gl->addWidget(m_spinRegionDelimX, 0, 1, 1, 2);
        QObject::connect(m_spinRegionDelimX, SIGNAL(valueChanged()),
                         this, SLOT(regionDelimXChanged()));
        m_spinRegionDelimY = new QUnsignedSpinBox;
        m_spinRegionDelimY->installEventFilter(this);
        m_spinRegionDelimY->setRange(qEbuLimits::getMinUInt(), qEbuLimits::getMaxUInt());
        m_checkRegionDelimY = new QCheckBox(tr("Region Delim Y"));
        gl->addWidget(m_checkRegionDelimY, 1, 0, 1, 2);
        gl->addWidget(m_spinRegionDelimY, 1, 1, 1, 2);
        QObject::connect(m_spinRegionDelimY, SIGNAL(valueChanged()),
                         this, SLOT(regionDelimYChanged()));
        m_vTab->addLayout(gl);

        m_editLengthWidth = new LengthTypeEditBox(m_format->width());
        m_editLengthWidth->editUnit()->installEventFilter(this);
        m_editLengthWidth->editValue()->installEventFilter(this);
        m_editLengthWidth->setLabel(tr("Width"));
        m_vTab->addWidget(m_editLengthWidth);
        m_editLengthHeight = new LengthTypeEditBox(m_format->height());
        m_editLengthHeight->editUnit()->installEventFilter(this);
        m_editLengthHeight->editValue()->installEventFilter(this);
        m_editLengthHeight->setLabel(tr("Height"));
        m_vTab->addWidget(m_editLengthHeight);

        QGridLayout *glTime = new QGridLayout;
        glTime->addWidget(new QLabel(tr("Start")),0,0);
        m_editStart = new QLineEdit;
        m_editStart->installEventFilter(this);
        m_editStart->setReadOnly(true);
        glTime->addWidget(m_editStart,0,1);
        QPushButton *buttonStart = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttonStart, SIGNAL(clicked()),
                         this, SLOT(startClicked()));
        glTime->addWidget(buttonStart,0,2);
        QPushButton *buttonStartRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonStartRemove, SIGNAL(clicked()),
                         this, SLOT(startRemoveClicked()));
        glTime->addWidget(buttonStartRemove,0,3);

        glTime->addWidget(new QLabel(tr("End")),1,0);
        m_editEnd = new QLineEdit;
        m_editEnd->installEventFilter(this);
        m_editEnd->setReadOnly(true);
        glTime->addWidget(m_editEnd,1,1);
        QPushButton *buttonEnd = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttonEnd, SIGNAL(clicked()),
                         this, SLOT(endClicked()));
        glTime->addWidget(buttonEnd,1,2);
        QPushButton *buttonEndRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonEndRemove, SIGNAL(clicked()),
                         this, SLOT(endRemoveClicked()));
        glTime->addWidget(buttonEndRemove,1,3);

        glTime->addWidget(new QLabel(tr("Duration")),2,0);
        m_editDuration = new QLineEdit;
        m_editDuration->installEventFilter(this);
        m_editDuration->setReadOnly(true);
        glTime->addWidget(m_editDuration,2,1);
        QPushButton *buttonDuration = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttonDuration, SIGNAL(clicked()),
                         this, SLOT(durationClicked()));
        glTime->addWidget(buttonDuration,2,2);
        QPushButton *buttonDurationRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonDurationRemove, SIGNAL(clicked()),
                         this, SLOT(durationRemoveClicked()));
        glTime->addWidget(buttonDurationRemove,2,3);

        m_vTab->addLayout(glTime);

        m_attributes->setLayout(m_vTab);
        m_tabFormat->addTab(m_attributes,"Attributes");

    }
    {
        QWidget *m_multimediaFormat = new QWidget();
        QHBoxLayout *m_hTab = new QHBoxLayout;
        QVBoxLayout *l = new QVBoxLayout;
        QGridLayout *gl = new QGridLayout;

        gl->addWidget(new QLabel("Medium", this),0,0);
        m_buttonMedium = new QPushButton(">>");
        m_buttonMedium->installEventFilter(this);
        gl->addWidget(m_buttonMedium,0,1);
        m_buttonMedium->setCheckable(true);
        QObject::connect(m_buttonMedium, SIGNAL(toggled(bool)), this, SLOT(mediumFormChecked(bool)));

        gl->addWidget(new QLabel("Mime Type", this),1,0);
        m_buttonMimeType = new QPushButton(">>");
        m_buttonMimeType->installEventFilter(this);
        gl->addWidget(m_buttonMimeType,1,1);
        m_buttonMimeType->setCheckable(true);
        QObject::connect(m_buttonMimeType, SIGNAL(toggled(bool)), this, SLOT(mimeTypeFormChecked(bool)));

        gl->addWidget(new QLabel("Containter Format", this),2,0);
        m_buttonContainerFormat = new QPushButton(">>");
        m_buttonContainerFormat->installEventFilter(this);
        gl->addWidget(m_buttonContainerFormat,2,1);
        m_buttonContainerFormat->setCheckable(true);
        QObject::connect(m_buttonContainerFormat, SIGNAL(toggled(bool)), this, SLOT(containerFormatFormChecked(bool)));

        gl->addWidget(new QLabel("Signing Format", this),3,0);
        m_buttonSigningFormat = new QPushButton(">>");
        m_buttonSigningFormat->installEventFilter(this);
        gl->addWidget(m_buttonSigningFormat,3,1);
        m_buttonSigningFormat->setCheckable(true);
        QObject::connect(m_buttonSigningFormat, SIGNAL(toggled(bool)), this, SLOT(signingFormatFormChecked(bool)));

        gl->addWidget(new QLabel("Image Format", this),4,0);
        m_buttonImageFormat = new QPushButton(">>");
        m_buttonImageFormat->installEventFilter(this);
        gl->addWidget(m_buttonImageFormat,4,1);
        m_buttonImageFormat->setCheckable(true);
        QObject::connect(m_buttonImageFormat, SIGNAL(toggled(bool)), this, SLOT(imageFormatFormChecked(bool)));

        gl->addWidget(new QLabel("Video Format", this),5,0);
        m_buttonVideoFormat = new QPushButton(">>");
        m_buttonVideoFormat->installEventFilter(this);
        gl->addWidget(m_buttonVideoFormat,5,1);
        m_buttonVideoFormat->setCheckable(true);
        QObject::connect(m_buttonVideoFormat, SIGNAL(toggled(bool)), this, SLOT(videoFormatFormChecked(bool)));

        gl->addWidget(new QLabel("Audio Format", this),6,0);
        m_buttonAudioFormat = new QPushButton(">>");
        m_buttonAudioFormat->installEventFilter(this);
        gl->addWidget(m_buttonAudioFormat,6,1);
        m_buttonAudioFormat->setCheckable(true);
        QObject::connect(m_buttonAudioFormat, SIGNAL(toggled(bool)), this, SLOT(audioFormatFormChecked(bool)));

        gl->addWidget(new QLabel("Data Format", this),7,0);
        m_buttonDataFormat = new QPushButton(">>");
        m_buttonDataFormat->installEventFilter(this);
        gl->addWidget(m_buttonDataFormat,7,1);
        m_buttonDataFormat->setCheckable(true);
        QObject::connect(m_buttonDataFormat, SIGNAL(toggled(bool)), this, SLOT(dataFormatFormChecked(bool)));

        QButtonGroup *group = new QButtonGroup(this);
        group->addButton(m_buttonMimeType);
        group->addButton(m_buttonMedium);
        group->addButton(m_buttonContainerFormat);
        group->addButton(m_buttonSigningFormat);
        group->addButton(m_buttonImageFormat);
        group->addButton(m_buttonVideoFormat);
        group->addButton(m_buttonAudioFormat);
        group->addButton(m_buttonDataFormat);

        l->addLayout(gl);
        m_hTab->addLayout(l);
        m_listView = new ListView();
        QObject::connect(m_listView->buttonAdd(), SIGNAL(clicked()),
                         this, SLOT(addClicked()));
        QObject::connect(m_listView->buttonEdit(), SIGNAL(clicked()),
                         this, SLOT(editClicked()));
        QObject::connect(m_listView->buttonRemove(), SIGNAL(clicked()),
                         this, SLOT(removeClicked()));
        m_hTab->addWidget(m_listView);
        m_multimediaFormat->setLayout(m_hTab);
        m_tabFormat->addTab(m_multimediaFormat,"Multimedia Format");
    }
    this->setLayout(mainHLayout);

    //Set Data Fields..
    m_textDocumentation->setText(tr("Technical metadata information on the physical or digital manifestation / instance of the resource. Use the descriptor Format to identify the format of a particular resource as it exists in its physical or digital form. Physical form = an actual physical form that occupies physical space, e.g. a tape. Digital form = a digital file residing on a server or hard drive.\nFormat may be used to determine the software, hardware or other equipment needed to display or operate the resource.\nFormat gathers all technical metadata about a content instance on video, audio, data, etc. It can be flexibility augmented at will by users using the technicalAttribute constructs.\nCombining the flexibility of the 'Format' and 'Part' elements allows the description of a large range of technical metadata that is optionally associated to timelines.\nThe 'format' element is optional, which means a valid EBUCore description may only contain descriptive information."));
    m_editFormatId->setText(m_format->formatId());
    m_editFormatName->setText(m_format->formatName());
    m_editFormatDefinition->setText(m_format->formatDefinition());
    m_editFileName->setText(m_format->fileName());
    if (m_format->regionDelimX()) {
        m_checkRegionDelimX->setChecked(true);
        m_spinRegionDelimX->setValue(*(m_format->regionDelimX()));
    }
    if (m_format->regionDelimY()) {
        m_checkRegionDelimY->setChecked(true);
        m_spinRegionDelimY->setValue(*(m_format->regionDelimY()));
    }
    if(m_format->fileSize()){
        m_checkFileSize->setChecked(true);
        m_spinFileSize->setValue(*(m_format->fileSize()));
    }
    if (m_format->format()) {
        m_editElementFormat->editValue()->setText(m_format->format()->value());
        m_editElementFormat->editLang()->setText(m_format->format()->lang());
    }
    if(m_format->locator()){
        m_editLocator->setText(m_format->locator()->toString());
    }
    if(m_format->dateCreated()){
        m_editDateCreated->setText(m_format->dateCreated()->toString());
    }
    if(m_format->dateModified()){
        m_editDateModified->setText(m_format->dateModified()->toString());
    }
    if(m_format->start()){
        m_editStart->setText(m_format->start()->toString());
    }
    if(m_format->end()){
        m_editEnd->setText(m_format->end()->toString());
    }
    if(m_format->duration()){
        m_editEnd->setText(m_format->duration()->toString());
    }
    if(m_format->documentFormat()) {
        m_editDocumentFormat->setText(m_format->documentFormat()->toString());
    }
    if(m_format->technicalAttributes()) {
        m_editTechnicalAttributes->setText(m_format->technicalAttributes()->toString());
    }

    m_buttonMedium->setChecked(true);

}

QString FormatTypeForm::toString()
{
     return QString(tr("Format"));
}

void FormatTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_format;
        m_format = 0;
    }
    emit closed(m_op, QVarPtr<FormatType>::asQVariant(m_format));
}

void FormatTypeForm::applyClicked()
{
    QString newFormatId = m_editFormatId->text();
    QString oldFormatId = m_format->formatId();
    m_format->setFormatId(newFormatId);
    mainWindow()->ebuCoreMain()->updateFormatId(oldFormatId, newFormatId, m_format);
    m_format->setFormatName(m_editFormatName->text());
    m_format->setFormatDefinition(m_editFormatDefinition->text());
    m_format->setFileName(m_editFileName->text());

    if (m_checkRegionDelimX->isChecked())
        m_format->setRegionDelimX(m_spinRegionDelimX->value());
    else
        m_format->clearRegionDelimX();
    if (m_checkRegionDelimY->isChecked())
        m_format->setRegionDelimY(m_spinRegionDelimY->value());
    else
        m_format->clearRegionDelimY();
    if (m_checkFileSize->isChecked())
        m_format->setFileSize(m_spinFileSize->value());
    else
        m_format->clearFileSize();

    m_format->setWidth(m_editLengthWidth->lengthType());
    m_format->setHeight(m_editLengthHeight->lengthType());
    if (m_editElementFormat->editLang()->text().isEmpty() && m_editElementFormat->editValue()->text().isEmpty())
        m_format->setFormat(0);
    else
        m_format->setFormat(
                    new ElementType(m_editElementFormat->editValue()->text(),
                                    m_editElementFormat->editLang()->text()));

    emit closed(m_op, QVarPtr<FormatType>::asQVariant(m_format));
}

void FormatTypeForm::documentFormatRemoveClicked()
{
    if (!m_format->documentFormat())
        return;
    m_format->setDocumentFormat(0);
    m_editDocumentFormat->setText(tr("(none)"));
}

void FormatTypeForm::documentFormatClicked()
{
    DocumentFormatTypeForm *documentFormatForm = new DocumentFormatTypeForm(
                m_format->documentFormat(),this->mainWindow());
    QObject::connect(documentFormatForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(documentFormatClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(documentFormatForm);
}

void FormatTypeForm::documentFormatClosed(StackableWidget::Operation op, QVariant value)
{
    DocumentFormatType *documentFormat = QVarPtr<DocumentFormatType>::asPointer(value);
    if (!documentFormat)
        return;
    if (op == Add)
        m_format->setDocumentFormat(documentFormat);
    m_editDocumentFormat->setText(documentFormat->toString());
}

void FormatTypeForm::locatorRemoveClicked()
{
    if (!m_format->locator())
        return;
    m_format->setLocator(0);
    m_editLocator->setText(tr("(none)"));
}

void FormatTypeForm::locatorClicked()
{
    LocatorTypeForm *locatorForm = new LocatorTypeForm(
                m_format->locator(),this->mainWindow());
    QObject::connect(locatorForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(locatorClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(locatorForm);
}

void FormatTypeForm::locatorClosed(StackableWidget::Operation op, QVariant value)
{
    LocatorType *locator = QVarPtr<LocatorType>::asPointer(value);
    if (!locator)
        return;
    if (op == Add)
        m_format->setLocator(locator);
    m_editLocator->setText(locator->toString());
}

void FormatTypeForm::dateCreatedRemoveClicked()
{
    if (!m_format->dateCreated())
        return;
    m_format->setDateCreated(0);
    m_editDateCreated->setText(tr("(none)"));
}

void FormatTypeForm::dateCreatedClicked()
{
    DateGroupForm *dateCreatedForm = new DateGroupForm(
                m_format->dateCreated(),this->mainWindow());
    dateCreatedForm->setTitle("Date Created");
    QObject::connect(dateCreatedForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(dateCreatedClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(dateCreatedForm);
}

void FormatTypeForm::dateCreatedClosed(StackableWidget::Operation op, QVariant value)
{
    DateGroup *dateCreated = QVarPtr<DateGroup>::asPointer(value);
    if (!dateCreated)
        return;
    if (op == Add)
        m_format->setDateCreated(dateCreated);
    m_editDateCreated->setText(dateCreated->toString());
}

void FormatTypeForm::dateModifiedRemoveClicked()
{
    if (!m_format->dateModified())
        return;
    m_format->setDateModified(0);
    m_editDateModified->setText(tr("(none)"));
}

void FormatTypeForm::dateModifiedClicked()
{
    DateGroupForm *dateModifiedForm = new DateGroupForm(
                m_format->dateModified(),this->mainWindow());
    dateModifiedForm->setTitle(tr("Date Modified"));
    QObject::connect(dateModifiedForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(dateModifiedClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(dateModifiedForm);
}

void FormatTypeForm::dateModifiedClosed(StackableWidget::Operation op, QVariant value)
{
    DateGroup *dateModified = QVarPtr<DateGroup>::asPointer(value);
    if (!dateModified)
        return;
    if (op == Add)
        m_format->setDateModified(dateModified);
    m_editDateModified->setText(dateModified->toString());
}

void FormatTypeForm::technicalAttributesRemoveClicked()
{
    if (!m_format->technicalAttributes())
        return;
    m_format->setTechnicalAttributes(0);
    m_editTechnicalAttributes->setText(tr("(none)"));
}

void FormatTypeForm::technicalAttributesClicked()
{
    TechnicalAttributesForm *technicalAttributesForm = new TechnicalAttributesForm(
                m_format->technicalAttributes(),this->mainWindow());
    QObject::connect(technicalAttributesForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(technicalAttributesClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(technicalAttributesForm);
}

void FormatTypeForm::technicalAttributesClosed(StackableWidget::Operation op, QVariant value)
{
    TechnicalAttributes *technicalAttributes = QVarPtr<TechnicalAttributes>::asPointer(value);
    if (!technicalAttributes)
        return;
    if (op == Add)
        m_format->setTechnicalAttributes(technicalAttributes);
    m_editTechnicalAttributes->setText(technicalAttributes->toString());
}

void FormatTypeForm::startRemoveClicked()
{
    if (!m_format->start())
        return;
    m_format->setStart(0);
    m_editStart->setText(tr("(none)"));
}

void FormatTypeForm::startClicked()
{
    TimeTypeForm *startForm = new TimeTypeForm(
                m_format->start(),this->mainWindow());
    QObject::connect(startForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(startClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(startForm);
}

void FormatTypeForm::startClosed(StackableWidget::Operation op, QVariant value)
{
    TimeType *start = QVarPtr<TimeType>::asPointer(value);
    if (!start)
        return;
    if (op == Add)
        m_format->setStart(start);
    m_editStart->setText(start->toString());
}

void FormatTypeForm::endRemoveClicked()
{
    if (!m_format->end())
        return;
    m_format->setEnd(0);
    m_editEnd->setText(tr("(none)"));
}

void FormatTypeForm::endClicked()
{
    TimeTypeForm *endForm = new TimeTypeForm(
                m_format->end(),this->mainWindow());
    QObject::connect(endForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(endClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(endForm);
}

void FormatTypeForm::endClosed(StackableWidget::Operation op, QVariant value)
{
    TimeType *end = QVarPtr<TimeType>::asPointer(value);
    if (!end)
        return;
    if (op == Add)
        m_format->setEnd(end);
    m_editEnd->setText(end->toString());
}

void FormatTypeForm::durationRemoveClicked()
{
    if (!m_format->duration())
        return;
    m_format->setDuration(0);
    m_editDuration->setText(tr("(none)"));
}

void FormatTypeForm::durationClicked()
{
    DurationTypeForm *durationForm = new DurationTypeForm(
                m_format->duration(),this->mainWindow());
    QObject::connect(durationForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(durationClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(durationForm);
}

void FormatTypeForm::durationClosed(StackableWidget::Operation op, QVariant value)
{
    DurationType *duration = QVarPtr<DurationType>::asPointer(value);
    if (!duration)
        return;
    if (op == Add)
        m_format->setDuration(duration);
    m_editDuration->setText(duration->toString());
}

void FormatTypeForm::mediumFormChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Medium;
    updateListAndButtons();
    int s = m_format->medium().size();
    for (int i=0; i < s; ++i) {
        TypeGroup *item = m_format->medium().at(i);
        if (!item)
            continue;
        m_listView->addItem(item->toString());
    }
}

void FormatTypeForm::mimeTypeFormChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = MimeType;
    updateListAndButtons();
    int s = m_format->mimeType().size();
    for (int i=0; i < s; ++i) {
        TypeGroup *item = m_format->mimeType().at(i);
        if (!item)
            continue;
        m_listView->addItem(item->toString());
    }
}

void FormatTypeForm::containerFormatFormChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = ContainerFormat;
    updateListAndButtons();
    int s = m_format->containerFormat().size();
    for (int i=0; i < s; ++i) {
        FormatGroup *item = m_format->containerFormat().at(i);
        if (!item)
            continue;
        m_listView->addItem(item->toString());
    }
}

void FormatTypeForm::signingFormatFormChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = SigningFormat;
    updateListAndButtons();
    int s = m_format->signingFormat().size();
    for (int i=0; i < s; ++i) {
        SigningFormatType *item = m_format->signingFormat().at(i);
        if (!item)
            continue;
        m_listView->addItem(item->toString());
    }
}

void FormatTypeForm::imageFormatFormChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = ImageFormat;
    updateListAndButtons();
    int s = m_format->imageFormat().size();
    for (int i=0; i < s; ++i) {
        ImageFormatType *item = m_format->imageFormat().at(i);
        if (!item)
            continue;
        m_listView->addItem(item->toString());
    }
}

void FormatTypeForm::videoFormatFormChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = VideoFormat;
    updateListAndButtons();
    int s = m_format->videoFormat().size();
    for (int i=0; i < s; ++i) {
        VideoFormatType *item = m_format->videoFormat().at(i);
        if (!item)
            continue;
        m_listView->addItem(item->toString());
    }
}

void FormatTypeForm::audioFormatFormChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = AudioFormat;
    updateListAndButtons();
    int s = m_format->audioFormat().size();
    for (int i=0; i < s; ++i) {
        AudioFormatType *item = m_format->audioFormat().at(i);
        if (!item)
            continue;
        m_listView->addItem(item->toString());
    }
}

void FormatTypeForm::dataFormatFormChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = DataFormat;
    updateListAndButtons();
    int s = m_format->dataFormat().size();
    for (int i=0; i < s; ++i) {
        DataFormatType *item = m_format->dataFormat().at(i);
        if (!item)
            continue;
        m_listView->addItem(item->toString());
    }
}

void FormatTypeForm::mediumFormClosed(StackableWidget::Operation op, QVariant value)
{
    TypeGroup *item = QVarPtr<TypeGroup>::asPointer(value);
    if(!item)
        return;
    if(op == Add) {
        m_listView->addItem(item->toString());
        m_format->medium().append(item);
    } else if(op == Edit) {
        int row = m_format->medium().indexOf(item);
        m_listView->setItem(row, item->toString());
    }
}

void FormatTypeForm::mimeTypeFormClosed(StackableWidget::Operation op, QVariant value)
{
    TypeGroup *item = QVarPtr<TypeGroup>::asPointer(value);
    if(!item)
        return;
    if(op == Add) {
        m_listView->addItem(item->toString());
        m_format->mimeType().append(item);
    } else if(op == Edit) {
        int row = m_format->mimeType().indexOf(item);
        m_listView->setItem(row, item->toString());
    }
}

void FormatTypeForm::containerFormatFormClosed(StackableWidget::Operation op, QVariant value)
{
    FormatGroup *item = QVarPtr<FormatGroup>::asPointer(value);
    if(!item)
        return;
    if(op == Add) {
        m_listView->addItem(item->toString());
        m_format->containerFormat().append(item);
    } else if(op == Edit) {
        int row = m_format->containerFormat().indexOf(item);
        m_listView->setItem(row, item->toString());
    }
}

void FormatTypeForm::signingFormatFormClosed(StackableWidget::Operation op, QVariant value)
{
    SigningFormatType *item = QVarPtr<SigningFormatType>::asPointer(value);
    if(!item)
        return;
    if(op == Add) {
        m_listView->addItem(item->toString());
        m_format->signingFormat().append(item);
    } else if(op == Edit) {
        int row = m_format->signingFormat().indexOf(item);
        m_listView->setItem(row, item->toString());
    }
}

void FormatTypeForm::imageFormatFormClosed(StackableWidget::Operation op, QVariant value)
{
    ImageFormatType *item = QVarPtr<ImageFormatType>::asPointer(value);
    if(!item)
        return;
    if(op == Add) {
        m_listView->addItem(item->toString());
        m_format->imageFormat().append(item);
    } else if(op == Edit) {
        int row = m_format->imageFormat().indexOf(item);
        m_listView->setItem(row, item->toString());
    }
}

void FormatTypeForm::videoFormatFormClosed(StackableWidget::Operation op, QVariant value)
{
    VideoFormatType *item = QVarPtr<VideoFormatType>::asPointer(value);
    if(!item)
        return;
    if(op == Add) {
        m_listView->addItem(item->toString());
        m_format->videoFormat().append(item);
    } else if(op == Edit) {
        int row = m_format->videoFormat().indexOf(item);
        m_listView->setItem(row, item->toString());
    }
}

void FormatTypeForm::audioFormatFormClosed(StackableWidget::Operation op, QVariant value)
{
    AudioFormatType *item = QVarPtr<AudioFormatType>::asPointer(value);
    if(!item)
        return;
    if(op == Add) {
        m_listView->addItem(item->toString());
        m_format->audioFormat().append(item);
    } else if(op == Edit) {
        int row = m_format->audioFormat().indexOf(item);
        m_listView->setItem(row, item->toString());
    }
}

void FormatTypeForm::dataFormatFormClosed(StackableWidget::Operation op, QVariant value)
{
    DataFormatType *item = QVarPtr<DataFormatType>::asPointer(value);
    if(!item)
        return;
    if(op == Add) {
        m_listView->addItem(item->toString());
        m_format->dataFormat().append(item);
    } else if(op == Edit) {
        int row = m_format->dataFormat().indexOf(item);
        m_listView->setItem(row, item->toString());
    }
}

void FormatTypeForm::fileSizeChanged()
{
    m_checkFileSize->setChecked(true);
}

void FormatTypeForm::regionDelimXChanged()
{
    m_checkRegionDelimX->setChecked(true);
}

void FormatTypeForm::regionDelimYChanged()
{
    m_checkRegionDelimY->setChecked(true);
}

void FormatTypeForm::addClicked()
{
    switch (m_currentEditMode) {
    case MimeType:
    {
        TypeGroupForm *form = new TypeGroupForm(0, this->mainWindow());
        form->addLinksMap(mainWindow()->getMap("ebu_MediaTypeCS"));
        form->setTitle(tr("Mime Type"));
        form->setGeneralDoc(tr("To define the type of medium in which the resource is available."));
        form->setDefinitionDoc(tr("An optional definition.\nExample: ‘the resource contains only video footage’."));
        form->setLinkDoc(tr("A link to a term or only identify a classification scheme."));
        form->setLabelDoc(tr("Free text field.\nExample: video only."));
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(mimeTypeFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case Medium:
    {
        TypeGroupForm *form = new TypeGroupForm(0, this->mainWindow());
        form->addLinksMap(mainWindow()->getMap("ebu_StorageMediaTypeCodeCS"));
        form->setTitle(tr("Medium"));
        form->setGeneralDoc(tr("To define the type of medium in which the resource is available."));
        form->setDefinitionDoc(tr("An optional definition."));
        form->setLinkDoc(tr("A link to a term or only identify a classification scheme."));
        form->setLabelDoc(tr("Free text field.\nExample: D5 format HDTV digital television tape."));
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(mediumFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case ContainerFormat:
    {
        FormatGroupForm *form = new FormatGroupForm(0, this->mainWindow());
        form->addLinksMap(mainWindow()->getMap("ebu_FileFormatCS"));
        form->setTitle("Container Format");
        form->setGeneralDoc(tr("To define the file format of the resource."));
        form->setLinkDoc(tr("A link to a term or only identify a classification scheme."));
        form->setLabelDoc(tr("Free text field\nExample: mpeg TS."));
        form->setDefinitionDoc(tr("An optional definition.\nExample: ‘The file format or wrapper defined by ISO/IEC (so called MPEG Transport Stream)’."));
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(containerFormatFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case SigningFormat:
    {
        SigningFormatTypeForm *form = new SigningFormatTypeForm(0, this->mainWindow());      
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(signingFormatFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case ImageFormat:
    {
        ImageFormatTypeForm *form = new ImageFormatTypeForm(0, this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(imageFormatFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case VideoFormat:
    {
        VideoFormatTypeForm *form = new VideoFormatTypeForm(0, this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(videoFormatFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case AudioFormat:
    {
        AudioFormatTypeForm *form = new AudioFormatTypeForm(0, this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(audioFormatFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case DataFormat:
    {
        DataFormatTypeForm *form = new DataFormatTypeForm(0, this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(dataFormatFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    }
}

void FormatTypeForm::editClicked()
{
    int index = m_listView->selected();
    if (index < 0)
        return;
    switch (m_currentEditMode) {
    case MimeType:
    {
        TypeGroupForm *form = new TypeGroupForm(m_format->mimeType().at(index), this->mainWindow());
        form->setTitle(tr("Mime Type"));
        form->setGeneralDoc(tr("To define the type of medium in which the resource is available."));
        form->setDefinitionDoc(tr("An optional definition.\nExample: ‘the resource contains only video footage’."));
        form->setLinkDoc(tr("A link to a term or only identify a classification scheme."));
        form->setLabelDoc(tr("Free text field.\nExample: video only."));
        form->addLinksMap(mainWindow()->getMap("ebu_MediaTypeCS"));
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(mimeTypeFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case Medium:
    {
        TypeGroupForm *form = new TypeGroupForm(m_format->medium().at(index), this->mainWindow());
        form->setTitle(tr("Medium"));
        form->setGeneralDoc(tr("To define the type of medium in which the resource is available."));
        form->setDefinitionDoc(tr("An optional definition."));
        form->setLinkDoc(tr("A link to a term or only identify a classification scheme."));
        form->setLabelDoc(tr("Free text field.\nExample: D5 format HDTV digital television tape."));
        form->addLinksMap(mainWindow()->getMap("ebu_StorageMediaTypeCodeCS"));
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(mediumFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case ContainerFormat:
    {
        FormatGroupForm *form = new FormatGroupForm(m_format->containerFormat().at(index), this->mainWindow());
        form->setTitle(tr("Container Format"));
        form->setGeneralDoc(tr("To define the file format of the resource."));
        form->setLinkDoc(tr("A link to a term or only identify a classification scheme."));
        form->setLabelDoc(tr("Free text field\nExample: mpeg TS."));
        form->setDefinitionDoc(tr("An optional definition.\nExample: ‘The file format or wrapper defined by ISO/IEC (so called MPEG Transport Stream)’."));
        form->addLinksMap(mainWindow()->getMap("ebu_FileFormatCS"));
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(containerFormatFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case SigningFormat:
    {
        SigningFormatTypeForm *form = new SigningFormatTypeForm(m_format->signingFormat().at(index), this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(signingFormatFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case ImageFormat:
    {
        ImageFormatTypeForm *form = new ImageFormatTypeForm(m_format->imageFormat().at(index), this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(imageFormatFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case VideoFormat:
    {
        VideoFormatTypeForm *form = new VideoFormatTypeForm(m_format->videoFormat().at(index), this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(videoFormatFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case AudioFormat:
    {
        AudioFormatTypeForm *form = new AudioFormatTypeForm(m_format->audioFormat().at(index), this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(audioFormatFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case DataFormat:
    {
        DataFormatTypeForm *form = new DataFormatTypeForm(m_format->dataFormat().at(index), this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(dataFormatFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    }
}

void FormatTypeForm::removeClicked()
{
    int row = m_listView->selected();
    if (row < 0)
        return;
    m_listView->removeAt(row);
    switch (m_currentEditMode) {
    case MimeType:
    {
        delete(m_format->mimeType().takeAt(row));
    }
        break;
    case Medium:
    {
        delete(m_format->medium().takeAt(row));
    }
        break;
    case ContainerFormat:
    {
        delete(m_format->containerFormat().takeAt(row));
    }
        break;
    case SigningFormat:
    {
        delete(m_format->signingFormat().takeAt(row));
    }
        break;
    case ImageFormat:
    {
        delete(m_format->imageFormat().takeAt(row));
    }
        break;
    case VideoFormat:
    {
        delete(m_format->videoFormat().takeAt(row));
    }
        break;
    case AudioFormat:
    {
        delete(m_format->audioFormat().takeAt(row));
    }
        break;
    case DataFormat:
    {
        delete(m_format->dataFormat().takeAt(row));
    }
        break;
    }
}

void FormatTypeForm::updateListAndButtons()
{
    QString title;
    switch (m_currentEditMode) {
    case MimeType:
    {
        title = tr("Mime Type");
    }
        break;
    case Medium:
    {
        title = tr("Medium");
    }
        break;
    case ContainerFormat:
    {
        title = tr("Container Format");
    }
        break;
    case SigningFormat:
    {
        title = tr("Signing Format");
    }
        break;
    case ImageFormat:
    {
        title = tr("Image Format");
    }
        break;
    case VideoFormat:
    {
        title = tr("Video Format");
    }
        break;
    case AudioFormat:
    {
        title = tr("Audio Format");
    }
        break;
    case DataFormat:
    {
        title = tr("Data Format");
    }
        break;
    }
    m_listView->setTitle(title);
    m_listView->clear();
}

bool FormatTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if ( obj == (QObject*) m_editFormatId)
            m_textDocumentation->setText(tr("An Identifier to identify a specific format in which the resource is available or has been published."));
        if ( obj == (QObject*) m_editFormatName)
            m_textDocumentation->setText(tr("A name attributed to a particular format."));
        if ( obj == (QObject*) m_editFormatDefinition)
            m_textDocumentation->setText(tr("A definition of the format information being provided either technical or editorial in nature."));
        if ( obj == (QObject*) m_editElementFormat->editLang())
            m_textDocumentation->setText(tr("The language in which the format is provided."));
        if ( obj == (QObject*) m_editElementFormat->editValue())
            m_textDocumentation->setText(tr("Free text to provide information on the format"));
        if ( obj == (QObject*) m_spinFileSize)
            m_textDocumentation->setText(tr("To indicate the storage requirements or file size of a digital resource. The file size is expressed in bytes."));
        if ( obj == (QObject*) m_editFileName)
            m_textDocumentation->setText(tr("To indicate the name of the file containing the resource."));
        if ( obj == (QObject*) m_editDocumentFormat)
            m_textDocumentation->setText(tr("To provide information on the document format."));
        if ( obj == (QObject*) m_editLocator)
            m_textDocumentation->setText(tr("An 'address for a resource'. For an organisation or producer acting as caretaker for a media resource, Format Location may contain information about a specific e.g. tape name, shelf location for an asset, including an organisation's name, departmental name, shelf id. And contact information. The Format Location for a data file or web page may include a complete URI with a domain, path, filename or html URL."));
        if ( obj == (QObject*) m_editDateCreated)
            m_textDocumentation->setText(tr("A date to indicate when the content instance was created / generated in this format."));
        if ( obj == (QObject*) m_editDateModified)
            m_textDocumentation->setText(tr("A date to indicate when the content instance format was modified."));
        if ( obj == (QObject*) m_editTechnicalAttributes)
            m_textDocumentation->setText(tr("An extension element to allow users and implementers to define their own technical attributes."));
        if ( obj == (QObject*) m_spinRegionDelimX)
            m_textDocumentation->setText(tr("The identification of a region in a document, an image or a video is done by defining the coordinates of the bottom left corner of the region. The region is defined from this point of reference using the width and height properties. regionDelimX is the coordinate on the horizontal axis and uses the same unit as the width attribute."));
        if ( obj == (QObject*) m_spinRegionDelimY)
            m_textDocumentation->setText(tr("The identification of a region in a document, an image or a video is done by defining the coordinates of the bottom left corner of the region. The region is defined from this point of reference using the width and height properties. regionDelimY is the coordinate on the vertical axis uses the same unit as the height attribute."));
        if ( obj == (QObject*) m_editLengthWidth->editUnit())
            m_textDocumentation->setText(tr("The width of the image or picture. Used as numerator to define the aspect ratio for video content."));
        if ( obj == (QObject*) m_editLengthWidth->editValue())
            m_textDocumentation->setText(tr("The width of the image or picture. Used as numerator to define the aspect ratio for video content."));
        if ( obj == (QObject*) m_editLengthHeight->editUnit())
            m_textDocumentation->setText(tr("The height of the image or picture. Used as denominator to define the aspect ratio for video content."));
        if ( obj == (QObject*) m_editLengthHeight->editValue())
            m_textDocumentation->setText(tr("The height of the image or picture. Used as denominator to define the aspect ratio for video content."));
        if ( obj == (QObject*) m_editStart)
            m_textDocumentation->setText(tr("The beginning point for playback of a time-based media item, such as digital video or audio. Use in combination with Format Duration to identify a sequence or segment of a media item that has a fixed start time and end time."));
        if ( obj == (QObject*) m_editEnd)
            m_textDocumentation->setText(tr("The ending point for playback of a time-based media item, such as digital video or audio. Use in combination with Format Start to identify a sequence or segment of a media item."));
        if ( obj == (QObject*) m_editDuration)
            m_textDocumentation->setText(tr("The time duration/extent of the resource. Format Duration is an alternative to Format End for identifying the extent of a sequence or segment."));
        if ( obj == (QObject*) m_buttonMedium)
            m_textDocumentation->setHtml(tr("To define the type of medium in which the resource is available.<br/>Reference data:<br/><a href=\"http://www.ebu.ch/metadata/cs/web/ebu_StorageMediaTypeCode_p.xml.htm\">ebu_StorageMediaTypeCode</a>"));
        if ( obj == (QObject*) m_buttonMimeType)
            m_textDocumentation->setHtml(tr("To define the type of mime type in which the resource is available.<br/>Reference data:<br/><a href=\"http://www.ebu.ch/metadata/cs/web/ebu_MediaTypeCS_p.xml.htm\">ebu_MediaTypeCS</a>"));
        if ( obj == (QObject*) m_buttonContainerFormat)
            m_textDocumentation->setHtml(tr("To provide information on the Container Format in complement to stream encoding information.<br/>Reference data<br/><a href=\"http://www.ebu.ch/metadata/cs/web/ebu_FileFormatCS_p.xml.htm\">ebu_FileFormatCS</a>"));
        if ( obj == (QObject*) m_buttonSigningFormat)
            m_textDocumentation->setText(tr("To provide information on the signing format, if used."));
        if ( obj == (QObject*) m_buttonImageFormat)
            m_textDocumentation->setText(tr("To provide information on the image format."));
        if ( obj == (QObject*) m_buttonVideoFormat)
            m_textDocumentation->setText(tr("To provide information on the video format."));
        if ( obj == (QObject*) m_buttonAudioFormat)
            m_textDocumentation->setText(tr("To provide information on the audio format."));
        if ( obj == (QObject*) m_buttonDataFormat)
            m_textDocumentation->setText(tr("To provide information on the captioning and ancillary data formats."));

    }
    return QObject::eventFilter(obj, event);
}
