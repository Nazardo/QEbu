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
    QPushButton *m_buttonTechnicalAttributes;
};

#endif // IMAGEFORMATTYPE_H
