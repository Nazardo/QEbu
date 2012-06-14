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

#ifndef DOCUMENTFORMATTYPEFORM_H
#define DOCUMENTFORMATTYPEFORM_H

#include "stackablewidget.h"

class DocumentFormatType;
class TypeGroupEditBox;
class FormatGroupEditBox;
class QLineEdit;
class QSpinBox;
class QUnsignedSpinBox;
class QCheckBox;
class LengthType;
class LengthTypeEditBox;
class QPushButton;

class DocumentFormatTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit DocumentFormatTypeForm(DocumentFormatType *documentFormat,
                                    QEbuMainWindow *mainWindow,
                                    QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // -
    void wordCountChanged();
    void regionDelimXChanged();
    void regionDelimYChanged();
    void technicalAttributesRemoveClicked();
    void technicalAttributesClicked();
    void technicalAttributesFormClosed(Operation op, QVariant value);
private:
    bool eventFilter(QObject *, QEvent *);
    TypeGroupEditBox *m_editTypeGroup;
    FormatGroupEditBox *m_formatTypeGroup;
    QLineEdit *m_editDocumentFormatId;
    QLineEdit *m_editDocumentFormatDefinition;
    QLineEdit *m_editDocumentFormatName;
    QLineEdit *m_editTechnicalAttributes;
    QSpinBox *m_spinWordCount;
    QCheckBox *m_checkWordCount;
    QUnsignedSpinBox *m_spinRegionDelimX;
    QCheckBox *m_checkRegionDelimX;
    QUnsignedSpinBox *m_spinRegionDelimY;
    QCheckBox *m_checkRegionDelimY;
    LengthTypeEditBox *m_editWidth;
    LengthTypeEditBox *m_editHeight;
    DocumentFormatType *m_documentFormat;
};

#endif // DOCUMENTFORMATTYPEFORM_H
