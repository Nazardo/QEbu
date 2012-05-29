#include "ratingtypeform.h"

#include "entitytypeform.h"
#include "qvarptr.h"

#include <QtGui>

RatingTypeForm::RatingTypeForm(RatingType *rating, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (rating) ? Edit : Add;
    if(!rating)
        m_rating = new RatingType;
    else
        m_rating = rating;
    QVBoxLayout *vl = new QVBoxLayout;
    {
        m_editTypeGroup = new TypeGroupEditBox(rating);
        vl->addWidget(m_editTypeGroup);
    }
    {
        m_editFormatGroup = new FormatGroupEditBox(rating);
        vl->addWidget(m_editFormatGroup);
    }
    {
        QFormLayout *fl = new QFormLayout;

        m_editRatingValue = new QLineEdit;
        fl->addRow(tr("Rating value"),m_editRatingValue);

        m_editRatingScaleMaxValue = new QLineEdit;
        fl->addRow(tr("Rating value"),m_editRatingScaleMaxValue);

        m_editRatingScaleMinValue = new QLineEdit;
        fl->addRow(tr("Rating value"),m_editRatingScaleMinValue);
        vl->addLayout(fl);
    }
    {
        QHBoxLayout *hl = new QHBoxLayout;
        hl->addWidget(new QLabel(tr("Rating Provider")));
        m_editRatingProvider = new QLineEdit;
        m_editRatingProvider->setEnabled(false);
        hl->addWidget(m_editRatingProvider);

        QPushButton *buttonRatingProvider = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttonRatingProvider, SIGNAL(clicked()),
                         this, SLOT(ratingProviderClicked()));
        hl->addWidget(buttonRatingProvider);
        QPushButton *buttonRatingProviderRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonRatingProviderRemove, SIGNAL(clicked()),
                         this, SLOT(ratingProviderRemoveClicked()));
        hl->addWidget(buttonRatingProviderRemove);
        vl->addLayout(hl);
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
    m_editRatingValue->setText(m_rating->ratingValue());
    m_editRatingScaleMaxValue->setText(m_rating->ratingScaleMaxValue());
    m_editRatingScaleMinValue->setText(m_rating->ratingScaleMinValue());
    if (m_rating->ratingProvider())
        m_editRatingProvider->setText(m_rating->ratingProvider()->toString());
}

QString RatingTypeForm::toString()
{
    return QString(tr("Rating Type"));
}

void RatingTypeForm::ratingProviderRemoveClicked()
{
    if (!m_rating->ratingProvider())
        return;
    m_rating->setRatingProvider(0);
    m_editRatingProvider->setText(tr("(none)"));
}

void RatingTypeForm::ratingProviderClicked()
{
    EntityTypeForm *ratingProviderForm = new EntityTypeForm(
                m_rating->ratingProvider(),this->mainWindow());
    QObject::connect(ratingProviderForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(ratingProviderClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(ratingProviderForm);
}

void RatingTypeForm::ratingProviderClosed(Operation op, QVariant value)
{
    EntityType *ratingProvider = QVarPtr<EntityType>::asPointer(value);
    if (!ratingProvider)
        return;
    if (op == Add)
        m_rating->setRatingProvider(ratingProvider);
    m_editRatingProvider->setText(ratingProvider->toString());
}

void RatingTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_rating;
        m_rating = 0;
    }
    emit closed(m_op, QVarPtr<RatingType>::asQVariant(m_rating));
}

void RatingTypeForm::applyClicked()
{
    if (!checkCompliance())
        return;
    m_editTypeGroup->updateExistingTypeGroup(m_rating);
    m_editFormatGroup->updateExistingFormatGroup(m_rating);

    m_rating->setRatingValue(m_editRatingValue->text());
    m_rating->setRatingScaleMaxValue(m_editRatingScaleMaxValue->text());
    m_rating->setRatingScaleMinValue(m_editRatingScaleMinValue->text());

    emit closed(m_op, QVarPtr<RatingType>::asQVariant(m_rating));
}

bool RatingTypeForm::checkCompliance()
{
    bool ok = true;
    QString error_msg = "";
    if (m_editRatingValue->text().isEmpty()) {
        ok = false;
        error_msg += "Rating value \n";
    }
    if (m_editRatingScaleMaxValue->text().isEmpty()) {
        ok = false;
        error_msg += "Rating max value \n";
    }
    if (m_editRatingScaleMinValue->text().isEmpty()) {
        ok = false;
        error_msg += "Rating min value \n";
    }
    if (!m_rating->ratingProvider()) {
        ok = false;
        error_msg += "Rating provider \n";
    }
    if(!ok) {
        QErrorMessage *e = new QErrorMessage(this);
        e->setWindowTitle(tr("Rrequired fields"));
        e->showMessage(error_msg);
    }
    return ok;
}

