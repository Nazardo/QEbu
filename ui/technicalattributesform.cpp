#include "technicalattributesform.h"
#include "../model/technicalattributes.h"
#include "listview.h"
#include "stringform.h"
#include "int8form.h"
#include "int16form.h"
#include "int32form.h"
#include "int64form.h"
#include "uint8form.h"
#include "uint16form.h"
#include "uint32form.h"
#include "uint64form.h"
#include "booleanform.h"
#include "floatform.h"
#include "technicalattributerationaltypeform.h"
#include "technicalattributeuritypeform.h"
#include "qvarptr.h"
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QLayout>
#include <QEvent>
#include <QTextBrowser>

TechnicalAttributesForm::TechnicalAttributesForm(TechnicalAttributes *technicalAttributes,
                                                 QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (technicalAttributes) ? Edit : Add;
    if (!technicalAttributes)
        m_technicalAttributes = new TechnicalAttributes;
    else
        m_technicalAttributes = technicalAttributes;

    // Layout
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;
    {
        QHBoxLayout *hL = new QHBoxLayout;
        hL->addWidget(new QLabel("String", this));
        m_buttonString = new QPushButton(">>");
        m_buttonString->installEventFilter(this);
        hL->addWidget(m_buttonString);
        l->addLayout(hL);
        m_buttonString->setCheckable(true);
        QObject::connect(m_buttonString, SIGNAL(toggled(bool)), this, SLOT(stringFormChecked(bool)));
    }
    {
        QHBoxLayout *hL = new QHBoxLayout;
        hL->addWidget(new QLabel("Byte", this));
        m_buttonByte = new QPushButton(">>");
        m_buttonByte->installEventFilter(this);
        hL->addWidget(m_buttonByte);
        l->addLayout(hL);
        m_buttonByte->setCheckable(true);
        QObject::connect(m_buttonByte, SIGNAL(toggled(bool)), this, SLOT(byteFormChecked(bool)));
    }
    {
        QHBoxLayout *hL = new QHBoxLayout;
        hL->addWidget(new QLabel("Short", this));
        m_buttonShort = new QPushButton(">>");
        m_buttonShort->installEventFilter(this);
        hL->addWidget(m_buttonShort);
        l->addLayout(hL);
        m_buttonShort->setCheckable(true);
        QObject::connect(m_buttonShort, SIGNAL(toggled(bool)), this, SLOT(shortFormChecked(bool)));
    }
    {
        QHBoxLayout *hL = new QHBoxLayout;
        hL->addWidget(new QLabel("Integer", this));
        m_buttonInteger = new QPushButton(">>");
        m_buttonInteger->installEventFilter(this);
        hL->addWidget(m_buttonInteger);
        l->addLayout(hL);
        m_buttonInteger->setCheckable(true);
        QObject::connect(m_buttonInteger, SIGNAL(toggled(bool)), this, SLOT(integerFormChecked(bool)));
    }
    {
        QHBoxLayout *hL = new QHBoxLayout;
        hL->addWidget(new QLabel("Long", this));
        m_buttonLong = new QPushButton(">>");
        m_buttonLong->installEventFilter(this);
        hL->addWidget(m_buttonLong);
        l->addLayout(hL);
        m_buttonLong->setCheckable(true);
        QObject::connect(m_buttonLong, SIGNAL(toggled(bool)), this, SLOT(longFormChecked(bool)));
    }
    {
        QHBoxLayout *hL = new QHBoxLayout;
        hL->addWidget(new QLabel("UnsignedByte", this));
        m_buttonUnsignedByte = new QPushButton(">>");
        m_buttonUnsignedByte->installEventFilter(this);
        hL->addWidget(m_buttonUnsignedByte);
        l->addLayout(hL);
        m_buttonUnsignedByte->setCheckable(true);
        QObject::connect(m_buttonUnsignedByte, SIGNAL(toggled(bool)), this, SLOT(unsignedByteFormChecked(bool)));
    }
    {
        QHBoxLayout *hL = new QHBoxLayout;
        hL->addWidget(new QLabel("UnsignedShort", this));
        m_buttonUnsignedShort = new QPushButton(">>");
        m_buttonUnsignedShort->installEventFilter(this);
        hL->addWidget(m_buttonUnsignedShort);
        l->addLayout(hL);
        m_buttonUnsignedShort->setCheckable(true);
        QObject::connect(m_buttonUnsignedShort, SIGNAL(toggled(bool)), this, SLOT(unsignedShortFormChecked(bool)));
    }
    {
        QHBoxLayout *hL = new QHBoxLayout;
        hL->addWidget(new QLabel("UnsignedInteger", this));
        m_buttonUnsignedInteger = new QPushButton(">>");
        m_buttonUnsignedInteger->installEventFilter(this);
        hL->addWidget(m_buttonUnsignedInteger);
        l->addLayout(hL);
        m_buttonUnsignedInteger->setCheckable(true);
        QObject::connect(m_buttonUnsignedInteger, SIGNAL(toggled(bool)), this, SLOT(unsignedIntegerFormChecked(bool)));
    }
    {
        QHBoxLayout *hL = new QHBoxLayout;
        hL->addWidget(new QLabel("UnsignedLong", this));
        m_buttonUnsignedLong = new QPushButton(">>");
        m_buttonUnsignedLong->installEventFilter(this);
        hL->addWidget(m_buttonUnsignedLong);
        l->addLayout(hL);
        m_buttonUnsignedLong->setCheckable(true);
        QObject::connect(m_buttonUnsignedLong, SIGNAL(toggled(bool)), this, SLOT(unsignedLongFormChecked(bool)));
    }
    {
        QHBoxLayout *hL = new QHBoxLayout;
        hL->addWidget(new QLabel("Boolean", this));
        m_buttonBoolean = new QPushButton(">>");
        m_buttonBoolean->installEventFilter(this);
        hL->addWidget(m_buttonBoolean);
        l->addLayout(hL);
        m_buttonBoolean->setCheckable(true);
        QObject::connect(m_buttonBoolean, SIGNAL(toggled(bool)), this, SLOT(booleanFormChecked(bool)));
    }
    {
        QHBoxLayout *hL = new QHBoxLayout;
        hL->addWidget(new QLabel("Float", this));
        m_buttonFloat = new QPushButton(">>");
        m_buttonFloat->installEventFilter(this);
        hL->addWidget(m_buttonFloat);
        l->addLayout(hL);
        m_buttonFloat->setCheckable(true);
        QObject::connect(m_buttonFloat, SIGNAL(toggled(bool)), this, SLOT(floatFormChecked(bool)));
    }
    {
        QHBoxLayout *hL = new QHBoxLayout;
        hL->addWidget(new QLabel("Rational", this));
        m_buttonRational = new QPushButton(">>");
        m_buttonRational->installEventFilter(this);
        hL->addWidget(m_buttonRational);
        l->addLayout(hL);
        m_buttonRational->setCheckable(true);
        QObject::connect(m_buttonRational, SIGNAL(toggled(bool)), this, SLOT(rationalFormChecked(bool)));
    }
    {
        QHBoxLayout *hL = new QHBoxLayout;
        hL->addWidget(new QLabel("Uri", this));
        m_buttonUri = new QPushButton(">>");
        m_buttonUri->installEventFilter(this);
        hL->addWidget(m_buttonUri);
        l->addLayout(hL);
        m_buttonUri->setCheckable(true);
        QObject::connect(m_buttonUri, SIGNAL(toggled(bool)), this, SLOT(uriFormChecked(bool)));
    }
    {
        QButtonGroup *group = new QButtonGroup(this);
        group->addButton(m_buttonString);
        group->addButton(m_buttonByte);
        group->addButton(m_buttonShort);
        group->addButton(m_buttonInteger);
        group->addButton(m_buttonLong);
        group->addButton(m_buttonUnsignedByte);
        group->addButton(m_buttonUnsignedShort);
        group->addButton(m_buttonUnsignedInteger);
        group->addButton(m_buttonUnsignedLong);
        group->addButton(m_buttonBoolean);
        group->addButton(m_buttonFloat);
        group->addButton(m_buttonRational);
        group->addButton(m_buttonUri);
    }
    mainHLayout->addLayout(l);
    m_textDocumentation->setText(tr("Allows users / implementers to define their own technical parameters."));
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

    // Set data fields...
    m_buttonString->setChecked(true);
}

