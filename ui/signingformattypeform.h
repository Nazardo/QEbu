#ifndef SIGNINGFORMATTYPEFORM_H
#define SIGNINGFORMATTYPEFORM_H


#include "stackablewidget.h"
#include "../model/ebucoremaintype.h"
#include "typegroupeditbox.h"
#include "formatgroupeditbox.h"
#include <QLineEdit>

class SigningFormatTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit SigningFormatTypeForm(SigningFormatType *signingFormat, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // -
private:
    QLineEdit *m_editTrackId;
    QLineEdit *m_editTrackName;
    QLineEdit *m_editLanguage;
    TypeGroupEditBox *m_editTypeGroup;
    FormatGroupEditBox *m_editFormatGroup;
    QLineEdit *m_editSigningSourceUri;
    QLineEdit *m_editSigningFormatId;
    QLineEdit *m_editSigningFormatName;
    QLineEdit *m_editSigningFormatDefinition;
    SigningFormatType *m_signingFormat;
    Operation m_op;
};

#endif // SIGNINGFORMATTYPEFORM_H