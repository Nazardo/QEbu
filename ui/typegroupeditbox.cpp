#include "typegroupeditbox.h"
#include "../model/typegroup.h"
#include <QLineEdit>
#include <QGroupBox>
#include <QFormLayout>
#include <QComboBox>
#include <QDebug>

TypeGroupEditBox::TypeGroupEditBox(TypeGroup *typeGroup,
                                   QWidget *parent) :
    QWidget(parent)
{
    m_editTypeLabel = new QLineEdit(this);
    m_editTypeDefinition = new QLineEdit(this);
    m_editTypeLink = new QComboBox(this);
    QHBoxLayout *l = new QHBoxLayout;
    QFormLayout *formL = new QFormLayout;
    m_groupBox = new QGroupBox(tr("Type"));
    formL->addRow(tr("Label"), m_editTypeLabel);
    formL->addRow(tr("Definition"), m_editTypeDefinition);
    formL->addRow(tr("Link"), m_editTypeLink);
    m_groupBox->setLayout(formL);
    l->addWidget(m_groupBox);
    this->setLayout(l);

    m_editTypeLink->setEditable(true);
    m_editTypeLink->setInsertPolicy(QComboBox::InsertAtTop);
    QObject::connect(m_editTypeLink, SIGNAL(currentIndexChanged(int)), this, SLOT(onChange(int)));
    m_editTypeLink->setStyleSheet("QComboBox::drop-down {border-width: 0px;} \
                                  QComboBox::down-arrow {image: url(noimg); \
                                  border-width: 0px;}");
    m_editTypeLink->setToolTip("Press Enter to save your custom value");

    if (!typeGroup) {
        m_editTypeLink->addItem("",""); //Add an empty item
        return;
    }
    // Set text fields
    m_editTypeLabel->setText(typeGroup->typeLabel());
    m_editTypeDefinition->setText(typeGroup->typeDefinition());
    m_editTypeLink->addItem(typeGroup->typeLink(),typeGroup->typeLink());
}

TypeGroup *TypeGroupEditBox::typeGroup()
{
    TypeGroup *typeGroup = new TypeGroup();
    updateExistingTypeGroup(typeGroup);
    return typeGroup;
}

void TypeGroupEditBox::setLabel(const QString &label)
{
    m_groupBox->setTitle(label);
}

void TypeGroupEditBox::addLinksMap(QMap<QString, QString> *values)
{
    int currentIndex = m_editTypeLink->currentIndex();
    QString selectedData = m_editTypeLink->itemData(currentIndex).toString();

    m_editTypeLink->setStyleSheet("");

    QList<QString> keys = values->keys();
    for (int i=0; i < keys.size(); ++i) {
        QString key = keys.at(i);
        if (m_editTypeLink->findText(values->value(key)) == -1) {
            // Discart duplicates (new user-defined values are saved in every maps used)
            m_editTypeLink->addItem(values->value(key),key);
            if (currentIndex == 0 && key == selectedData) { // This is the value previously stored
                m_editTypeLink->setItemData(currentIndex,""); //This is the empty value
                m_editTypeLink->setItemText(currentIndex,""); //This is the empty value
                m_editTypeLink->setCurrentIndex(m_editTypeLink->count()-1); //Select this last item
            }
        }
    }

    m_linkMaps.append(values);  // Save the pointer to this linkMap
}

QLineEdit *TypeGroupEditBox::editTypeLabel()
{
    return m_editTypeLabel;
}

QComboBox *TypeGroupEditBox::editTypeLink()
{
    return m_editTypeLink;
}

QLineEdit *TypeGroupEditBox::editTypeDefinition()
{
    return m_editTypeDefinition;
}

void TypeGroupEditBox::updateExistingTypeGroup(TypeGroup *typeGroup)
{
    typeGroup->setTypeDefinition(m_editTypeDefinition->text());
    typeGroup->setTypeLabel(m_editTypeLabel->text());
    typeGroup->setTypeLink(m_editTypeLink->itemData(m_editTypeLink->currentIndex()).toString());
}

void TypeGroupEditBox::onChange(int index) {
    if(m_editTypeLink->itemData(index).isValid()) {
        qDebug() << m_editTypeLink->itemData(index).toString();
    } else {
        QString linkText = m_editTypeLink->itemText(index);
        m_editTypeLink->setItemData(index, linkText);
        qDebug() <<"New value:" << linkText;

        //Add it to the autocompletion maps
        for (int i=0;    i<m_linkMaps.size();    i++)
            m_linkMaps[i]->insert(linkText,linkText);
    }
}
