#ifndef ELEMENTTYPEEDITBOX_H
#define ELEMENTTYPEEDITBOX_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>

class ElementTypeEditBox : public QWidget
{
    Q_OBJECT
public:
    explicit ElementTypeEditBox(QWidget *parent = 0);
    QLineEdit *editValue();
    QLineEdit *editLang();
    void setLabel(const QString &label);

private:
    QLineEdit *m_editValue;
    QLineEdit *m_editLang;
    QLabel *m_label;
};

#endif // ELEMENTTYPEEDITBOX_H
