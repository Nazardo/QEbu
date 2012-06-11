#include "audioformattypeform.h"
#include "../model/formattype.h"
#include "listview.h"
#include "qvarptr.h"
#include "typegroupform.h"
#include "audiotracktypeform.h"
#include "technicalattributesform.h"
#include <QPushButton>
#include <QLineEdit>
#include <QEvent>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QButtonGroup>

AudioFormatTypeForm::AudioFormatTypeForm(AudioFormatType *audioFormat,
                                         QEbuMainWindow *mainWindow,
                                         QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (audioFormat) ? Edit : Add;
    if (!audioFormat)
        m_audioFormat = new AudioFormatType;
    else
        m_audioFormat = audioFormat;
    // Layout
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;
    {
        QFormLayout *gl = new QFormLayout;
        m_editAudioFormatId = new QLineEdit;
        m_editAudioFormatDefinition = new QLineEdit;
        m_editAudioFormatName = new QLineEdit;
        gl->addRow(tr("Audio Format Id"), m_editAudioFormatId);
        gl->addRow(tr("Audio Format Name"), m_editAudioFormatName);
        gl->addRow(tr("Audio Format Definition"), m_editAudioFormatDefinition);
        l->addLayout(gl);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_buttonAudioEncoding = new QPushButton(">>");
        fl->addRow(tr("Audio Encoding"), m_buttonAudioEncoding);
        QObject::connect(m_buttonAudioEncoding, SIGNAL(toggled(bool)),
                         this, SLOT(audioEncodingChecked(bool)));
        m_buttonAudioTrackConfiguration = new QPushButton(">>");
        fl->addRow(tr("Audio Track Configuration"), m_buttonAudioTrackConfiguration);
        QObject::connect(m_buttonAudioTrackConfiguration, SIGNAL(toggled(bool)),
                         this, SLOT(audioTrackConfigurationChecked(bool)));
        m_buttonAudioTrack = new QPushButton(">>");
        fl->addRow(tr("Audio Track"), m_buttonAudioTrack);
        QObject::connect(m_buttonAudioTrack, SIGNAL(toggled(bool)),
                         this, SLOT(audioTrackChecked(bool)));
        m_buttonTechnicalAttributes = new QPushButton(">>");
        fl->addRow(tr("Technical Attributes"), m_buttonTechnicalAttributes);
        QObject::connect(m_buttonTechnicalAttributes, SIGNAL(toggled(bool)),
                         this, SLOT(TechnicalAttributesChecked(bool)));
        l->addLayout(fl);
        QButtonGroup *group = new QButtonGroup(this);
        m_buttonAudioEncoding->setCheckable(true);
        group->addButton(m_buttonAudioEncoding);
        m_buttonAudioTrackConfiguration->setCheckable(true);
        group->addButton(m_buttonAudioTrackConfiguration);
        m_buttonAudioTrack->setCheckable(true);
        group->addButton(m_buttonAudioTrack);
        m_buttonTechnicalAttributes->setCheckable(true);
        group->addButton(m_buttonTechnicalAttributes);
    }
    mainHLayout->addLayout(l);
    // Add list view on the right
    m_listView = new ListView();
    QObject::connect(m_listView->buttonAdd(), SIGNAL(clicked()),
                     this, SLOT(addClicked()));
    QObject::connect(m_listView->buttonEdit(), SIGNAL(clicked()),
                     this, SLOT(editClicked()));
    QObject::connect(m_listView->buttonRemove(), SIGNAL(clicked()),
                     this, SLOT(removeClicked()));
    mainHLayout->addWidget(m_listView);
    this->setLayout(mainHLayout);

    // Event Filter
    m_textDocumentation->setText(tr("To provide information on the Audio Format."));
    m_editAudioFormatId->installEventFilter(this);
    m_editAudioFormatDefinition->installEventFilter(this);
    m_editAudioFormatName->installEventFilter(this);
    m_buttonAudioEncoding->installEventFilter(this);
    m_buttonAudioTrackConfiguration->installEventFilter(this);
    m_buttonAudioTrack->installEventFilter(this);
    m_buttonTechnicalAttributes->installEventFilter(this);

    // Set data fields...
    m_editAudioFormatId->setText(m_audioFormat->audioFormatId());
    m_editAudioFormatDefinition->setText(m_audioFormat->audioFormatDefinition());
    m_editAudioFormatName->setText(m_audioFormat->audioFormatName());
    m_buttonAudioEncoding->setChecked(true);
}

QString AudioFormatTypeForm::toString()
{
    return QString(tr("Audio Format"));
}

void AudioFormatTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_audioFormat;
        m_audioFormat = 0;
    }
    emit closed(m_op, QVarPtr<AudioFormatType>::asQVariant(m_audioFormat));
}

