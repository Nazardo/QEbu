#ifndef FORMATGROUPFORM_H
#define FORMATGROUPFORM_H

#include "stackablewidget.h"
#include <QMap>

class FormatGroup;
class FormatGroupEditBox;
class QString;

class FormatGroupForm : public StackableWidget
{
Q_OBJECT
public:
    explicit FormatGroupForm(FormatGroup *typeGroup,
                             QEbuMainWindow *mainWindow,
                             QWidget *parent = 0);
    QString toString();
    void setTitle(const QString &title);
    void addLinksMap(QMap<QString, QString> *values);
private slots:
    void cancelClicked();
    void applyClicked();
private:
    FormatGroupEditBox *m_editFormatGroup;
    QString m_title;
};

#endif // FORMATGROUPFORM_H
