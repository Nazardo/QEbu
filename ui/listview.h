#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QWidget>
#include <QList>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>

class ListView : public QWidget
{
    Q_OBJECT
public:
    ListView(QString name = QString(), QWidget *parent = 0);
    void setTitle(QString &title);
    void setContent(const QList<QListWidgetItem *> &items);
    void addItem(const QString &label);
    void setItem(int row, const QString &label);
    QString item(int row);
    void removeAt(int row);
    int selected();
    void clear();
    void enableAdd(bool state);
    QPushButton *buttonAdd();
    QPushButton *buttonEdit();
    QPushButton *buttonRemove();

private:
    QLabel *m_labelTitle;
    QListWidget *m_listWidget;
    QPushButton *m_buttonClose;
    QPushButton *m_buttonAdd;
    QPushButton *m_buttonEdit;
    QPushButton *m_buttonRemove;
};

#endif // LISTVIEW_H
