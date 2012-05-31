#ifndef TIMETYPEFORM_H
#define TIMETYPEFORM_H

#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include "stackablewidget.h"
#include "listview.h"
#include "../model/ebucoremaintype.h"
#include "formatgroupeditbox.h"

class TimeTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit TimeTypeForm(TimeType *time, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // -
    void timecodeChecked(bool checked);
    void normalPlaytimeChecked(bool checked);
    void editUnitNumberChecked(bool checked);
    void timeChecked(bool checked);
    // -
    void rateChanged();
    void factorNumeratorChanged();
    void factorDenominatorChanged();
    void unitNumberValueChanged();
private:
    void updateListAndButtons();

    QHBoxLayout *m_mainHLayout;
    QLineEdit *m_editTimecode;
    QLineEdit *m_editNormalPlaytime;
    QSpinBox *m_spinRate;
    QSpinBox *m_spinFactorNumerator;
    QSpinBox *m_spinFactorDenominator;
    QSpinBox *m_spinUnitNumberValue;
    QCheckBox *m_checkRate;
    QCheckBox *m_checkFactorNumerator;
    QCheckBox *m_checkFactorDenominator;
    QCheckBox *m_checkUnitNumberValue;
    FormatGroupEditBox *m_editFormatGroup;
    QRadioButton *m_radioTimecode;
    QRadioButton *m_radioNormalPlaytime;
    QRadioButton *m_radioTime;
    QRadioButton *m_radioEditUnitNumber;
    TimeType *m_time;
    Operation m_op;
};

#endif // TIMETYPEFORM_H
