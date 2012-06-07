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
    int s = m_imageFormat->imageEncoding().size();
    for (int i=0; i < s; ++i) {
        m_listView->addItem(m_imageFormat->imageEncoding().at(i)->toString());
    }
}

QString ImageFormatTypeForm::toString()
{
    return QString(tr("ImageFormatType"));
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
