#ifndef TECHNICALATTRIBUTERATIONALTYPEFORM_H
#define TECHNICALATTRIBUTERATIONALTYPEFORM_H

#include "stackablewidget.h"

class TechnicalAttributeRationalType;
class QDoubleSpinBox;
class QSignedSpinBox;
class QSpinBox;
class QUnsignedSpinBox;
class QCheckBox;
class TypeGroupEditBox;

class TechnicalAttributeRationalTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit TechnicalAttributeRationalTypeForm(
            TechnicalAttributeRationalType *rational,
            QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    void valueChanged();
    void numeratorChanged();
    void denominatorChanged();
private:
    QSignedSpinBox *m_spinValue;
    QSpinBox *m_spinFactorNumerator;
    QSpinBox *m_spinFactorDenominator;
    QCheckBox *m_checkValue;
    QCheckBox *m_checkNumerator;
    QCheckBox *m_checkDenominator;
    TypeGroupEditBox *m_editTypeGroup;
    TechnicalAttributeRationalType *m_rational;
};


#endif // TECHNICALATTRIBUTERATIONALTYPEFORM_H
