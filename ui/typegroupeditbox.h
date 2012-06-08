#ifndef TYPEGROUPEDITBOX_H
#define TYPEGROUPEDITBOX_H

#include <QWidget>

class TypeGroup;
class QLineEdit;
class QGroupBox;

class TypeGroupEditBox : public QWidget
{
    Q_OBJECT
public:
    explicit TypeGroupEditBox(TypeGroup *typeGroup = 0,
                              QWidget *parent = 0);
    TypeGroup *typeGroup();
    void updateExistingTypeGroup(TypeGroup *typeGroup);
    void setLabel(const QString &label);
private:
    QGroupBox *m_groupBox;
    QLineEdit *m_editTypeLabel;
    QLineEdit *m_editTypeDefinition;
    QLineEdit *m_editTypeLink;
};

#endif // TYPEGROUPEDITBOX_H
