#ifndef VIDEOFORMATTYPEFORM_H
#define VIDEOFORMATTYPEFORM_H

#include "stackablewidget.h"

class VideoFormatType;
class QLineEdit;
class QPushButton;
class QCheckBox;
class QUnsignedSpinBox;
class ListView;
class LengthTypeEditBox;

class VideoFormatTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit VideoFormatTypeForm(VideoFormatType *dataFormat,
                                 QEbuMainWindow *mainWindow,
                                 QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // -
    void regionDelimXChanged();
    void regionDelimYChanged();
    // List view
    void addClicked();
    void editClicked();
    void removeClicked();
    // -
    void aspectRatioChecked(bool checked);
    void videoEncodingChecked(bool checked);
    void videoTrackTypeChecked(bool checked);
    void technicalAttributesChecked(bool checked);
    // -
    void aspectRatioFormClosed(Operation op, QVariant value);
    void videoEncodingFormClosed(Operation op, QVariant value);
    void videoTrackFormClosed(Operation op, QVariant value);
    void technicalAttributesFormClosed(Operation op, QVariant value);
private:
    bool eventFilter(QObject *obj, QEvent *event);
    enum EditMode { AspectRatio, VideoEncoding, VideoTrack, TechnicalAttributesMode };
    void updateListAndButtons();

    QLineEdit *m_editVideoFormatId;
    QLineEdit *m_editVideoFormatName;
    QLineEdit *m_editVideoFormatDefinition;
    QUnsignedSpinBox *m_spinRegionDelimX;
    QUnsignedSpinBox *m_spinRegionDelimY;
    QCheckBox *m_checkRegionDelimX;
    QCheckBox *m_checkRegionDelimY;
    LengthTypeEditBox *m_editWidth;
    LengthTypeEditBox *m_editHeight;
    QPushButton *m_buttonAspectRatio;
    QPushButton *m_buttonVideoEncoding;
    QPushButton *m_buttonVideoTrack;
    QPushButton *m_buttonTechnicalAttributes;
    ListView *m_listView;
    VideoFormatType *m_videoFormat;
    EditMode m_currentEditMode;
};

#endif // VIDEOFORMATTYPEFORM_H
