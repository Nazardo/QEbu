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

    QLayout *m_mainCentralLayout;
    EbuCoreMainType *m_ebuCoreMain;
    QStackedWidget *m_stackedWidget;
    QLabel *m_labelNavigation;
    QList<QString> m_listLabel;
    QMap<QString, QMap<QString,QString> * > m_maps;
};

#endif // QEBUMAINWINDOW_H
