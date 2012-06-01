#ifndef ANCILLARYDATAFORMATTYPEFORM_H
#define ANCILLARYDATAFORMATTYPEFORM_H

#include "stackablewidget.h"
#include "../model/ebucoremaintype.h"
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include "listview.h"


class AncillaryDataFormatTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit AncillaryDataFormatTypeForm(AncillaryDataFormatType *ancillaryDataFormat, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // List view
    void addClicked();
    void editClicked();
    void removeClicked();
    void numberLineChecked(bool checked);
    // -
    void DIDChanged();
    void SDIDChanged();
    void wrappingTypeChanged();
private:
    void updateListAndButtons();
    QHBoxLayout *m_mainHLayout;
    ListView *m_listView;
    QPushButton *m_buttonLineNumber;
    QLineEdit *m_editAncillaryDataFormatId;
    QLineEdit *m_editAncillaryDataFormatName;
    QSpinBox *m_spinDID;
    QSpinBox *m_spinSDID;
    QSpinBox *m_spinWrappingType;
    QCheckBox *m_checkDID;
    QCheckBox *m_checkSDID;
    QCheckBox *m_checkWrappingType;
    AncillaryDataFormatType *m_ancillaryDataFormat;
    Operation m_op;
};


#endif // ANCILLARYDATAFORMATTYPEFORM_H
