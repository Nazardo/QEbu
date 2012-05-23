#ifndef EBUCOREMAINFORM_H
#define EBUCOREMAINFORM_H

#include "stackablewidget.h"
#include "../model/ebucoremaintype.h"

class EbuCoreMainForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit EbuCoreMainForm(EbuCoreMainType *ebuCoreMain, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    void updateData();
signals:
private slots:
    void onMetadataProviderClicked();
private:
    EbuCoreMainType *m_ebuCoreMain;
};

#endif // EBUCOREMAINFORM_H
