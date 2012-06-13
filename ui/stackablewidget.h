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

#ifndef STACKABLEWIDGET_H
#define STACKABLEWIDGET_H

#include <QWidget>
#include <QVariant>
#include "qebumainwindow.h"

class QVBoxLayout;
class QLayout;
class QTextBrowser;
class VerticalScrollArea;

class StackableWidget : public QWidget
{
    Q_OBJECT
protected:
    enum Operation { Add, Edit };
    enum WidgetItem {
        None        = 0x00000000,
        DocText     = 0x00000002,
        ApplyCancel = 0x00000400
    };
    Q_DECLARE_FLAGS(WidgetItems, WidgetItem)

    QEbuMainWindow *mainWindow();
    void setLayout(QLayout *layout); // Overrides QWidget::setLayout()

    Operation m_op;
public:
    StackableWidget(QEbuMainWindow *mainWindow,
                    QWidget *parent = 0,
                    WidgetItems items = WidgetItems(DocText | ApplyCancel));
    virtual QString toString() = 0;
signals:
    void closed(enum Operation op, QVariant value);
protected slots:
    virtual void applyClicked();
    virtual void cancelClicked();
protected:
    QTextBrowser *m_textDocumentation;
private:
    QVBoxLayout *m_vLayout;
    QEbuMainWindow *m_mainWindow;
    VerticalScrollArea *m_verticalScrollArea;
    
};

#endif // STACKABLEWIDGET_H
