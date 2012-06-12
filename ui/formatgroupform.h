#ifndef FORMATGROUPFORM_H
#define FORMATGROUPFORM_H

#include "stackablewidget.h"
#include <QMap>

class FormatGroup;
class FormatGroupEditBox;
class QString;

class FormatGroupForm : public StackableWidget
{
Q_OBJECT
public:
    explicit FormatGroupForm(FormatGroup *typeGroup,
                             QEbuMainWindow *mainWindow,
                             QWidget *parent = 0);
    QString toString();
    void setTitle(const QString &title);
    void addLinksMap(QMap<QString, QString> *values);
    void setLabelDoc(const QString &doc);
    void setLinkDoc(const QString &doc);
    void setGeneralDoc(const QString &doc);
    void setDefinitionDoc(const QString &doc);
private slots:
    void cancelClicked();
    void applyClicked();
private:
    FormatGroupEditBox *m_editFormatGroup;
    QString m_title;
    QString m_definitionDoc;
    QString m_labelDoc;
    QString m_linkDoc;
    QString m_generalDoc;
    FormatGroup *m_formatGroup;
};

#endif // FORMATGROUPFORM_H
