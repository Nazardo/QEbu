#ifndef LANGUAGETYPEFORM_H
#define LANGUAGETYPEFORM_H

#include "stackablewidget.h"

class LanguageType;
class TypeGroupEditBox;
class ElementTypeEditBox;
class QTextEdit;

class LanguageTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit LanguageTypeForm(LanguageType *language,
                              QEbuMainWindow *mainWindow,
                              QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
private:
    TypeGroupEditBox *m_editTypeGroup;
    QTextEdit *m_textNote;
    ElementTypeEditBox *m_editElementLanguage;
    LanguageType *m_language;
};
#endif // LANGUAGETYPEFORM_H
