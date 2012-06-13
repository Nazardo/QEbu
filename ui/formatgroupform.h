#ifndef FORMATGROUPFORM_H
#define FORMATGROUPFORM_H

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

#include "stackablewidget.h"
#include <QMap>

class FormatGroup;
class FormatGroupEditBox;
class QString;

class FormatGroupForm : public StackableWidget
{
Q_OBJECT
public:
    explicit FormatGroupForm(FormatGroup *typeGroup,
                             QEbuMainWindow *mainWindow,
                             QWidget *parent = 0);
    QString toString();
    void setTitle(const QString &title);
    void addLinksMap(QMap<QString, QString> *values);
    void setLabelDoc(const QString &doc);
    void setLinkDoc(const QString &doc);
    void setGeneralDoc(const QString &doc);
    void setDefinitionDoc(const QString &doc);
private slots:
    void cancelClicked();
    void applyClicked();
private:
    FormatGroupEditBox *m_editFormatGroup;
    QString m_title;
    QString m_definitionDoc;
    QString m_labelDoc;
    QString m_linkDoc;
    QString m_generalDoc;
    FormatGroup *m_formatGroup;
};

#endif // FORMATGROUPFORM_H
