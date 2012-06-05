#ifndef FORMATTYPEFORM_H
#define FORMATTYPEFORM_H

#include "stackablewidget.h"

class FormatType;
class QLineEdit;
class QPushButton;
class ListView;
class TypeGroupEditBox;
class DetailsType;
class QTabWidget;
class QSpinBox;
class QCheckBox;
class ElementTypeEditBox;
class LengthTypeEditBox;

class FormatTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit FormatTypeForm(FormatType *format,
                             QEbuMainWindow *mainWindow,
                             QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // -
    void documentFormatRemoveClicked();
    void documentFormatClicked();
    void documentFormatClosed(Operation op, QVariant value);
    // -
    void locatorRemoveClicked();
    void locatorClicked();
    void locatorClosed(Operation op, QVariant value);
    // -
    void dateCreatedRemoveClicked();
    void dateCreatedClicked();
    void dateCreatedClosed(Operation op, QVariant value);
    // -
    void dateModifiedRemoveClicked();
    void dateModifiedClicked();
    void dateModifiedClosed(Operation op, QVariant value);
    // -
    void technicalAttributesRemoveClicked();
    void technicalAttributesClicked();
    void technicalAttributesClosed(Operation op, QVariant value);
    // -
    void startRemoveClicked();
    void startClicked();
    void startClosed(Operation op, QVariant value);
    // -
    void endRemoveClicked();
    void endClicked();
    void endClosed(Operation op, QVariant value);
    // -
    void durationRemoveClicked();
    void durationClicked();
    void durationClosed(Operation op, QVariant value);
    // -
    void mediumFormChecked(bool checked);
    void mimeTypeFormChecked(bool checked);
    void containerFormatFormChecked(bool checked);
    void signingFormatFormChecked(bool checked);
    void imageFormatFormChecked(bool checked);
    void videoFormatFormChecked(bool checked);
    void audioFormatFormChecked(bool checked);
    void dataFormatFormChecked(bool checked);
    // -
    void mediumFormClosed(Operation op, QVariant value);
    void mimeTypeFormClosed(Operation op, QVariant value);
    void containerFormatFormClosed(Operation op, QVariant value);
    void signingFormatFormClosed(Operation op, QVariant value);
    void imageFormatFormClosed(Operation op, QVariant value);
    void videoFormatFormClosed(Operation op, QVariant value);
    void audioFormatFormClosed(Operation op, QVariant value);
    void dataFormatFormClosed(Operation op, QVariant value);
    // -
    void fileSizeChanged();
    void regionDelimXChanged();
    void regionDelimYChanged();
    // List view
    void addClicked();
    void editClicked();
    void removeClicked();
    // -
private:
    enum EditMode { Medium, MimeType, ContainerFormat, SigningFormat,
                    ImageFormat, VideoFormat, AudioFormat, DataFormat};
    void updateListAndButtons();

    ListView *m_listView;
    QTabWidget *m_tabFormat;
    FormatType *m_format;
    QLineEdit *m_editFormatId;
    QLineEdit *m_editFormatName;
    QLineEdit *m_editFormatDefinition;
    QLineEdit *m_editFileName;
    QSpinBox *m_spinFileSize;
    QCheckBox *m_checkFileSize;
    QSpinBox *m_spinRegionDelimX;
    QSpinBox *m_spinRegionDelimY;
    QCheckBox *m_checkRegionDelimX;
    QCheckBox *m_checkRegionDelimY;
    QLineEdit *m_editDocumentFormat;
    QLineEdit *m_editLocator;
    QLineEdit *m_editDateCreated;
    QLineEdit *m_editDateModified;
    QLineEdit *m_editTechnicalAttributes;
    QLineEdit *m_editStart;
    QLineEdit *m_editEnd;
    QLineEdit *m_editDuration;
    ElementTypeEditBox *m_editElementFormat;
    LengthTypeEditBox *m_editLengthWidth;
    LengthTypeEditBox *m_editLengthHeight;
    QPushButton *m_buttonMimeType;
    QPushButton *m_buttonMedium;
    QPushButton *m_buttonContainerFormat;
    QPushButton *m_buttonSigningFormat;
    QPushButton *m_buttonImageFormat;
    QPushButton *m_buttonVideoFormat;
    QPushButton *m_buttonAudioFormat;
    QPushButton *m_buttonDataFormat;
    EditMode m_currentEditMode;
};

#endif // FORMATTYPEFORM_H
