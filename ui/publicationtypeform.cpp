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
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>

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
    QGroupBox *group = new QGroupBox(tr("Publication"));
    QGridLayout *gl = new QGridLayout;
    m_editPublicationDate = new QDateEdit;
    m_editPublicationDate->setCalendarPopup(true);
    m_checkPublicationDate = new QCheckBox(tr("Publication date"));
    QObject::connect(m_editPublicationDate, SIGNAL(dateChanged(QDate)),
                     this, SLOT(publicationDateChanged()));
    gl->addWidget(m_checkPublicationDate, 0, 0);
    gl->addWidget(m_editPublicationDate, 0, 1);
    m_editPublicationTime = new QTimeEdit;
    m_checkPublicationTime = new QCheckBox(tr("Publication Time"));
    QObject::connect(m_editPublicationTime, SIGNAL(timeChanged(QTime)),
                     this, SLOT(publicationTimeChanged()));
    gl->addWidget(m_checkPublicationTime, 1, 0);
    gl->addWidget(m_editPublicationTime, 1, 1);
    m_editPublicationChannel = new QComboBox;
    QStringList sl(mainWindow->ebuCoreMain()->formatMap().keys());
    m_editPublicationChannel->addItems(sl);
    gl->addWidget(new QLabel(tr("Channel format")), 2, 0);
    gl->addWidget(m_editPublicationChannel, 2, 1);
    m_editPublicationChannelString = new QLineEdit;
    gl->addWidget(new QLabel(tr("Channel title")), 3, 0);
    gl->addWidget(m_editPublicationChannelString, 3, 1);
    group->setLayout(gl);
    QVBoxLayout *l = new QVBoxLayout;
    l->addWidget(group);
    this->setLayout(l);

    // Set data fields...
    if (m_publication) {
        m_editPublicationDate->setDate(m_publication->date().date());
        m_editPublicationTime->setTime(m_publication->time().time());
        if (m_publication->channel()) {
            int index = m_editPublicationChannel->findText(m_publication->channel()->formatId());
            m_editPublicationChannel->setCurrentIndex(index);
        }
        m_editPublicationChannelString->setText(m_publication->channelString());
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
    if (m_checkPublicationTime->isChecked())
        m_publication->setTime(m_editPublicationTime->dateTime());
    else
        m_publication->clearTime();
    if (m_checkPublicationDate->isChecked())
        m_publication->setDate(m_editPublicationDate->dateTime());
    else
        m_publication->clearDate();
    if (!m_editPublicationChannel->currentText().isEmpty()) {
        QString formatIdRef = m_editPublicationChannel->currentText();
        QMap<QString, FormatType*> &formatMap = mainWindow()->ebuCoreMain()->formatMap();
        QMap<QString, FormatType*>::const_iterator iter = formatMap.find(formatIdRef);
        if (iter != formatMap.end()) {
            m_publication->setChannel(iter.value());
        } else {
            m_publication->setChannel(0);
        }
    } else {
        m_publication->setChannel(0);
    }
    m_publication->setChannelString(m_editPublicationChannelString->text());
    emit closed(m_op, QVarPtr<PublicationType>::asQVariant(m_publication));
}

void PublicationTypeForm::publicationTimeChanged()
{
    m_checkPublicationTime->setChecked(true);
}

void PublicationTypeForm::publicationDateChanged()
{
    m_checkPublicationDate->setChecked(true);
}
