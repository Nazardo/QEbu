#include "titletypeform.h"
#include "qvarptr.h"
#include <QtGui>

TitleTypeForm::TitleTypeForm(TitleType *title, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (title) ? Edit : Add;
    if (!title)
        m_title = new TitleType;
    else
        m_title = title;
    // Layout
    m_mainHLayout = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;
    m_editAttributionDate = new QDateEdit;
    m_editAttributionDate->setCalendarPopup(true);
    m_textNote = new QTextEdit;
    QFormLayout *formL = new QFormLayout;
    formL->addRow(tr("Attribution date"), m_editAttributionDate);
    formL->addRow(tr("Note"), m_textNote);
    l->addLayout(formL);
    m_editTitle = new ElementTypeEditBox;
    m_editTitle->setLabel(tr("Title"));
    l->addWidget(m_editTitle);
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

    // Set data fields
    if(m_title->title()) {
        m_editTitle->editLang()->setText(m_title->title()->lang());
        m_editTitle->editValue()->setText(m_title->title()->value());
    }
    m_editAttributionDate->setDate(m_title->attributionDate().date());
    m_textNote->setText(m_title->note());
}

QString TitleTypeForm::toString()
{
    return QString("Title Type");
}

void TitleTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_title;
        m_title = 0;
    }
    emit closed(m_op, QVarPtr<TitleType>::asQVariant(m_title));
}

void TitleTypeForm::applyClicked()
{
    QDateTime *qdt = new QDateTime;
    qdt->setDate(m_editAttributionDate->date());
    m_title->setAttributionDate(*qdt);
    m_title->setNote(m_textNote->toPlainText());
    m_title->setTitle(new ElementType(m_editTitle->editValue()->text(),
                                      m_editTitle->editLang()->text()));
    emit closed(m_op, QVarPtr<TitleType>::asQVariant(m_title));
}
