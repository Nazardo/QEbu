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

#ifndef STATUSGROUPEDITBOX_H
#define STATUSGROUPEDITBOX_H

#include <QWidget>
#include <QMap>

class StatusGroup;
class QLineEdit;
class QComboBox;
class QString;

class StatusGroupEditBox : public QWidget
{
    Q_OBJECT
public:
    explicit StatusGroupEditBox(StatusGroup *statusGroup = 0,
                                QWidget *parent = 0);
    StatusGroup *statusGroup();
    void updateExistingStatusGroup(StatusGroup *statusGroup);
    void addLinksMap(QMap<QString, QString> *values);
    QLineEdit *editStatusLabel();
    QComboBox *editStatusLink();
    QLineEdit *editStatusDefinition();
private slots:
    void onChange(int index);
    void onChange();
private:
    QLineEdit *m_editStatusLabel;
    QLineEdit *m_editStatusDefinition;
    QComboBox *m_editStatusLink;
    QList<QMap<QString, QString> *> m_linkMaps;
};

#endif // STATUSGROUPEDITBOX_H
