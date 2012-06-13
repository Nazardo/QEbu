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

#ifndef TYPEGROUPEDITBOX_H
#define TYPEGROUPEDITBOX_H

#include <QWidget>
#include <QMap>

class TypeGroup;
class QLineEdit;
class QGroupBox;
class QComboBox;
class QString;

class TypeGroupEditBox : public QWidget
{
    Q_OBJECT
public:
    explicit TypeGroupEditBox(TypeGroup *typeGroup = 0,
                              QWidget *parent = 0);
    TypeGroup *typeGroup();
    void updateExistingTypeGroup(TypeGroup *typeGroup);
    void setLabel(const QString &label);
    void addLinksMap(QMap<QString, QString> *values);
    QLineEdit *editTypeLabel();
    QComboBox *editTypeLink();
    QLineEdit *editTypeDefinition();
private slots:
    void onChange(int index);
    void onChange();
private:
    QGroupBox *m_groupBox;
    QLineEdit *m_editTypeLabel;
    QLineEdit *m_editTypeDefinition;
    QComboBox *m_editTypeLink;
    QList<QMap<QString, QString> *> m_linkMaps;
};

#endif // TYPEGROUPEDITBOX_H
