#include "durationtypeform.h"

#include "qvarptr.h"
#include "organisationdetailstypeform.h"
#include "detailstypeform.h"
#include "entitytypeform.h"
#include "typegroupform.h"
#include "../model/typeconverter.h"
#include <QtGui>

DurationTypeForm::DurationTypeForm(DurationType *duration, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (duration) ? Edit : Add;
    if (!duration)
        m_duration = new DurationType;
    else
        m_duration = duration;
    // Layout
    m_mainHLayout = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;
    {
        m_radioTimecode = new QRadioButton(tr("Timecode"));
        m_radioTimecode->setCheckable(true);
        l->addWidget(m_radioTimecode);
        QFormLayout *fl = new QFormLayout;
        m_editTimecode = new QLineEdit;
        fl->addRow(tr("Timecode"), m_editTimecode);
        l->addLayout(fl);

    }
    {
        m_radioNormalPlaytime = new QRadioButton(tr("Normal playtime"));
        m_radioNormalPlaytime->setCheckable(true);
        l->addWidget(m_radioNormalPlaytime);
        QFormLayout *fl = new QFormLayout;
        m_editNormalPlaytime = new QLineEdit;
        fl->addRow(tr("Normal playtime"), m_editNormalPlaytime);
        l->addLayout(fl);
    }
    {
        m_radioEditUnitNumber = new QRadioButton(tr("Edit unit number"));
        m_radioEditUnitNumber->setCheckable(true);
        l->addWidget(m_radioEditUnitNumber);
        QFormLayout *fl = new QFormLayout;
        m_editRate = new QSpinBox;
        m_editFactorNumerator = new QSpinBox;
        m_editFactorDenomiantor = new QSpinBox;
        m_editUnitNumberValue = new QSpinBox;
        fl->addRow(tr("Edit rate"), m_editRate);
        fl->addRow(tr("Factor numerator"), m_editFactorNumerator);
        fl->addRow(tr("Factor denominator"), m_editFactorDenomiantor);
        fl->addRow(tr("Edit unit value"), m_editUnitNumberValue);
        l->addLayout(fl);
    }
    {
        m_radioTime = new QRadioButton(tr("Time"));
        m_radioTime->setCheckable(true);
        l->addWidget(m_radioTime);
        m_editFormatGroup = new FormatGroupEditBox(m_duration->time());
        l->addWidget(m_editFormatGroup);
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

    QButtonGroup *radio = new QButtonGroup;
    radio->addButton(m_radioTimecode);
    radio->addButton(m_radioNormalPlaytime);
    radio->addButton(m_radioEditUnitNumber);
    radio->addButton(m_radioTime);

    QObject::connect(m_radioTimecode, SIGNAL(toggled(bool)),
                     this, SLOT(timecodeChecked(bool)));
    QObject::connect(m_radioTime, SIGNAL(toggled(bool)),
                     this, SLOT(timeChecked(bool)));
    QObject::connect(m_radioNormalPlaytime, SIGNAL(toggled(bool)),
                     this, SLOT(normalPlaytimeChecked(bool)));
    QObject::connect(m_radioEditUnitNumber, SIGNAL(toggled(bool)),
                     this, SLOT(editUnitNumberChecked(bool)));

    m_mainHLayout->addLayout(l);
    this->setLayout(m_mainHLayout);

    // Set data fields...
    m_editTimecode->setText(m_duration->timecode());
    m_editNormalPlaytime->setText(TypeConverter::durationToString(m_duration->normalPlayTime()));
    if (m_duration->editRate())
        m_editRate->setValue(*(m_duration->editRate()));
    m_editFactorNumerator->setValue(m_duration->factorNumerator());
    m_editFactorDenomiantor->setValue(m_duration->factorDenominator());
    if (m_duration->editUnitNumberValue())
        m_editUnitNumberValue->setValue(*(m_duration->editUnitNumberValue()));

    if (duration) {
        switch (duration->durationTypeRepresentation()) {
        case DurationType::enumTimecode:
        {
            m_radioTimecode->setChecked(true);
        }
            break;
        case DurationType::enumTime:
        {
            m_radioTime->setChecked(true);
        }
            break;
        case DurationType::enumNormalPlayTime:
        {
            m_radioNormalPlaytime->setChecked(true);
        }
            break;
        case DurationType::enumEditUnitNumber:
        {
            m_radioEditUnitNumber->setChecked(true);
        }
            break;
        }
    }
    else
        m_radioTimecode->setChecked(true);
}

QString DurationTypeForm::toString()
{
    return QString("Time Type");
}

void DurationTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_duration;
        m_duration = 0;
    }
    emit closed(m_op, QVarPtr<DurationType>::asQVariant(m_duration));
}

void DurationTypeForm::applyClicked()
{
    if (!checkCompliance())
        return;
    if (m_radioTimecode->isChecked()) {
        m_duration->setTimecode(m_editTimecode->text());

    } else if (m_radioNormalPlaytime->isChecked()) {
        m_duration->setNormalPlayTime(TypeConverter::stringToDuration(m_editNormalPlaytime->text()));

    } else if (m_radioTime->isChecked()) {
        FormatGroup *fg = m_editFormatGroup->formatGroup();
        m_duration->setTime(fg);

    } else if (m_radioEditUnitNumber->isChecked()) {
        m_duration->setEditRate(m_editRate->value());
        m_duration->setEditUnitNumberValue(m_editUnitNumberValue->value());
        m_duration->setFactorDenominator(m_editFactorDenomiantor->value());
        m_duration->setFactorNumerator(m_editFactorNumerator->value());
    }

    emit closed(m_op, QVarPtr<DurationType>::asQVariant(m_duration));
}

void DurationTypeForm::timeChecked(bool checked)
{
    if (!checked)
        return;
    m_editFormatGroup->setEnabled(true);
    m_editUnitNumberValue->setEnabled(false);
    m_editRate->setEnabled(false);
    m_editFactorNumerator->setEnabled(false);
    m_editFactorDenomiantor->setEnabled(false);
    m_editTimecode->setEnabled(false);
    m_editNormalPlaytime->setEnabled(false);
}

void DurationTypeForm::timecodeChecked(bool checked)
{
    if (!checked)
        return;
    m_editFormatGroup->setEnabled(false);
    m_editUnitNumberValue->setEnabled(false);
    m_editRate->setEnabled(false);
    m_editFactorNumerator->setEnabled(false);
    m_editFactorDenomiantor->setEnabled(false);
    m_editTimecode->setEnabled(true);
    m_editNormalPlaytime->setEnabled(false);
}

void DurationTypeForm::normalPlaytimeChecked(bool checked)
{
    if (!checked)
        return;
    m_editFormatGroup->setEnabled(false);
    m_editUnitNumberValue->setEnabled(false);
    m_editRate->setEnabled(false);
    m_editFactorNumerator->setEnabled(false);
    m_editFactorDenomiantor->setEnabled(false);
    m_editTimecode->setEnabled(false);
    m_editNormalPlaytime->setEnabled(true);
}

void DurationTypeForm::editUnitNumberChecked(bool checked)
{
    if (!checked)
        return;
    m_editFormatGroup->setEnabled(false);
    m_editUnitNumberValue->setEnabled(true);
    m_editRate->setEnabled(true);
    m_editFactorNumerator->setEnabled(true);
    m_editFactorDenomiantor->setEnabled(true);
    m_editTimecode->setEnabled(false);
    m_editNormalPlaytime->setEnabled(false);
}

bool DurationTypeForm::checkCompliance()
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

