#include "listview.h"
#include <QtGui>
ListView::ListView(QString name, QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *verticalLayout = new QVBoxLayout;

    QHBoxLayout *header = new QHBoxLayout;
    header->addWidget(new QLabel(name));
    m_buttonClose = new QPushButton("<<");
    header->addWidget(m_buttonClose);
    verticalLayout->addLayout(header);

    listWidget = new QListWidget(this);
    verticalLayout->addWidget(listWidget);
    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    m_buttonAdd = new QPushButton(this);
    m_buttonAdd->setText(tr("Add"));
    horizontalLayout->addWidget(m_buttonAdd);
    m_buttonEdit = new QPushButton(this);
    m_buttonEdit->setText(tr("Edit"));
    horizontalLayout->addWidget(m_buttonEdit);
    m_buttonRemove = new QPushButton(this);
    m_buttonRemove->setText(tr("Remove"));
    horizontalLayout->addWidget(m_buttonRemove);
    verticalLayout->addLayout(horizontalLayout);
    this->setLayout(verticalLayout);
}

void ListView::setContent(const QList<QListWidgetItem *> &items)
{
    int s = items.size();
    for (int i=0; i < s; ++i)
        listWidget->addItem(items.at(i));
}

void ListView::addItem(QListWidgetItem *item)
{
    listWidget->addItem(item);
}

QPushButton *ListView::buttonAdd()
{
    return m_buttonAdd;
}

QPushButton *ListView::buttonEdit()
{
    return m_buttonEdit;
}

QPushButton *ListView::buttonRemove()
{
    return m_buttonRemove;
}

QPushButton *ListView::buttonClose()
{
    return m_buttonClose;
}
