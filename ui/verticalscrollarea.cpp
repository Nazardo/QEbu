/****************************************************************************
** Copyright (C) 2012 by
**  Mauro Levra  (nazardo)     mauro@nazardo.it
**  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it
**  Denis Patti  (dextp3)      denis.patti@studenti.polito.it
**  Giovanni Pessiva           giovanni.pessiva@gmail.com
**  Stefano Ricossa            stefano.ricossa@gmail.com
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
