#ifndef ALTERNATIVETYPEFORM_H
#define ALTERNATIVETYPEFORM_H

#include "stackablewidget.h"

class AlternativeType;
class CoreMetadataType;
class DateGroupEditBox;
class TypeGroupEditBox;

class AlternativeTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit AlternativeTypeForm(AlternativeType *alternative,
                                 QEbuMainWindow *mainWindow,
                                 QWidget *parent = 0);
    QString toString();
    void setTitle(const QString &title);
private slots:
    void cancelClicked();
    void applyClicked();
private:
    bool eventFilter(QObject *obj, QEvent *event);
    AlternativeType *m_alternative;
    DateGroupEditBox *m_editDateGroup;
    TypeGroupEditBox *m_editTypeGroup;
};

#endif // ALTERNATIVETYPEFORM_H
