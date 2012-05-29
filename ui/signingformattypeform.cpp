#include "signingformattypeform.h"
#include "qvarptr.h"
#include <QtGui>

SigningFormatTypeForm::SigningFormatTypeForm(SigningFormatType *signingFormat, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (signingFormat) ? Edit : Add;
    if(!signingFormat)
        m_signingFormat = new SigningFormatType;
    else
        m_signingFormat = signingFormat;
    QVBoxLayout *vl = new QVBoxLayout;
    {
        QFormLayout *fl = new QFormLayout;

        m_editTrackId = new QLineEdit;
        fl->addRow(tr("Track id"),m_editTrackId);

        m_editTrackName = new QLineEdit;
        fl->addRow(tr("Track name"),m_editTrackName);

        m_editLanguage = new QLineEdit;
        fl->addRow(tr("Language"),m_editLanguage);
        vl->addLayout(fl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox;
        vl->addWidget(m_editTypeGroup);
    }
    {
        m_editFormatGroup = new FormatGroupEditBox;
        vl->addWidget(m_editFormatGroup);
    }
    {
        QFormLayout *fl = new QFormLayout;

        m_editSigningSourceUri = new QLineEdit;
        fl->addRow(tr("Source uri"),m_editSigningSourceUri);

        m_editSigningFormatId = new QLineEdit;
        fl->addRow(tr("Format id"),m_editSigningFormatId);

        m_editSigningFormatName = new QLineEdit;
        fl->addRow(tr("Format name"),m_editSigningFormatName);

        m_editSigningFormatDefinition = new QLineEdit;
        fl->addRow(tr("Format definition"),m_editSigningFormatDefinition);
        vl->addLayout(fl);
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
        vl->addLayout(hl);
    }
    this->setLayout(vl);
    // Set text fields...
    m_editTrackId->setText(m_signingFormat->trackId());
    m_editTrackName->setText(m_signingFormat->trackName());
    m_editLanguage->setText(m_signingFormat->language());
    m_editTypeGroup->typeLabel()->setText(m_signingFormat->typeLabel());
    m_editTypeGroup->typeDefinition()->setText(m_signingFormat->typeDefinition());
    m_editTypeGroup->typeLink()->setText(m_signingFormat->typeLink());
    m_editFormatGroup->formatLabel()->setText(m_signingFormat->formatLabel());
    m_editFormatGroup->formatDefinition()->setText(m_signingFormat->formatDefinition());
    m_editFormatGroup->formatLink()->setText(m_signingFormat->formatLink());
    m_editSigningSourceUri->setText(m_signingFormat->signingSourceUri());
    m_editSigningFormatId->setText(m_signingFormat->signingSourceUri());
    m_editSigningFormatName->setText(m_signingFormat->signingSourceUri());
    m_editSigningFormatDefinition->setText(m_signingFormat->signingSourceUri());
}

QString SigningFormatTypeForm::toString()
{
    return QString(tr("Signing Format Type"));
}

void SigningFormatTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_signingFormat;
        m_signingFormat = 0;
    }
    emit closed(m_op, QVarPtr<SigningFormatType>::asQVariant(m_signingFormat));
}

void SigningFormatTypeForm::applyClicked()
{
    if (!checkCompliance())
        return;

    m_signingFormat->setTrackId(m_editTrackId->text());
    m_signingFormat->setTrackName(m_editTrackName->text());
    m_signingFormat->setLanguage(m_editLanguage->text());

    m_signingFormat->setTypeLabel(m_editTypeGroup->typeLabel()->text());
    m_signingFormat->setTypeDefinition(m_editTypeGroup->typeDefinition()->text());
    m_signingFormat->setTypeLink(m_editTypeGroup->typeLink()->text());

    m_signingFormat->setFormatLabel(m_editFormatGroup->formatLabel()->text());
    m_signingFormat->setFormatDefinition(m_editFormatGroup->formatDefinition()->text());
    m_signingFormat->setFormatLink(m_editFormatGroup->formatLink()->text());

    m_signingFormat->setSigningSourceUri(m_editSigningSourceUri->text());
    m_signingFormat->setSigningFormatId(m_editSigningFormatId->text());
    m_signingFormat->setSigningFormatName(m_editSigningFormatName->text());
    m_signingFormat->setSigningFormatDefinition(m_editSigningFormatDefinition->text());

    emit closed(m_op, QVarPtr<SigningFormatType>::asQVariant(m_signingFormat));
}

bool SigningFormatTypeForm::checkCompliance()
{
    bool ok = true;
    QString error_msg = "";
    if(!ok) {
        QErrorMessage *e = new QErrorMessage(this);
        e->setWindowTitle(tr("Rrequired fields"));
        e->showMessage(error_msg);
    }
    return ok;
}
