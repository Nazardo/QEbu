#include "titletypeform.h"
#include "../model/coremetadatatype.h"
#include "elementtypeeditbox.h"
#include "qvarptr.h"
#include <QTextEdit>
#include <QDateEdit>
#include <QLineEdit>
#include <QCheckBox>
#include <QFormLayout>
#include <QMessageBox>
#include <QEvent>

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

    // Doc filter
    m_textDocumentation->setText(tr("A Title is the ‘main’ name given to a resource e.g. a media item, a media object, or a sequence as specified by the associated title type. It corresponds for a series to the series title, for a programme to the programme title, for an item to the item title, etc.\nTitles are recorded as they appear.\nThe Title is the name by which a resource is formally known and that everyone should use to refer to or search for that particular resource.\nThe Title may be provided in several languages.\nIf present, the attributionDate attribute indicates when the Title was attributed."));
    m_editAttributionDate->installEventFilter(this);
    m_textNote->installEventFilter(this);
    m_editTitle->editValue()->installEventFilter(this);
    m_editTitle->editLang()->installEventFilter(this);

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
    return QString(tr("Title"));
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
    if (!checkCompliance())
        return;
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

bool TitleTypeForm::checkCompliance()
{
    bool ok = true;
    QStringList fields;
    if (m_editTitle->editValue()->text().isEmpty()) {
        ok = false;
        fields += tr("Title");
    }
    if(!ok) {
        QMessageBox::warning(this, this->toString(),
                             tr("<b>Required fields:</b><br>")
                             +fields.join(",<br>"),
                             QMessageBox::Ok, QMessageBox::Ok);
    }
    return ok;
}

bool TitleTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if ( obj == (QObject*) m_editAttributionDate)
            m_textDocumentation->setText(tr("The date at which the title was attributed."));
        else if ( obj == (QObject*) m_textNote )
            m_textDocumentation->setText(tr("A note element to provide additional contextual information."));
        else if  (obj == (QObject*) m_editTitle->editValue())
            m_textDocumentation->setText(tr("Free-text to provide the main title by which the resource is known. The title can be provided in different languages.\nExample: ‘the fifth element’."));
        else if  (obj == (QObject*) m_editTitle->editLang())
            m_textDocumentation->setText(tr("The language in which the title is provided."));
    }
    return QObject::eventFilter(obj, event);
}
