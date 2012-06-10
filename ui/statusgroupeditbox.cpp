#include "statusgroupeditbox.h"
#include "../model/statusgroup.h"
#include <QLineEdit>
#include <QFormLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QDebug>

StatusGroupEditBox::StatusGroupEditBox(StatusGroup *statusGroup, QWidget *parent) :
    QWidget(parent)
{
    m_editStatusLabel = new QLineEdit(this);
    m_editStatusDefinition = new QLineEdit(this);
    m_editStatusLink = new QComboBox(this);
    QHBoxLayout *l = new QHBoxLayout;
    QFormLayout *formL = new QFormLayout;
    QGroupBox *group = new QGroupBox(tr("Status"));
    formL->addRow(tr("Label"), m_editStatusLabel);
    formL->addRow(tr("Definition"), m_editStatusDefinition);
    formL->addRow(tr("Link"), m_editStatusLink);
    group->setLayout(formL);
    l->addWidget(group);
    this->setLayout(l);

    m_editStatusLink->setEditable(true);
    m_editStatusLink->setInsertPolicy(QComboBox::InsertAtTop);
    QObject::connect(m_editStatusLink, SIGNAL(currentIndexChanged(int)), this, SLOT(onChange(int)));

    if (!statusGroup)
        return;
    // Set text fields
    m_editStatusLabel->setText(statusGroup->statusLabel());
    m_editStatusDefinition->setText(statusGroup->statusDefinition());
    m_editStatusLink->addItem("",statusGroup->statusLink());
}

StatusGroup *StatusGroupEditBox::statusGroup()
{
    StatusGroup *statusGroup = new StatusGroup;
    updateExistingStatusGroup(statusGroup);
    return statusGroup;
}

void StatusGroupEditBox::addLinksMap(QMap<QString, QString> *values)
{
    QString selectedData = m_editStatusLink->itemData(m_editStatusLink->currentIndex()).toString();
    QString selectedText = m_editStatusLink->itemText(m_editStatusLink->currentIndex());
    m_editStatusLink->setItemData(m_editStatusLink->currentIndex(),"");


    QList<QString> keys = values->keys();
    for (int i=0; i < keys.size(); ++i) {
        QString key = keys.at(i);
        if (m_editStatusLink->findText(values->value(key)) == -1) {
            m_editStatusLink->addItem(values->value(key),key);
            if (key == selectedData)
                selectedText = values->value(key);
        }
    }

    m_editStatusLink->setCurrentIndex(m_editStatusLink->findText(selectedText));

    m_linkMaps.append(values);
}

void StatusGroupEditBox::updateExistingStatusGroup(StatusGroup *statusGroup)
{
    statusGroup->setStatusDefinition(m_editStatusDefinition->text());
    statusGroup->setStatusLabel(m_editStatusLabel->text());
    statusGroup->setStatusLink(m_editStatusLink->itemData(m_editStatusLink->currentIndex()).toString());

    qDebug() <<"setStatusLink index------" <<m_editStatusLink->currentIndex() <<"--------";
    qDebug() <<"setStatusLink data ------" <<m_editStatusLink->itemData(m_editStatusLink->currentIndex()).toString() <<"--------";
}

void StatusGroupEditBox::onChange(int index) {
    if(m_editStatusLink->itemData(index).isValid()) {
        qDebug() << m_editStatusLink->itemData(index).toString();
    } else {
        qDebug() << m_editStatusLink->currentText();

        //If its is a new value, add it to the autocompletion maps
        QString linkData = m_editStatusLink->itemData(index).toString();
        QString linkText = m_editStatusLink->itemText(index);
        bool newValue = true;
        for (int i=0;    i<m_linkMaps.size();    i++)
            if (m_linkMaps[i]->contains(linkData))
                newValue = false;

        if (newValue)
            for (int i=0;    i<m_linkMaps.size();    i++)
                m_linkMaps[i]->insert(linkData,linkText);
    }
}

