#ifndef TECHNICALATTRIBUTERATIONALTYPEFORM_H
#define TECHNICALATTRIBUTERATIONALTYPEFORM_H

#include "stackablewidget.h"
#include "typegroupeditbox.h"
#include <QSpinBox>
#include <QCheckBox>

class TechnicalAttributeRationalTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit TechnicalAttributeRationalTypeForm(TechnicalAttributeRationalType *rational,
                                                QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    void valueChanged();
    void numeratorChanged();
    void denominatorChanged();
private:
    QHBoxLayout *m_mainHLayout;
    QDoubleSpinBox *m_spinValue;
    QSpinBox *m_spinFactorNumerator;
    QSpinBox *m_spinFactorDenominator;
    QCheckBox *m_checkValue;
    QCheckBox *m_checkNumerator;
    QCheckBox *m_checkDenominator;
    TypeGroupEditBox *m_editTypeGroup;
    TechnicalAttributeRationalType *m_rational;
    Operation m_op;
};


#endif // TECHNICALATTRIBUTERATIONALTYPEFORM_H
