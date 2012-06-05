#ifndef EBUCOREMAINFORM_H
#define EBUCOREMAINFORM_H

#include "stackablewidget.h"

class EbuCoreMainType;
class QLineEdit;
class QCheckBox;
class QDateEdit;

class EbuCoreMainForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit EbuCoreMainForm(EbuCoreMainType *ebuCoreMain,
                             QEbuMainWindow *mainWindow,
                             QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void metadataProviderRemoveClicked();
    void metadataProviderClicked();
    void metadataProviderClosed(Operation op, QVariant value);
    void coreMetadataRemoveClicked();
    void coreMetadataClicked();
    void coreMetadataClosed(Operation op, QVariant value);
    // -
    void dateLastModifiedChanged();
private:

    QLineEdit *m_editSchema;
    QLineEdit *m_editVersion;
    QCheckBox *m_checkDateLastModified;
    QDateEdit  *m_editDateLastModified;
    QLineEdit *m_editDocumentId;
    QLineEdit *m_editLang;
    QLineEdit *m_editCoreMetadata;
    QLineEdit *m_editMetadataProvider;

    EbuCoreMainType *m_ebuCoreMain;

};

#endif // EBUCOREMAINFORM_H
