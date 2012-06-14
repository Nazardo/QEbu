/****************************************************************************
** Copyright (C) 2012 by
**  Mauro Levra  (nazardo)     mauro@nazardo.it
**  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it
**  Denis Patti  (dextp3)      denis.patti@studenti.polito.it
**  Giovanni Pessiva           giovanni.pessiva@gmail.com
**  Stefano Ricossa            stefano.ricossa@gmail.com
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
