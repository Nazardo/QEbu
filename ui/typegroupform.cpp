#include "typegroupform.h"
#include "../model/typegroup.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include <QLayout>
#include <QString>
#include <QEvent>
#include <QDebug>
#include <QLineEdit>
#include <QTextEdit>
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
            m_textDocumentation->setText("Aliquam dictum ante egestas purus euismod nec molestie velit pretium. Phasellus bibendum porttitor tortor ac suscipit. Proin vehicula tellus sit amet urna fringilla sodales. Integer eget suscipit tellus. Maecenas id justo condimentum magna mattis consectetur. Aenean suscipit, augue eget egestas tincidunt, tortor ante cursus augue, eu fermentum leo risus ut nisl. Vivamus luctus, lectus vitae molestie condimentum, augue enim ultricies ante, eu accumsan enim urna ornare leo. Sed auctor lobortis magna, sed tristique justo ornare vitae. Nam lobortis ultricies luctus. Donec ac lorem non tellus consectetur faucibus vitae quis tellus. Phasellus lacinia est vitae mauris bibendum id ultricies mauris tristique. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Duis luctus luctus dui, id vehicula mauris faucibus vulputate. Vestibulum sagittis, tortor ut dignissim eleifend, neque est rutrum justo, a pellentesque tortor dui in enim...");
        else if ( obj ==(QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText("Label...");
        else if ( obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setText("Link...");
    }
    return QObject::eventFilter(obj, event);
}

void TypeGroupForm::cancelClicked()
{
    emit closed(m_op, QVarPtr<TypeGroup>::asQVariant(0));
}