QString TechnicalAttributesForm::toString()
{
    return QString(tr("Technical Attributes"));
}

void TechnicalAttributesForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_technicalAttributes;
        m_technicalAttributes = 0;
    }
    emit closed(m_op, QVarPtr<TechnicalAttributes>::asQVariant(m_technicalAttributes));
}

void TechnicalAttributesForm::applyClicked()
{
    emit closed(m_op, QVarPtr<TechnicalAttributes>::asQVariant(m_technicalAttributes));
}

void TechnicalAttributesForm::addClicked()
{
    switch (m_currentEditMode) {
    case StringMode:
    {
        StringForm *form = new StringForm(0, this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(stringFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case Byte:
    {
        Int8Form *form = new Int8Form(0, this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(byteFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case Short:
    {
        Int16Form *form = new Int16Form(0, this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(shortFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case Integer:
    {
        Int32Form *form = new Int32Form(0, this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(integerFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case Long:
    {
        Int64Form *form = new Int64Form(0, this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(longFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case UnsignedByte:
    {
        Uint8Form *form = new Uint8Form(0, this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(unsignedByteFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case UnsignedShort:
    {
        Uint16Form *form = new Uint16Form(0, this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(unsignedShortFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case UnsignedInteger:
    {
        Uint32Form *form = new Uint32Form(0, this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(unsignedIntegerFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case UnsignedLong:
    {
        Uint64Form *form = new Uint64Form(0, this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(unsignedLongFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case BooleanMode:
    {
        BooleanForm *form = new BooleanForm(0, this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(booleanFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case FloatMode:
    {
        FloatForm *form = new FloatForm(0, this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(floatFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case Rational:
    {
        TechnicalAttributeRationalTypeForm *form =
                new TechnicalAttributeRationalTypeForm(0, this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(rationalFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case Uri:
    {
        TechicalAttributeUriTypeForm *form =
                new TechicalAttributeUriTypeForm(0, this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(uriFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    }
}

void TechnicalAttributesForm::editClicked()
{
    int index = m_listView->selected();
    if (index < 0)
        return;
    switch (m_currentEditMode) {
    case StringMode:
    {
        StringForm *form = new StringForm(m_technicalAttributes->technicalAttributeString().at(index), this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(stringFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case Byte:
    {
        Int8Form *form = new Int8Form(m_technicalAttributes->technicalAttributeByte().at(index), this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(byteFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case Short:
    {
        Int16Form *form = new Int16Form(m_technicalAttributes->technicalAttributeShort().at(index), this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(shortFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case Integer:
    {
        Int32Form *form = new Int32Form(m_technicalAttributes->technicalAttributeInteger().at(index), this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(integerFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case Long:
    {
        Int64Form *form = new Int64Form(m_technicalAttributes->technicalAttributeLong().at(index), this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(longFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case UnsignedByte:
    {
        Uint8Form *form = new Uint8Form(m_technicalAttributes->technicalAttributeUnsignedByte().at(index), this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(unsignedbyteFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case UnsignedShort:
    {
        Uint16Form *form = new Uint16Form(m_technicalAttributes->technicalAttributeUnsignedShort().at(index), this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(unsignedShortFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case UnsignedInteger:
    {
        Uint32Form *form = new Uint32Form(m_technicalAttributes->technicalAttributeUnsignedInteger().at(index), this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(unsignedIntegerFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case UnsignedLong:
    {
        Uint64Form *form = new Uint64Form(m_technicalAttributes->technicalAttributeUnsignedLong().at(index), this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(unsignedLongFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case BooleanMode:
    {
        BooleanForm *form = new BooleanForm(m_technicalAttributes->technicalAttributeBoolean().at(index), this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(booleanFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case FloatMode:
    {
        FloatForm *form = new FloatForm(m_technicalAttributes->technicalAttributeFloat().at(index), this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(floatFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case Rational:
    {
        TechnicalAttributeRationalTypeForm *form = new TechnicalAttributeRationalTypeForm(
                    m_technicalAttributes->technicalAttributeRational().at(index), this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(rationalFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    case Uri:
    {
        TechicalAttributeUriTypeForm *form = new TechicalAttributeUriTypeForm(
                    m_technicalAttributes->technicalAttributeUri().at(index), this->mainWindow());
        QObject::connect(form, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(uriFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(form);
    }
        break;
    }
}

void TechnicalAttributesForm::removeClicked()
{
    int row = m_listView->selected();
    if (row < 0)
        return;
    m_listView->removeAt(row);
    switch (m_currentEditMode) {
    case StringMode:
    {
        delete(m_technicalAttributes->technicalAttributeString().takeAt(row));
    }
        break;
    case Byte:
    {
        delete(m_technicalAttributes->technicalAttributeByte().takeAt(row));
    }
        break;
    case Short:
    {
        delete(m_technicalAttributes->technicalAttributeShort().takeAt(row));
    }
        break;
    case Integer:
    {
        delete(m_technicalAttributes->technicalAttributeInteger().takeAt(row));
    }
        break;
    case Long:
    {
        delete(m_technicalAttributes->technicalAttributeLong().takeAt(row));
    }
        break;
    case UnsignedByte:
    {
        delete(m_technicalAttributes->technicalAttributeUnsignedByte().takeAt(row));
    }
        break;
    case UnsignedShort:
    {
        delete(m_technicalAttributes->technicalAttributeUnsignedShort().takeAt(row));
    }
        break;
    case UnsignedInteger:
    {
        delete(m_technicalAttributes->technicalAttributeUnsignedInteger().takeAt(row));
    }
        break;
    case UnsignedLong:
    {
        delete(m_technicalAttributes->technicalAttributeUnsignedLong().takeAt(row));
    }
        break;
    case BooleanMode:
    {
        delete(m_technicalAttributes->technicalAttributeBoolean().takeAt(row));
    }
        break;
    case FloatMode:
    {
        delete(m_technicalAttributes->technicalAttributeFloat().takeAt(row));
    }
        break;
    case Rational:
    {
        delete(m_technicalAttributes->technicalAttributeRational().takeAt(row));
    }
        break;
    case Uri:
    {
        delete(m_technicalAttributes->technicalAttributeUri().takeAt(row));
    }
        break;

    }
}

void TechnicalAttributesForm::stringFormChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = StringMode;
    updateListAndButtons();
    int s = m_technicalAttributes->technicalAttributeString().size();
    for (int i=0; i < s; ++i) {
        String *item = m_technicalAttributes->technicalAttributeString().at(i);
        if (!item)
            continue;
        m_listView->addItem(item->toString());
    }
}

void TechnicalAttributesForm::byteFormChecked(bool checked)
{
    if (!checked)
        return;
     m_currentEditMode = Byte;
     updateListAndButtons();
     int s = m_technicalAttributes->technicalAttributeByte().size();
     for (int i=0; i < s; ++i) {
         Int8 *item = m_technicalAttributes->technicalAttributeByte().at(i);
         if (!item)
             continue;
         m_listView->addItem(item->toString());
     }
}

void TechnicalAttributesForm::shortFormChecked(bool checked)
{
    if (!checked)
        return;
     m_currentEditMode = Short;
     updateListAndButtons();
     int s = m_technicalAttributes->technicalAttributeShort().size();
     for (int i=0; i < s; ++i) {
         Int16 *item = m_technicalAttributes->technicalAttributeShort().at(i);
         if (!item)
             continue;
         m_listView->addItem(item->toString());
     }
}

void TechnicalAttributesForm::integerFormChecked(bool checked)
{
    if (!checked)
        return;
     m_currentEditMode = Integer;
     updateListAndButtons();
     int s = m_technicalAttributes->technicalAttributeInteger().size();
     for (int i=0; i < s; ++i) {
         Int32 *item = m_technicalAttributes->technicalAttributeInteger().at(i);
         if (!item)
             continue;
         m_listView->addItem(item->toString());
     }
}

void TechnicalAttributesForm::longFormChecked(bool checked)
{
    if (!checked)
        return;
     m_currentEditMode = Long;
     updateListAndButtons();
     int s = m_technicalAttributes->technicalAttributeLong().size();
     for (int i=0; i < s; ++i) {
         Int64 *item = m_technicalAttributes->technicalAttributeLong().at(i);
         if (!item)
             continue;
         m_listView->addItem(item->toString());
     }
}

void TechnicalAttributesForm::unsignedByteFormChecked(bool checked)
{
    if (!checked)
        return;
     m_currentEditMode = UnsignedByte;
     updateListAndButtons();
     int s = m_technicalAttributes->technicalAttributeUnsignedByte().size();
     for (int i=0; i < s; ++i) {
         UInt8 *item = m_technicalAttributes->technicalAttributeUnsignedByte().at(i);
         if (!item)
             continue;
         m_listView->addItem(item->toString());
     }
}

void TechnicalAttributesForm::unsignedShortFormChecked(bool checked)
{
    if (!checked)
        return;
     m_currentEditMode = UnsignedShort;
     updateListAndButtons();
     int s = m_technicalAttributes->technicalAttributeUnsignedShort().size();
     for (int i=0; i < s; ++i) {
         UInt16 *item = m_technicalAttributes->technicalAttributeUnsignedShort().at(i);
         if (!item)
             continue;
         m_listView->addItem(item->toString());
     }
}

void TechnicalAttributesForm::unsignedIntegerFormChecked(bool checked)
{
    if (!checked)
        return;
     m_currentEditMode = UnsignedInteger;
     updateListAndButtons();
     int s = m_technicalAttributes->technicalAttributeUnsignedInteger().size();
     for (int i=0; i < s; ++i) {
         UInt32 *item = m_technicalAttributes->technicalAttributeUnsignedInteger().at(i);
         if (!item)
             continue;
         m_listView->addItem(item->toString());
     }
}

void TechnicalAttributesForm::unsignedLongFormChecked(bool checked)
{
    if (!checked)
        return;
     m_currentEditMode = UnsignedLong;
     updateListAndButtons();
     int s = m_technicalAttributes->technicalAttributeUnsignedLong().size();
     for (int i=0; i < s; ++i) {
         UInt64 *item = m_technicalAttributes->technicalAttributeUnsignedLong().at(i);
         if (!item)
             continue;
         m_listView->addItem(item->toString());
     }
}

void TechnicalAttributesForm::booleanFormChecked(bool checked)
{
    if (!checked)
        return;
     m_currentEditMode = BooleanMode;
     updateListAndButtons();
     int s = m_technicalAttributes->technicalAttributeBoolean().size();
     for (int i=0; i < s; ++i) {
         Boolean *item = m_technicalAttributes->technicalAttributeBoolean().at(i);
         if (!item)
             continue;
         m_listView->addItem(item->toString());
     }
}

void TechnicalAttributesForm::floatFormChecked(bool checked)
{
    if (!checked)
        return;
     m_currentEditMode = FloatMode;
     updateListAndButtons();
     int s = m_technicalAttributes->technicalAttributeFloat().size();
     for (int i=0; i < s; ++i) {
         Float *item = m_technicalAttributes->technicalAttributeFloat().at(i);
         if (!item)
             continue;
         m_listView->addItem(item->toString());
     }
}

void TechnicalAttributesForm::rationalFormChecked(bool checked)
{
    if (!checked)
        return;
     m_currentEditMode = Rational;
     updateListAndButtons();
     int s = m_technicalAttributes->technicalAttributeRational().size();
     for (int i=0; i < s; ++i) {
         TechnicalAttributeRationalType *item =
                 m_technicalAttributes->technicalAttributeRational().at(i);
         if (!item)
             continue;
         m_listView->addItem(item->toString());
     }
}

void TechnicalAttributesForm::uriFormChecked(bool checked)
{
    if (!checked)
        return;
     m_currentEditMode = Uri;
     updateListAndButtons();
     int s = m_technicalAttributes->technicalAttributeUri().size();
     for (int i=0; i < s; ++i) {
         TechnicalAttributeUriType *item =
                 m_technicalAttributes->technicalAttributeUri().at(i);
         if (!item)
             continue;
         m_listView->addItem(item->toString());
     }
}

void TechnicalAttributesForm::stringFormClosed(Operation op, QVariant value)
{
    String *item = QVarPtr<String>::asPointer(value);
    if(!item)
        return;
    if(op == Add) {
        m_listView->addItem(item->toString());
        m_technicalAttributes->technicalAttributeString().append(item);
    } else if(op == Edit) {
        int row = m_technicalAttributes->technicalAttributeString().indexOf(item);
        m_listView->setItem(row, item->toString());
    }
}

void TechnicalAttributesForm::byteFormClosed(Operation op, QVariant value)
{
    Int8 *item = QVarPtr<Int8>::asPointer(value);
    if(!item)
        return;
    if(op == Add) {
        m_listView->addItem(item->toString());
        m_technicalAttributes->technicalAttributeByte().append(item);
    } else if(op == Edit) {
        int row = m_technicalAttributes->technicalAttributeByte().indexOf(item);
        m_listView->setItem(row, item->toString());
    }
}

void TechnicalAttributesForm::shortFormClosed(Operation op, QVariant value)
{
    Int16 *item = QVarPtr<Int16>::asPointer(value);
    if(!item)
        return;
    if(op == Add) {
        m_listView->addItem(item->toString());
        m_technicalAttributes->technicalAttributeShort().append(item);
    } else if(op == Edit) {
        int row = m_technicalAttributes->technicalAttributeShort().indexOf(item);
        m_listView->setItem(row, item->toString());
    }
}

void TechnicalAttributesForm::integerFormClosed(Operation op, QVariant value)
{
    Int32 *item = QVarPtr<Int32>::asPointer(value);
    if(!item)
        return;
    if(op == Add) {
        m_listView->addItem(item->toString());
        m_technicalAttributes->technicalAttributeInteger().append(item);
    } else if(op == Edit) {
        int row = m_technicalAttributes->technicalAttributeInteger().indexOf(item);
        m_listView->setItem(row, item->toString());
    }
}

void TechnicalAttributesForm::longFormClosed(Operation op, QVariant value)
{
    Int64 *item = QVarPtr<Int64>::asPointer(value);
    if(!item)
        return;
    if(op == Add) {
        m_listView->addItem(item->toString());
        m_technicalAttributes->technicalAttributeLong().append(item);
    } else if(op == Edit) {
        int row = m_technicalAttributes->technicalAttributeLong().indexOf(item);
        m_listView->setItem(row, item->toString());
    }
}

void TechnicalAttributesForm::unsignedByteFormClosed(Operation op, QVariant value)
{
    UInt8 *item = QVarPtr<UInt8>::asPointer(value);
    if(!item)
        return;
    if(op == Add) {
        m_listView->addItem(item->toString());
        m_technicalAttributes->technicalAttributeUnsignedByte().append(item);
    } else if(op == Edit) {
        int row = m_technicalAttributes->technicalAttributeUnsignedByte().indexOf(item);
        m_listView->setItem(row, item->toString());
    }
}

void TechnicalAttributesForm::unsignedShortFormClosed(Operation op, QVariant value)
{
    UInt16 *item = QVarPtr<UInt16>::asPointer(value);
    if(!item)
        return;
    if(op == Add) {
        m_listView->addItem(item->toString());
        m_technicalAttributes->technicalAttributeUnsignedShort().append(item);
    } else if(op == Edit) {
        int row = m_technicalAttributes->technicalAttributeUnsignedShort().indexOf(item);
        m_listView->setItem(row, item->toString());
    }
}

void TechnicalAttributesForm::unsignedIntegerFormClosed(Operation op, QVariant value)
{
    UInt32 *item = QVarPtr<UInt32>::asPointer(value);
    if(!item)
        return;
    if(op == Add) {
        m_listView->addItem(item->toString());
        m_technicalAttributes->technicalAttributeUnsignedInteger().append(item);
    } else if(op == Edit) {
        int row = m_technicalAttributes->technicalAttributeUnsignedInteger().indexOf(item);
        m_listView->setItem(row, item->toString());
    }
}

void TechnicalAttributesForm::unsignedLongFormClosed(Operation op, QVariant value)
{
    UInt64 *item = QVarPtr<UInt64>::asPointer(value);
    if(!item)
        return;
    if(op == Add) {
        m_listView->addItem(item->toString());
        m_technicalAttributes->technicalAttributeUnsignedLong().append(item);
    } else if(op == Edit) {
        int row = m_technicalAttributes->technicalAttributeUnsignedLong().indexOf(item);
        m_listView->setItem(row, item->toString());
    }
}

void TechnicalAttributesForm::booleanFormClosed(Operation op, QVariant value)
{
    Boolean *item = QVarPtr<Boolean>::asPointer(value);
    if(!item)
        return;
    if(op == Add) {
        m_listView->addItem(item->toString());
        m_technicalAttributes->technicalAttributeBoolean().append(item);
    } else if(op == Edit) {
        int row = m_technicalAttributes->technicalAttributeBoolean().indexOf(item);
        m_listView->setItem(row, item->toString());
    }
}

void TechnicalAttributesForm::floatFormClosed(Operation op, QVariant value)
{
    Float *item = QVarPtr<Float>::asPointer(value);
    if(!item)
        return;
    if(op == Add) {
        m_listView->addItem(item->toString());
        m_technicalAttributes->technicalAttributeFloat().append(item);
    } else if(op == Edit) {
        int row = m_technicalAttributes->technicalAttributeFloat().indexOf(item);
        m_listView->setItem(row, item->toString());
    }
}

void TechnicalAttributesForm::rationalFormClosed(Operation op, QVariant value)
{
    TechnicalAttributeRationalType *item = QVarPtr<TechnicalAttributeRationalType>::asPointer(value);
    if(!item)
        return;
    if(op == Add) {
        m_listView->addItem(item->toString());
        m_technicalAttributes->technicalAttributeRational().append(item);
    } else if(op == Edit) {
        int row = m_technicalAttributes->technicalAttributeRational().indexOf(item);
        m_listView->setItem(row, item->toString());
    }
}

void TechnicalAttributesForm::uriFormClosed(Operation op, QVariant value)
{
    TechnicalAttributeUriType *item = QVarPtr<TechnicalAttributeUriType>::asPointer(value);
    if(!item)
        return;
    if(op == Add) {
        m_listView->addItem(item->toString());
        m_technicalAttributes->technicalAttributeUri().append(item);
    } else if(op == Edit) {
        int row = m_technicalAttributes->technicalAttributeUri().indexOf(item);
        m_listView->setItem(row, item->toString());
    }
}

void TechnicalAttributesForm::updateListAndButtons()
{
    QString title;
    switch (m_currentEditMode) {
    case StringMode:
    {
        title = tr("String");
    }
        break;
    case Byte:
    {
        title = tr("Byte");
    }
        break;
    case Short:
    {
        title = tr("Short");
    }
        break;
    case Integer:
    {
        title = tr("Integer");
    }
        break;
    case Long:
    {
        title = tr("Long");
    }
        break;
    case UnsignedByte:
    {
        title = tr("Unsigned Byte");
    }
        break;
    case UnsignedShort:
    {
        title = tr("Unsigned Short");
    }
        break;
    case UnsignedInteger:
    {
        title = tr("Unsigned Integer");
    }
        break;
    case UnsignedLong:
    {
        title = tr("Unsigned Long");
    }
        break;
    case BooleanMode:
    {
        title = tr("Boolean");
    }
        break;
    case FloatMode:
    {
        title = tr("Float");
    }
        break;
    case Rational:
    {
        title = tr("Rational Type");
    }
        break;
    case Uri:
    {
        title = tr("Uri Type");
    }
        break;

    }

    m_listView->setTitle(title);
    m_listView->clear();
}

bool TechnicalAttributesForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if ( obj == (QObject*) m_buttonString)
            m_textDocumentation->setText(tr("A technical attribute of type string."));
        if ( obj == (QObject*) m_buttonByte)
            m_textDocumentation->setText(tr("A technical attribute of type 'byte' also called int8."));
        if ( obj == (QObject*) m_buttonShort)
            m_textDocumentation->setText(tr("A technical attribute of type 'short' also called int16."));
        if ( obj == (QObject*) m_buttonInteger)
            m_textDocumentation->setText(tr("A technical attribute of type 'integer' also called int32."));
        if ( obj == (QObject*) m_buttonLong)
            m_textDocumentation->setText(tr("A technical attribute of type 'long' also called int64."));
        if ( obj == (QObject*) m_buttonUnsignedByte)
            m_textDocumentation->setText(tr("A technical attribute of type 'byte' also called UInt8."));
        if ( obj == (QObject*) m_buttonUnsignedShort)
            m_textDocumentation->setText(tr("A technical attribute of type 'short' also called UInt16."));
        if ( obj == (QObject*) m_buttonUnsignedInteger)
            m_textDocumentation->setText(tr("A technical attribute of type 'integer' also called UInt32."));
        if ( obj == (QObject*) m_buttonUnsignedLong)
            m_textDocumentation->setText(tr("A technical attribute of type 'long' also called UInt64."));
        if ( obj == (QObject*) m_buttonBoolean)
            m_textDocumentation->setText(tr("A technical attribute of type 'boolean'."));
        if ( obj == (QObject*) m_buttonFloat)
            m_textDocumentation->setText(tr("A technical attribute of type 'float' or 'double'."));
        if ( obj == (QObject*) m_buttonRational)
            m_textDocumentation->setText(tr("A technical attribute of type 'rational'."));
        if ( obj == (QObject*) m_buttonUri)
            m_textDocumentation->setText(tr("A technical attribute of type 'URI'."));
    }
    return QObject::eventFilter(obj, event);
}
