#ifndef FORMATGROUPEDITBOX_H
#define FORMATGROUPEDITBOX_H

#include <QWidget>
#include <QLineEdit>
#include "../model/formatgroup.h"

class FormatGroupEditBox : public QWidget
{
    Q_OBJECT
public:
    explicit FormatGroupEditBox(FormatGroup *formatGroup = 0, QWidget *parent = 0);
    FormatGroup *formatGroup();
    void updateExistingFormatGroup(FormatGroup *formatGroup);
private:
    QLineEdit *m_editFormatLabel;
    QLineEdit *m_editFormatDefinition;
    QLineEdit *m_editFormatLink;
};

#endif // FORMATGROUPEDITBOX_H
