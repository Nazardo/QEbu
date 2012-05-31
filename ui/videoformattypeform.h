#ifndef VIDEOFORMATTYPEFORM_H
#define VIDEOFORMATTYPEFORM_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include "listview.h"
#include "stackablewidget.h"

class VideoFormatTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit VideoFormatTypeForm(VideoFormatType *dataFormat, QEbuMainWindow *mainWindow, QWidget *parent = 0);
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
    void widthChecked(bool checked);
    void heightChecked(bool checked);
    void videoEncodingChecked(bool checked);
    void videoTrackTypeChecked(bool checked);
    void technicalAttributesChecked(bool checked);
    // -
    void aspectRatioFormClosed(Operation op, QVariant value);
    void widthFormClosed(Operation op, QVariant value);
    void heightFormClosed(Operation op, QVariant value);
    void videoEncodingFormClosed(Operation op, QVariant value);
    void videoTrackFormClosed(Operation op, QVariant value);
    void technicalAttributesFormClosed(Operation op, QVariant value);
private:
    enum EditMode { AspectRatio, Width, Height,
                    VideoEncoding, VideoTrack, TechnicalAttributesMode };
    void updateListAndButtons();

    QHBoxLayout *m_mainHLayout;
    QLineEdit *m_editVideoFormatId;
    QLineEdit *m_editVideoFormatName;
    QLineEdit *m_editVideoFormatDefinition;
    QSpinBox *m_spinRegionDelimX;
    QSpinBox *m_spinRegionDelimY;
    QCheckBox *m_checkRegionDelimX;
    QCheckBox *m_checkRegionDelimY;
    QPushButton *m_buttonWidth;
    QPushButton *m_buttonHeight;
    QPushButton *m_buttonAspectRatio;
    QPushButton *m_buttonVideoEncoding;
    QPushButton *m_buttonVideoTrack;
    QPushButton *m_buttonTechnicalAttributes;
    ListView *m_listView;
    Operation m_op;
    VideoFormatType *m_videoFormat;
    EditMode m_currentEditMode;
};

#endif // VIDEOFORMATTYPEFORM_H
