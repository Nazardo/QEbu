#ifndef TYPEGROUPEDITBOX_H
#define TYPEGROUPEDITBOX_H

#include <QWidget>
#include <QLineEdit>

class TypeGroupEditBox : public QWidget
{
    Q_OBJECT
public:
    explicit TypeGroupEditBox(QWidget *parent = 0);
    QLineEdit *typeLabel();
    QLineEdit *typeDefinition();
    QLineEdit *typeLink();
signals:
    
public slots:
    
private:
    QLineEdit *m_typeLabel;
    QLineEdit *m_typeDefinition;
    QLineEdit *m_typeLink;
};

#endif // TYPEGROUPEDITBOX_H
