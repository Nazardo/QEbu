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

#ifndef SIGNINGFORMATTYPEFORM_H
#define SIGNINGFORMATTYPEFORM_H


#include "stackablewidget.h"

class SigningFormatType;
class QLineEdit;
class TypeGroupEditBox;
class FormatGroupEditBox;

class SigningFormatTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit SigningFormatTypeForm(SigningFormatType *signingFormat,
                                   QEbuMainWindow *mainWindow,
                                   QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // -
private:
    bool eventFilter(QObject *, QEvent *);
    QLineEdit *m_editTrackId;
    QLineEdit *m_editTrackName;
    QLineEdit *m_editLanguage;
    TypeGroupEditBox *m_editTypeGroup;
    FormatGroupEditBox *m_editFormatGroup;
    QLineEdit *m_editSigningSourceUri;
    QLineEdit *m_editSigningFormatId;
    QLineEdit *m_editSigningFormatName;
    QLineEdit *m_editSigningFormatDefinition;
    SigningFormatType *m_signingFormat;
};

#endif // SIGNINGFORMATTYPEFORM_H
