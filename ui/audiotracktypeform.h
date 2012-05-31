#ifndef AUDIOTRACKTYPEFORM_H
#define AUDIOTRACKTYPEFORM_H

#include "stackablewidget.h"
#include "../model/ebucoremaintype.h"
#include "typegroupeditbox.h"
#include <QLineEdit>

class AudioTrackTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit AudioTrackTypeForm(AudioTrackType *signingFormat, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // -
private:
    QHBoxLayout *m_mainHLayout;
    QLineEdit *m_editTrackLanguage;
    QLineEdit *m_editTrackId;
    QLineEdit *m_editTrackName;
    TypeGroupEditBox *m_editTypeGroup;
    QLineEdit *m_editSigningFormatDefinition;
    AudioTrackType *m_audioTrack;
    Operation m_op;
};

#endif // AUDIOTRACKTYPEFORM_H
