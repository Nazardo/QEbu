#ifndef QEBUMAINWINDOW_H
#define QEBUMAINWINDOW_H

#include <QMainWindow>

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
    
private slots:
    void childClosed();

private:
    void updateLabel();

    QLayout *m_mainCentralLayout;
    EbuCoreMainType *m_ebuCoreMain;
    QStackedWidget *m_stackedWidget;
    QLabel *m_labelNavigation;
    QList<QString> m_listLabel;
};

#endif // QEBUMAINWINDOW_H
