#ifndef VIDEOTRACKTYPEFORM_H
#define VIDEOTRACKTYPEFORM_H

#include "stackablewidget.h"
#include "typegroupeditbox.h"
#include <QTextEdit>
#include <QLineEdit>

class VideoTrackTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit VideoTrackTypeForm(VideoTrackType *videoTrack, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
private slots:
    void cancelClicked();
    void applyClicked();
private:
    QVBoxLayout *m_mainVLayout;
    QLineEdit *m_editTrackId;
    QLineEdit *m_editTrackName;
    TypeGroupEditBox *m_editTypeGroup;
    VideoTrackType *m_videoTrack;
    Operation m_op;
};

#endif // VIDEOTRACKTYPEFORM_H
