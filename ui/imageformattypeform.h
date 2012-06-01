#ifndef IMAGEFORMATTYPE_H
#define IMAGEFORMATTYPE_H

#include "stackablewidget.h"

class ImageFormatType;
class QLineEdit;
class QCheckBox;
class QSpinBox;
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
    void typeGroupFormClosed(Operation op, QVariant value);
    void technicalAttributesFormClosed(Operation op, QVariant value);
private:
    ImageFormatType *m_imageFormat;
    // Edit fields:
    QLineEdit *m_editImageFormatId;
    QLineEdit *m_editImageFormatName;
    QLineEdit *m_editImageFormatDefinition;
    QCheckBox *m_checkRegionDelimX;
    QSpinBox *m_editRegionDelimX;
    QCheckBox *m_checkRegionDelimY;
    QSpinBox *m_editRegionDelimY;
    LengthTypeEditBox *m_editWidth;
    LengthTypeEditBox *m_editHeight;
    QCheckBox *m_checkOrientation;
    QComboBox *m_comboOrientation;
    ListView *m_listView;
    QPushButton *m_buttonTechnicalAttributes;
};

#endif // IMAGEFORMATTYPE_H
