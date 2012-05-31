#include "captioningformattypeform.h"
#include "qvarptr.h"
#include <QtGui>

CaptioningFormatTypeForm::CaptioningFormatTypeForm(CaptioningFormatType *captioningFormat, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (captioningFormat) ? Edit : Add;
    if (!captioningFormat)
        m_captioningFormat = new CaptioningFormatType;
    else
        m_captioningFormat = captioningFormat;

    m_mainVLayout = new QVBoxLayout;
    {
        QFormLayout *fl = new QFormLayout;
        m_editTrackId = new QLineEdit;
        fl->addRow(tr("Track ID"), m_editTrackId);
        m_editTrackName = new QLineEdit;
        fl->addRow(tr("Track name"), m_editTrackName);
        m_editLanguage = new QLineEdit;
        fl->addRow(tr("Language"), m_editLanguage);
        m_mainVLayout->addLayout(fl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(captioningFormat);
        m_mainVLayout->addWidget(m_editTypeGroup);
        m_editFormatGroup = new FormatGroupEditBox(captioningFormat);
        m_mainVLayout->addWidget(m_editFormatGroup);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_editCaptioningSourceUri = new QLineEdit;
        fl->addRow(tr("Captioning Source URI"), m_editCaptioningSourceUri);
        m_editCaptioningFormatId = new QLineEdit;
        fl->addRow(tr("Captioning Format ID"), m_editCaptioningFormatId);
        m_editCaptioningFormatName = new QLineEdit;
        fl->addRow(tr("Captioning Format Name"), m_editCaptioningFormatName);
        m_mainVLayout->addLayout(fl);
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
    // Set text fields...
    m_editTrackId->setText(m_captioningFormat->trackId());
    m_editTrackName->setText(m_captioningFormat->trackName());
    m_editLanguage->setText(m_captioningFormat->trackLanguage());
    m_editCaptioningSourceUri->setText(m_captioningFormat->captioningSourceUri());
    m_editCaptioningFormatId->setText(m_captioningFormat->captioningFormatId());
    m_editCaptioningFormatName->setText(m_captioningFormat->captioningFormatName());
}

QString CaptioningFormatTypeForm::toString()
{
    return QString("Captioning Format Type");
}

void CaptioningFormatTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_captioningFormat;
        m_captioningFormat = 0;
    }
    emit closed(m_op, QVarPtr<CaptioningFormatType>::asQVariant(m_captioningFormat));
}

void CaptioningFormatTypeForm::applyClicked()
{
    if(!checkCompliance())
        return;
    m_captioningFormat->setTrackId(m_editTrackId->text());
    m_captioningFormat->setTrackName(m_editTrackName->text());
    m_captioningFormat->setTrackLanguage(m_editLanguage->text());
    m_captioningFormat->setCaptioningSourceUri(m_editCaptioningSourceUri->text());
    m_captioningFormat->setCaptioningFormatId(m_editCaptioningFormatId->text());
    m_captioningFormat->setCaptioningFormatName(m_editCaptioningFormatName->text());
    m_editTypeGroup->updateExistingTypeGroup(m_captioningFormat);
    m_editFormatGroup->updateExistingFormatGroup(m_captioningFormat);
    emit closed(m_op, QVarPtr<CaptioningFormatType>::asQVariant(m_captioningFormat));
}

bool CaptioningFormatTypeForm::checkCompliance()
{
    bool ok = true;
    return ok;
}
