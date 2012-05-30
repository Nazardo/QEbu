#include "videotracktypeform.h"
#include "qvarptr.h"
#include <QFormLayout>
#include <QPushButton>

VideoTrackTypeForm::VideoTrackTypeForm(VideoTrackType *videoTrack, QEbuMainWindow *mainWindow, QWidget *parent)  :
    StackableWidget(mainWindow, parent)
{
    m_op = (videoTrack) ? Edit : Add;
    if (!videoTrack)
        m_videoTrack = new VideoTrackType;
    else
        m_videoTrack = videoTrack;
    // Layout
    m_mainVLayout = new QVBoxLayout;
    {
        QFormLayout *fl = new QFormLayout;
        m_editTrackId = new QLineEdit;
        fl->addRow(tr("Track ID"), m_editTrackId);
        m_editTrackName = new QLineEdit;
        fl->addRow(tr("Track Name"), m_editTrackName);
        m_mainVLayout->addLayout(fl);
        m_editTypeGroup = new TypeGroupEditBox(videoTrack);
        m_mainVLayout->addWidget(m_editTypeGroup);
    }
    {
        QHBoxLayout *hl = new QHBoxLayout;
        QPushButton *buttonClose = new QPushButton(tr("Apply changes"));
        QPushButton *buttonCancel = new QPushButton(tr("Cancel"));
        QObject::connect(buttonClose, SIGNAL(clicked()),
                         this, SLOT(applyClicked()));
        QObject::connect(buttonCancel, SIGNAL(clicked()),
                         this, SLOT(cancelClicked()));
        hl->addWidget(buttonClose);
        hl->addWidget(buttonCancel);
        m_mainVLayout->addLayout(hl);
    }
    this->setLayout(m_mainVLayout);

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
    if(!checkCompliance())
        return;
    m_videoTrack->setTrackId(m_editTrackId->text());
    m_videoTrack->setTrackName(m_editTrackName->text());
    m_editTypeGroup->updateExistingTypeGroup(m_videoTrack);
    emit closed(m_op, QVarPtr<VideoTrackType>::asQVariant(m_videoTrack));
}

bool VideoTrackTypeForm::checkCompliance()
{
    bool ok = true;
    return ok;
}
