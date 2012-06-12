#include "parttypeform.h"
#include "qvarptr.h"
#include "../model/coremetadatatype.h"
#include "../ui/coremetadatatypeform.h"
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QMessageBox>
#include <QEvent>
#include <QTextEdit>

PartTypeForm::PartTypeForm(PartType *part, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (part) ? Edit : Add;
    if(!part)
        m_part = new PartType;
    else
        m_part = part;


    QVBoxLayout *vl = new QVBoxLayout;
    {
        QFormLayout *fl = new QFormLayout;

        m_editPartId = new QLineEdit;
        fl->addRow(tr("Part Id"), m_editPartId);

        m_editPartName = new QLineEdit;
        fl->addRow(tr("Part Name"), m_editPartName);

        vl->addLayout(fl);
    }
    {
        QHBoxLayout *hl = new QHBoxLayout;

        hl->addWidget(new QLabel(tr("CoreMetadata details")));
        m_editCoreDetails = new QLineEdit;
        m_editCoreDetails->setReadOnly(true);
        hl->addWidget(m_editCoreDetails);

        QPushButton *buttonCoreDetails = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttonCoreDetails, SIGNAL(clicked()),
                         this, SLOT(coreDetailsClicked()));
        hl->addWidget(buttonCoreDetails);
        QPushButton *buttonCoreDetailsRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonCoreDetailsRemove, SIGNAL(clicked()),
                         this, SLOT(coreDetailsRemoveClicked()));
        hl->addWidget(buttonCoreDetailsRemove);
        vl->addLayout(hl);
    }
    this->setLayout(vl);

    // Install Event filters
    m_textDocumentation->setText(tr("To describe a part/segment/fragment within the resource."));
    m_editPartId->installEventFilter(this);
    m_editPartName->installEventFilter(this);
    m_editCoreDetails->installEventFilter(this);

    // Set text fields...

    m_editPartId->setText(m_part->partId());
    m_editPartName->setText(m_part->partName());
    if (m_part)
        m_editCoreDetails->setText(tr("Core Metada details"));
}

QString PartTypeForm::toString()
{
    return QString(tr("Part"));
}

