#ifndef ASPECTRATIOTYPE_H
#define ASPECTRATIOTYPE_H

#include "stackablewidget.h"

class AspectRatioType;
class FormatGroupEditBox;
class QTextEdit;

class AspectRatioTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit AspectRatioTypeForm(AspectRatioType *aspectRatio,
                                 QEbuMainWindow *mainWindow,
                                 QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
private:
    FormatGroupEditBox *m_editFormatGroup;
    QTextEdit *m_textNote;
    AspectRatioType *m_aspectRatio;
};

#endif // ASPECTRATIOTYPE_H
