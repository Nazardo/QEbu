#include "audiotracktypeform.h"
#include "../model/ebucoremaintype.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include <QLineEdit>
#include <QErrorMessage>
#include <QVBoxLayout>
#include <QFormLayout>

AudioTrackTypeForm::AudioTrackTypeForm(AudioTrackType *audioTrack, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (audioTrack) ? Edit : Add;
    if(!audioTrack)
        m_audioTrack = new AudioTrackType;
    else
        m_audioTrack = audioTrack;
    QVBoxLayout *vl = new QVBoxLayout;
    {
        QFormLayout *fl = new QFormLayout;

        m_editTrackId = new QLineEdit;
        fl->addRow(tr("Track id"),m_editTrackId);

        m_editTrackName = new QLineEdit;
        fl->addRow(tr("Track name"),m_editTrackName);

        m_editTrackLanguage = new QLineEdit;
        fl->addRow(tr("Language"),m_editTrackLanguage);
        vl->addLayout(fl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(m_audioTrack);
        vl->addWidget(m_editTypeGroup);
    }
    this->setLayout(vl);
    // Set text fields...
    m_editTrackId->setText(m_audioTrack->trackId());
    m_editTrackName->setText(m_audioTrack->trackName());
    m_editTrackLanguage->setText(m_audioTrack->trackLanguage());

}

QString AudioTrackTypeForm::toString()
{
    return QString(tr("Audio Track Type"));
}

void AudioTrackTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_audioTrack;
        m_audioTrack = 0;
    }
    emit closed(m_op, QVarPtr<AudioTrackType>::asQVariant(m_audioTrack));
}

void AudioTrackTypeForm::applyClicked()
{
    if (!checkCompliance())
        return;

    m_editTrackId->setText(m_editTrackId->text());
    m_editTrackName->setText(m_editTrackName->text());
    m_editTrackLanguage->setText(m_editTrackLanguage->text());
    m_editTypeGroup->updateExistingTypeGroup(m_audioTrack);
    emit closed(m_op, QVarPtr<AudioTrackType>::asQVariant(m_audioTrack));
}

bool AudioTrackTypeForm::checkCompliance()
{
    bool ok = true;
    QString error_msg = "";
    if(!ok) {
        QErrorMessage *e = new QErrorMessage(this);
        e->setWindowTitle(tr("Required fields"));
        e->showMessage(error_msg);
    }
    return ok;
}
