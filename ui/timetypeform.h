#ifndef TIMETYPEFORM_H
#define TIMETYPEFORM_H

#include "stackablewidget.h"
#include <QTimeEdit>

class TimeType;
class QLineEdit;
class QSignedSpinBox;
class QUnsignedSpinBox;
class QCheckBox;
class FormatGroupEditBox;
class QRadioButton;
class QLabel;

class TimeTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit TimeTypeForm(TimeType *time,
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
private:
    void updateListAndButtons();

    QWidget *m_labelTimecode;
    QLineEdit *m_editTimecode;
    QWidget *m_labelNormalPlaytime;
    QTimeEdit *m_editNormalPlaytime;
    QUnsignedSpinBox *m_spinRate;
    QUnsignedSpinBox *m_spinFactorNumerator;
    QUnsignedSpinBox *m_spinFactorDenominator;
    QSignedSpinBox *m_spinUnitNumberValue;
    QCheckBox *m_checkRate;
    QCheckBox *m_checkFactorNumerator;
    QCheckBox *m_checkFactorDenominator;
    QLabel *m_labelUnitNumberValue;
    QWidget *m_labelTime;
    FormatGroupEditBox *m_editFormatGroup;
    QRadioButton *m_radioTimecode;
    QRadioButton *m_radioNormalPlaytime;
    QRadioButton *m_radioTime;
    QRadioButton *m_radioEditUnitNumber;
    TimeType *m_time;
};

#endif // TIMETYPEFORM_H
