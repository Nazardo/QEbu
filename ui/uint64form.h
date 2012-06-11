#ifndef UINTFORM64_H
#define UINTFORM64_H

#include "stackablewidget.h"

class UInt64;
class TypeGroupEditBox;
class QUnsignedSpinBox;
class QCheckBox;

class Uint64Form : public StackableWidget
{
    Q_OBJECT
public:
    explicit Uint64Form(UInt64 *uint64,
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
    UInt64 *m_uint64;
};

#endif // UINTFORM64_H
