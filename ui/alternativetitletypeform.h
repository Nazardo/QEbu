#ifndef ALTERNATIVETITLETYPEFORM_H
#define ALTERNATIVETITLETYPEFORM_H

#include "stackablewidget.h"

class QTextEdit;
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
    bool checkCompliance();
private slots:
    void applyClicked();
    void cancelClicked();
private:
    bool eventFilter(QObject *obj, QEvent *event);
    AlternativeTitleType *m_alternativeTitle;
    TypeGroupEditBox *m_editTypeGroup;
    StatusGroupEditBox *m_editStatusGroup;
    DateGroupEditBox *m_editDateGroup;
    QTextEdit *m_textNote;
    ElementTypeEditBox *m_editTitle;
};

#endif // ALTERNATIVETITLETYPEFORM_H
