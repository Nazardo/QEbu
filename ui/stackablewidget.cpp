#include "stackablewidget.h"
#include <QVariant>
#include <QVBoxLayout>
#include <QLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QTextEdit>
#include <QEvent>

StackableWidget::StackableWidget(QEbuMainWindow *mainWindow,
                                 QWidget *parent,
                                 WidgetItems items)
    : QWidget(parent)
{
    m_mainWindow = mainWindow;
    m_vLayout = new QVBoxLayout;
    QWidget::setLayout(m_vLayout);

    // Add lastRow layout
    if (items.testFlag(None))
        return;
    QHBoxLayout *lastRow = new QHBoxLayout;
    m_vLayout->addLayout(lastRow);
    if (items.testFlag(ApplyCancel)) {
        QDialogButtonBox *dialogButtonBox = new QDialogButtonBox(
                    QDialogButtonBox::Apply | QDialogButtonBox::Cancel,
                    Qt::Horizontal);
        lastRow->addWidget(dialogButtonBox, 0, Qt::AlignLeft | Qt::AlignBottom);
        QObject::connect(dialogButtonBox->button(QDialogButtonBox::Apply),
                         SIGNAL(clicked()), this, SLOT(applyClicked()));
        QObject::connect(dialogButtonBox, SIGNAL(rejected()),
                         this, SLOT(cancelClicked()));

    }
    if (items.testFlag(DocText)) {
        m_textDocumentation = new QTextEdit;
        m_textDocumentation->setReadOnly(true);
        QPalette* palette = new QPalette();
        palette->setColor(QPalette::Base, palette->color(QPalette::Window));
        m_textDocumentation->setFrameShape( QTextEdit::NoFrame );
        m_textDocumentation->setPalette(*palette);
        m_textDocumentation->setFrameShadow( QTextEdit::Plain );
        m_textDocumentation->setMinimumHeight(80);
        m_textDocumentation->setMaximumSize(400, 160);
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
    m_vLayout->insertLayout(0, layout);
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
