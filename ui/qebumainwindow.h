#ifndef QEBUMAINWINDOW_H
#define QEBUMAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QStackedWidget>
#include "stackablewidget.h"

class StackableWidget;

class QEbuMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit QEbuMainWindow(QWidget *parent = 0);
    ~QEbuMainWindow();
    void pushWidget(StackableWidget *widget);
    
private slots:
    void childClosed();

private:
    QLayout *m_mainCentralLayout;
    QStackedWidget *m_stackedWidget;
};

#endif // QEBUMAINWINDOW_H
