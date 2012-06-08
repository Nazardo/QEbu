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
    if (!typeGroup)
        return;
    // Set text fields
    m_editTypeLabel->setText(typeGroup->typeLabel());
    m_editTypeDefinition->setText(typeGroup->typeDefinition());
    m_editTypeLink->addItem("",typeGroup->typeLink());
    m_editTypeLink->setEditable(true);
    m_editTypeLink->setInsertPolicy(QComboBox::InsertAtTop);
    QObject::connect(m_editTypeLink, SIGNAL(currentIndexChanged(int)), this, SLOT(onChange(int)));
    QObject::connect(m_editTypeLink, SIGNAL(editTextChanged(QString)), this, SLOT(onInsertion(QString)));
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

void TypeGroupEditBox::addLinksMap(QMap<QString, QString> values)
{
    QString currentData = m_editTypeLink->itemData(m_editTypeLink->currentIndex()).toString();
    QString currentText;

    m_linksMap.unite(values);

    QList<QString> keys = m_linksMap.keys();
    for (int i=0; i < keys.size(); ++i) {
         m_editTypeLink->addItem(m_linksMap.value(keys.at(i)),keys.at(i));
         if (keys.at(i) == currentData)
            currentText = m_linksMap.value(keys.at(i));
    }

    if (currentText.isEmpty())
        m_editTypeLink->setCurrentIndex(0);  //if cant find that value, select the first
    else
        m_editTypeLink->setCurrentIndex(m_editTypeLink->findText(currentText));
}

void TypeGroupEditBox::updateExistingTypeGroup(TypeGroup *typeGroup)
{
    typeGroup->setTypeDefinition(m_editTypeDefinition->text());
    typeGroup->setTypeLabel(m_editTypeLabel->text());
    typeGroup->setTypeLink(m_editTypeLink->itemData(m_editTypeLink->currentIndex()).toString());
}

void TypeGroupEditBox::onChange(int index) {
    if(m_editTypeLink->itemData(index).isValid())
        qDebug() << m_editTypeLink->itemData(index).toString();
    else
        qDebug() << m_editTypeLink->currentText();
}

void TypeGroupEditBox::onInsertion(QString text) {
    m_linksMap.insert(text,text);
    m_editTypeLink->itemData(m_editTypeLink->currentIndex()).setValue(text);
}
