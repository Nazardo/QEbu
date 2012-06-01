#include "aspectratiotypeform.h"
#include "../model/formattype.h"
#include "qvarptr.h"
#include "formatgroupeditbox.h"
#include <QPushButton>
#include <QTextEdit>
#include <QFormLayout>

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
    // Set text fields...
    m_textNote->setText(m_aspectRatio->note());
}

QString AspectRatioTypeForm::toString()
{
    return QString("Aspect Ratio Type");
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
