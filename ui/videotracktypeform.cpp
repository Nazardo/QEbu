#include "videotracktypeform.h"
#include "../model/formattype.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QFormLayout>
#include <QComboBox>
#include <QEvent>

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

    //Event filter
    m_textDocumentation->setText(tr("To describe the main features of video tracks such as in multiview systems."));
    m_editTrackId->installEventFilter(this);
    m_editTrackName->installEventFilter(this);
    m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
    m_editTypeGroup->editTypeLabel()->installEventFilter(this);
    m_editTypeGroup->editTypeLink()->installEventFilter(this);

    // Set data fields
    m_editTrackId->setText(m_videoTrack->trackId());
    m_editTrackName->setText(m_videoTrack->trackName());
}

QString VideoTrackTypeForm::toString()
{
        return QString(tr("Video Track"));
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

bool VideoTrackTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editTrackId )
            m_textDocumentation->setText(tr("The track ID or track number."));
        else if  (obj == (QObject*) m_editTrackName)
            m_textDocumentation->setText(tr("The track name."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("An optional definition."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setText(tr("A link to a term or only identify a classification scheme.\n"));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("Free text to define the type of video track.\nExample: particular view angle."));
    }
    return QObject::eventFilter(obj, event);
}
