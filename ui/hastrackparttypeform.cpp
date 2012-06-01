#include "hastrackparttypeform.h"
#include "timetypeform.h"
#include "alternativetitletypeform.h"
#include "relationtypeform.h"
#include "qvarptr.h"
#include <QtGui>



HasTrackPartTypeForm::HasTrackPartTypeForm(HasTrackPartType *hasTrackPart,
                                           QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (hasTrackPart) ? Edit : Add;
    if (hasTrackPart)
        m_hasTrackPart = hasTrackPart;
    else
        m_hasTrackPart = new HasTrackPartType;

    m_mainHLayout = new QHBoxLayout;
    QGridLayout *gl = new QGridLayout;
    {

        gl->addWidget(new QLabel(tr("TrackPart title")), 0, 0);
        m_editTrackPartTitle = new QLineEdit;
        m_editTrackPartTitle->setEnabled(false);
        gl->addWidget(m_editTrackPartTitle, 0, 1);
        QPushButton *buttonTrackPartTitle = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttonTrackPartTitle, SIGNAL(clicked()),
                         this, SLOT(trackPartTitleClicked()));
        gl->addWidget(buttonTrackPartTitle, 0, 2);
        QPushButton *buttonTrackPartTitleRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonTrackPartTitleRemove, SIGNAL(clicked()),
                         this, SLOT(trackPartTitleRemoveClicked()));
        gl->addWidget(buttonTrackPartTitleRemove, 0, 3);
    }
    {

        gl->addWidget(new QLabel(tr("Destination Start")), 1, 0);
        m_editDestinationStart = new QLineEdit;
        m_editDestinationStart->setEnabled(false);
        gl->addWidget(m_editDestinationStart, 1, 1);
        QPushButton *buttonDestinationStart = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttonDestinationStart, SIGNAL(clicked()),
                         this, SLOT(destinationStartClicked()));
        gl->addWidget(buttonDestinationStart, 1, 2);
        QPushButton *buttonDestinationStartRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonDestinationStartRemove, SIGNAL(clicked()),
                         this, SLOT(destinationStartRemoveClicked()));
        gl->addWidget(buttonDestinationStartRemove, 1, 3);
    }
    {

        gl->addWidget(new QLabel(tr("Destination End")), 2, 0);
        m_editDestinationEnd = new QLineEdit;
        m_editDestinationEnd->setEnabled(false);
        gl->addWidget(m_editDestinationEnd, 2, 1);
        QPushButton *buttonDestinationEnd = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttonDestinationEnd, SIGNAL(clicked()),
                         this, SLOT(destinationEndClicked()));
        gl->addWidget(buttonDestinationEnd, 2, 2);
        QPushButton *buttonDestinationEndRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonDestinationEndRemove, SIGNAL(clicked()),
                         this, SLOT(destinationEndRemoveClicked()));
        gl->addWidget(buttonDestinationEndRemove, 2, 3);
    }
    {

        gl->addWidget(new QLabel(tr("Source Start")), 3, 0);
        m_editSourceStart = new QLineEdit;
        m_editSourceStart->setEnabled(false);
        gl->addWidget(m_editSourceStart, 3, 1);
        QPushButton *buttonSourceStart = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttonSourceStart, SIGNAL(clicked()),
                         this, SLOT(sourceStartClicked()));
        gl->addWidget(buttonSourceStart, 3, 2);
        QPushButton *buttonSourceStartRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonSourceStartRemove, SIGNAL(clicked()),
                         this, SLOT(sourceStartRemoveClicked()));
        gl->addWidget(buttonSourceStartRemove, 3, 3);
    }
    {

        gl->addWidget(new QLabel(tr("Source End")), 4, 0);
        m_editSourceEnd = new QLineEdit;
        m_editSourceEnd->setEnabled(false);
        gl->addWidget(m_editSourceEnd, 4, 1);
        QPushButton *buttonSourceEnd = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttonSourceEnd, SIGNAL(clicked()),
                         this, SLOT(sourceEndClicked()));
        gl->addWidget(buttonSourceEnd, 4, 2);
        QPushButton *buttonSourceEndRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonSourceEndRemove, SIGNAL(clicked()),
                         this, SLOT(sourceEndRemoveClicked()));
        gl->addWidget(buttonSourceEndRemove, 4, 3);
    }
    {

        gl->addWidget(new QLabel(tr("Relation details")), 5, 0);
        m_editRelation = new QLineEdit;
        m_editRelation->setEnabled(false);
        gl->addWidget(m_editRelation, 5, 1);
        QPushButton *buttonRelation = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttonRelation, SIGNAL(clicked()),
                         this, SLOT(relationClicked()));
        gl->addWidget(buttonRelation, 5, 2);
        QPushButton *buttonRelationRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonRelationRemove, SIGNAL(clicked()),
                         this, SLOT(relationRemovedClicked()));
        gl->addWidget(buttonRelationRemove, 5, 3);
    }
    {
        QPushButton *buttonClose = new QPushButton(tr("Apply changes"));
        QPushButton *buttonCancel = new QPushButton(tr("Cancel"));
        QObject::connect(buttonClose, SIGNAL(clicked()),
                         this, SLOT(applyClicked()));
        QObject::connect(buttonCancel, SIGNAL(clicked()),
                         this, SLOT(cancelClicked()));
        gl->addWidget(buttonClose, 6, 1);
        gl->addWidget(buttonCancel, 6, 2);

    }
    if (m_hasTrackPart->trackPartTitle())
        m_editTrackPartTitle->setText(m_hasTrackPart->trackPartTitle()->toString());
    if (m_hasTrackPart->destinationStart())
        m_editDestinationStart->setText(m_hasTrackPart->destinationStart()->toString());
    if (m_hasTrackPart->destinationEnd())
        m_editDestinationEnd->setText(m_hasTrackPart->destinationEnd()->toString());
    if (m_hasTrackPart->sourceStart())
        m_editSourceStart->setText(m_hasTrackPart->sourceStart()->toString());
    if (m_hasTrackPart->destinationStart())
        m_editSourceStart->setText(m_hasTrackPart->sourceEnd()->toString());

    m_mainHLayout->addLayout(gl);
    this->setLayout(m_mainHLayout);
}


