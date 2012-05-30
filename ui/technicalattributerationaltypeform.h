#ifndef TECHNICALATTRIBUTERATIONALTYPEFORM_H
#define TECHNICALATTRIBUTERATIONALTYPEFORM_H

#include "stackablewidget.h"
#include "typegroupeditbox.h"
#include <QSpinBox>
#include <QtGui>

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
private:
    QHBoxLayout *m_mainHLayout;
    QDoubleSpinBox *m_spinValue;
    QSpinBox *m_spinFactorNumerator;
    QSpinBox *m_spinFactorDenominator;
    TypeGroupEditBox *m_editTypeGroup;
    TechnicalAttributeRationalType *m_rational;
    Operation m_op;
};


#endif // TECHNICALATTRIBUTERATIONALTYPEFORM_H
