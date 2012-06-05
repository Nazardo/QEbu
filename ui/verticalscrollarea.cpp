#include "verticalscrollarea.h"
#include <QScrollArea>
#include <QScrollBar>
#include <QEvent>

VerticalScrollArea::VerticalScrollArea(QWidget *parent)
    : QScrollArea(parent)
{
    setWidgetResizable(true);
    setFrameStyle(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_scrollAreaWidgetContents = new QWidget(this);
    m_scrollAreaWidgetContents->setSizePolicy(QSizePolicy::Preferred,
                                              QSizePolicy::Preferred);
    setWidget(m_scrollAreaWidgetContents);
    m_scrollAreaWidgetContents->installEventFilter(this);
}

bool VerticalScrollArea::eventFilter(QObject *o, QEvent *e)
{
    if(o == m_scrollAreaWidgetContents && e->type() == QEvent::Resize)
        setMinimumWidth(m_scrollAreaWidgetContents->minimumSizeHint().width()
                        + verticalScrollBar()->width());
    return false;
}

void VerticalScrollArea::setLayout(QLayout *layout)
{
    m_scrollAreaWidgetContents->setLayout(layout);
}
