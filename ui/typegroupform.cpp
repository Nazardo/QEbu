#include "typegroupform.h"
#include "../model/typegroup.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include <QLayout>
#include <QString>
#include <QEvent>
#include <QDebug>
#include <QLineEdit>
#include <QTextBrowser>
#include <QComboBox>

TypeGroupForm::TypeGroupForm(TypeGroup *typeGroup,
                             QEbuMainWindow *mainWindow,
                             QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (typeGroup) ? Edit : Add;
    if (!typeGroup)
        m_typeGroup = new TypeGroup;
    else
        m_typeGroup = typeGroup;
    QVBoxLayout *vl = new QVBoxLayout;
    m_title = QString(tr("Type Group"));
    m_editTypeGroup = new TypeGroupEditBox(m_typeGroup);
    m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
    m_editTypeGroup->editTypeLabel()->installEventFilter(this);
    m_editTypeGroup->editTypeLink()->installEventFilter(this);
    m_editTypeGroup->setLabel(m_title);
    vl->addWidget(m_editTypeGroup);
    this->setLayout(vl);
}

void TypeGroupForm::addLinksMap(QMap<QString, QString> *values) {
    m_editTypeGroup->addLinksMap(values); //Autocompletion values
}

QString TypeGroupForm::toString()
{
    return m_title;
}

void TypeGroupForm::setTitle(const QString &title)
{
    m_title = title;
    m_editTypeGroup->setLabel(title);
}

void TypeGroupForm::applyClicked()
{
    m_editTypeGroup->updateExistingTypeGroup(m_typeGroup);
    emit closed(m_op, QVarPtr<TypeGroup>::asQVariant(m_typeGroup));
}

bool TypeGroupForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if ( obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(m_definitionDoc);
        else if ( obj ==(QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(m_labelDoc);
        else if ( obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setHtml(m_linkDoc);
    }
    return QObject::eventFilter(obj, event);
}

void TypeGroupForm::cancelClicked()
{
    emit closed(m_op, QVarPtr<TypeGroup>::asQVariant(0));
}

void TypeGroupForm::setLabelDoc(const QString &doc)
{
    m_labelDoc = doc;
}

void TypeGroupForm::setLinkDoc(const QString &doc)
{
    m_linkDoc = doc;
}

void TypeGroupForm::setGeneralDoc(const QString &doc)
{
    m_generalDoc = doc;
    m_textDocumentation->setText(doc);
}

void TypeGroupForm::setDefinitionDoc(const QString &doc)
{
    m_definitionDoc = doc;
}
