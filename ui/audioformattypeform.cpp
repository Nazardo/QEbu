#include "audioformattypeform.h"

#include "qvarptr.h"
#include "typegroupform.h"
#include "audiotracktypeform.h"
#include "technicalattributesform.h"
#include <QtGui>

AudioFormatTypeForm::AudioFormatTypeForm(AudioFormatType *audioFormat,
                                         QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (audioFormat) ? Edit : Add;
    if (!audioFormat)
        m_audioFormat = new AudioFormatType;
    else
        m_audioFormat = audioFormat;
    // Layout
    m_mainHLayout = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;
    {
        QFormLayout *gl = new QFormLayout;
        m_editAudioFormatId = new QLineEdit;
        m_editAudioFormatDefinition = new QLineEdit;
        m_editAudioFormatName = new QLineEdit;
        gl->addRow(tr("AudioFormat Id"), m_editAudioFormatId);
        gl->addRow(tr("AudioFormat Name"), m_editAudioFormatName);
        gl->addRow(tr("AudioFormat Definition"), m_editAudioFormatDefinition);
        l->addLayout(gl);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_buttonAudioEncoding = new QPushButton(">>");
        fl->addRow(tr("Audio encoding"), m_buttonAudioEncoding);
        QObject::connect(m_buttonAudioEncoding, SIGNAL(toggled(bool)),
                         this, SLOT(audioEncodingChecked(bool)));
        m_buttonAudioTrackConfiguration = new QPushButton(">>");
        fl->addRow(tr("AudioTrack Configuration"), m_buttonAudioTrackConfiguration);
        QObject::connect(m_buttonAudioTrackConfiguration, SIGNAL(toggled(bool)),
                         this, SLOT(audioTrackConfigurationChecked(bool)));
        m_buttonAudioTrack = new QPushButton(">>");
        fl->addRow(tr("AudioTrack"), m_buttonAudioTrack);
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
        l->addLayout(hl);
    }
    m_mainHLayout->addLayout(l);
    // Add list view on the right
    m_listView = new ListView();
    QObject::connect(m_listView->buttonAdd(), SIGNAL(clicked()),
                     this, SLOT(addClicked()));
    QObject::connect(m_listView->buttonEdit(), SIGNAL(clicked()),
                     this, SLOT(editClicked()));
    QObject::connect(m_listView->buttonRemove(), SIGNAL(clicked()),
                     this, SLOT(removeClicked()));
    m_mainHLayout->addWidget(m_listView);
    this->setLayout(m_mainHLayout);

    // Set data fields...
    m_editAudioFormatId->setText(m_audioFormat->audioFormatId());
    m_editAudioFormatDefinition->setText(m_audioFormat->audioFormatDefinition());
    m_editAudioFormatName->setText(m_audioFormat->audioFormatName());
    m_buttonAudioEncoding->setChecked(true);
}

QString AudioFormatTypeForm::toString()
{
    return QString("AudioFormat Type");
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
        QObject::connect(audioEncodingForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(audioEncodingFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(audioEncodingForm);
    }
        break;
    case AudioTrackConfiguration:
    {
        TypeGroupForm *audioTrackConfigurationForm = new TypeGroupForm(0, this->mainWindow());
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
        QObject::connect(audioEncodingForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(audioEncodingFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(audioEncodingForm);
    }
        break;
    case AudioTrackConfiguration:
    {
        TypeGroupForm *audioTrackConfigurationForm = new TypeGroupForm(
                    m_audioFormat->audioTrackConfiguration(), this->mainWindow());
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
        title = tr("Audio encoding");
    else if (m_currentEditMode == AudioTrackConfiguration)
        title = tr("AudioTrack configuration");
    else if (m_currentEditMode == AudioTrack)
        title = tr("AudioTrack");
    else if (m_currentEditMode == TechnicalAttributesMode)
        title = tr("Technical Attributes");
    m_listView->setTitle(title);
    m_listView->clear();
}


