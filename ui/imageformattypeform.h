#ifndef IMAGEFORMATTYPE_H
#define IMAGEFORMATTYPE_H

#include "stackablewidget.h"

class ImageFormatType;
class QLineEdit;
class QCheckBox;
class QUnsignedSpinBox;
class QComboBox;
class LengthTypeEditBox;
class ListView;
class QPushButton;

class ImageFormatTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit ImageFormatTypeForm(ImageFormatType *imageFormat,
                                 QEbuMainWindow *mainWindow,
                                 QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void applyClicked();
    void cancelClicked();
    // --
    void addClicked();
    void editClicked();
    void removeClicked();
    void regionDelimXChanged();
    void regionDelimYChanged();
    void orientationChanged();
    void technicalAttributesClicked();
    void technicalAttributesRemoveClicked();
    void typeGroupFormClosed(Operation op, QVariant value);
    void technicalAttributesFormClosed(Operation op, QVariant value);
private:
    bool eventFilter(QObject *obj, QEvent *event);
    ImageFormatType *m_imageFormat;
    // Edit fields:
    QLineEdit *m_editImageFormatId;
    QLineEdit *m_editImageFormatName;
    QLineEdit *m_editImageFormatDefinition;
    QCheckBox *m_checkRegionDelimX;
    QUnsignedSpinBox *m_editRegionDelimX;
    QCheckBox *m_checkRegionDelimY;
    QUnsignedSpinBox *m_editRegionDelimY;
    LengthTypeEditBox *m_editWidth;
    LengthTypeEditBox *m_editHeight;
    QCheckBox *m_checkOrientation;
    QComboBox *m_comboOrientation;
    ListView *m_listView;
    QLineEdit *m_editTechnicalAttributes;
    ///@todo: here misses imageEncoding!
    QPushButton *m_buttonTechnicalAttributes;
};

#endif // IMAGEFORMATTYPE_H
