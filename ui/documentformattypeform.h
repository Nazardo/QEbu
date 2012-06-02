#ifndef DOCUMENTFORMATTYPEFORM_H
#define DOCUMENTFORMATTYPEFORM_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include "stackablewidget.h"
#include "listview.h"
#include "../model/ebucoremaintype.h"
#include "typegroupeditbox.h"
#include "formatgroupeditbox.h"
#include "lengthtypeeditbox.h"
#include <QSpinBox>
#include <QCheckBox>



class DocumentFormatTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit DocumentFormatTypeForm(DocumentFormatType *documentFormat, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // -
    void wordCountChanged();
    void regionDelimXChanged();
    void regionDelimYChanged();
    void technicalAttributesRemoveClicked();
    void technicalAttributesClicked();
    void technicalAttributesFormClosed(Operation op, QVariant value);
private:
    TypeGroupEditBox *m_editTypeGroup;
    FormatGroupEditBox *m_formatTypeGroup;
    QHBoxLayout *m_mainHLayout;
    QLineEdit *m_editDocumentFormatId;
    QLineEdit *m_editDocumentFormatDefinition;
    QLineEdit *m_editDocumentFormatName;
    QLineEdit *m_editTechnicalAttributes;
    QSpinBox *m_spinWordCount;
    QCheckBox *m_checkWordCount;
    QSpinBox *m_spinRegionDelimX;
    QCheckBox *m_checkRegionDelimX;
    QSpinBox *m_spinRegionDelimY;
    QCheckBox *m_checkRegionDelimY;
    LengthType *m_lengthWidth;
    LengthType *m_lengthHeight;
    LengthTypeEditBox *m_editWidth;
    LengthTypeEditBox *m_editHeight;
    TechnicalAttributes *m_technicalAttributes;
    QPushButton *m_buttonTechnicalAttributes;
    DocumentFormatType *m_documentFormat;
    Operation m_op;
};

#endif // DOCUMENTFORMATTYPEFORM_H
