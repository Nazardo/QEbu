#ifndef TYPEGROUPFORM_H
#define TYPEGROUPFORM_H

#include "stackablewidget.h"
#include <QMap>

class TypeGroup;
class TypeGroupEditBox;
class QString;

class TypeGroupForm : public StackableWidget
{
Q_OBJECT
public:
    explicit TypeGroupForm(TypeGroup *typeGroup,
                           QEbuMainWindow *mainWindow,
                           QWidget *parent = 0);
    QString toString();
    void setTitle(const QString &title);
    void addLinksMap(QMap<QString,QString> *values);
private slots:
    void cancelClicked();
    void applyClicked();
private:
    bool eventFilter(QObject *, QEvent *);
    TypeGroupEditBox *m_editTypeGroup;
    QString m_title;
    TypeGroup *m_typeGroup;
};

#endif // TYPEGROUPFORM_H
