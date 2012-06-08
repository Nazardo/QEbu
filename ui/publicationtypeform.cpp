#include "publicationtypeform.h"
#include "../model/ebucoremaintype.h"
#include "listview.h"
#include "qvarptr.h"
#include "organisationdetailstypeform.h"
#include "contactdetailstypeform.h"
#include "../model/typeconverter.h"
#include "typegroupform.h"
#include <QTimeEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QFormLayout>

PublicationTypeForm::PublicationTypeForm(PublicationType *publication,
                                         QEbuMainWindow *mainWindow,
                                         QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (publication) ? Edit : Add;
    if (!publication)
        m_publication = new PublicationType;
    else
        m_publication = publication;
    // Layout
    QFormLayout *fl = new QFormLayout;
    m_editPublicationDate = new QDateEdit;
    m_editPublicationDate->setCalendarPopup(true);
    fl->addRow(tr("Publication date"), m_editPublicationDate);
    m_editPublicationTime = new QTimeEdit;
    fl->addRow(tr("Publication time"), m_editPublicationTime);
    m_editPublicationChannel = new QComboBox;
    QStringList sl(mainWindow->ebuCoreMain()->formatMap().keys());
    m_editPublicationChannel->addItems(sl);
    fl->addRow(tr("Publication channel"), m_editPublicationChannel);
    this->setLayout(fl);

    // Set data fields...
    if (m_publication) {
        m_editPublicationDate->setDate(m_publication->date().date());
        m_editPublicationTime->setTime(m_publication->time().time());
        if (m_publication->channel()) {
            int index = m_editPublicationChannel->findText(m_publication->channel()->formatId());
            m_editPublicationChannel->setCurrentIndex(index);
        }
    }
}

QString PublicationTypeForm::toString()
{
    return QString(tr("Publication"));
}

void PublicationTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_publication;
        m_publication = 0;
    }
    emit closed(m_op, QVarPtr<PublicationType>::asQVariant(m_publication));
}

void PublicationTypeForm::applyClicked()
{
    m_publication->setTime(m_editPublicationTime->dateTime());
    m_publication->setDate(m_editPublicationDate->dateTime());
    m_publication->setChannel(0); /// @todo
    emit closed(m_op, QVarPtr<PublicationType>::asQVariant(m_publication));
}
