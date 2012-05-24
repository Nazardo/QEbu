#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QWidget>
#include <QList>
#include <QPushButton>
#include <QListWidget>

class ListView : public QWidget
{
    Q_OBJECT
public:
    ListView(QString name, QWidget *parent = 0);
    void setContent(const QList<QListWidgetItem *> &items);
    void addItem(QString label);
    void setItem(int row, QString label);
    void removeAt(int row);
    int selected();
    QPushButton *buttonAdd();
    QPushButton *buttonEdit();
    QPushButton *buttonRemove();
    QPushButton *buttonClose();

private:
    QListWidget *m_listWidget;
    QPushButton *m_buttonClose;
    QPushButton *m_buttonAdd;
    QPushButton *m_buttonEdit;
    QPushButton *m_buttonRemove;
};

#endif // LISTVIEW_H
