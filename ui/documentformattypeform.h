#ifndef DOCUMENTFORMATTYPEFORM_H
#define DOCUMENTFORMATTYPEFORM_H

#include "stackablewidget.h"

class DocumentFormatType;
class TypeGroupEditBox;
class FormatGroupEditBox;
class QLineEdit;
class QSpinBox;
class QCheckBox;
class LengthType;
class LengthTypeEditBox;
class QPushButton;

class DocumentFormatTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit DocumentFormatTypeForm(DocumentFormatType *documentFormat,
                                    QEbuMainWindow *mainWindow,
                                    QWidget *parent = 0);
    QString toString();
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
    DocumentFormatType *m_documentFormat;
};

#endif // DOCUMENTFORMATTYPEFORM_H
