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
    QVBoxLayout *vl = new QVBoxLayout;
    m_editFormatGroup = new FormatGroupEditBox(formatGroup);
    vl->addWidget(m_editFormatGroup);
    this->setLayout(vl);
    m_title = QString(tr("Format Group"));
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
    emit closed(m_op, QVarPtr<FormatGroup>::asQVariant(m_editFormatGroup->formatGroup()));
}

void FormatGroupForm::cancelClicked()
{
    emit closed(m_op, QVarPtr<FormatGroup>::asQVariant(0));
}
