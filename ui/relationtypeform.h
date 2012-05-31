#ifndef RELATIONTYPEFORM_H
#define RELATIONTYPEFORM_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QCheckBox>
#include "stackablewidget.h"
#include "typegroupeditbox.h"
#include "elementtypeeditbox.h"
#include "../model/coremetadatatype.h"

class RelationTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit RelationTypeForm(RelationType *relation, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // -
    void relationIdentifierRemoveClicked();
    void relationIdentifierClicked();
    void relationIdentifierClosed(Operation op, QVariant value);
    // -
    void runningOrderNumberChanged();
private:

    QHBoxLayout *m_mainHLayout;
    TypeGroupEditBox *m_editTypeGroup;
    QSpinBox *m_spinRunningOrderNumber;
    QCheckBox *m_checkRunningOrderNumber;
    QTextEdit *m_textNote;
    QLineEdit *m_editRelationLink;
    ElementTypeEditBox *m_editElementRelation;
    QLineEdit *m_editRelationIdentifier;
    Operation m_op;
    RelationType *m_relation;
};

#endif // RELATIONTYPEFORM_H
