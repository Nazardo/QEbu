#ifndef AUDIOTRACKTYPEFORM_H
#define AUDIOTRACKTYPEFORM_H

#include "stackablewidget.h"

class QLineEdit;
class TypeGroupEditBox;
class AudioTrackType;

class AudioTrackTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit AudioTrackTypeForm(AudioTrackType *signingFormat,
                                QEbuMainWindow *mainWindow,
                                QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
private:
    QLineEdit *m_editTrackLanguage;
    QLineEdit *m_editTrackId;
    QLineEdit *m_editTrackName;
    TypeGroupEditBox *m_editTypeGroup;
    QLineEdit *m_editSigningFormatDefinition;
    AudioTrackType *m_audioTrack;
};

#endif // AUDIOTRACKTYPEFORM_H