void PartTypeForm::coreDetailsRemoveClicked()
{
    if (!m_part)
        return;
    m_part->setVersion(0);
    m_part->setPubblicationHistory(0);
    for(int i=0; i < m_part->title().size(); ++i)
        delete m_part->title().takeAt(i);
    for(int i=0; i < m_part->alternativeTitle().size(); ++i)
        delete m_part->alternativeTitle().takeAt(i);
    for(int i=0; i < m_part->creator().size(); ++i)
        delete m_part->creator().takeAt(i);
    for(int i=0; i < m_part->subject().size(); ++i)
        delete m_part->subject().takeAt(i);
    for(int i=0; i < m_part->description().size(); ++i)
        delete m_part->description().takeAt(i);
    for(int i=0; i < m_part->publisher().size(); ++i)
        delete m_part->publisher().takeAt(i);
    for(int i=0; i < m_part->contributor().size(); ++i)
        delete m_part->contributor().takeAt(i);
    for(int i=0; i < m_part->date().size(); ++i)
        delete m_part->date().takeAt(i);
    for(int i=0; i < m_part->type().size(); ++i)
        delete m_part->type().takeAt(i);
    for(int i=0; i < m_part->format().size(); ++i)
        delete m_part->format().takeAt(i);
    for(int i=0; i < m_part->identifier().size(); ++i)
        delete m_part->identifier().takeAt(i);
    for(int i=0; i < m_part->source().size(); ++i)
        delete m_part->source().takeAt(i);
    for(int i=0; i < m_part->language().size(); ++i)
        delete m_part->language().takeAt(i);
    for(int i=0; i < m_part->relation().size(); ++i)
        delete m_part->relation().takeAt(i);
    for(int i=0; i < m_part->isVersionOf().size(); ++i)
        delete m_part->isVersionOf().takeAt(i);
    for(int i=0; i < m_part->hasVersion().size(); ++i)
        delete m_part->hasVersion().takeAt(i);
    for(int i=0; i < m_part->isReplacedBy().size(); ++i)
        delete m_part->isReplacedBy().takeAt(i);
    for(int i=0; i < m_part->replaces().size(); ++i)
        delete m_part->replaces().takeAt(i);
    for(int i=0; i < m_part->isRequiredBy().size(); ++i)
        delete m_part->isRequiredBy().takeAt(i);
    for(int i=0; i < m_part->requires().size(); ++i)
        delete m_part->requires().takeAt(i);
    for(int i=0; i < m_part->isPartOf().size(); ++i)
        delete m_part->isPartOf().takeAt(i);
    for(int i=0; i < m_part->hasPart().size(); ++i)
        delete m_part->hasPart().takeAt(i);
    for(int i=0; i < m_part->hasTrackPart().size(); ++i)
        delete m_part->hasTrackPart().takeAt(i);
    for(int i=0; i < m_part->isReferencedBy().size(); ++i)
        delete m_part->isReferencedBy().takeAt(i);
    for(int i=0; i < m_part->references().size(); ++i)
        delete m_part->references().takeAt(i);
    for(int i=0; i < m_part->isFormatOf().size(); ++i)
        delete m_part->isFormatOf().takeAt(i);
    for(int i=0; i < m_part->hasFormat().size(); ++i)
        delete m_part->hasFormat().takeAt(i);
    for(int i=0; i < m_part->isEpisodeOf().size(); ++i)
        delete m_part->isEpisodeOf().takeAt(i);
    for(int i=0; i < m_part->isMemberOf().size(); ++i)
        delete m_part->isMemberOf().takeAt(i);
    for(int i=0; i < m_part->coverage().size(); ++i)
        delete m_part->coverage().takeAt(i);
    for(int i=0; i < m_part->rights().size(); ++i)
        delete m_part->rights().takeAt(i);
    for(int i=0; i < m_part->rating().size(); ++i)
        delete m_part->rating().takeAt(i);
    for(int i=0; i < m_part->part().size(); ++i)
        delete m_part->part().takeAt(i);
    m_editCoreDetails->setText(tr("(none)"));
}

void PartTypeForm::coreDetailsClicked()
{
    CoreMetadataTypeForm *coreDetailsForm = new CoreMetadataTypeForm(
                m_part, this->mainWindow());
    QObject::connect(coreDetailsForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(coreDetailsClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(coreDetailsForm);
}

void PartTypeForm::coreDetailsClosed(Operation op, QVariant value)
{
    (void) op;
    CoreMetadataType *coreMetadara = QVarPtr<CoreMetadataType>::asPointer(value);
    if (!coreMetadara)
        return;
    m_editCoreDetails->setText(tr("Core Metadata Details"));
}

bool PartTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editPartId)
            m_textDocumentation->setText(tr("To identify the part/segment/fragment within the resource."));
        else if (obj == (QObject*) m_editPartName)
            m_textDocumentation->setText(tr("To identify the part/segment/fragment within the resource."));
        else if (obj == (QObject*) m_editCoreDetails)
            m_textDocumentation->setText(tr("To provide all the core descriptive information regarding the part/segment/fragment."));
    }
    return QObject::eventFilter(obj, event);
}

void PartTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_part;
        m_part = 0;
    }
    emit closed(m_op, QVarPtr<PartType>::asQVariant(m_part));
}

void PartTypeForm::applyClicked()
{
    if (!checkCompliance())
        return;
    m_part->setPartId(m_editPartId->text());
    m_part->setPartName(m_editPartName->text());

    emit closed(m_op, QVarPtr<PartType>::asQVariant(m_part));
}

bool PartTypeForm::checkCompliance()
{
    bool ok = true;

    return ok;
}
