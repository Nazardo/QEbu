#ifndef DATEGROUPEDITBOX_H
#define DATEGROUPEDITBOX_H

#include <QWidget>

class DateGroup;
class QSpinBox;
class QDateEdit;
class QTimeEdit;
class QGroupBox;
class QCheckBox;
class QLineEdit;

class DateGroupEditBox : public QWidget
{
    Q_OBJECT
public:
    explicit DateGroupEditBox(DateGroup *dateGroup,
                              QWidget *parent = 0);
    DateGroup *dateGroup();
    void updateExistingDateGroup(DateGroup *dateGroup);
    void setLabel(const QString &label);
    QSpinBox *editStartYear();
    QDateEdit *editStartDate();
    QTimeEdit *editStartTime();
    QSpinBox *editEndYear();
    QDateEdit *editEndDate();
    QTimeEdit *editEndTime();
    QLineEdit *editPeriod();
private slots:
    void startYearChanged();
    void startDateChanged();
    void startTimeChanged();
    void endYearChanged();
    void endDateChanged();
    void endTimeChanged();
private:
    QGroupBox *m_groupBox;
    QCheckBox *m_checkStartYear;
    QSpinBox *m_editStartYear;
    QCheckBox *m_checkStartDate;
    QDateEdit *m_editStartDate;
    QCheckBox *m_checkStartTime;
    QTimeEdit *m_editStartTime;
    QCheckBox *m_checkEndYear;
    QSpinBox *m_editEndYear;
    QCheckBox *m_checkEndDate;
    QDateEdit *m_editEndDate;
    QCheckBox *m_checkEndTime;
    QTimeEdit *m_editEndTime;
    QLineEdit *m_editPeriod;
};

#endif // DATEGROUPEDITBOX_H
