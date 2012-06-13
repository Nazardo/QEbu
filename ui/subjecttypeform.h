#ifndef SUBJECTTYPEFORM_H
#define SUBJECTTYPEFORM_H

#include "stackablewidget.h"
#include <QMap>

class SubjectType;
class TypeGroupEditBox;
class ElementTypeEditBox;
class QTextEdit;
class QLineEdit;
class QComboBox;
class QString;

class SubjectTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit SubjectTypeForm(SubjectType *subject,
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
    void onChange(int index);
    void onChange();
private:
    bool eventFilter(QObject *obj, QEvent *event);

    TypeGroupEditBox *m_editTypeGroup;
    QTextEdit *m_textNote;
    ElementTypeEditBox *m_editElementSubject;
    QComboBox *m_editSubjectCode;
    QLineEdit *m_editSubjectDefinition;
    QLineEdit *m_editAttributor;
    SubjectType *m_subject;
    QMap<QString, QString> *m_linkMap;
};

#endif // SUBJECTTYPEFORM_H
