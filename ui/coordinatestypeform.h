#ifndef COORDINATESTYPEFORM_H
#define COORDINATESTYPEFORM_H

#include "stackablewidget.h"
#include "model/coremetadatatype.h"
#include "formatgroupeditbox.h"
#include <QDoubleSpinBox>

class CoordinatesTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit CoordinatesTypeForm(CoordinatesType *coordinates, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
private slots:
    void cancelClicked();
    void applyClicked();
private:
    QVBoxLayout *m_mainVLayout;
    FormatGroupEditBox *m_editFormatGroup;
    QDoubleSpinBox *m_spinPosx;
    QDoubleSpinBox *m_spinPosy;
    CoordinatesType *m_coordinates;
    Operation m_op;
};

#endif // COORDINATESTYPEFORM_H
