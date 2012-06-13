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

#include "imageformattypeform.h"
#include "lengthtypeeditbox.h"
#include "technicalattributesform.h"
#include "qvarptr.h"
#include "listview.h"
#include "typegroupform.h"
#include "../model/formattype.h"
#include "../model/qebulimits.h"
#include <QGridLayout>
#include <QFormLayout>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QTextBrowser>
#include <QEvent>
#include <QDialogButtonBox>
#include <QPushButton>
#include "qextendedspinbox.h"

ImageFormatTypeForm::ImageFormatTypeForm(ImageFormatType *imageFormat,
                                         QEbuMainWindow *mainWindow,
                                         QWidget *parent)
    : StackableWidget(mainWindow, parent)
{
    m_op = (imageFormat) ? Edit : Add;
    if (!imageFormat)
        m_imageFormat = new ImageFormatType;
    else
        m_imageFormat = imageFormat;
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *leftVLayout = new QVBoxLayout;
    {
        QGroupBox *group = new QGroupBox(tr("Image Format"));
        QFormLayout *form = new QFormLayout;
        m_editImageFormatId = new QLineEdit;
        form->addRow(tr("Id"), m_editImageFormatId);
        m_editImageFormatName = new QLineEdit;
        form->addRow(tr("Name"), m_editImageFormatName);
        m_editImageFormatDefinition = new QLineEdit;
        form->addRow(tr("Definition"), m_editImageFormatDefinition);
        group->setLayout(form);
        leftVLayout->addWidget(group);
    }
    {
        QGridLayout *gridLayout = new QGridLayout;
        m_checkRegionDelimX = new QCheckBox(tr("Region Delim X"));
        m_editRegionDelimX = new QUnsignedSpinBox;
        m_editRegionDelimX->setRange(qEbuLimits::getMinUInt(),
                                     qEbuLimits::getMaxUInt());
        gridLayout->addWidget(m_checkRegionDelimX, 0, 0);
        gridLayout->addWidget(m_editRegionDelimX, 0, 1);
        QObject::connect(m_editRegionDelimX, SIGNAL(valueChanged()),
                         this, SLOT(regionDelimXChanged()));
        m_checkRegionDelimY = new QCheckBox(tr("Region Delim Y"));
        m_editRegionDelimY = new QUnsignedSpinBox;
        m_editRegionDelimY->setRange(qEbuLimits::getMinUInt(),
                                     qEbuLimits::getMaxUInt());
        gridLayout->addWidget(m_checkRegionDelimY, 1, 0);
        gridLayout->addWidget(m_editRegionDelimY, 1, 1);
        QObject::connect(m_editRegionDelimY, SIGNAL(valueChanged()),
                         this, SLOT(regionDelimYChanged()));

        m_editWidth = new LengthTypeEditBox(m_imageFormat->width());
        m_editWidth->setLabel(tr("Width"));
        gridLayout->addWidget(m_editWidth, 2, 0, 1, 2);

        m_editHeight = new LengthTypeEditBox(m_imageFormat->height());
        m_editHeight->setLabel(tr("Height"));
        gridLayout->addWidget(m_editHeight, 3, 0, 1, 2);

        m_checkOrientation = new QCheckBox(tr("Orientation"));
        m_comboOrientation = new QComboBox;
        m_comboOrientation->insertItem(ImageFormatType::Landscape, tr("landscape"));
        m_comboOrientation->insertItem(ImageFormatType::Portrait, tr("portrait"));
        gridLayout->addWidget(m_checkOrientation, 4, 0);
        gridLayout->addWidget(m_comboOrientation, 4, 1);
        QObject::connect(m_comboOrientation, SIGNAL(currentIndexChanged(int)),
                         this, SLOT(orientationChanged()));
        leftVLayout->addLayout(gridLayout);
    }
    {
        QHBoxLayout *hl = new QHBoxLayout;
        hl->addWidget(new QLabel(tr("Technical attributes")));
        m_editTechnicalAttributes = new QLineEdit;
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
        leftVLayout->addLayout(hl);
    }
    mainHLayout->addLayout(leftVLayout);
    {
        m_listView = new ListView(tr("Image Encoding"));
        QObject::connect(m_listView->buttonAdd(), SIGNAL(clicked()),
                         this, SLOT(addClicked()));
        QObject::connect(m_listView->buttonEdit(), SIGNAL(clicked()),
                         this, SLOT(editClicked()));
        QObject::connect(m_listView->buttonRemove(), SIGNAL(clicked()),
                         this, SLOT(removeClicked()));
        mainHLayout->addWidget(m_listView);
    }
    this->setLayout(mainHLayout);

    // Event Filter
    m_textDocumentation->setText(tr("A description of image characteristics of the resource to provide technical information such as width, height, orientation, encoding."));
    m_editImageFormatId->installEventFilter(this);
    m_editImageFormatName->installEventFilter(this);
    m_editImageFormatDefinition->installEventFilter(this);
    m_editRegionDelimX->installEventFilter(this);
    m_editRegionDelimY->installEventFilter(this);
    m_editTechnicalAttributes->installEventFilter(this);
    m_editWidth->editUnit()->installEventFilter(this);
    m_editWidth->editValue()->installEventFilter(this);
    m_editHeight->editUnit()->installEventFilter(this);
    m_editHeight->editValue()->installEventFilter(this);
    m_comboOrientation->installEventFilter(this);
    m_listView->buttonAdd()->installEventFilter(this);

    // Set fields...
    if (m_op == Add)
        return;
    m_editImageFormatId->setText(m_imageFormat->imageFormatId());
    m_editImageFormatName->setText(m_imageFormat->imageFormatName());
    m_editImageFormatDefinition->setText(m_imageFormat->imageFormatDefinition());
    if (m_imageFormat->regionDelimX()) {
        m_checkRegionDelimX->setChecked(true);
        m_editRegionDelimX->setValue(*(m_imageFormat->regionDelimX()));
    }
    if (m_imageFormat->regionDelimY()) {
        m_checkRegionDelimY->setChecked(true);
        m_editRegionDelimY->setValue(*(m_imageFormat->regionDelimY()));
    }
    if (m_imageFormat->orientation()) {
        m_checkOrientation->setChecked(true);
        ImageFormatType::Orientation o = *(m_imageFormat->orientation());
        if (o == ImageFormatType::Portrait)
            m_comboOrientation->setCurrentIndex(ImageFormatType::Portrait);
        else
            m_comboOrientation->setCurrentIndex(ImageFormatType::Landscape);
    }
    if (m_imageFormat->technicalAttributes())
        m_editTechnicalAttributes->setText(m_imageFormat->technicalAttributes()->toString());
    int s = m_imageFormat->imageEncoding().size();
    for (int i=0; i < s; ++i) {
        m_listView->addItem(m_imageFormat->imageEncoding().at(i)->toString());
    }
}

