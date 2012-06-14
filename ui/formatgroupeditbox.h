#ifndef FORMATGROUPEDITBOX_H
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

#define FORMATGROUPEDITBOX_H

#include <QWidget>
#include <QList>
#include <QMap>

class FormatGroup;
class QLineEdit;
class QGroupBox;
class QComboBox;
class QString;

class FormatGroupEditBox : public QWidget
{
    Q_OBJECT
public:
    explicit FormatGroupEditBox(FormatGroup *formatGroup = 0,
                                QWidget *parent = 0);
    FormatGroup *formatGroup();
    void updateExistingFormatGroup(FormatGroup *formatGroup);
    void setLabel(const QString &label);
    void addLinksMap(QMap<QString, QString> *values);
    QLineEdit *editFormatLabel();
    QComboBox *editFormatLink();
    QLineEdit *editFormatDefinition();

private slots:
    void onChange(int index);
    void onChange();
private:
    QGroupBox *m_groupBox;
    QLineEdit *m_editFormatLabel;
    QLineEdit *m_editFormatDefinition;
    QComboBox *m_editFormatLink;
    QList<QMap<QString, QString> *> m_linkMaps;
};

#endif // FORMATGROUPEDITBOX_H
