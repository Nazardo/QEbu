#include "audiotracktypeform.h"
#include "../model/ebucoremaintype.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QEvent>
#include <QTextBrowser>

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
        fl->addRow(tr("Track Id"),m_editTrackId);

        m_editTrackName = new QLineEdit;
        fl->addRow(tr("Track Name"),m_editTrackName);

        m_editTrackLanguage = new QLineEdit;
        fl->addRow(tr("Language"),m_editTrackLanguage);
        vl->addLayout(fl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(m_audioTrack);
        m_editTypeGroup->addLinksMap(mainWindow->getMap("ebu_AudioChannelPurposeCodeCS"));
        vl->addWidget(m_editTypeGroup);
    }
    this->setLayout(vl);

    // Event Filter
    m_textDocumentation->setText(tr("A description of some or all of the audio tracks part of the audio track configuration: track type, track ID, track name and language (for what purpose) used if relevant."));
    m_editTrackLanguage->installEventFilter(this);
    m_editTrackId->installEventFilter(this);
    m_editTrackName->installEventFilter(this);
    m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
    m_editTypeGroup->editTypeLabel()->installEventFilter(this);
    m_editTypeGroup->editTypeLink()->installEventFilter(this);
    // Set text fields...
    m_editTrackId->setText(m_audioTrack->trackId());
    m_editTrackName->setText(m_audioTrack->trackName());
    m_editTrackLanguage->setText(m_audioTrack->trackLanguage());

}

QString AudioTrackTypeForm::toString()
{
    return QString(tr("Audio Track"));
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
    m_audioTrack->setTrackId(m_editTrackId->text());
    m_audioTrack->setTrackName(m_editTrackName->text());
    m_audioTrack->setTrackLanguage(m_editTrackLanguage->text());
    m_editTypeGroup->updateExistingTypeGroup(m_audioTrack);
    emit closed(m_op, QVarPtr<AudioTrackType>::asQVariant(m_audioTrack));
}

bool AudioTrackTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("Free text for an optional definition of the purpose of the track"));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setHtml(tr("Link to a classification scheme.<br/>Reference data:<br/><a href=\"http://www.ebu.ch/metadata/cs/web/ebu_AudioChannelPurposeCodeCS_p.xml.htm\">ebu_AudioChannelPurposeCodeCS</a>"));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("Free text.\nExample: ‘dubbing’."));
        else if (obj == (QObject*) m_editTrackLanguage)
            m_textDocumentation->setText(tr("The language used in the audio track and possible purpose refinement using languageType’s typeGroup attributes."));
        else if (obj == (QObject*) m_editTrackId)
            m_textDocumentation->setText(tr("An optional identifier applied to each track."));
        else if (obj == (QObject*) m_editTrackName)
            m_textDocumentation->setText(tr("An optional identifier applied to each track."));
    }
    return QObject::eventFilter(obj, event);
}
