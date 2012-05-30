#ifndef ALTERNATIVETYPEFORM_H
#define ALTERNATIVETYPEFORM_H

#include "stackablewidget.h"
#include "../model/coremetadatatype.h"
#include "dategroupeditbox.h"
#include "typegroupeditbox.h"

class AlternativeTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit AlternativeTypeForm(AlternativeType *alternative, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    void setTitle(const QString &title);
private slots:
    void cancelClicked();
    void applyClicked();
private:
    AlternativeType *m_alternative;
    DateGroupEditBox *m_editDateGroup;
    TypeGroupEditBox *m_editTypeGroup;
    Operation m_op;
};

#endif // ALTERNATIVETYPEFORM_H
