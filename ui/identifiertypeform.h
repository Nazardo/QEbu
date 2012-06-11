#ifndef IDENTIFIERTYPEFORM_H
#define IDENTIFIERTYPEFORM_H

#include "stackablewidget.h"

class IdentifierType;
class TypeGroupEditBox;
class FormatGroupEditBox;
class QTextEdit;
class QLineEdit;
class ElementTypeEditBox;

class IdentifierTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit IdentifierTypeForm(IdentifierType *identifier,
                                QEbuMainWindow *mainWindow,
                                QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // -
    void attributorRemoveClicked();
    void attributorClicked();
    void attributorClosed(Operation op, QVariant value);
private:
    bool eventFilter(QObject *obj, QEvent *event);
    TypeGroupEditBox *m_editTypeGroup;
    FormatGroupEditBox *m_editFormatGroup;
    QTextEdit *m_textNote;
    ElementTypeEditBox *m_editElementIdentifier;
    QLineEdit *m_editAttributor;
    IdentifierType *m_identifier;
};


#endif // IDENTIFIERTYPEFORM_H
