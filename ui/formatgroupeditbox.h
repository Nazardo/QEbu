#ifndef FORMATGROUPEDITBOX_H
#define FORMATGROUPEDITBOX_H

#include <QWidget>

class FormatGroup;
class QLineEdit;
class QGroupBox;

class FormatGroupEditBox : public QWidget
{
    Q_OBJECT
public:
    explicit FormatGroupEditBox(FormatGroup *formatGroup = 0,
                                QWidget *parent = 0);
    FormatGroup *formatGroup();
    void updateExistingFormatGroup(FormatGroup *formatGroup);
    void setLabel(const QString &label);
private:
    QGroupBox *m_groupBox;
    QLineEdit *m_editFormatLabel;
    QLineEdit *m_editFormatDefinition;
    QLineEdit *m_editFormatLink;
};

#endif // FORMATGROUPEDITBOX_H
