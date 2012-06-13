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

#ifndef TYPEGROUPFORM_H
#define TYPEGROUPFORM_H

#include "stackablewidget.h"
#include <QMap>

class TypeGroup;
class TypeGroupEditBox;
class QString;

class TypeGroupForm : public StackableWidget
{
Q_OBJECT
public:
    explicit TypeGroupForm(TypeGroup *typeGroup,
                           QEbuMainWindow *mainWindow,
                           QWidget *parent = 0);
    QString toString();
    void setTitle(const QString &title);
    void setDefinitionDoc(const QString &doc);
    void setLabelDoc(const QString &doc);
    void setLinkDoc(const QString &doc);
    void setGeneralDoc(const QString &doc);
    void addLinksMap(QMap<QString,QString> *values);
private slots:
    void cancelClicked();
    void applyClicked();
private:
    bool eventFilter(QObject *, QEvent *);
    TypeGroupEditBox *m_editTypeGroup;
    QString m_title;
    QString m_definitionDoc;
    QString m_labelDoc;
    QString m_linkDoc;
    QString m_generalDoc;
    TypeGroup *m_typeGroup;
};

#endif // TYPEGROUPFORM_H
