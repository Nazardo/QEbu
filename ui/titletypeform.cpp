#include "titletypeform.h"
#include "../model/coremetadatatype.h"
#include "elementtypeeditbox.h"
#include "qvarptr.h"
#include <QTextEdit>
#include <QDateEdit>
#include <QLineEdit>
#include <QCheckBox>
#include <QFormLayout>

TitleTypeForm::TitleTypeForm(TitleType *title,
                             QEbuMainWindow *mainWindow,
                             QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (title) ? Edit : Add;
    if (!title)
        m_title = new TitleType;
    else
        m_title = title;
    // Layout
    QVBoxLayout *l = new QVBoxLayout;
    m_editAttributionDate = new QDateEdit;
    m_editAttributionDate->setCalendarPopup(true);
    m_checkAttributionDate = new QCheckBox(tr("Attribution date"));
    m_checkAttributionDate->setCheckable(true);
    QObject::connect(m_editAttributionDate, SIGNAL(dateChanged(QDate)),
                     this, SLOT(attributionDateChanged()));

    QHBoxLayout *hl = new QHBoxLayout;
    hl->addWidget(m_checkAttributionDate);
    hl->addWidget(m_editAttributionDate);
    l->addLayout(hl);

    m_textNote = new QTextEdit;
    QFormLayout *formL = new QFormLayout;
    formL->addRow(tr("Note"), m_textNote);
    l->addLayout(formL);
    m_editTitle = new ElementTypeEditBox;
    m_editTitle->setLabel(tr("Title"));
    l->addWidget(m_editTitle);
    this->setLayout(l);

    // Set data fields
    if (m_title->title()) {
        m_editTitle->editLang()->setText(m_title->title()->lang());
        m_editTitle->editValue()->setText(m_title->title()->value());
    }
    if (m_title->attributionDate().isValid()) {
        m_editAttributionDate->setDate(m_title->attributionDate().date());
        m_checkAttributionDate->setChecked(true);
    }
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
    if (m_checkAttributionDate->isChecked()) {
        QDateTime *qdt = new QDateTime;
        qdt->setDate(m_editAttributionDate->date());
        m_title->setAttributionDate(*qdt);
    }
    m_title->setNote(m_textNote->toPlainText());
    m_title->setTitle(new ElementType(m_editTitle->editValue()->text(),
                                      m_editTitle->editLang()->text()));
    emit closed(m_op, QVarPtr<TitleType>::asQVariant(m_title));
}

void TitleTypeForm::attributionDateChanged()
{
    m_checkAttributionDate->setChecked(true);
}
