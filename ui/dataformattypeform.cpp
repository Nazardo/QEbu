#include "dataformattypeform.h"
#include "../model/formattype.h"
#include "../model/typeconverter.h"
#include "listview.h"
#include "qvarptr.h"
#include "listview.h"
#include "captioningformattypeform.h"
#include "ancillarydataformattypeform.h"
#include "technicalattributesform.h"
#include <QPushButton>
#include <QButtonGroup>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QTextEdit>
#include <QEvent>

DataFormatTypeForm::DataFormatTypeForm(DataFormatType *dataFormat,
                                       QEbuMainWindow *mainWindow,
                                       QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (dataFormat) ? Edit : Add;
    if (!dataFormat)
        m_dataFormat = new DataFormatType;
    else
        m_dataFormat = dataFormat;
    //Layout
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *vl = new QVBoxLayout;
    {
        QFormLayout *fl = new QFormLayout;
        m_editDataFormatId = new QLineEdit;
        m_editDataFormatId->setValidator(TypeConverter::getUriValidator());
        fl->addRow(tr("Data format ID"), m_editDataFormatId);
        m_editDataFormatName = new QLineEdit;
        fl->addRow(tr("Data format name"), m_editDataFormatName);
        m_editDataFormatDefinition = new QLineEdit;
        fl->addRow(tr("Data format definition"), m_editDataFormatDefinition);
        vl->addLayout(fl);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_buttonCaptioningFormat = new QPushButton(">>");
        fl->addRow(tr("Captioning format"), m_buttonCaptioningFormat);
        QObject::connect(m_buttonCaptioningFormat, SIGNAL(toggled(bool)),
                         this, SLOT(captioningFormatChecked(bool)));
        m_buttonAncillaryDataFormat = new QPushButton(">>");
        fl->addRow(tr("Ancillary data format"), m_buttonAncillaryDataFormat);
        QObject::connect(m_buttonAncillaryDataFormat, SIGNAL(toggled(bool)),
                         this, SLOT(ancillaryDataFormatChecked(bool)));
        m_buttonTechnicalAttributes = new QPushButton(">>");
        fl->addRow(tr("Technical attributes"), m_buttonTechnicalAttributes);
        QObject::connect(m_buttonTechnicalAttributes, SIGNAL(toggled(bool)),
                         this, SLOT(technicalAttributesChecked(bool)));
        vl->addLayout(fl);
        QButtonGroup *group = new QButtonGroup(this);
        m_buttonCaptioningFormat->setCheckable(true);
        group->addButton(m_buttonCaptioningFormat);
        m_buttonAncillaryDataFormat->setCheckable(true);
        group->addButton(m_buttonAncillaryDataFormat);
        m_buttonTechnicalAttributes->setCheckable(true);
        group->addButton(m_buttonTechnicalAttributes);
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

    //Set data fields...
    m_textDocumentation->setText(tr("To provide information on captioning and ancillary data formats optionally used in the resource"));
    m_editDataFormatId->setText(m_dataFormat->dataFormatId());
    m_editDataFormatName->setText(m_dataFormat->dataFormatName());
    m_editDataFormatDefinition->setText(m_dataFormat->dataFormatDefinition());
    m_editDataFormatId->installEventFilter(this);
    m_editDataFormatName->installEventFilter(this);
    m_editDataFormatDefinition->installEventFilter(this);
    m_buttonCaptioningFormat->installEventFilter(this);
    m_buttonAncillaryDataFormat->installEventFilter(this);
    m_buttonTechnicalAttributes->installEventFilter(this);
    m_buttonCaptioningFormat->setChecked(true);
}

QString DataFormatTypeForm::toString()
{
    return QString(tr("Data Format"));
}

void DataFormatTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_dataFormat;
        m_dataFormat = 0;
    }
    emit closed(m_op, QVarPtr<DataFormatType>::asQVariant(m_dataFormat));
}

void DataFormatTypeForm::applyClicked()
{
    m_dataFormat->setDataFormatId(m_editDataFormatId->text());
    m_dataFormat->setDataFormatName(m_editDataFormatName->text());
    m_dataFormat->setDataFormatDefinition(m_editDataFormatDefinition->text());
    emit closed(m_op, QVarPtr<DataFormatType>::asQVariant(m_dataFormat));
}

