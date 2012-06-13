#include "formatgroupeditbox.h"
#include "../model/formatgroup.h"
#include "../model/typeconverter.h"
#include <QLineEdit>
#include <QFormLayout>
#include <QGroupBox>
#include <QString>
#include <QComboBox>
#include <QDebug>

FormatGroupEditBox::FormatGroupEditBox(FormatGroup *formatGroup,
                                       QWidget *parent) :
    QWidget(parent)
{
    m_editFormatLabel = new QLineEdit(this);
    m_editFormatDefinition = new QLineEdit(this);
    m_editFormatLink = new QComboBox(this);
    QHBoxLayout *l = new QHBoxLayout;
    QFormLayout *formL = new QFormLayout;
    m_groupBox = new QGroupBox(tr("Format"));
    formL->addRow(tr("Label"), m_editFormatLabel);
    formL->addRow(tr("Definition"), m_editFormatDefinition);
    formL->addRow(tr("Link"), m_editFormatLink);
    m_groupBox->setLayout(formL);
    l->addWidget(m_groupBox);
    this->setLayout(l);

    m_editFormatLink->setEditable(true);
    m_editFormatLink->setInsertPolicy(QComboBox::InsertAtTop);
    QObject::connect(m_editFormatLink, SIGNAL(currentIndexChanged(int)), this, SLOT(onChange(int)));
    QObject::connect(m_editFormatLink->lineEdit(), SIGNAL(editingFinished()), this, SLOT(onChange()));
    m_editFormatLink->setStyleSheet("QComboBox::drop-down {border-width: 0px;} \
                                  QComboBox::down-arrow {image: url(noimg); \
                                  border-width: 0px;}");
    m_editFormatLink->setToolTip("Press Enter to save your custom value");
    m_editFormatLink->setValidator(TypeConverter::getUriValidator());

    if (!formatGroup) {
        m_editFormatLink->addItem("",""); //Add an empty item
        return;
    }
    // Set text fields
    m_editFormatLabel->setText(formatGroup->formatLabel());
    m_editFormatDefinition->setText(formatGroup->formatDefinition());
    m_editFormatLink->addItem(formatGroup->formatLink(),formatGroup->formatLink());
}

FormatGroup *FormatGroupEditBox::formatGroup()
{
    FormatGroup *formatGroup = new FormatGroup;
    updateExistingFormatGroup(formatGroup);
    return formatGroup;
}

void FormatGroupEditBox::setLabel(const QString &label)
{
    m_groupBox->setTitle(label);
}

void FormatGroupEditBox::addLinksMap(QMap<QString, QString> *values)
{
    int currentIndex = m_editFormatLink->currentIndex();
    QString selectedData = m_editFormatLink->itemData(currentIndex).toString();

    m_editFormatLink->setStyleSheet(""); //Restore default style (show arrow)

    QList<QString> keys = values->keys();
    for (int i=0; i < keys.size(); ++i) {
        QString key = keys.at(i);
        if (m_editFormatLink->findText(values->value(key)) == -1) {
            // Discart duplicates (new user-defined values are saved in every maps used)
            m_editFormatLink->addItem(values->value(key),key);
            if (currentIndex == 0 && key == selectedData) { // This is the value previously stored
                m_editFormatLink->setItemData(currentIndex,""); //This is the empty value
                m_editFormatLink->setItemText(currentIndex,""); //This is the empty value
                m_editFormatLink->setCurrentIndex(m_editFormatLink->count()-1); //Select this last item
            }
        }
    }

    m_linkMaps.append(values);  // Save the pointer to this linkMap
}

QLineEdit *FormatGroupEditBox::editFormatLabel()
{
    return m_editFormatLabel;
}

QComboBox *FormatGroupEditBox::editFormatLink()
{
    return m_editFormatLink;
}

QLineEdit *FormatGroupEditBox::editFormatDefinition()
{
    return m_editFormatDefinition;
}

void FormatGroupEditBox::updateExistingFormatGroup(FormatGroup *formatGroup)
{
    formatGroup->setFormatLabel(m_editFormatDefinition->text());
    formatGroup->setFormatDefinition(m_editFormatLabel->text());
    formatGroup->setFormatLink(m_editFormatLink->itemData(m_editFormatLink->currentIndex()).toString());
}

void FormatGroupEditBox::onChange(int index) {
    if(m_editFormatLink->itemData(index).isValid()) {
        qDebug() << m_editFormatLink->itemData(index).toString();
    } else {
        QString linkText = m_editFormatLink->itemText(index);
        m_editFormatLink->setItemData(index, linkText);
        qDebug() <<"New value:" << linkText;

        //Add it to the autocompletion maps
        for (int i=0;    i<m_linkMaps.size();    i++)
            m_linkMaps[i]->insert(linkText,linkText);
    }
}

void FormatGroupEditBox::onChange()
{
    QString s = m_editFormatLink->lineEdit()->text();
    if (m_editFormatLink->findText(s) < 0) {
        m_editFormatLink->addItem(s, s);
        //Add it to the autocompletion maps
        for (int i=0; i<m_linkMaps.size(); ++i)
            m_linkMaps[i]->insert(s,s);
        int i = m_editFormatLink->findText(s);
        if (i >= 0)
            m_editFormatLink->setCurrentIndex(i);
    }
}
