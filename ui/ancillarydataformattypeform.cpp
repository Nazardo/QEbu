#include "ancillarydataformattypeform.h"

#include "qvarptr.h"
#include "../model/qebulimits.h"
#include <QtGui>

AncillaryDataFormatTypeForm::AncillaryDataFormatTypeForm(AncillarityDataFormatType *ancillaryDataFormat, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (ancillaryDataFormat) ? Edit : Add;
    if(!ancillaryDataFormat)
        m_ancillaryDataFormat = new AncillarityDataFormatType();
    else
        m_ancillaryDataFormat = ancillaryDataFormat;
    m_mainHLayout = new QHBoxLayout;
    QVBoxLayout *vl = new QVBoxLayout;
    {
        QFormLayout *fl = new QFormLayout;

        m_editAncillarityDataFormatId = new QLineEdit;
        fl->addRow(tr("Ancillarity data format id"), m_editAncillarityDataFormatId);

        m_editAncillarityDataFormatName = new QLineEdit;
        fl->addRow(tr("Ancillarity data format name"), m_editAncillarityDataFormatName);


        m_spinDID = new QSpinBox;
        fl->addRow(tr("DID"), m_spinDID);
        m_spinSDID = new QSpinBox;
        fl->addRow(tr("SDID"), m_spinSDID);
        m_spinWrappingType = new QSpinBox;
        fl->addRow(tr("DID"), m_spinWrappingType);
        m_buttonLineNumber = new QPushButton(">>");
        m_buttonLineNumber->setCheckable(true);
        fl->addRow(tr("Line number"), m_buttonLineNumber);
        QObject::connect(m_buttonLineNumber, SIGNAL(toggled(bool)),
                         this, SLOT(numberLineChecked(bool)));
        vl->addLayout(fl);
    }
    {
        QHBoxLayout *hl = new QHBoxLayout;
        QPushButton *buttonClose = new QPushButton(tr("Apply changes"));
        QPushButton *buttonCancel = new QPushButton(tr("Cancel"));
        QObject::connect(buttonClose, SIGNAL(clicked()),
                         this, SLOT(applyClicked()));
        QObject::connect(buttonCancel, SIGNAL(clicked()),
                         this, SLOT(cancelClicked()));
        hl->addWidget(buttonClose);
        hl->addWidget(buttonCancel);
        vl->addLayout(hl);
    }
    m_mainHLayout->addLayout(vl);

    // Add list view on the right
    m_listView = new ListView();
    QObject::connect(m_listView->buttonAdd(), SIGNAL(clicked()),
                     this, SLOT(addClicked()));
    QObject::connect(m_listView->buttonEdit(), SIGNAL(clicked()),
                     this, SLOT(editClicked()));
    QObject::connect(m_listView->buttonRemove(), SIGNAL(clicked()),
                     this, SLOT(removeClicked()));
    m_mainHLayout->addWidget(m_listView);

    this->setLayout(m_mainHLayout);

    //Set Data fields
    m_editAncillarityDataFormatId->setText(m_ancillaryDataFormat->ancillaryDataFormatId());
    m_editAncillarityDataFormatName->setText(m_ancillaryDataFormat->ancillaryDataFormatName());
    if (m_ancillaryDataFormat->DID())
        m_spinDID->setValue(*(m_ancillaryDataFormat->DID()));
    if (m_ancillaryDataFormat->SDID())
        m_spinSDID->setValue(*(m_ancillaryDataFormat->SDID()));
    if (m_ancillaryDataFormat->wrappingType())
        m_spinWrappingType->setValue(*(m_ancillaryDataFormat->wrappingType()));

    m_buttonLineNumber->setChecked(true);
}

QString AncillaryDataFormatTypeForm::toString()
{
    return QString(tr("Ancillary data format"));
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

}

void AncillaryDataFormatTypeForm::numberLineFormClosed(Operation op, QVariant value)
{

}

void AncillaryDataFormatTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_ancillaryDataFormat;
        m_ancillaryDataFormat = 0;
    }
    emit closed(m_op, QVarPtr<AncillarityDataFormatType>::asQVariant(m_ancillaryDataFormat));
}

void AncillaryDataFormatTypeForm::applyClicked()
{
    if (!checkCompliance())
        return;
    m_ancillaryDataFormat->setAncillaryDataFormatId(m_editAncillarityDataFormatId->text());
    m_ancillaryDataFormat->setAncillaryDataFormatName(m_editAncillarityDataFormatName->text());
    m_ancillaryDataFormat->setDID(m_spinDID->value());
    m_ancillaryDataFormat->setSDID(m_spinSDID->value());
    //TODO line number
    m_ancillaryDataFormat->setWrappingType(m_spinWrappingType->value());
    emit closed(m_op, QVarPtr<AncillarityDataFormatType>::asQVariant(m_ancillaryDataFormat));
}

bool AncillaryDataFormatTypeForm::checkCompliance()
{
    bool ok = true;
    QString error_msg = "";
    //TODO
    if(!ok) {
        QErrorMessage *e = new QErrorMessage(this);
        e->setWindowTitle(tr("Rrequired fields"));
        e->showMessage(error_msg);
    }
    return ok;
}
