#include "technicalattributeuritypeform.h"
#include "../model/technicalattributes.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include <QLineEdit>
#include <QFormLayout>

TechicalAttributeUriTypeForm::TechicalAttributeUriTypeForm(TechnicalAttributeUriType *uri, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (uri) ? Edit : Add;
    if (!uri)
        m_uri = new TechnicalAttributeUriType;
    else
        m_uri = uri;

    // Layout
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
    this->setLayout(l);

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
    m_uri->setValue(m_editValue->text());
    m_editTypeGroup->updateExistingTypeGroup(m_uri);

    emit closed(m_op, QVarPtr<TechnicalAttributeUriType>::asQVariant(m_uri));
}
