/****************************************************************************
** Copyright (C) 2012 by
**  Mauro Levra  (nazardo)     mauro@nazardo.it
**  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it
**  Denis Patti  (dextp3)      denis.patti@studenti.polito.it
**  Giovanni Pessiva           giovanni.pessiva@gmail.com
**  Stefano Ricossa            stefano.ricossa@studenti.polito.it
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

#include "stackablewidget.h"
#include "verticalscrollarea.h"
#include <QVariant>
#include <QVBoxLayout>
#include <QLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QTextBrowser>
#include <QEvent>

StackableWidget::StackableWidget(QEbuMainWindow *mainWindow,
                                 QWidget *parent,
                                 WidgetItems items)
    : QWidget(parent)
{
    m_mainWindow = mainWindow;
    m_vLayout = new QVBoxLayout;
    QWidget::setLayout(m_vLayout);

    m_verticalScrollArea = new VerticalScrollArea;
    m_verticalScrollArea->setFrameStyle(QFrame::Panel | QFrame::Raised);
    m_vLayout->addWidget(m_verticalScrollArea);

    // Add lastRow layout
    if (items.testFlag(None))
        return;
    QHBoxLayout *lastRow = new QHBoxLayout;
    m_vLayout->addLayout(lastRow);
    if (items.testFlag(ApplyCancel)) {
        QDialogButtonBox *dialogButtonBox = new QDialogButtonBox(
                    QDialogButtonBox::Apply | QDialogButtonBox::Cancel,
                    Qt::Horizontal);
        lastRow->addWidget(dialogButtonBox, 0, Qt::AlignLeft);
        QObject::connect(dialogButtonBox->button(QDialogButtonBox::Apply),
                         SIGNAL(clicked()), this, SLOT(applyClicked()));
        QObject::connect(dialogButtonBox, SIGNAL(rejected()),
                         this, SLOT(cancelClicked()));

    }
    if (items.testFlag(DocText)) {
        m_textDocumentation = new QTextBrowser;
        m_textDocumentation->setReadOnly(true);
        m_textDocumentation->setOpenExternalLinks(true);
        QPalette* palette = new QPalette();
        palette->setColor(QPalette::Base, Qt::transparent);
        m_textDocumentation->setFrameShape( QTextEdit::NoFrame );
        m_textDocumentation->setPalette(*palette);
        m_textDocumentation->setFrameShadow( QTextEdit::Plain );
        m_textDocumentation->setMinimumHeight(40);
        m_textDocumentation->setMaximumSize(400, 100);
        lastRow->addWidget(m_textDocumentation);
    }
    // ... maybe some day there will be other things to add.
}

QEbuMainWindow *StackableWidget::mainWindow()
{
    return m_mainWindow;
}

void StackableWidget::setLayout(QLayout *layout)
{
    //m_vLayout->insertLayout(0, layout);
    m_verticalScrollArea->setLayout(layout);
}

void StackableWidget::applyClicked()
{
    // Dummy implementation
    emit closed(m_op, 0);
}

void StackableWidget::cancelClicked()
{
    // Dummy implementation
    emit closed(m_op, 0);
}
