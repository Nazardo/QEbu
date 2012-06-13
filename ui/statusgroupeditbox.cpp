/****************************************************************************
** Copyright (C) 2012 by
**  Mauro Levra  (nazardo)     mauro@nazardo.it
**  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it
**  Denis Patti  (dextp3)      denis.patti@studenti.polito.it
**  Giovanni Pessiva           giovanni.pessiva@gmail.com
**  Stefano Ricossa            stefano.ricossa@studenti.polito.it
**
** This file is part of QEbu.
** QEbu is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, in the version 3 of the License.
**
** QEbu is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with QEbu.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#include "statusgroupeditbox.h"
#include "../model/statusgroup.h"
#include "../model/typeconverter.h"
#include <QLineEdit>
#include <QFormLayout>
#include <QGroupBox>
#include <QComboBox>

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
    QObject::connect(m_editStatusLink->lineEdit(), SIGNAL(editingFinished()), this, SLOT(onChange()));
    m_editStatusLink->setStyleSheet("QComboBox::drop-down {border-width: 0px;} \
                                  QComboBox::down-arrow {image: url(noimg); \
                                  border-width: 0px;}");
    m_editStatusLink->setToolTip("Press Enter to save your custom value");
    m_editStatusLink->setValidator(TypeConverter::getUriValidator());

    if (!statusGroup)
        return;
    // Set text fields
    m_editStatusLabel->setText(statusGroup->statusLabel());
    m_editStatusDefinition->setText(statusGroup->statusDefinition());
    m_editStatusLink->addItem(statusGroup->statusLink(),statusGroup->statusLink());
}

StatusGroup *StatusGroupEditBox::statusGroup()
{
    StatusGroup *statusGroup = new StatusGroup;
    updateExistingStatusGroup(statusGroup);
    return statusGroup;
}

void StatusGroupEditBox::addLinksMap(QMap<QString, QString> *values)
{
    int currentIndex = m_editStatusLink->currentIndex();
    QString selectedData = m_editStatusLink->itemData(currentIndex).toString();

    m_editStatusLink->setStyleSheet("");

    QList<QString> keys = values->keys();
    for (int i=0; i < keys.size(); ++i) {
        QString key = keys.at(i);
        if (m_editStatusLink->findText(values->value(key)) == -1) {
            // Discart duplicates (new user-defined values are saved in every maps used)
            m_editStatusLink->addItem(values->value(key),key);
            if (currentIndex == 0 && key == selectedData) { // This is the value previously stored
                m_editStatusLink->setItemData(currentIndex,""); //This is the empty value
                m_editStatusLink->setItemText(currentIndex,""); //This is the empty value
                m_editStatusLink->setCurrentIndex(m_editStatusLink->count()-1); //Select this last item
            }
        }
    }
}



void StatusGroupEditBox::updateExistingStatusGroup(StatusGroup *statusGroup)
{
    statusGroup->setStatusDefinition(m_editStatusDefinition->text());
    statusGroup->setStatusLabel(m_editStatusLabel->text());
    statusGroup->setStatusLink(m_editStatusLink->itemData(m_editStatusLink->currentIndex()).toString());
}

void StatusGroupEditBox::onChange(int index) {
    if(!m_editStatusLink->itemData(index).isValid()) {
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

void StatusGroupEditBox::onChange()
{
    QString s = m_editStatusLink->lineEdit()->text();
    if (m_editStatusLink->findText(s) < 0) {
        m_editStatusLink->addItem(s, s);
        //Add it to the autocompletion maps
        for (int i=0; i<m_linkMaps.size(); ++i)
            m_linkMaps[i]->insert(s,s);
        int i = m_editStatusLink->findText(s);
        if (i >= 0)
            m_editStatusLink->setCurrentIndex(i);
    }
}

QLineEdit *StatusGroupEditBox::editStatusLabel()
{
    return m_editStatusLabel;
}

QLineEdit *StatusGroupEditBox::editStatusDefinition()
{
    return m_editStatusDefinition;
}

QComboBox *StatusGroupEditBox::editStatusLink()
{
    return m_editStatusLink;
}