void DataFormatTypeForm::addClicked()
{
    switch (m_currentEditMode) {
    case CaptioningFormat:
    {
        CaptioningFormatTypeForm *captioningFormatForm = new CaptioningFormatTypeForm(0, this->mainWindow());
        QObject::connect(captioningFormatForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(captioningFormatFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(captioningFormatForm);
    }
        break;
    case AncillaryDataFormat:
    {
        AncillaryDataFormatTypeForm *ancillaryDataFormatForm = new AncillaryDataFormatTypeForm(0, this->mainWindow());
        QObject::connect(ancillaryDataFormatForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(ancillaryDataFormatFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(ancillaryDataFormatForm);
    }
        break;
    case TechnicalAttributesMode:
    {
        TechnicalAttributesForm *technicalAttributesForm = new TechnicalAttributesForm(0, this->mainWindow());
        QObject::connect(technicalAttributesForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(technicalAttributesFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(technicalAttributesForm);
    }
        break;
    }
}

void DataFormatTypeForm::editClicked()
{
    int index = m_listView->selected();
    if (index < 0)
        return;
    switch (m_currentEditMode) {
    case CaptioningFormat:
    {
        CaptioningFormatTypeForm *captioningFormatForm = new CaptioningFormatTypeForm(
                    m_dataFormat->captioningFormat().at(index), this->mainWindow());
        QObject::connect(captioningFormatForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(captioningFormatFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(captioningFormatForm);
    }
        break;
    case AncillaryDataFormat:
    {
        AncillaryDataFormatTypeForm *ancillaryDataFormatForm = new AncillaryDataFormatTypeForm(
                    m_dataFormat->ancillaryDataFormat().at(index), this->mainWindow());
        QObject::connect(ancillaryDataFormatForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(ancillaryDataFormatFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(ancillaryDataFormatForm);
    }
        break;
    case TechnicalAttributesMode:
    {
        TechnicalAttributesForm *technicalAttributesForm = new TechnicalAttributesForm(
                    m_dataFormat->technicalAttributes(), this->mainWindow());
        QObject::connect(technicalAttributesForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(organisationDetailsFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(technicalAttributesForm);
    }
        break;
    }
}

void DataFormatTypeForm::removeClicked()
{
    int row = m_listView->selected();
    if (row < 0)
        return;
    m_listView->removeAt(row);
    switch (m_currentEditMode) {
    case CaptioningFormat:
    {
        delete(m_dataFormat->captioningFormat().takeAt(row));
    }
        break;
    case AncillaryDataFormat:
    {
        delete(m_dataFormat->ancillaryDataFormat().takeAt(row));
    }
        break;
    case TechnicalAttributesMode:
    {
        m_dataFormat->setTechnicalAttributes(0);
        m_listView->buttonAdd()->setEnabled(true);
    }
        break;
    }
}

void DataFormatTypeForm::captioningFormatChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = CaptioningFormat;
    updateListAndButtons();
    int s = m_dataFormat->captioningFormat().size();
    for (int i=0; i < s; ++i) {
        CaptioningFormatType *cft = m_dataFormat->captioningFormat().at(i);
        if (!cft)
            continue;
        m_listView->addItem(cft->toString());
    }
}

void DataFormatTypeForm::ancillaryDataFormatChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = AncillaryDataFormat;
    updateListAndButtons();
    int s = m_dataFormat->ancillaryDataFormat().size();
    for (int i=0; i < s; ++i) {
        AncillaryDataFormatType *adft = m_dataFormat->ancillaryDataFormat().at(i);
        if (!adft)
            continue;
        m_listView->addItem(adft->toString());
    }
}

void DataFormatTypeForm::technicalAttributesChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = TechnicalAttributesMode;
    updateListAndButtons();
    TechnicalAttributes *ta = m_dataFormat->technicalAttributes();
    if (ta) {
        m_listView->addItem(ta->toString());
        m_listView->enableAdd(false);
    }
}

void DataFormatTypeForm::captioningFormatFormClosed(StackableWidget::Operation op, QVariant value)
{
    CaptioningFormatType *captioningFormat = QVarPtr<CaptioningFormatType>::asPointer(value);
    if(!captioningFormat)
        return;
    if(op == Add) {
        m_listView->addItem(captioningFormat->toString());
        m_dataFormat->captioningFormat().append(captioningFormat);
    } else if(op == Edit) {
        int row = m_dataFormat->captioningFormat().indexOf(captioningFormat);
        m_listView->setItem(row, captioningFormat->toString());
    }
}

void DataFormatTypeForm::ancillaryDataFormatFormClosed(Operation op, QVariant value)
{
    AncillaryDataFormatType *ancillaryDataFormat = QVarPtr<AncillaryDataFormatType>::asPointer(value);
    if (!ancillaryDataFormat)
        return;
    if (op == Add) {
        m_listView->addItem(ancillaryDataFormat->toString());
        m_dataFormat->ancillaryDataFormat().append(ancillaryDataFormat);
    } else if (op == Edit) {
        int row = m_dataFormat->ancillaryDataFormat().indexOf(ancillaryDataFormat);
        m_listView->setItem(row, ancillaryDataFormat->toString());
    }
}

void DataFormatTypeForm::technicalAttributesFormClosed(StackableWidget::Operation op, QVariant value)
{
    TechnicalAttributes *technicalAttributes = QVarPtr<TechnicalAttributes>::asPointer(value);
    if(!technicalAttributes)
        return;
    if(op == Add) {
        m_listView->addItem(technicalAttributes->toString());
        m_dataFormat->setTechnicalAttributes(technicalAttributes);
        m_listView->enableAdd(false);
    } else if(op == Edit) {
        int row = 0;
        m_listView->setItem(row, technicalAttributes->toString());
    }
}

void DataFormatTypeForm::updateListAndButtons()
{
    QString title;
    if (m_currentEditMode == CaptioningFormat)
        title = tr("Captioning format");
    else if (m_currentEditMode == AncillaryDataFormat)
        title = tr("Ancillary data format");
    else if (m_currentEditMode == TechnicalAttributesMode)
        title = tr("Technical attributes");
    m_listView->setTitle(title);
    m_listView->clear();
}

bool DataFormatTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if ( obj == (QObject*) m_editDataFormatId)
            m_textDocumentation->setText(tr("An Identifier to identify a specific format in which the resource is available or has been published."));
        else if ( obj == (QObject*) m_editDataFormatName )
            m_textDocumentation->setText(tr("A name attributed to a particular format."));
        else if  (obj == (QObject*) m_editDataFormatDefinition)
            m_textDocumentation->setText(tr("A definition of the format information being provided either technical or editorial in nature."));
        else if  (obj == (QObject*) m_buttonCaptioningFormat)
            m_textDocumentation->setText(tr("Information on the captioning format used in the media resource."));
        else if  (obj == (QObject*) m_buttonAncillaryDataFormat)
            m_textDocumentation->setText(tr("Information on ancillary data available in the media resource."));
        else if  (obj == (QObject*) m_buttonTechnicalAttributes)
            m_textDocumentation->setText(tr("An extension element to allow users and implementers defining their own technical attributes."));
    }
    return QObject::eventFilter(obj, event);
}