QString ImageFormatTypeForm::toString()
{
    return QString(tr("Image Format"));
}

void ImageFormatTypeForm::applyClicked()
{
    m_imageFormat->setImageFormatId(m_editImageFormatId->text());
    m_imageFormat->setImageFormatName(m_editImageFormatName->text());
    m_imageFormat->setImageFormatDefinition(m_editImageFormatDefinition->text());

    if (m_checkRegionDelimX->isChecked())
        m_imageFormat->setRegionDelimX(m_editRegionDelimX->value());
    else
        m_imageFormat->clearRegionDelimX();

    if (m_checkRegionDelimY->isChecked())
        m_imageFormat->setRegionDelimY(m_editRegionDelimY->value());
    else
        m_imageFormat->clearRegionDelimY();

    m_imageFormat->setWidth(m_editWidth->lengthType());
    m_imageFormat->setHeight(m_editHeight->lengthType());

    if (m_checkOrientation->isChecked()) {
        ImageFormatType::Orientation o;
        if (m_comboOrientation->currentIndex() == ImageFormatType::Portrait)
            o = ImageFormatType::Portrait;
        else
            o = ImageFormatType::Landscape;
        m_imageFormat->setOrientation(o);
    } else {
        m_imageFormat->clearOrientation();
    }
    emit closed(m_op, QVarPtr<ImageFormatType>::asQVariant(m_imageFormat));
}

void ImageFormatTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_imageFormat;
        m_imageFormat = 0;
    }
    emit closed(m_op, QVarPtr<ImageFormatType>::asQVariant(m_imageFormat));
}

void ImageFormatTypeForm::addClicked()
{
    TypeGroupForm *form = new TypeGroupForm(0, mainWindow());
    form->addLinksMap(this->mainWindow()->getMap("ebu_VideoCompressionCodeCS")); //Autocompletion values
    form->setTitle(tr("Image Encoding"));
    form->setGeneralDoc(tr("The type group attributes provide the information on the encoding format"));
    form->setDefinitionDoc(tr("Free text for an optional definition.\nExample: 'standard file format for compressing pictures so they can be stored or sent by e-mail more easily. JPEG is an abbreviation for `Joint Photographic Experts Group'."));
    form->setLinkDoc(tr("A link to a classification scheme.<br/>Reference data:<br/><a href=\"http://www.ebu.ch/metadata/cs/web/ebu_VideoCompressionCodeCS_p.xml.htm\">ebu_ImageCompressionCodeCS</a>"));
    form->setLabelDoc(tr("Free text field.\nExample: JPEG."));
    QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(typeGroupFormClosed(Operation,QVariant)));
    mainWindow()->pushWidget(form);
}

void ImageFormatTypeForm::editClicked()
{
    int index = m_listView->selected();
    if (index < 0)
        return;
    TypeGroupForm *form = new TypeGroupForm(
                m_imageFormat->imageEncoding().at(index),
                mainWindow());
    form->setTitle(tr("Image Encoding"));
    form->setGeneralDoc(tr("The type group attributes provide the information on the encoding format"));
    form->setDefinitionDoc(tr("Free text for an optional definition.\nExample: 'standard file format for compressing pictures so they can be stored or sent by e-mail more easily. JPEG is an abbreviation for `Joint Photographic Experts Group'."));
    form->setLinkDoc(tr("A link to a classification scheme.<br/>Reference data:<br/><a href=\"http://www.ebu.ch/metadata/cs/web/ebu_VideoCompressionCodeCS_p.xml.htm\">ebu_ImageCompressionCodeCS</a>"));
    form->setLabelDoc(tr("Free text field.\nExample: JPEG."));
    form->addLinksMap(this->mainWindow()->getMap("ebu_VideoCompressionCodeCS")); //Autocompletion values
    QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(typeGroupFormClosed(Operation,QVariant)));
    mainWindow()->pushWidget(form);
}

