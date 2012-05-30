#include "technicalattributeuritypeform.h"
#include "qvarptr.h"
#include <QtGui>

TechicalAttributeUriTypeForm::TechicalAttributeUriTypeForm(TechnicalAttributeUriType *uri, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (uri) ? Edit : Add;
    if (!uri)
        m_uri = new TechnicalAttributeUriType;
    else
        m_uri = uri;

    // Layout
    m_mainHLayout = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;

    {
        QFormLayout *fl = new QFormLayout;
        m_editValue = new QLineEdit;
        fl->addRow(tr("Value"), m_editValue);
        l->addLayout(fl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(uri);
        l->addWidget(m_editTypeGroup);
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
        l->addLayout(hl);
    }

    m_mainHLayout->addLayout(l);
    this->setLayout(m_mainHLayout);

    // Set data fields...
    m_editValue->setText(m_uri->value());
}

QString TechicalAttributeUriTypeForm::toString()
{
    return QString("TechicalAttributeUriType");
}

void TechicalAttributeUriTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_uri;
        m_uri = 0;
    }
    emit closed(m_op, QVarPtr<TechnicalAttributeUriType>::asQVariant(m_uri));
}

void TechicalAttributeUriTypeForm::applyClicked()
{
    if (!checkCompliance())
        return;

    m_uri->setValue(m_editValue->text());
    m_editTypeGroup->updateExistingTypeGroup(m_uri);

    emit closed(m_op, QVarPtr<TechnicalAttributeUriType>::asQVariant(m_uri));
}


bool TechicalAttributeUriTypeForm::checkCompliance()
{
    bool ok = true;
    QString error_msg = "";

    if(!ok) {
        QErrorMessage *e = new QErrorMessage(this);
        e->setWindowTitle(tr("Required fields"));
        e->showMessage(error_msg);
    }
    return ok;
}
