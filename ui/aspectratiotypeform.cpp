#include "aspectratiotypeform.h"
#include "../model/formattype.h"
#include "qvarptr.h"
#include "formatgroupeditbox.h"
#include <QPushButton>
#include <QTextEdit>
#include <QFormLayout>
#include <QString>
#include <QLineEdit>
#include <QComboBox>
#include <QEvent>

AspectRatioTypeForm::AspectRatioTypeForm(AspectRatioType *aspectRatio,
                                         QEbuMainWindow *mainWindow,
                                         QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (aspectRatio) ? Edit : Add;
    if (!aspectRatio)
        m_aspectRatio = new AspectRatioType;
    else
        m_aspectRatio = aspectRatio;

    QVBoxLayout *vl = new QVBoxLayout;
    {
        m_editFormatGroup = new FormatGroupEditBox(aspectRatio);
        vl->addWidget(m_editFormatGroup);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_textNote = new QTextEdit;
        fl->addRow(tr("Note"), m_textNote);
        vl->addLayout(fl);
    }
    this->setLayout(vl);

    // Event Filter
    m_textDocumentation->setText(tr("The value of the ratio of the width by the height of the video expressed in the format defined by the formatGroup attributes"));
    m_textNote->installEventFilter(this);
    m_editFormatGroup->editFormatDefinition()->installEventFilter(this);
    m_editFormatGroup->editFormatLabel()->installEventFilter(this);
    m_editFormatGroup->editFormatLink()->installEventFilter(this);

    // Set text fields...
    m_textNote->setText(m_aspectRatio->note());
}

void AspectRatioTypeForm::addLinksMap(QMap<QString, QString> *values) {
    m_editFormatGroup->addLinksMap(values); //Autocompletion values
}

QString AspectRatioTypeForm::toString()
{
    return QString(tr("Aspect Ratio"));
}

void AspectRatioTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_aspectRatio;
        m_aspectRatio = 0;
    }
    emit closed(m_op, QVarPtr<AspectRatioType>::asQVariant(m_aspectRatio));
}

void AspectRatioTypeForm::applyClicked()
{
    m_aspectRatio->setNote(m_textNote->toPlainText());
    m_editFormatGroup->updateExistingFormatGroup(m_aspectRatio);
    emit closed(m_op, QVarPtr<AspectRatioType>::asQVariant(m_aspectRatio));
}

bool AspectRatioTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_textNote)
            m_textDocumentation->setText(tr("A note to add contextual additional information."));
        else if (obj == (QObject*) m_editFormatGroup->editFormatDefinition())
            m_textDocumentation->setText(tr("Free text for an optional definition.\nExample: ‘the so-called “widescreen” picture format’"));
        else if (obj == (QObject*) m_editFormatGroup->editFormatLink())
            m_textDocumentation->setText(tr("Link to a classification scheme."));
        else if (obj == (QObject*) m_editFormatGroup->editFormatLabel())
            m_textDocumentation->setText(tr("Free text\nExample: 16:9."));
    }
    return QObject::eventFilter(obj, event);
}
