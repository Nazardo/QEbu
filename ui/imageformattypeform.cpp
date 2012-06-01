#include "imageformattypeform.h"
#include "lengthtypeeditbox.h"
#include "technicalattributesform.h"
#include "qvarptr.h"
#include "listview.h"
#include "typegroupform.h"
#include "../model/formattype.h"
#include "../model/qebulimits.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QSpinBox>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QPushButton>

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
        m_editRegionDelimX = new QSpinBox;
        m_editRegionDelimX->setRange(qEbuLimits::getMinUInt(),
                                     qEbuLimits::getMaxUInt());
        gridLayout->addWidget(m_checkRegionDelimX, 0, 0);
        gridLayout->addWidget(m_editRegionDelimX, 0, 1);
        QObject::connect(m_editRegionDelimX, SIGNAL(valueChanged(int)),
                         this, SLOT(regionDelimXChanged()));
        m_checkRegionDelimY = new QCheckBox(tr("Region Delim Y"));
        m_editRegionDelimY = new QSpinBox;
        m_editRegionDelimY->setRange(qEbuLimits::getMinUInt(),
                                     qEbuLimits::getMaxUInt());
        gridLayout->addWidget(m_checkRegionDelimY, 1, 0);
        gridLayout->addWidget(m_editRegionDelimY, 1, 1);
        QObject::connect(m_editRegionDelimY, SIGNAL(valueChanged(int)),
                         this, SLOT(regionDelimYChanged()));

        m_editWidth = new LengthTypeEditBox(m_imageFormat->width());
        gridLayout->addWidget(m_editWidth, 2, 0, 1, 2);

        m_editHeight = new LengthTypeEditBox(m_imageFormat->height());
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
        QDialogButtonBox *dialogButtonBox = new QDialogButtonBox(
                    QDialogButtonBox::Apply | QDialogButtonBox::Cancel,
                    Qt::Horizontal);
        leftVLayout->addWidget(dialogButtonBox, 0, Qt::AlignLeft);
        QObject::connect(dialogButtonBox->button(QDialogButtonBox::Apply),
                         SIGNAL(clicked()), this, SLOT(applyClicked()));
        QObject::connect(dialogButtonBox, SIGNAL(rejected()),
                         this, SLOT(applyClicked()));
    }
    mainHLayout->addLayout(leftVLayout);
    {
        QVBoxLayout *rightVLayout = new QVBoxLayout;
        m_listView = new ListView(tr("Image Encoding"));
        QObject::connect(m_listView->buttonAdd(), SIGNAL(clicked()),
                         this, SLOT(addClicked()));
        QObject::connect(m_listView->buttonEdit(), SIGNAL(clicked()),
                         this, SLOT(editClicked()));
        QObject::connect(m_listView->buttonRemove(), SIGNAL(clicked()),
                         this, SLOT(removeClicked()));
        rightVLayout->addWidget(m_listView);

        m_buttonTechnicalAttributes = new QPushButton(tr("Technical Attributes"));
        QObject::connect(m_buttonTechnicalAttributes, SIGNAL(clicked()),
                         this, SLOT(technicalAttributesClicked()));
        rightVLayout->addWidget(m_buttonTechnicalAttributes);
        mainHLayout->addLayout(rightVLayout);
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

void ImageFormatTypeForm::technicalAttributesClicked()
{
    TechnicalAttributesForm *form = new TechnicalAttributesForm(
                m_imageFormat->technicalAttributes(), mainWindow());
    QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(technicalAttributesFormClosed(Operation,QVariant)));
    mainWindow()->pushWidget(form);
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

void ImageFormatTypeForm::technicalAttributesFormClosed(StackableWidget::Operation op, QVariant value)
{
    TechnicalAttributes *technicalAttributes = QVarPtr<TechnicalAttributes>::asPointer(value);
    if (!technicalAttributes)
        return;
    if (op == Add) {
        m_imageFormat->setTechnicalAttributes(technicalAttributes);
    }
    // Nothing to do for m_op == Edit
}
