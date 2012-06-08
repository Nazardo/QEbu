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
private slots:
    void onChange(int index);
private:
    QGroupBox *m_groupBox;
    QLineEdit *m_editTypeLabel;
    QLineEdit *m_editTypeDefinition;
    QComboBox *m_editTypeLink;
    QList<QMap<QString, QString> *> m_linkMaps;
};

#endif // TYPEGROUPEDITBOX_H
