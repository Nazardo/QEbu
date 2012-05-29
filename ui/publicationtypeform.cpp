#include "publicationtypeform.h"
#include "qvarptr.h"
#include "organisationdetailstypeform.h"
#include "contactdetailstypeform.h"
#include "../model/typeconverter.h"
#include "typegroupform.h"
#include <QtGui>

PublicationTypeForm::PublicationTypeForm(PublicationType *publication, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (publication) ? Edit : Add;
    if (!publication)
        m_publication = new PublicationType;
    else
        m_publication = publication;
    // Layout
    m_mainHLayout = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;
    {
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
        l->addLayout(fl);
    }
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
    return QString("Publication Type");
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
