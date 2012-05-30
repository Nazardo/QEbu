#ifndef ALTERNATIVETITLETYPEFORM_H
#define ALTERNATIVETITLETYPEFORM_H

#include "stackablewidget.h"

class QLineEdit;
class AlternativeTitleType;
class TypeGroupEditBox;
class StatusGroupEditBox;
class DateGroupEditBox;
class ElementTypeEditBox;

class AlternativeTitleTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit AlternativeTitleTypeForm(AlternativeTitleType *alternativeTitle,
                                      QEbuMainWindow *mainWindow,
                                      QWidget *parent = 0);
    QString toString();
private slots:
    void applyClicked();
    void cancelClicked();
private:
    AlternativeTitleType *m_alternativeTitle;
    TypeGroupEditBox *m_editTypeGroup;
    StatusGroupEditBox *m_editStatusGroup;
    DateGroupEditBox *m_editDateGroup;
    QLineEdit *m_editNote;
    ElementTypeEditBox *m_editTitle;
    Operation m_op;
};

#endif // ALTERNATIVETITLETYPEFORM_H
