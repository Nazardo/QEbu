#include "durationtypeform.h"
#include "../model/ebucoremaintype.h"
#include "listview.h"
#include "formatgroupeditbox.h"
#include "qvarptr.h"
#include "organisationdetailstypeform.h"
#include "detailstypeform.h"
#include "entitytypeform.h"
#include "timezoneeditbox.h"
#include "../model/typeconverter.h"
#include "../model/qebulimits.h"
#include <QRadioButton>
#include <QButtonGroup>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QSpinBox>
#include <QCheckBox>
#include <QFormLayout>
#include <QLabel>
#include <QEvent>
#include <QTextEdit>
#include "qextendedspinbox.h"

DurationTypeForm::DurationTypeForm( DurationType *duration,
                                    QEbuMainWindow *mainWindow,
                                    QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (duration) ? Edit : Add;
    if (!duration)
        m_duration = new DurationType;
    else
        m_duration = duration;
    // Layout
    QVBoxLayout *l = new QVBoxLayout;
    {
        m_radioTimecode = new QRadioButton(tr("Timecode"));
        m_radioTimecode->setCheckable(true);
        l->addWidget(m_radioTimecode);
        QFormLayout *fl = new QFormLayout;

        m_labelTimecode = new QLabel(tr("Start time"));
        m_editTimecode = new QLineEdit();
        m_editTimecode->installEventFilter(this);
        QRegExp SMPTE_ST_2021_1_2009("[0-9][0-9]:[0-5][0-9]:[0-5][0-9]:[0-9][0-9]");
        m_editTimecode->setValidator(new QRegExpValidator(SMPTE_ST_2021_1_2009));
        m_editTimecode->setPlaceholderText("hh:mm:ss:ff");
        fl->addRow(m_labelTimecode, m_editTimecode);
        l->addLayout(fl);

    }
    {
        m_radioNormalPlaytime = new QRadioButton(tr("Normal playtime"));
        m_radioNormalPlaytime->setCheckable(true);
        l->addWidget(m_radioNormalPlaytime);

        {
            QGridLayout *gl = new QGridLayout;

            m_labelNormalPlaytimeHour = new QLabel(tr("Hours"));
            m_labelNormalPlaytimeMinute = new QLabel(tr("Minutes"));
            m_labelNormalPlaytimeSecond = new QLabel(tr("Seconds"));
            m_labelNormalPlaytimeMSecond = new QLabel(tr("MSeconds"));
            m_spinNormalPlaytimeHour = new QSpinBox;
            m_spinNormalPlaytimeMinute = new QSpinBox;
            m_spinNormalPlaytimeSecond = new QSpinBox;
            m_spinNormalPlaytimeMSecond = new QSpinBox;
            m_spinNormalPlaytimeHour->installEventFilter(this);
            m_spinNormalPlaytimeMinute->installEventFilter(this);
            m_spinNormalPlaytimeSecond->installEventFilter(this);
            m_spinNormalPlaytimeMSecond->installEventFilter(this);
            m_spinNormalPlaytimeHour->setMinimum(0);
            m_spinNormalPlaytimeMinute->setMinimum(0);
            m_spinNormalPlaytimeSecond->setMinimum(0);
            m_spinNormalPlaytimeMSecond->setMinimum(0);

            gl->addWidget(m_labelNormalPlaytimeHour, 0, 0);
            gl->addWidget(m_spinNormalPlaytimeHour, 0, 1);
            gl->addWidget(m_labelNormalPlaytimeMinute, 1, 0);
            gl->addWidget(m_spinNormalPlaytimeMinute, 1, 1);
            gl->addWidget(m_labelNormalPlaytimeSecond, 2, 0);
            gl->addWidget(m_spinNormalPlaytimeSecond, 2, 1);
            gl->addWidget(m_labelNormalPlaytimeMSecond, 3, 0);
            gl->addWidget(m_spinNormalPlaytimeMSecond, 3, 1);
            l->addLayout(gl);
        }
    }
    {
        m_radioEditUnitNumber = new QRadioButton(tr("Edit unit number"));
        m_radioEditUnitNumber->setCheckable(true);
        l->addWidget(m_radioEditUnitNumber);
        {
            QGridLayout *gl = new QGridLayout;

            m_spinUnitNumberValue = new QSignedSpinBox;
            m_spinUnitNumberValue->setRange(qEbuLimits::getMinInt64(), qEbuLimits::getMaxInt64());
            m_spinUnitNumberValue->installEventFilter(this);
            m_labelUnitNumber = new QLabel(tr("Unit value"));
            gl->addWidget(m_labelUnitNumber, 0, 0);
            gl->addWidget(m_spinUnitNumberValue, 0, 1);

            m_spinRate = new QUnsignedSpinBox;
            m_spinRate->installEventFilter(this);
            m_spinRate->setRange(1, qEbuLimits::getMaxUInt());
            m_spinRate->setValue(1);
            m_checkRate = new QCheckBox(tr("Rate"));
            QObject::connect(m_spinRate, SIGNAL(valueChanged()),
                             this, SLOT(rateChanged()));
            gl->addWidget(m_checkRate, 1, 0);
            gl->addWidget(m_spinRate, 1, 1);

            m_spinFactorNumerator = new QUnsignedSpinBox;
            m_spinFactorNumerator->installEventFilter(this);
            m_spinFactorNumerator->setRange(1, qEbuLimits::getMaxUInt());
            m_checkFactorNumerator = new QCheckBox(tr("Factor numerator"));
            QObject::connect(m_spinFactorNumerator, SIGNAL(valueChanged()),
                             this, SLOT(factorNumeratorChanged()));
            gl->addWidget(m_checkFactorNumerator, 2, 0);
            gl->addWidget(m_spinFactorNumerator, 2, 1);

            m_spinFactorDenominator = new QUnsignedSpinBox;
            m_spinFactorDenominator->installEventFilter(this);
            m_spinFactorDenominator->setRange(1, qEbuLimits::getMaxUInt());
            m_checkFactorDenominator = new QCheckBox(tr("Factor denominator"));
            QObject::connect(m_spinFactorDenominator, SIGNAL(valueChanged()),
                             this, SLOT(factorDenominatorChanged()));
            gl->addWidget(m_checkFactorDenominator, 3, 0);
            gl->addWidget(m_spinFactorDenominator, 3, 1);

            l->addLayout(gl);
        }
    }
    {
        m_radioTime = new QRadioButton(tr("Time"));
        m_radioTime->setCheckable(true);
        l->addWidget(m_radioTime);

        m_editTimeValue = new QLineEdit(m_duration->timeValue());
        m_editTimeValue->installEventFilter(this);
        l->addWidget(m_editTimeValue);
        m_editFormatGroup = new FormatGroupEditBox(m_duration->time());
        m_editFormatGroup->editFormatDefinition()->installEventFilter(this);
        m_editFormatGroup->editFormatLabel()->installEventFilter(this);
        m_editFormatGroup->editFormatLink()->installEventFilter(this);
        m_editFormatGroup->setLabel(tr("Time"));
        l->addWidget(m_editFormatGroup);
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

    this->setLayout(l);

    // Set data fields...
    m_textDocumentation->setText(tr("To express a duration"));
    m_editTimecode->setText(m_duration->timecode());
    if (m_duration->normalPlayTime()) {
        m_spinNormalPlaytimeHour->setValue(m_duration->normalPlayTime()->hours());
        m_spinNormalPlaytimeMinute->setValue(m_duration->normalPlayTime()->minutes());
        m_spinNormalPlaytimeSecond->setValue(m_duration->normalPlayTime()->seconds());
        m_spinNormalPlaytimeMSecond->setValue(m_duration->normalPlayTime()->mseconds());
    }

    if (m_duration->editUnitNumberValue()) {
        m_spinUnitNumberValue->setValue(*(m_duration->editUnitNumberValue()));
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
    return QString(tr("Duration"));
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
    if (m_radioTimecode->isChecked()) {
        m_duration->setTimecode(m_editTimecode->text());

    } else if (m_radioNormalPlaytime->isChecked()) {
        m_duration->setNormalPlayTime(new Duration(true,0,0,0,
                                                   m_spinNormalPlaytimeHour->value(),
                                                   m_spinNormalPlaytimeMinute->value(),
                                                   m_spinNormalPlaytimeSecond->value(),
                                                   m_spinNormalPlaytimeMSecond->value()));

    } else if (m_radioTime->isChecked()) {
        m_duration->setTimeValue(m_editTimeValue->text());
        FormatGroup *fg = m_editFormatGroup->formatGroup();
        m_duration->setTime(fg);

    } else if (m_radioEditUnitNumber->isChecked()) {
        if (m_checkRate->isChecked())
            m_duration->setEditRate(m_spinRate->value());
        else
            m_duration->clearEditRate();

        m_duration->setEditUnitNumberValue(m_spinUnitNumberValue->value());

        if (m_checkFactorNumerator->isChecked())
            m_duration->setFactorNumerator(m_spinFactorNumerator->value());
        else
            m_duration->clearFactorNumerator();
        if (m_checkFactorDenominator->isChecked())
            m_duration->setFactorDenominator(m_spinFactorDenominator->value());
        else
            m_duration->clearFactorDenominator();
    }

    emit closed(m_op, QVarPtr<DurationType>::asQVariant(m_duration));
}

void DurationTypeForm::timeChecked(bool checked)
{
    if (!checked)
        return;

    m_editTimeValue->setEnabled(true);
    m_editFormatGroup->setEnabled(true);
    m_spinUnitNumberValue->setEnabled(false);
    m_spinRate->setEnabled(false);
    m_spinFactorNumerator->setEnabled(false);
    m_spinFactorDenominator->setEnabled(false);
    m_labelUnitNumber->setEnabled(false);
    m_checkRate->setEnabled(false);
    m_checkFactorNumerator->setEnabled(false);
    m_checkFactorDenominator->setEnabled(false);
    m_labelTimecode->setEnabled(false);
    m_editTimecode->setEnabled(false);
    m_labelNormalPlaytimeHour->setEnabled(false);
    m_labelNormalPlaytimeMinute->setEnabled(false);
    m_labelNormalPlaytimeSecond->setEnabled(false);
    m_labelNormalPlaytimeMSecond->setEnabled(false);
    m_spinNormalPlaytimeHour->setEnabled(false);
    m_spinNormalPlaytimeMinute->setEnabled(false);
    m_spinNormalPlaytimeSecond->setEnabled(false);
    m_spinNormalPlaytimeMSecond->setEnabled(false);
}

void DurationTypeForm::timecodeChecked(bool checked)
{
    if (!checked)
        return;

    m_editTimeValue->setEnabled(false);
    m_editFormatGroup->setEnabled(false);
    m_spinUnitNumberValue->setEnabled(false);
    m_spinRate->setEnabled(false);
    m_spinFactorNumerator->setEnabled(false);
    m_spinFactorDenominator->setEnabled(false);
    m_labelUnitNumber->setEnabled(false);
    m_checkRate->setEnabled(false);
    m_checkFactorNumerator->setEnabled(false);
    m_checkFactorDenominator->setEnabled(false);
    m_labelTimecode->setEnabled(true);
    m_editTimecode->setEnabled(true);
    m_labelNormalPlaytimeHour->setEnabled(false);
    m_labelNormalPlaytimeMinute->setEnabled(false);
    m_labelNormalPlaytimeSecond->setEnabled(false);
    m_labelNormalPlaytimeMSecond->setEnabled(false);
    m_spinNormalPlaytimeHour->setEnabled(false);
    m_spinNormalPlaytimeMinute->setEnabled(false);
    m_spinNormalPlaytimeSecond->setEnabled(false);
    m_spinNormalPlaytimeMSecond->setEnabled(false);
}

void DurationTypeForm::normalPlaytimeChecked(bool checked)
{
    if (!checked)
        return;

    m_editTimeValue->setEnabled(false);
    m_editFormatGroup->setEnabled(false);
    m_spinUnitNumberValue->setEnabled(false);
    m_spinRate->setEnabled(false);
    m_spinFactorNumerator->setEnabled(false);
    m_spinFactorDenominator->setEnabled(false);
    m_labelUnitNumber->setEnabled(false);
    m_checkRate->setEnabled(false);
    m_checkFactorNumerator->setEnabled(false);
    m_checkFactorDenominator->setEnabled(false);
    m_labelTimecode->setEnabled(false);
    m_editTimecode->setEnabled(false);
    m_labelNormalPlaytimeHour->setEnabled(true);
    m_labelNormalPlaytimeMinute->setEnabled(true);
    m_labelNormalPlaytimeSecond->setEnabled(true);
    m_labelNormalPlaytimeMSecond->setEnabled(true);
    m_spinNormalPlaytimeHour->setEnabled(true);
    m_spinNormalPlaytimeMinute->setEnabled(true);
    m_spinNormalPlaytimeSecond->setEnabled(true);
    m_spinNormalPlaytimeMSecond->setEnabled(true);
}

void DurationTypeForm::editUnitNumberChecked(bool checked)
{
    if (!checked)
        return;

    m_editTimeValue->setEnabled(false);
    m_editFormatGroup->setEnabled(false);
    m_spinUnitNumberValue->setEnabled(true);
    m_spinRate->setEnabled(true);
    m_spinFactorNumerator->setEnabled(true);
    m_spinFactorDenominator->setEnabled(true);
    m_labelUnitNumber->setEnabled(true);
    m_checkRate->setEnabled(true);
    m_checkFactorNumerator->setEnabled(true);
    m_checkFactorDenominator->setEnabled(true);
    m_labelTimecode->setEnabled(false);
    m_editTimecode->setEnabled(false);
    m_labelNormalPlaytimeHour->setEnabled(false);
    m_labelNormalPlaytimeMinute->setEnabled(false);
    m_labelNormalPlaytimeSecond->setEnabled(false);
    m_labelNormalPlaytimeMSecond->setEnabled(false);
    m_spinNormalPlaytimeHour->setEnabled(false);
    m_spinNormalPlaytimeMinute->setEnabled(false);
    m_spinNormalPlaytimeSecond->setEnabled(false);
    m_spinNormalPlaytimeMSecond->setEnabled(false);
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

bool DurationTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if ( obj == (QObject*) m_editTimecode)
            m_textDocumentation->setText(tr("To express the duration using timecode compliant with SMPTE ST\n2021-1:2009"));
        else if ( obj == (QObject*) m_spinNormalPlaytimeHour )
            m_textDocumentation->setText(tr("The express the duration in the extended format PnYnMnDTnHnMnS"));
        else if  (obj == (QObject*) m_spinNormalPlaytimeMinute)
            m_textDocumentation->setText(tr("The express the duration in the extended format PnYnMnDTnHnMnS"));
        else if  (obj == (QObject*) m_spinNormalPlaytimeSecond)
            m_textDocumentation->setText(tr("The express the duration in the extended format PnYnMnDTnHnMnS"));
        else if  (obj == (QObject*) m_spinNormalPlaytimeMSecond)
            m_textDocumentation->setText(tr("The express the duration in the extended format PnYnMnDTnHnMnS"));
        else if  (obj == (QObject*) m_spinUnitNumberValue)
            m_textDocumentation->setText(tr("The express the duration as a number of edit Units"));
        else if  (obj == (QObject*) m_spinRate)
            m_textDocumentation->setText(tr("The base reference for the material, i.e. the frame rate for video or sample rate for audio"));
        else if  (obj == (QObject*) m_spinFactorNumerator)
            m_textDocumentation->setText(tr("The numerator of the correction factor if applicable, Value is '1' by default."));
        else if  (obj == (QObject*) m_spinFactorDenominator)
            m_textDocumentation->setText(tr("The denominator of the correction factor if applicable Value is '1' by default."));
        else if  (obj == (QObject*) m_editTimeValue)
            m_textDocumentation->setText(tr("To express the duration in a user defined time format."));
        else if  (obj == (QObject*) m_editFormatGroup->editFormatDefinition())
            m_textDocumentation->setText(tr("An optional definition."));
        else if  (obj == (QObject*) m_editFormatGroup->editFormatLabel())
            m_textDocumentation->setText(tr("Free text."));
        else if  (obj == (QObject*) m_editFormatGroup->editFormatLink())
            m_textDocumentation->setText(tr("A URI to e.g. a classification scheme term."));
    }
    return QObject::eventFilter(obj, event);
}