void ImageFormatTypeForm::removeClicked()
{
    int index = m_listView->selected();
    if (index < 0)
        return;
    m_listView->removeAt(index);
    delete(m_imageFormat->imageEncoding().takeAt(index));
}

void ImageFormatTypeForm::regionDelimXChanged()
{
    m_checkRegionDelimX->setChecked(true);
}

void ImageFormatTypeForm::regionDelimYChanged()
{
    m_checkRegionDelimY->setChecked(true);
}

void ImageFormatTypeForm::orientationChanged()
{
    m_checkOrientation->setChecked(true);
}

void ImageFormatTypeForm::typeGroupFormClosed(Operation op, QVariant value)
{
    TypeGroup *typeGroup = QVarPtr<TypeGroup>::asPointer(value);
    if (!typeGroup)
        return;
    if (op == Add) {
        m_listView->addItem(typeGroup->toString());
        m_imageFormat->imageEncoding().append(typeGroup);
    } else if (op == Edit) {
        int row = m_imageFormat->imageEncoding().indexOf(typeGroup);
        m_listView->setItem(row, typeGroup->toString());
    }
}

void ImageFormatTypeForm::technicalAttributesRemoveClicked()
{
    if (!m_imageFormat->technicalAttributes())
        return;
    m_imageFormat->setTechnicalAttributes(0);
    m_editTechnicalAttributes->setText(tr("(none)"));
}

void ImageFormatTypeForm::technicalAttributesClicked()
{
    TechnicalAttributesForm *technicalAttributesForm = new TechnicalAttributesForm(
                m_imageFormat->technicalAttributes(),this->mainWindow());
    QObject::connect(technicalAttributesForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(technicalAttributesFormClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(technicalAttributesForm);
}

void ImageFormatTypeForm::technicalAttributesFormClosed(StackableWidget::Operation op, QVariant value)
{
    TechnicalAttributes *technicalAttributes = QVarPtr<TechnicalAttributes>::asPointer(value);
    if (!technicalAttributes)
        return;
    if (op == Add)
        m_imageFormat->setTechnicalAttributes(technicalAttributes);
    m_editTechnicalAttributes->setText(technicalAttributes->toString());
}

bool ImageFormatTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editImageFormatId )
            m_textDocumentation->setText(tr("An Identifier to identify a specific format in which the resource is available or has been published."));
        else if  (obj == (QObject*) m_editImageFormatName)
            m_textDocumentation->setText(tr("A name attributed to a particular format."));
        else if  (obj == (QObject*) m_editImageFormatDefinition)
            m_textDocumentation->setText(tr("A definition of the format information being provided either technical or editorial in nature."));
        else if (obj == (QObject*) m_editRegionDelimX)
            m_textDocumentation->setText(tr("The identification of a region in a document, an image or a video is done by defining the coordinates of the bottom left corner of the region. The region is defined from this point of reference using the width and height properties. regionDelimX is the coordinate on the horizontal axis and uses the same unit as the width attribute."));
        else if (obj == (QObject*) m_editRegionDelimY)
            m_textDocumentation->setText(tr("The identification of a region in a document, an image or a video is done by defining the coordinates of the bottom left corner of the region. The region is defined from this point of reference using the width and height properties. regionDelimY is the coordinate on the vertical axis uses the same unit as the height attribute."));
        else if (obj == (QObject*) m_editWidth->editUnit())
            m_textDocumentation->setText(tr("An attribute to specify the unit in which the width is expressed."));
        else if (obj == (QObject*) m_editWidth->editValue())
            m_textDocumentation->setText(tr("The width of the image or picture. Used as numerator to define the aspect ratio for video content."));
        else if (obj == (QObject*) m_editHeight->editUnit())
            m_textDocumentation->setText(tr("An attribute to specify the unit in which the height is expressed."));
        else if (obj == (QObject*) m_editHeight->editValue())
            m_textDocumentation->setText(tr("The height of the image or picture. Used as denominator to define the aspect ratio for video content."));
        else if (obj == (QObject*) m_editTechnicalAttributes)
            m_textDocumentation->setText(tr("An extension element to allowusers and implementers defining their own technical attributes."));
        else if (obj == (QObject*) m_comboOrientation)
            m_textDocumentation->setText(tr("To express the orientation of the image, i.e. 'portrait' or 'landscape'."));
        else if (obj == (QObject*) m_listView->buttonAdd())
            m_textDocumentation->setText(tr("Used to express the encoding parameters of the resource.\nExample: jpeg, tiff, H264 frame."));
    }
    return QObject::eventFilter(obj, event);
}
