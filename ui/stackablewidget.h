#ifndef STACKABLEWIDGET_H
#define STACKABLEWIDGET_H

#include <QWidget>
#include "qebumainwindow.h"

class QEbuMainWindow;

class StackableWidget : public QWidget
{
    Q_OBJECT
public:
    StackableWidget(QEbuMainWindow *mainWindow, QWidget *parent = 0) : QWidget(parent)
    {
        m_mainWindow = mainWindow;
    }

    virtual QString toString() = 0;
    virtual void updateData() = 0;
protected:
    QEbuMainWindow *mainWindow()
    {
        return m_mainWindow;
    }
    
signals:
    void closed();
public slots:

private:
    QEbuMainWindow *m_mainWindow;
    
};

#endif // STACKABLEWIDGET_H
