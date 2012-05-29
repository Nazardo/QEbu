#ifndef EBUCOREMAINFORM_H
#define EBUCOREMAINFORM_H

#include "stackablewidget.h"
#include "../model/ebucoremaintype.h"
#include <QLineEdit>

class EbuCoreMainForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit EbuCoreMainForm(EbuCoreMainType *ebuCoreMain, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void metadataProviderRemoveClicked();
    void metadataProviderClicked();
    void metadataProviderClosed(Operation op, QVariant value);
    // TEST!!!
    void testClicked();
private:
    EbuCoreMainType *m_ebuCoreMain;
    QLineEdit *m_editMetadataProvider;
};

#endif // EBUCOREMAINFORM_H
