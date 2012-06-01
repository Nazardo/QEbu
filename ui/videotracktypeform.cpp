#include "videotracktypeform.h"
#include "../model/formattype.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QFormLayout>

VideoTrackTypeForm::VideoTrackTypeForm(VideoTrackType *videoTrack,
                                       QEbuMainWindow *mainWindow,
                                       QWidget *parent)  :
    StackableWidget(mainWindow, parent)
{
    m_op = (videoTrack) ? Edit : Add;
    if (!videoTrack)
        m_videoTrack = new VideoTrackType;
    else
        m_videoTrack = videoTrack;
    // Layout
    QVBoxLayout *l = new QVBoxLayout;
    {
        QFormLayout *fl = new QFormLayout;
        m_editTrackId = new QLineEdit;
        fl->addRow(tr("Track ID"), m_editTrackId);
        m_editTrackName = new QLineEdit;
        fl->addRow(tr("Track Name"), m_editTrackName);
        l->addLayout(fl);
        m_editTypeGroup = new TypeGroupEditBox(videoTrack);
        l->addWidget(m_editTypeGroup);
    }
    this->setLayout(l);

    // Set data fields
    m_editTrackId->setText(m_videoTrack->trackId());
    m_editTrackName->setText(m_videoTrack->trackName());
}

QString VideoTrackTypeForm::toString()
{
        return QString("Video Track Type");
}

void VideoTrackTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_videoTrack;
        m_videoTrack = 0;
    }
    emit closed(m_op, QVarPtr<VideoTrackType>::asQVariant(m_videoTrack));
}

void VideoTrackTypeForm::applyClicked()
{
    m_videoTrack->setTrackId(m_editTrackId->text());
    m_videoTrack->setTrackName(m_editTrackName->text());
    m_editTypeGroup->updateExistingTypeGroup(m_videoTrack);
    emit closed(m_op, QVarPtr<VideoTrackType>::asQVariant(m_videoTrack));
}
