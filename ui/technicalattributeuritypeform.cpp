#include "technicalattributeuritypeform.h"
#include "../model/technicalattributes.h"
#include "../model/typeconverter.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QEvent>
#include <QFormLayout>
#include <QComboBox>

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
        m_editValue->setValidator(TypeConverter::getUriValidator());
        fl->addRow(tr("Value"), m_editValue);
        l->addLayout(fl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(uri);
        l->addWidget(m_editTypeGroup);
    }
    this->setLayout(l);

    // Event Filter
    m_textDocumentation->setText(tr("Allows users / implementers to define their own technical parameters using the type attribute of their need."));
    m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
    m_editTypeGroup->editTypeLabel()->installEventFilter(this);
    m_editTypeGroup->editTypeLink()->installEventFilter(this);
    m_editValue->installEventFilter(this);

    // Set data fields...
    m_editValue->setText(m_uri->value());
}

QString TechicalAttributeUriTypeForm::toString()
{
    return QString(tr("Techical Attribute Uri"));
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

bool TechicalAttributeUriTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("Free text.\nExample: ‘a flag indicating that the video bitrate corresponds to an average bitrate’."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setText(tr("Link to a classification scheme."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("Free text.\nExample: averageBitrateFlag, bitrate."));
        else if (obj == (QObject*) m_editValue)
            m_textDocumentation->setText(tr("The value of the technical attribute."));
    }
    return QObject::eventFilter(obj, event);
}
