#ifndef FORMATGROUPEDITBOX_H
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
private slots:
    void onChange(int index);
private:
    QGroupBox *m_groupBox;
    QLineEdit *m_editFormatLabel;
    QLineEdit *m_editFormatDefinition;
    QComboBox *m_editFormatLink;
    QList<QMap<QString, QString> *> m_linkMaps;
};

#endif // FORMATGROUPEDITBOX_H
