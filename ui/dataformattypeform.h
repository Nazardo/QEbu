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

#ifndef DATAFORMATTYPEFORM_H
#define DATAFORMATTYPEFORM_H

#include "stackablewidget.h"

class DataFormatType;
class QLineEdit;
class QPushButton;
class ListView;

class DataFormatTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit DataFormatTypeForm(DataFormatType *dataFormat,
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
    void captioningFormatChecked(bool checked);
    void ancillaryDataFormatChecked(bool checked);
    void technicalAttributesChecked(bool checked);
    // -
    void captioningFormatFormClosed(Operation op, QVariant value);
    void ancillaryDataFormatFormClosed(Operation op, QVariant value);
    void technicalAttributesFormClosed(Operation op, QVariant value);
private:
    enum EditMode {
        CaptioningFormat,
        AncillaryDataFormat,
        TechnicalAttributesMode
    };
    void updateListAndButtons();
    bool eventFilter(QObject *, QEvent *);
    QLineEdit *m_editDataFormatId;
    QLineEdit *m_editDataFormatName;
    QLineEdit *m_editDataFormatDefinition;
    QPushButton *m_buttonCaptioningFormat;
    QPushButton *m_buttonAncillaryDataFormat;
    QPushButton *m_buttonTechnicalAttributes;
    ListView *m_listView;
    DataFormatType *m_dataFormat;
    EditMode m_currentEditMode;
};

#endif // DATAFORMATTYPEFORM_H
