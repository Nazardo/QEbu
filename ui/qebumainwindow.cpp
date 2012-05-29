#include "qebumainwindow.h"
#include "ebucoremainform.h"
#include "../model/ebucoremaintype.h"
#include <QtGui>


QEbuMainWindow::QEbuMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *cw = new QWidget;
    m_mainCentralLayout = new QVBoxLayout;
    m_mainCentralLayout->addWidget(new QLabel(tr("<h2>QEbu</h2>")));
    m_stackedWidget = new QStackedWidget;
    m_ebuCoreMain = new EbuCoreMainType;
    StackableWidget *main = new EbuCoreMainForm(m_ebuCoreMain, this);
    m_stackedWidget->addWidget(main);
    m_mainCentralLayout->addWidget(m_stackedWidget);
    cw->setLayout(m_mainCentralLayout);
    this->setCentralWidget(cw);
}

QEbuMainWindow::~QEbuMainWindow()
{
}

void QEbuMainWindow::pushWidget(StackableWidget *widget)
{
    m_stackedWidget->addWidget(widget);
    m_stackedWidget->setCurrentWidget(widget);
    QObject::connect(widget, SIGNAL(closed(Operation,QVariant)), this, SLOT(childClosed()));
}

EbuCoreMainType *QEbuMainWindow::ebuCoreMain()
{
    return m_ebuCoreMain;
}

void QEbuMainWindow::childClosed()
{
    QWidget *currentWidget = m_stackedWidget->currentWidget();
    m_stackedWidget->removeWidget(currentWidget);
//    currentWidget->deleteLater();
//    StackableWidget *old = dynamic_cast<StackableWidget *>(m_stackedWidget->currentWidget());
}
