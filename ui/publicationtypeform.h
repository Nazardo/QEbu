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

#ifndef PUBLICATIONTYPEFORM_H
#define PUBLICATIONTYPEFORM_H

#include "stackablewidget.h"

class PublicationType;
class QDateEdit;
class QTimeEdit;
class QComboBox;
class QLineEdit;
class QCheckBox;

class PublicationTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit PublicationTypeForm(PublicationType *publication,
                                 QEbuMainWindow *mainWindow,
                                 QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // -
    void publicationTimeChanged();
    void publicationDateChanged();
    void publicationChannelChanged();
private:
    void updateListAndButtons();
    bool eventFilter(QObject *obj, QEvent *event);

    QDateEdit *m_editPublicationDate;
    QTimeEdit *m_editPublicationTime;
    QCheckBox *m_checkPublicationDate;
    QCheckBox *m_checkPublicationTime;
    QCheckBox *m_checkPublicationChannel;
    QComboBox *m_editPublicationChannel;
    QLineEdit *m_editPublicationChannelString;
    PublicationType *m_publication;
};

#endif // PUBLICATIONTYPEFORM_H
