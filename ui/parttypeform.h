#ifndef PARTTYPEFORM_H
#define PARTTYPEFORM_H

#include "stackablewidget.h"

class PartType;
class QTextEdit;
class QLineEdit;

class PartTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit PartTypeForm(PartType *part,
                             QEbuMainWindow *mainWindow,
                             QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // -
    void coreDetailsRemoveClicked();
    void coreDetailsClicked();
    void coreDetailsClosed(Operation op, QVariant value);
private:
    bool eventFilter(QObject *obj, QEvent *event);

    QLineEdit *m_editPartId;
    QLineEdit *m_editPartName;
    QLineEdit *m_editCoreDetails;
    PartType *m_part;
};

#endif // PARTTYPEFORM_H
