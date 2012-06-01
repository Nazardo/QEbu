#ifndef TECHNICALATTRIBUTEURITYPEFORM_H
#define TECHNICALATTRIBUTEURITYPEFORM_H

#include "stackablewidget.h"

class TechnicalAttributeUriType;
class QLineEdit;
class TypeGroupEditBox;

class TechicalAttributeUriTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit TechicalAttributeUriTypeForm(TechnicalAttributeUriType *uri,
                                          QEbuMainWindow *mainWindow,
                                          QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
private:
    QLineEdit *m_editValue;
    TypeGroupEditBox *m_editTypeGroup;
    TechnicalAttributeUriType  *m_uri;
};

#endif // TECHNICALATTRIBUTEURITYPEFORM_H
