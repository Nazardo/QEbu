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

#ifndef ANCILLARYDATAFORMATTYPEFORM_H
#define ANCILLARYDATAFORMATTYPEFORM_H

#include "stackablewidget.h"

class AncillaryDataFormatType;
class QLineEdit;
class QCheckBox;
class QSpinBox;
class QPushButton;
class ListView;

class AncillaryDataFormatTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit AncillaryDataFormatTypeForm(
            AncillaryDataFormatType *ancillaryDataFormat,
            QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // List view
    void addClicked();
    void editClicked();
    void removeClicked();
    void numberLineChecked(bool checked);
    // -
    void DIDChanged();
    void SDIDChanged();
    void wrappingTypeChanged();
private:
    void updateListAndButtons();
    bool eventFilter(QObject *obj, QEvent *event);
    ListView *m_listView;
    QPushButton *m_buttonLineNumber;
    QLineEdit *m_editAncillaryDataFormatId;
    QLineEdit *m_editAncillaryDataFormatName;
    QSpinBox *m_spinDID;
    QSpinBox *m_spinSDID;
    QSpinBox *m_spinWrappingType;
    QCheckBox *m_checkDID;
    QCheckBox *m_checkSDID;
    QCheckBox *m_checkWrappingType;
    AncillaryDataFormatType *m_ancillaryDataFormat;
};


#endif // ANCILLARYDATAFORMATTYPEFORM_H
