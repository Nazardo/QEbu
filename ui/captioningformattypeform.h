#ifndef CAPTIONINGFORMATTYPEFORM_H
#define CAPTIONINGFORMATTYPEFORM_H

#include "stackablewidget.h"

class CaptioningFormatType;
class QLineEdit;
class TypeGroupEditBox;
class FormatGroupEditBox;

class CaptioningFormatTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit CaptioningFormatTypeForm(CaptioningFormatType *captioningFormat,
                                      QEbuMainWindow *mainWindow,
                                      QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
private:
    QLineEdit *m_editTrackId;
    QLineEdit *m_editTrackName;
    QLineEdit *m_editLanguage;
    TypeGroupEditBox *m_editTypeGroup;
    FormatGroupEditBox *m_editFormatGroup;
    QLineEdit *m_editCaptioningSourceUri;
    QLineEdit *m_editCaptioningFormatId;
    QLineEdit *m_editCaptioningFormatName;
    CaptioningFormatType *m_captioningFormat;
};

#endif // CAPTIONINGFORMATTYPEFORM_H
