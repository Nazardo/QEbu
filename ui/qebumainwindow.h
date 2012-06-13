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

#ifndef QEBUMAINWINDOW_H
#define QEBUMAINWINDOW_H

#include <QMainWindow>
#include <QMap>

class QLayout;
class EbuCoreMainType;
class QStackedWidget;
class StackableWidget;
class QLabel;

class QEbuMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit QEbuMainWindow(QWidget *parent = 0);
    ~QEbuMainWindow();
    void pushWidget(StackableWidget *widget);
    EbuCoreMainType *ebuCoreMain();
    QMap<QString,QString> *getMap(QString name);
    QIcon ebuIcon() const;
private slots:
    void childClosed();

    void actionOpen();
    void actionSave();
    void actionClose();
    void actionQuit();
    void actionAbout();
    void actionWizard();
private:
    void resetView();
    bool removeWidgetFromTop();
    void updateLabel();

    bool doOpen();
    bool doSave();
    bool doClose();

    QIcon m_icon;
    QLayout *m_mainCentralLayout;
    EbuCoreMainType *m_ebuCoreMain;
    QStackedWidget *m_stackedWidget;
    QLabel *m_labelNavigation;
    QList<QString> m_listLabel;
    QMap<QString, QMap<QString,QString> * > m_maps;
};

#endif // QEBUMAINWINDOW_H
