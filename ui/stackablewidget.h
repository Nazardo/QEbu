#ifndef STACKABLEWIDGET_H
#define STACKABLEWIDGET_H

#include <QWidget>
#include <QVariant>
#include "qebumainwindow.h"

class QVBoxLayout;
class QLayout;

class StackableWidget : public QWidget
{
    Q_OBJECT
protected:
    enum Operation { Add, Edit };
    enum WidgetItem {
        None        = 0x00000000,
        ApplyCancel = 0x00000400
    };
    Q_DECLARE_FLAGS(WidgetItems, WidgetItem)

    QEbuMainWindow *mainWindow();
    void setLayout(QLayout *layout); // Overrides QWidget::setLayout()

    Operation m_op;
public:
    StackableWidget(QEbuMainWindow *mainWindow,
                    QWidget *parent = 0,
                    WidgetItems items = ApplyCancel);
    virtual QString toString() = 0;
signals:
    void closed(enum Operation op, QVariant value);
protected slots:
    virtual void applyClicked();
    virtual void cancelClicked();
private:
    QVBoxLayout *m_vLayout;
    QEbuMainWindow *m_mainWindow;
    
};

#endif // STACKABLEWIDGET_H
