#ifndef VERTICALSCROLLAREA_H
#define VERTICALSCROLLAREA_H

#include <QScrollArea>

class VerticalScrollArea : public QScrollArea
{
public:
    VerticalScrollArea(QWidget *parent = 0);
    bool eventFilter(QObject *o, QEvent *e);
    void setLayout(QLayout *layout); // override QWidget::setLayout()
private:
    QWidget *m_scrollAreaWidgetContents;
};


#endif // VERTICALSCROLLAREA_H