void AudioFormatTypeForm::applyClicked()
{
    m_audioFormat->setAudioFormatDefinition(m_editAudioFormatId->text());
    m_audioFormat->setAudioFormatId(m_editAudioFormatId->text());
    m_audioFormat->setAudioFormatName(m_editAudioFormatName->text());
    emit closed(m_op, QVarPtr<AudioFormatType>::asQVariant(m_audioFormat));
}

void AudioFormatTypeForm::addClicked()
{
    switch (m_currentEditMode) {
    case AudioEncoding:
    {
        TypeGroupForm *audioEncodingForm = new TypeGroupForm(0, this->mainWindow());
        audioEncodingForm->addLinksMap(this->mainWindow()->getMap("ebu_AudioCompressionCodeCS")); //Autocompletion values
        audioEncodingForm->setTitle(tr("Audio Encoding"));
        QObject::connect(audioEncodingForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(audioEncodingFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(audioEncodingForm);
    }
        break;
    case AudioTrackConfiguration:
    {
        TypeGroupForm *audioTrackConfigurationForm = new TypeGroupForm(0, this->mainWindow());
        audioTrackConfigurationForm->addLinksMap(this->mainWindow()->getMap("ebu_AudioFormatCodeCS")); //Autocompletion values
        audioTrackConfigurationForm->setTitle(tr("Audio Track Configuration"));
        QObject::connect(audioTrackConfigurationForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(audioTrackConfigurationFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(audioTrackConfigurationForm);
    }
        break;
    case AudioTrack:
    {
        AudioTrackTypeForm *audioTrackForm = new AudioTrackTypeForm(0, this->mainWindow());
        QObject::connect(audioTrackForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(audioTrackFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(audioTrackForm);
    }
        break;
    case TechnicalAttributesMode:
    {
        TechnicalAttributesForm *technicalAttributesForm = new TechnicalAttributesForm(0, this->mainWindow());
        QObject::connect(technicalAttributesForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(TechnicalAttributesFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(technicalAttributesForm);
    }
        break;
    }
}

void AudioFormatTypeForm::editClicked()
{
    int index = m_listView->selected();
    if (index < 0)
        return;
    switch (m_currentEditMode) {
    case AudioEncoding:
    {
        TypeGroupForm *audioEncodingForm = new TypeGroupForm(
                    m_audioFormat->audioEncoding().at(index), this->mainWindow());
        audioEncodingForm->addLinksMap(this->mainWindow()->getMap("ebu_AudioCompressionCodeCS")); //Autocompletion values
        audioEncodingForm->setTitle(tr("Audio Encoding"));
        QObject::connect(audioEncodingForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(audioEncodingFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(audioEncodingForm);
    }
        break;
    case AudioTrackConfiguration:
    {
        TypeGroupForm *audioTrackConfigurationForm = new TypeGroupForm(
                    m_audioFormat->audioTrackConfiguration(), this->mainWindow());
        audioTrackConfigurationForm->addLinksMap(this->mainWindow()->getMap("ebu_AudioFormatCodeCS")); //Autocompletion values
        audioTrackConfigurationForm->setTitle(tr("Audio Track Configuration"));
        QObject::connect(audioTrackConfigurationForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(audioTrackConfigurationFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(audioTrackConfigurationForm);
    }
        break;
    case AudioTrack:
    {
        AudioTrackTypeForm *audioTrackForm = new AudioTrackTypeForm(
                    m_audioFormat->audioTrack().at(index), this->mainWindow());
        QObject::connect(audioTrackForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(audioTrackFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(audioTrackForm);
    }
        break;
    case TechnicalAttributesMode:
    {
        TechnicalAttributesForm *technicalAttributesForm =
                new TechnicalAttributesForm(m_audioFormat->technicalAttributes(), this->mainWindow());
        QObject::connect(technicalAttributesForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(TechnicalAttributesFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(technicalAttributesForm);
    }
        break;
    }
}

void AudioFormatTypeForm::removeClicked()
{
    int row = m_listView->selected();
    if (row < 0)
        return;
    m_listView->removeAt(row);
    switch (m_currentEditMode) {
    case AudioEncoding:
    {
        delete(m_audioFormat->audioEncoding().takeAt(row));
    }
        break;
    case AudioTrackConfiguration:
    {
        m_audioFormat->setAudioTrackConfiguration(0);
        m_listView->buttonAdd()->setEnabled(true);
    }
        break;
    case AudioTrack:
    {
        delete(m_audioFormat->audioTrack().takeAt(row));
    }
        break;
    case TechnicalAttributesMode:
    {
        m_audioFormat->setTechnicalAttributes(0);
        m_listView->buttonAdd()->setEnabled(true);
    }
        break;
    }
}

void AudioFormatTypeForm::audioEncodingChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = AudioEncoding;
    updateListAndButtons();
    int s = m_audioFormat->audioEncoding().size();
    for (int i=0; i < s; ++i) {
        TypeGroup *f = m_audioFormat->audioEncoding().at(i);
        if (!f)
            continue;
        m_listView->addItem(f->toString());
    }
}

void AudioFormatTypeForm::audioTrackConfigurationChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = AudioTrackConfiguration;
    updateListAndButtons();
    TypeGroup *f = m_audioFormat->audioTrackConfiguration();
    if (f) {
        m_listView->addItem(f->toString());
        m_listView->enableAdd(false);
    }
}

void AudioFormatTypeForm::audioTrackChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = AudioTrack;
    updateListAndButtons();
    int s = m_audioFormat->audioTrack().size();
    for (int i=0; i < s; ++i) {
        AudioTrackType *at = m_audioFormat->audioTrack().at(i);
        if (!at)
            continue;
        m_listView->addItem(at->toString());
    }
}

void AudioFormatTypeForm::TechnicalAttributesChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = TechnicalAttributesMode;
    updateListAndButtons();
    TechnicalAttributes *ta = m_audioFormat->technicalAttributes();
    if (ta) {
        m_listView->addItem(ta->toString());
        m_listView->enableAdd(false);
    }
}

void AudioFormatTypeForm::audioEncodingFormClosed(StackableWidget::Operation op, QVariant value)
{
    TypeGroup *tg = QVarPtr<TypeGroup>::asPointer(value);
    if(!tg)
        return;
    if(op == Add) {
        m_listView->addItem(tg->toString());
        m_audioFormat->audioEncoding().append(tg);
    } else if(op == Edit) {
        int row = m_audioFormat->audioEncoding().indexOf(tg);
        m_listView->setItem(row, tg->toString());
    }
}

void AudioFormatTypeForm::audioTrackConfigurationFormClosed(StackableWidget::Operation op, QVariant value)
{
    TypeGroup *tg = QVarPtr<TypeGroup>::asPointer(value);
    if(!tg)
        return;
    if(op == Add) {
        m_listView->addItem(tg->toString());
        m_audioFormat->setAudioTrackConfiguration(tg);
        m_listView->enableAdd(false);
    } else if(op == Edit) {
        int row = 0;
        m_listView->setItem(row, tg->toString());
    }
}

void AudioFormatTypeForm::audioTrackFormClosed(Operation op, QVariant value)
{
    AudioTrackType *at = QVarPtr<AudioTrackType>::asPointer(value);
    if (!at)
        return;
    if (op == Add) {
        m_listView->addItem(at->toString());
        m_audioFormat->audioTrack().append(at);
    } else if (op == Edit) {
        int row = m_audioFormat->audioTrack().indexOf(at);
        m_listView->setItem(row, at->toString());
    }
}

void AudioFormatTypeForm::TechnicalAttributesFormClosed(StackableWidget::Operation op, QVariant value)
{
    TechnicalAttributes *ta = QVarPtr<TechnicalAttributes>::asPointer(value);
    if(!ta)
        return;
    if(op == Add) {
        m_listView->addItem(ta->toString());
        m_audioFormat->setTechnicalAttributes(ta);
        m_listView->enableAdd(false);
    } else if(op == Edit) {
        int row = 0;
        m_listView->setItem(row, ta->toString());
    }
}

void AudioFormatTypeForm::updateListAndButtons()
{
    QString title;
    if (m_currentEditMode == AudioEncoding)
        title = tr("Audio Encoding");
    else if (m_currentEditMode == AudioTrackConfiguration)
        title = tr("Audio Track Configuration");
    else if (m_currentEditMode == AudioTrack)
        title = tr("Audio Track");
    else if (m_currentEditMode == TechnicalAttributesMode)
        title = tr("Technical Attributes");
    m_listView->setTitle(title);
    m_listView->clear();
}

bool AudioFormatTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editAudioFormatId)
            m_textDocumentation->setText(tr("An Identifier to identify a specific format in which the resource is available or has been published."));
        else if ( obj ==(QObject*) m_editAudioFormatDefinition)
            m_textDocumentation->setText(tr("A definition of the format information being provided either technical or editorial in nature."));
        else if ( obj == (QObject*) m_editAudioFormatName)
            m_textDocumentation->setText(tr("A name attributed to a particular format."));
        else if ( obj == (QObject*) m_buttonAudioEncoding)
            m_textDocumentation->setText(tr("To define the audio compression format of the resource e.g. AAC for an audio channel."));
        else if ( obj == (QObject*) m_buttonAudioTrackConfiguration)
            m_textDocumentation->setText(tr("To describe the audio track configuration. Used to express the arrangement or audio tracks e.g. 'stereo', '2+1', 'surround', 'surround (7+1)'."));
        else if ( obj == (QObject*) m_buttonAudioTrack)
            m_textDocumentation->setText(tr("To describe the track allocation e.g. in conformance with EBU R123."));
        else if ( obj == (QObject*) m_buttonTechnicalAttributes)
            m_textDocumentation->setText(tr("An extension element to allow users and implementers defining their own technical attributes."));
    }
    return QObject::eventFilter(obj, event);
}



