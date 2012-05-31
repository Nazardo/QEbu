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
        {
            QGridLayout *gl = new QGridLayout;

            m_spinRate = new QSpinBox;
            m_checkRate = new QCheckBox(tr("Rate"));
            QObject::connect(m_spinRate, SIGNAL(valueChanged(int)),
                             this, SLOT(rateChanged()));
            gl->addWidget(m_checkRate, 0, 0);
            gl->addWidget(m_spinRate, 0, 1);

            m_spinFactorNumerator = new QSpinBox;
            m_checkFactorNumerator = new QCheckBox(tr("Factor numerator"));
            QObject::connect(m_spinFactorNumerator, SIGNAL(valueChanged(int)),
                             this, SLOT(factorNumeratorChanged()));
            gl->addWidget(m_checkFactorNumerator, 1, 0);
            gl->addWidget(m_spinFactorNumerator, 1, 1);

            m_spinFactorDenominator = new QSpinBox;
            m_checkFactorDenominator = new QCheckBox(tr("Factor denominator"));
            QObject::connect(m_spinFactorDenominator, SIGNAL(valueChanged(int)),
                             this, SLOT(factorDenominatorChanged()));
            gl->addWidget(m_checkFactorDenominator, 2, 0);
            gl->addWidget(m_spinFactorDenominator, 2, 1);

            m_spinUnitNumberValue = new QSpinBox;
            m_checkUnitNumberValue = new QCheckBox(tr("Unit value"));
            QObject::connect(m_spinUnitNumberValue, SIGNAL(valueChanged(int)),
                             this, SLOT(denominatorChanged()));
            gl->addWidget(m_checkUnitNumberValue, 3, 0);
            gl->addWidget(m_spinUnitNumberValue, 3, 1);

            l->addLayout(gl);
        }
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

    if (m_duration->editUnitNumberValue()) {
        m_spinUnitNumberValue->setValue(*(m_duration->editUnitNumberValue()));
        m_checkUnitNumberValue->setChecked(true);
    }
    if (m_duration->editRate()) {
        m_spinRate->setValue(*(m_duration->editRate()));
        m_checkRate->setChecked(true);
    }
    if (m_duration->factorNumerator()) {
        m_spinFactorNumerator->setValue(m_duration->factorNumerator());
        m_checkFactorNumerator->setChecked(true);
    }
    if (m_duration->factorDenominator()) {
        m_spinFactorDenominator->setValue(m_duration->factorDenominator());
        m_checkFactorDenominator->setChecked(true);
    }

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
        if (m_checkRate->isChecked())
            m_duration->setEditRate(m_spinRate->value());
        if (m_checkUnitNumberValue->isChecked())
            m_duration->setEditUnitNumberValue(m_spinUnitNumberValue->value());
        if (m_checkFactorNumerator->isChecked())
            m_duration->setFactorNumerator(m_spinFactorNumerator->value());
        if (m_checkFactorDenominator->isChecked())
            m_duration->setFactorDenominator(m_spinFactorDenominator->value());
    }

    emit closed(m_op, QVarPtr<DurationType>::asQVariant(m_duration));
}

void DurationTypeForm::timeChecked(bool checked)
{
    if (!checked)
        return;
    m_editFormatGroup->setEnabled(true);
    m_spinUnitNumberValue->setEnabled(false);
    m_spinRate->setEnabled(false);
    m_spinFactorNumerator->setEnabled(false);
    m_spinFactorDenominator->setEnabled(false);
    m_editTimecode->setEnabled(false);
    m_editNormalPlaytime->setEnabled(false);
}

void DurationTypeForm::timecodeChecked(bool checked)
{
    if (!checked)
        return;
    m_editFormatGroup->setEnabled(false);
    m_spinUnitNumberValue->setEnabled(false);
    m_spinRate->setEnabled(false);
    m_spinFactorNumerator->setEnabled(false);
    m_spinFactorDenominator->setEnabled(false);
    m_editTimecode->setEnabled(true);
    m_editNormalPlaytime->setEnabled(false);
}

void DurationTypeForm::normalPlaytimeChecked(bool checked)
{
    if (!checked)
        return;
    m_editFormatGroup->setEnabled(false);
    m_spinUnitNumberValue->setEnabled(false);
    m_spinRate->setEnabled(false);
    m_spinFactorNumerator->setEnabled(false);
    m_spinFactorDenominator->setEnabled(false);
    m_editTimecode->setEnabled(false);
    m_editNormalPlaytime->setEnabled(true);
}

void DurationTypeForm::editUnitNumberChecked(bool checked)
{
    if (!checked)
        return;
    m_editFormatGroup->setEnabled(false);
    m_spinUnitNumberValue->setEnabled(true);
    m_spinRate->setEnabled(true);
    m_spinFactorNumerator->setEnabled(true);
    m_spinFactorDenominator->setEnabled(true);
    m_editTimecode->setEnabled(false);
    m_editNormalPlaytime->setEnabled(false);
}

void DurationTypeForm::rateChanged()
{
    m_checkRate->setChecked(true);
}

void DurationTypeForm::factorNumeratorChanged()
{
    m_checkFactorNumerator->setChecked(true);
}

void DurationTypeForm::factorDenominatorChanged()
{
    m_checkFactorDenominator->setChecked(true);
}

void DurationTypeForm::unitNumberValueChanged()
{
    m_checkUnitNumberValue->setChecked(true);
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

