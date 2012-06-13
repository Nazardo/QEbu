/****************************************************************************
** Copyright (C) 2012 by
**  Mauro Levra  (nazardo)     mauro@nazardo.it
**  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it
**  Denis Patti  (dextp3)      denis.patti@studenti.polito.it
**  Giovanni Pessiva           giovanni.pessiva@gmail.com
**  Stefano Ricossa            stefano.ricossa@studenti.polito.it
**
** This file is part of QEbu.
** QEbu is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, in the version 3 of the License.
**
** QEbu is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with QEbu.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

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
    bool eventFilter(QObject *obj, QEvent *event);
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
