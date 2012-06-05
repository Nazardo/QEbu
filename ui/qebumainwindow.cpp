#include "qebumainwindow.h"
#include "../model/ebucoremaintype.h"
#include "ebucoremainform.h"
#include <QLabel>
#include <QLayout>
#include <QStackedWidget>


QEbuMainWindow::QEbuMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *cw = new QWidget;
    m_mainCentralLayout = new QVBoxLayout;
    m_labelNavigation = new QLabel;
    m_listLabel.append("<b>EbuCoreMain Type</b>");
    m_mainCentralLayout->addWidget(m_labelNavigation);
    m_stackedWidget = new QStackedWidget;
    m_ebuCoreMain = new EbuCoreMainType;
    StackableWidget *main = new EbuCoreMainForm(m_ebuCoreMain, this);
    m_stackedWidget->addWidget(main);
    m_mainCentralLayout->addWidget(m_stackedWidget);
    cw->setLayout(m_mainCentralLayout);
    updateLabel();
    this->setCentralWidget(cw);
}

QEbuMainWindow::~QEbuMainWindow()
{
    delete m_ebuCoreMain;
}

void QEbuMainWindow::pushWidget(StackableWidget *widget)
{
    QString title = widget->toString();
    m_listLabel.append(title);
    updateLabel();
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
    m_listLabel.takeLast();
    updateLabel();

}

void QEbuMainWindow::updateLabel()
{
    QString title = "";
    int size = m_listLabel.size();

    if (size > 5) {
        title += m_listLabel.at(0) + " > ...";
        for (int i = size - 4; i < size; ++i) {
            title += " > ";
            title += m_listLabel.at(i);
        }
    } else {
        for (int i = 0; i < size; ++i) {
            if (i > 0) title += " > ";
            title += m_listLabel.at(i);
        }
    }
    m_labelNavigation->setText(title);
}
