#ifndef ASPECTRATIOTYPE_H
#define ASPECTRATIOTYPE_H

#include "stackablewidget.h"
#include <QMap>

class AspectRatioType;
class FormatGroupEditBox;
class QTextEdit;
class QString;

class AspectRatioTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit AspectRatioTypeForm(AspectRatioType *aspectRatio,
                                 QEbuMainWindow *mainWindow,
                                 QWidget *parent = 0);
    QString toString();
    void addLinksMap(QMap<QString, QString> *values);
signals:
private slots:
    void cancelClicked();
    void applyClicked();
private:
    bool eventFilter(QObject *obj, QEvent *event);
    FormatGroupEditBox *m_editFormatGroup;
    QTextEdit *m_textNote;
    AspectRatioType *m_aspectRatio;
};

#endif // ASPECTRATIOTYPE_H
