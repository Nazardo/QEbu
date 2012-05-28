#ifndef FORMATGROUPEDITBOX_H
#define FORMATGROUPEDITBOX_H

#include <QWidget>
#include <QLineEdit>

class FormatGroupEditBox : public QWidget
{
    Q_OBJECT
public:
    explicit FormatGroupEditBox(QWidget *parent = 0);
    QLineEdit *formatLabel();
    QLineEdit *formatDefinition();
    QLineEdit *formatLink();
signals:

public slots:

private:
    QLineEdit *m_formatLabel;
    QLineEdit *m_formatDefinition;
    QLineEdit *m_formatLink;
};

#endif // FORMATGROUPEDITBOX_H
