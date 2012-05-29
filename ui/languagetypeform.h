#ifndef LANGUAGETYPEFORM_H
#define LANGUAGETYPEFORM_H

#include "ebucoremainform.h"
#include "typegroupeditbox.h"
#include "elementtypeeditbox.h"
#include <QTextEdit>

class LanguageTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit LanguageTypeForm(LanguageType *language, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // -
private:
    TypeGroupEditBox *m_editTypeGroup;
    QTextEdit *m_textNote;
    ElementTypeEditBox *m_editElementLanguage;
    LanguageType *m_language;
    Operation m_op;
};
#endif // LANGUAGETYPEFORM_H
