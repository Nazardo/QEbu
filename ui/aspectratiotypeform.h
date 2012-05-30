#ifndef ASPECTRATIOTYPE_H
#define ASPECTRATIOTYPE_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include "stackablewidget.h"
#include "formatgroupeditbox.h"

class AspectRatioTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit AspectRatioTypeForm(AspectRatioType *aspectRatio, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
private:

    QHBoxLayout *m_mainHLayout;
    FormatGroupEditBox *m_editFormatGroup;
    QTextEdit *m_textNote;
    Operation m_op;
    AspectRatioType *m_aspectRatio;
};

#endif // ASPECTRATIOTYPE_H
