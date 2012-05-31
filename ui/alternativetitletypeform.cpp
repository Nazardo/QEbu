#include "alternativetitletypeform.h"
#include "../model/coremetadatatype.h"
#include "dategroupeditbox.h"
#include "statusgroupeditbox.h"
#include "typegroupeditbox.h"
#include "elementtypeeditbox.h"
#include "qvarptr.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QTextEdit>

AlternativeTitleTypeForm::AlternativeTitleTypeForm(
        AlternativeTitleType *alternativeTitle,
        QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (alternativeTitle) ? Edit : Add;
    if (!alternativeTitle)
        m_alternativeTitle = new AlternativeTitleType;
    else
        m_alternativeTitle = alternativeTitle;

    QHBoxLayout *hLayout = new QHBoxLayout;
    QVBoxLayout *leftVLayout = new QVBoxLayout;
    m_editTypeGroup = new TypeGroupEditBox(m_alternativeTitle);
    leftVLayout->addWidget(m_editTypeGroup);
    m_editStatusGroup = new StatusGroupEditBox(m_alternativeTitle);
    leftVLayout->addWidget(m_editStatusGroup);
    m_editTitle = new ElementTypeEditBox;
    m_editTitle->setLabel(tr("Title"));
    leftVLayout->addWidget(m_editTitle);
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
        leftVLayout->addLayout(hl);
    }
    hLayout->addLayout(leftVLayout);
    QVBoxLayout *rightVLayout = new QVBoxLayout;
    {
        QFormLayout *form = new QFormLayout;
        m_textNote = new QTextEdit;
        form->addRow(tr("Note"), m_textNote);
        rightVLayout->addLayout(form);
    }
    m_editDateGroup = new DateGroupEditBox(m_alternativeTitle);
    rightVLayout->addWidget(m_editDateGroup);
    hLayout->addLayout(rightVLayout);
    hLayout->setAlignment(leftVLayout, Qt::AlignTop);
    hLayout->setAlignment(rightVLayout, Qt::AlignTop);
    this->setLayout(hLayout);
    // Set text fields
    if (m_op == Add)
        return;
    m_textNote->setText(m_alternativeTitle->note());
    if (m_alternativeTitle->title()) {
        m_editTitle->editValue()->setText(m_alternativeTitle->title()->value());
        m_editTitle->editLang()->setText(m_alternativeTitle->title()->lang());
    }
}

QString AlternativeTitleTypeForm::toString()
{
    return QString(tr("AlternativeTitleType"));
}

void AlternativeTitleTypeForm::applyClicked()
{
    m_alternativeTitle->setNote(m_textNote->toPlainText());
    m_editTypeGroup->updateExistingTypeGroup(m_alternativeTitle);
    m_editStatusGroup->updateExistingStatusGroup(m_alternativeTitle);
    m_editDateGroup->updateExistingDateGroup(m_alternativeTitle);
    if (m_editTitle->editLang()->text().isEmpty() && m_editTitle->editValue()->text().isEmpty())
        m_alternativeTitle->setTitle(0);
    else
        m_alternativeTitle->setTitle(
                    new ElementType(m_editTitle->editValue()->text(),
                                    m_editTitle->editLang()->text()));
    emit closed(m_op, QVarPtr<AlternativeTitleType>::asQVariant(m_alternativeTitle));
}

void AlternativeTitleTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_alternativeTitle;
        m_alternativeTitle = 0;
    }
    emit closed(m_op, QVarPtr<AlternativeTitleType>::asQVariant(m_alternativeTitle));
}
