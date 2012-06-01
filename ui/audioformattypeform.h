#ifndef AUDIOFORMATTYPEFORM_H
#define AUDIOFORMATTYPEFORM_H

#include "stackablewidget.h"

class AudioFormatType;
class ListView;
class QLineEdit;
class QPushButton;

class AudioFormatTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit AudioFormatTypeForm(AudioFormatType *audioFormat,
                                 QEbuMainWindow *mainWindow,
                                 QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // List view
    void addClicked();
    void editClicked();
    void removeClicked();
    // -
    void audioEncodingChecked(bool checked);
    void audioTrackConfigurationChecked(bool checked);
    void audioTrackChecked(bool checked);
    void TechnicalAttributesChecked(bool checked);
    // -
    void audioEncodingFormClosed(Operation op, QVariant value);
    void audioTrackConfigurationFormClosed(Operation op, QVariant value);
    void audioTrackFormClosed(Operation op, QVariant value);
    void TechnicalAttributesFormClosed(Operation op, QVariant value);
private:
    enum EditMode { AudioEncoding, AudioTrackConfiguration, AudioTrack, TechnicalAttributesMode };
    void updateListAndButtons();

    ListView *m_listView;
    QLineEdit *m_editAudioFormatId;
    QLineEdit *m_editAudioFormatDefinition;
    QLineEdit *m_editAudioFormatName;
    QPushButton *m_buttonAudioEncoding;
    QPushButton *m_buttonAudioTrackConfiguration;
    QPushButton *m_buttonAudioTrack;
    QPushButton *m_buttonTechnicalAttributes;
    AudioFormatType *m_audioFormat;
    EditMode m_currentEditMode;
};

#endif // AUDIOFORMATTYPEFORM_H
