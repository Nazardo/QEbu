#include "locatortypeform.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include "../model/formattype.h"
#include <QLineEdit>
#include <QFormLayout>
#include <QComboBox>
#include <QEvent>
#include <QTextEdit>
#include <QTextBrowser>

LocatorTypeForm::LocatorTypeForm(LocatorType *locator,
                                 QEbuMainWindow *mainWindow,
                                 QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (locator) ? Edit : Add;
    if (!locator)
        m_locator = new LocatorType;
    else
        m_locator = locator;

    QVBoxLayout *vl = new QVBoxLayout;
    m_editTypeGroup = new TypeGroupEditBox(m_locator);
    vl->addWidget(m_editTypeGroup);
    {
        QFormLayout *fl = new QFormLayout;
        m_editLocatorValue = new QLineEdit;
        fl->addRow(tr("Locator value"), m_editLocatorValue);
        vl->addLayout(fl);
    }
    this->setLayout(vl);

    // Install Events filter
    m_textDocumentation->setText(tr("An \"address for a resource\".\nFor an organisation or producer acting as caretaker for a media resource, Format Location may contain information about a specific e.g. tape name, shelf location for an asset, including an organisation's name, departmental name, shelf id. And contact information. The Format Location for a data file or web page may include a complete URI with a domain, path, filename or html URL."));
    m_editTypeGroup->editTypeLabel()->installEventFilter(this);
    m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
    m_editTypeGroup->editTypeLink()->installEventFilter(this);
    m_editLocatorValue->installEventFilter(this);

    // Set text fields
    if (m_op == Edit)
        m_editLocatorValue->setText(m_locator->locatorValue());
}

QString LocatorTypeForm::toString()
{
    return tr("Locator");
}

void LocatorTypeForm::applyClicked()
{
    m_locator->setLocatorValue(m_editLocatorValue->text());
    m_editTypeGroup->updateExistingTypeGroup(m_locator);
    emit closed(m_op, QVarPtr<LocatorType>::asQVariant(m_locator));
}

bool LocatorTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("Free text. An optional label."));
        if (obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("Free text. An optional definition."));
        if (obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setText(tr("Link to a classification scheme."));
        if (obj == (QObject*) m_editLocatorValue)
            m_textDocumentation->setText(tr("An \"address for a resource\"."));
    }
    return QObject::eventFilter(obj, event);
}
