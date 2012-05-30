#ifndef CAPTIONINGFORMATTYPEFORM_H
#define CAPTIONINGFORMATTYPEFORM_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include "stackablewidget.h"
#include "typegroupeditbox.h"
#include "formatgroupeditbox.h"

class CaptioningFormatTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit CaptioningFormatTypeForm(CaptioningFormatType *captioningFormat, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
private:

    QHBoxLayout *m_mainHLayout;
    QLineEdit *m_editTrackId;
    QLineEdit *m_editTrackName;
    QLineEdit *m_editLanguage;
    TypeGroupEditBox *m_editTypeGroup;
    FormatGroupEditBox *m_editFormatGroup;
    QLineEdit *m_editCaptioningSourceUri;
    QLineEdit *m_editCaptioningFormatId;
    QLineEdit *m_editCaptioningFormatName;
    Operation m_op;
    CaptioningFormatType *m_captioningFormat;
};

#endif // CAPTIONINGFORMATTYPEFORM_H
