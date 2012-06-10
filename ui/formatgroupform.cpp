#include "formatgroupform.h"
#include "../model/formatgroup.h"
#include "formatgroupeditbox.h"
#include "qvarptr.h"
#include <QLayout>
#include <QString>

FormatGroupForm::FormatGroupForm(FormatGroup *formatGroup,
                                 QEbuMainWindow *mainWindow,
                                 QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (formatGroup) ? Edit : Add;
    if (!formatGroup)
        m_formatGroup = new FormatGroup;
    else
        m_formatGroup = formatGroup;
    QVBoxLayout *vl = new QVBoxLayout;
    m_title = QString(tr("Format Group"));
    m_editFormatGroup = new FormatGroupEditBox(m_formatGroup);
    m_editFormatGroup->setLabel(m_title);
    vl->addWidget(m_editFormatGroup);
    this->setLayout(vl);  
}

void FormatGroupForm::addLinksMap(QMap<QString, QString> *values) {
    m_editFormatGroup->addLinksMap(values); //Autocompletion values
}

QString FormatGroupForm::toString()
{
    return m_title;
}

void FormatGroupForm::setTitle(const QString &title)
{
    m_title = title;
}

void FormatGroupForm::applyClicked()
{
    m_editFormatGroup->updateExistingFormatGroup(m_formatGroup);
    emit closed(m_op, QVarPtr<FormatGroup>::asQVariant(m_formatGroup));
}

void FormatGroupForm::cancelClicked()
{
    emit closed(m_op, QVarPtr<FormatGroup>::asQVariant(0));
}