QString HasTrackPartTypeForm::toString()
{
    return QString(tr("HasTrackPart Type"));
}

void HasTrackPartTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_hasTrackPart;
        m_hasTrackPart = 0;
    }
    emit closed(m_op, QVarPtr<HasTrackPartType>::asQVariant(m_hasTrackPart));
}

void HasTrackPartTypeForm::applyClicked()
{
    if (!checkCompliance())
        return;
    emit closed(m_op, QVarPtr<HasTrackPartType>::asQVariant(m_hasTrackPart));
}

void HasTrackPartTypeForm::trackPartTitleRemoveClicked()
{
    if (!m_hasTrackPart->trackPartTitle())
        return;
    m_hasTrackPart->setTrackPartTitle(0);
    m_editTrackPartTitle->setText(tr("(none)"));
}

void HasTrackPartTypeForm::trackPartTitleClicked()
{
    AlternativeTitleTypeForm *trackPartTitleForm = new AlternativeTitleTypeForm(
                m_hasTrackPart->trackPartTitle(),this->mainWindow());
    QObject::connect(trackPartTitleForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(trackPartTitleClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(trackPartTitleForm);
}

void HasTrackPartTypeForm::trackPartTitleClosed(Operation op, QVariant value)
{
    AlternativeTitleType *trackPartTitle = QVarPtr<AlternativeTitleType>::asPointer(value);
    if (!trackPartTitle)
        return;
    if (op == Add)
        m_hasTrackPart->setTrackPartTitle(trackPartTitle);
    m_editTrackPartTitle->setText(trackPartTitle->toString());
}

void HasTrackPartTypeForm::destinationStartRemoveClicked()
{
    if (!m_hasTrackPart->destinationStart())
        return;
    m_hasTrackPart->setDestinationStart(0);
    m_editDestinationStart->setText(tr("(none)"));
}

void HasTrackPartTypeForm::destinationStartClicked()
{
    TimeTypeForm *timeForm = new TimeTypeForm(
                m_hasTrackPart->destinationStart(),this->mainWindow());
    QObject::connect(timeForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(destinationStartClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(timeForm);
}

void HasTrackPartTypeForm::destinationStartClosed(Operation op, QVariant value)
{
    TimeType *time = QVarPtr<TimeType>::asPointer(value);
    if (!time)
        return;
    if (op == Add)
        m_hasTrackPart->setDestinationStart(time);
    m_editDestinationStart->setText(time->toString());
}

void HasTrackPartTypeForm::destinationEndRemoveClicked()
{
    if (!m_hasTrackPart->destinationEnd())
        return;
    m_hasTrackPart->setDestinationEnd(0);
    m_editDestinationEnd->setText(tr("(none)"));
}

void HasTrackPartTypeForm::destinationEndClicked()
{
    TimeTypeForm *timeForm = new TimeTypeForm(
                m_hasTrackPart->destinationEnd(),this->mainWindow());
    QObject::connect(timeForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(destinationEndClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(timeForm);
}

void HasTrackPartTypeForm::destinationEndClosed(Operation op, QVariant value)
{
    TimeType *time = QVarPtr<TimeType>::asPointer(value);
    if (!time)
        return;
    if (op == Add)
        m_hasTrackPart->setDestinationEnd(time);
    m_editDestinationEnd->setText(time->toString());
}

void HasTrackPartTypeForm::sourceStartRemoveClicked()
{
    if (!m_hasTrackPart->sourceStart())
        return;
    m_hasTrackPart->setSourceStart(0);
    m_editSourceStart->setText(tr("(none)"));
}

void HasTrackPartTypeForm::sourceStartClicked()
{
    TimeTypeForm *timeForm = new TimeTypeForm(
                m_hasTrackPart->sourceStart(),this->mainWindow());
    QObject::connect(timeForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(sourceStartClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(timeForm);
}

void HasTrackPartTypeForm::sourceStartClosed(Operation op, QVariant value)
{
    TimeType *time = QVarPtr<TimeType>::asPointer(value);
    if (!time)
        return;
    if (op == Add)
        m_hasTrackPart->setSourceStart(time);
    m_editSourceStart->setText(time->toString());
}

void HasTrackPartTypeForm::sourceEndRemoveClicked()
{
    if (!m_hasTrackPart->sourceEnd())
        return;
    m_hasTrackPart->setSourceEnd(0);
    m_editSourceEnd->setText(tr("(none)"));
}

void HasTrackPartTypeForm::sourceEndClicked()
{
    TimeTypeForm *timeForm = new TimeTypeForm(
                m_hasTrackPart->sourceEnd(),this->mainWindow());
    QObject::connect(timeForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(sourceEndClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(timeForm);
}

void HasTrackPartTypeForm::sourceEndClosed(Operation op, QVariant value)
{
    TimeType *time = QVarPtr<TimeType>::asPointer(value);
    if (!time)
        return;
    if (op == Add)
        m_hasTrackPart->setSourceEnd(time);
    m_editSourceEnd->setText(time->toString());
}

void HasTrackPartTypeForm::relationRemovedClicked()
{
    if (!m_hasTrackPart)
        return;
    // Clean up of the relation fields
    m_hasTrackPart->setTypeDefinition("");
    m_hasTrackPart->setTypeLabel("");
    m_hasTrackPart->setTypeLink("");
    m_hasTrackPart->setNote("");
    if (m_hasTrackPart->runningOrderNumber())
        m_hasTrackPart->setRunningOrderNumber(0);
    if (m_hasTrackPart->relation())
        m_hasTrackPart->setRelation(0);
    if (m_hasTrackPart->relationIdentifier())
        m_hasTrackPart->setRelationIdentifier(0);
    m_hasTrackPart->setRelationLink("");
    m_editRelation->setText(tr("(none)"));
}

void HasTrackPartTypeForm::relationClicked()
{
    RelationTypeForm *relationForm = new RelationTypeForm(
                m_hasTrackPart, this->mainWindow());
    QObject::connect(relationForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(relationClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(relationForm);
}

void HasTrackPartTypeForm::relationClosed(StackableWidget::Operation op, QVariant value)
{
    (void)op; // avoid Warning(unused-parameter)
    RelationType *relation = QVarPtr<RelationType>::asPointer(value);
    if (!relation)
        return;
    m_editRelation->setText(relation->toString());
}

bool HasTrackPartTypeForm::checkCompliance()
{
    bool ok = true;
    QString error_msg = "";

    if (!m_hasTrackPart->trackPartTitle()) {
        ok = false;
        error_msg = "TrackPart Title";
    }

    if(!ok) {
        QErrorMessage *e = new QErrorMessage(this);
        e->setWindowTitle(tr("Required fields"));
        e->showMessage(error_msg);
    }
    return ok;
}
