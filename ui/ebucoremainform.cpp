#include "ebucoremainform.h"
#include "entitytypeform.h"
#include <QtGui>

EbuCoreMainForm::EbuCoreMainForm(EbuCoreMainType *ebuCoreMain, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_ebuCoreMain = ebuCoreMain;
    QVBoxLayout *layout = new QVBoxLayout;
    QPushButton *buttonMetadataProvider = new QPushButton(tr("Metadata Provider..."));
    QObject::connect(buttonMetadataProvider, SIGNAL(clicked()), this, SLOT(onMetadataProviderClicked()));
    layout->addWidget(buttonMetadataProvider);
    this->setLayout(layout);
}

QString EbuCoreMainForm::toString()
{
    return QString(tr("EbuCoreMain"));
}

void EbuCoreMainForm::updateData()
{
    qDebug("%s", qPrintable("updateData() called on ebuCoreMainForm"));
}

void EbuCoreMainForm::onMetadataProviderClicked()
{
    if (!m_ebuCoreMain->metadataProvider()) {
        m_ebuCoreMain->setMetadataProvider(new EntityType());
    }
    this->mainWindow()->pushWidget(new EntityTypeForm(m_ebuCoreMain->metadataProvider(),this->mainWindow()));
}
