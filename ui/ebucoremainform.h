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

#ifndef EBUCOREMAINFORM_H
#define EBUCOREMAINFORM_H

#include "stackablewidget.h"

class EbuCoreMainType;
class QLineEdit;
class QCheckBox;
class QDateEdit;

class EbuCoreMainForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit EbuCoreMainForm(EbuCoreMainType *ebuCoreMain,
                             QEbuMainWindow *mainWindow,
                             QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void metadataProviderRemoveClicked();
    void metadataProviderClicked();
    void metadataProviderClosed(Operation op, QVariant value);
    void coreMetadataRemoveClicked();
    void coreMetadataClicked();
    void coreMetadataClosed(Operation op, QVariant value);
    // -
    void dateLastModifiedChanged();
    void dateLastModifiedToggled(bool checked);
    void documentIdChanged(QString documentId);
    void langChanged(QString lang);
private:
    bool eventFilter(QObject *obj, QEvent *event);

    QLineEdit *m_editSchema;
    QLineEdit *m_editVersion;
    QCheckBox *m_checkDateLastModified;
    QDateEdit  *m_editDateLastModified;
    QLineEdit *m_editDocumentId;
    QLineEdit *m_editLang;
    QLineEdit *m_editCoreMetadata;
    QLineEdit *m_editMetadataProvider;

    EbuCoreMainType *m_ebuCoreMain;

};

#endif // EBUCOREMAINFORM_H
