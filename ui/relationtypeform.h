#ifndef RELATIONTYPEFORM_H
#define RELATIONTYPEFORM_H

#include "stackablewidget.h"

class RelationType;
class QSpinBox;
class QCheckBox;
class QTextEdit;
class QLineEdit;
class TypeGroupEditBox;
class ElementTypeEditBox;

class RelationTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit RelationTypeForm(RelationType *relation,
                              QEbuMainWindow *mainWindow,
                              QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
    void setTitle(const QString &title);
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
    bool eventFilter(QObject *obj, QEvent *event);

    TypeGroupEditBox *m_editTypeGroup;
    QSpinBox *m_spinRunningOrderNumber;
    QCheckBox *m_checkRunningOrderNumber;
    QTextEdit *m_textNote;
    QLineEdit *m_editRelationLink;
    ElementTypeEditBox *m_editElementRelation;
    QLineEdit *m_editRelationIdentifier;
    RelationType *m_relation;
    QString m_title;
};

#endif // RELATIONTYPEFORM_H
