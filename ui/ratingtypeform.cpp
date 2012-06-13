/****************************************************************************
** Copyright (C) 2012 by
**  Mauro Levra  (nazardo)     mauro@nazardo.it
**  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it
**  Denis Patti  (dextp3)      denis.patti@studenti.polito.it
**  Giovanni Pessiva           giovanni.pessiva@gmail.com
**  Stefano Ricossa            stefano.ricossa@studenti.polito.it
**
** This file is part of QEbu.
** QEbu is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, in the version 3 of the License.
**
** QEbu is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with QEbu.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#include "ratingtypeform.h"
#include "../model/ebucoremaintype.h"
#include "typegroupeditbox.h"
#include "elementtypeeditbox.h"
#include "formatgroupeditbox.h"
#include "entitytypeform.h"
#include "qvarptr.h"
#include <QTextBrowser>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include <QMessageBox>
#include <QEvent>
#include <QComboBox>

RatingTypeForm::RatingTypeForm(RatingType *rating,
                               QEbuMainWindow *mainWindow,
                               QWidget *parent) :
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
        fl->addRow(tr("Rating max value"),m_editRatingScaleMaxValue);

        m_editRatingScaleMinValue = new QLineEdit;
        fl->addRow(tr("Rating min value"),m_editRatingScaleMinValue);
        vl->addLayout(fl);
    }
    {
        QHBoxLayout *hl = new QHBoxLayout;
        hl->addWidget(new QLabel(tr("Rating Provider")));
        m_editRatingProvider = new QLineEdit;
        m_editRatingProvider->setReadOnly(true);
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
    this->setLayout(vl);

    //Event filter
    m_textDocumentation->setText(tr("An element to provide rating values attributed to the media resource."));
    m_editRatingValue->installEventFilter(this);
    m_editRatingScaleMaxValue->installEventFilter(this);
    m_editRatingScaleMinValue->installEventFilter(this);
    m_editRatingProvider->installEventFilter(this);
    m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
    m_editTypeGroup->editTypeLabel()->installEventFilter(this);
    m_editTypeGroup->editTypeLink()->installEventFilter(this);
    m_editFormatGroup->editFormatDefinition()->installEventFilter(this);
    m_editFormatGroup->editFormatLabel()->installEventFilter(this);
    m_editFormatGroup->editFormatLink()->installEventFilter(this);

    // Set text fields...
    m_editRatingValue->setText(m_rating->ratingValue());
    m_editRatingScaleMaxValue->setText(m_rating->ratingScaleMaxValue());
    m_editRatingScaleMinValue->setText(m_rating->ratingScaleMinValue());
    if (m_rating->ratingProvider())
        m_editRatingProvider->setText(m_rating->ratingProvider()->toString());
}

QString RatingTypeForm::toString()
{
    return QString(tr("Rating"));
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
    ratingProviderForm->setTitle(tr("Rating Provider"));
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
    QStringList fields;
    if (m_editRatingValue->text().isEmpty()) {
        ok = false;
        fields += tr("Rating value");
    }
    if (m_editRatingScaleMaxValue->text().isEmpty()) {
        ok = false;
        fields += tr("Rating max value");
    }
    if (m_editRatingScaleMinValue->text().isEmpty()) {
        ok = false;
        fields += tr("Rating min value");
    }
    if (!m_rating->ratingProvider()) {
        ok = false;
        fields += tr("Rating Provider");
    }
    if(!ok) {
        QMessageBox::warning(this, this->toString(),
                             tr("<b>Required fields:</b><br>")
                             +fields.join(",<br>"),
                             QMessageBox::Ok, QMessageBox::Ok);
    }
    return ok;
}

bool RatingTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editRatingValue )
            m_textDocumentation->setText(tr("The value given to the rating e.g. a number or else."));
        else if  (obj == (QObject*) m_editRatingScaleMaxValue)
            m_textDocumentation->setText(tr("Provides the maximum value of the rating scale."));
        else if  (obj == (QObject*) m_editRatingScaleMinValue)
            m_textDocumentation->setText(tr("Provides the minimum value of the rating scale."));
        else if (obj == (QObject*) m_editRatingProvider)
            m_textDocumentation->setText(tr("An entity element to identify the provider of the rating value."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("An optional definition of the type of rating used."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setText(tr("A link to a classification scheme."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("Free text to define the type of rating used."));
        else if (obj == (QObject*) m_editFormatGroup->editFormatDefinition())
            m_textDocumentation->setText(tr("An optional definition of the type of format of the rating used."));
        else if (obj == (QObject*) m_editFormatGroup->editFormatLink())
            m_textDocumentation->setText(tr("A link to a classification scheme."));
        else if (obj == (QObject*) m_editFormatGroup->editFormatLabel())
            m_textDocumentation->setText(tr("Free text to define the type of format of the rating used."));
    }
    return QObject::eventFilter(obj, event);
}
