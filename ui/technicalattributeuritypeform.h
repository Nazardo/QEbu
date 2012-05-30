#ifndef TECHNICALATTRIBUTEURITYPEFORM_H
#define TECHNICALATTRIBUTEURITYPEFORM_H

#include "stackablewidget.h"
#include "typegroupeditbox.h"
#include <QLineEdit>

class TechicalAttributeUriTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit TechicalAttributeUriTypeForm(TechnicalAttributeUriType *uri, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
private:
    QHBoxLayout *m_mainHLayout;
    QLineEdit *m_editValue;
    TypeGroupEditBox *m_editTypeGroup;
    TechnicalAttributeUriType  *m_uri;
    Operation m_op;
};

#endif // TECHNICALATTRIBUTEURITYPEFORM_H
