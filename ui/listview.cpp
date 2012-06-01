#include "listview.h"
#include <QList>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QLayout>

ListView::ListView(QString name, QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *verticalLayout = new QVBoxLayout;
    m_labelTitle = new QLabel(name);
    verticalLayout->addWidget(m_labelTitle);
    m_listWidget = new QListWidget(this);
    verticalLayout->addWidget(m_listWidget);
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

void ListView::setTitle(QString &title)
{
    m_labelTitle->setText("<h4>"+title+"</h4>");
}

void ListView::setContent(const QList<QListWidgetItem *> &items)
{
    int s = items.size();
    for (int i=0; i < s; ++i)
        m_listWidget->addItem(items.at(i));
}

void ListView::addItem(const QString &label)
{
    m_listWidget->addItem(new QListWidgetItem(label));
}

void ListView::setItem(int row, const QString &label)
{
    QListWidgetItem *wi = m_listWidget->item(row);
    if (wi)
        wi->setText(label);
}

QString ListView::item(int row)
{
    return m_listWidget->item(row)->text();
}

void ListView::removeAt(int row)
{
    delete m_listWidget->item(row);
}

int ListView::selected()
{
    return m_listWidget->currentIndex().row();
}

void ListView::clear()
{
    m_listWidget->clear();
    m_buttonAdd->setEnabled(true);
}

void ListView::enableAdd(bool state)
{
    m_buttonAdd->setEnabled(state);
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
