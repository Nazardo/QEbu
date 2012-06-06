#ifndef DURATIONTYPEFORM_H
#define DURATIONTYPEFORM_H

#include "stackablewidget.h"
#include <QTimeEdit>

class DurationType;
class QLineEdit;
class QSpinBox;
class QCheckBox;
class FormatGroupEditBox;
class QRadioButton;

class DurationTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit DurationTypeForm(  DurationType *duration,
                                QEbuMainWindow *mainWindow,
                                QWidget *parent = 0);
    QString toString();
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

    QLabel *m_labelTimecode;
    QLineEdit *m_editTimecode;
    QLabel *m_labelNormalPlaytimeHour;
    QLabel *m_labelNormalPlaytimeMinute;
    QLabel *m_labelNormalPlaytimeSecond;
    QLabel *m_labelNormalPlaytimeMSecond;
    QSpinBox *m_spinNormalPlaytimeHour;
    QSpinBox *m_spinNormalPlaytimeMinute;
    QSpinBox *m_spinNormalPlaytimeSecond;
    QSpinBox *m_spinNormalPlaytimeMSecond;
    QSpinBox *m_spinRate;
    QSpinBox *m_spinFactorNumerator;
    QSpinBox *m_spinFactorDenominator;
    QSpinBox *m_spinUnitNumberValue;
    QCheckBox *m_checkRate;
    QCheckBox *m_checkFactorNumerator;
    QCheckBox *m_checkFactorDenominator;
    QCheckBox *m_checkUnitNumberValue;
    QLabel *m_labelTime;
    FormatGroupEditBox *m_editFormatGroup;
    QRadioButton *m_radioTimecode;
    QRadioButton *m_radioNormalPlaytime;
    QRadioButton *m_radioTime;
    QRadioButton *m_radioEditUnitNumber;
    DurationType *m_duration;
};

#endif // DURATIONTYPEFORM_H
