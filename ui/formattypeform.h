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
class QSignedSpinBox;
class QUnsignedSpinBox;
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
    bool eventFilter(QObject *, QEvent *);
    ListView *m_listView;
    QTabWidget *m_tabFormat;
    FormatType *m_format;
    QLineEdit *m_editFormatId;
    QLineEdit *m_editFormatName;
    QLineEdit *m_editFormatDefinition;
    QLineEdit *m_editFileName;
    QSignedSpinBox *m_spinFileSize;
    QCheckBox *m_checkFileSize;
    QUnsignedSpinBox *m_spinRegionDelimX;
    QUnsignedSpinBox *m_spinRegionDelimY;
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
