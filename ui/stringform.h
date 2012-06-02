#ifndef STRINGFORM_H
#define STRINGFORM_H

#include "stackablewidget.h"

class String;
class QLineEdit;
class FormatGroupEditBox;
class TypeGroupEditBox;

class StringForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit StringForm(String *string,
                        QEbuMainWindow *mainWindow,
                        QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
private:
    QLineEdit *m_editValue;
    FormatGroupEditBox *m_editFormatGroup;
    TypeGroupEditBox *m_editTypeGroup;
    String  *m_string;
};

#endif // STRINGFORM_H
