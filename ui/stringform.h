#ifndef STRINGFORM_H
#define STRINGFORM_H

#include "stackablewidget.h"
#include "formatgroupeditbox.h"
#include "typegroupeditbox.h"
#include <QLineEdit>

class StringForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit StringForm(String *string, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
private:
    QHBoxLayout *m_mainHLayout;
    QLineEdit *m_editValue;
    FormatGroupEditBox *m_editFormatGroup;
    TypeGroupEditBox *m_editTypeGroup;
    String  *m_string;
    Operation m_op;
};

#endif // STRINGFORM_H
