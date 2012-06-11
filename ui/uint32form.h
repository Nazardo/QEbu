#ifndef UINT32FORM_H
#define UINT32FORM_H

#include "stackablewidget.h"

class UInt32;
class TypeGroupEditBox;
class QUnsignedSpinBox;
class QCheckBox;

class Uint32Form : public StackableWidget
{
    Q_OBJECT
public:
    explicit Uint32Form(UInt32 *uint32,
                        QEbuMainWindow *mainWindow,
                        QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    void valueChanged();
private:
    bool eventFilter(QObject *obj, QEvent *event);
    TypeGroupEditBox *m_editTypeGroup;
    QUnsignedSpinBox *m_spinValue;
    QCheckBox *m_checkValue;
    UInt32 *m_uint32;
};

#endif // UINT32FORM_H
