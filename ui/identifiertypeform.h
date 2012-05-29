#ifndef IDENTIFIERTYPEFORM_H
#define IDENTIFIERTYPEFORM_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include "stackablewidget.h"
#include "typegroupeditbox.h"
#include "formatgroupeditbox.h"
#include "elementtypeeditbox.h"
#include "../model/coremetadatatype.h"

class IdentifierTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit IdentifierTypeForm(IdentifierType *identifier, QEbuMainWindow *mainWindow, QWidget *parent = 0);
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

    QHBoxLayout *m_mainHLayout;
    TypeGroupEditBox *m_editTypeGroup;
    FormatGroupEditBox *m_editFormatGroup;
    QTextEdit *m_textNote;
    QLineEdit *m_editRelationLink;
    ElementTypeEditBox *m_editElementIdentifier;
    QLineEdit *m_editAttributor;
    Operation m_op;
    IdentifierType *m_identifier;
};


#endif // IDENTIFIERTYPEFORM_H
