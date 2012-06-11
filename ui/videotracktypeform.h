#ifndef VIDEOTRACKTYPEFORM_H
#define VIDEOTRACKTYPEFORM_H

#include "stackablewidget.h"

class VideoTrackType;
class QLineEdit;
class TypeGroupEditBox;

class VideoTrackTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit VideoTrackTypeForm(VideoTrackType *videoTrack,
                                QEbuMainWindow *mainWindow,
                                QWidget *parent = 0);
    QString toString();
private slots:
    void cancelClicked();
    void applyClicked();
private:
    bool eventFilter(QObject *obj, QEvent *event);

    QLineEdit *m_editTrackId;
    QLineEdit *m_editTrackName;
    TypeGroupEditBox *m_editTypeGroup;
    VideoTrackType *m_videoTrack;
};

#endif // VIDEOTRACKTYPEFORM_H
