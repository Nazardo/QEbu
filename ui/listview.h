/****************************************************************************
** Copyright (C) 2012 by
**  Mauro Levra  (nazardo)     mauro@nazardo.it
**  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it
**  Denis Patti  (dextp3)      denis.patti@studenti.polito.it
**  Giovanni Pessiva           giovanni.pessiva@gmail.com
**  Stefano Ricossa            stefano.ricossa@gmail.com
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

#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QWidget>
#include <QList>

class QLabel;
class QListWidget;
class QPushButton;
class QListWidgetItem;

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
    QPushButton *m_buttonAdd;
    QPushButton *m_buttonEdit;
    QPushButton *m_buttonRemove;
};

#endif // LISTVIEW_H
