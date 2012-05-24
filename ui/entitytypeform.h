#ifndef ENTITYTYPEFORM_H
#define ENTITYTYPEFORM_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include "stackablewidget.h"
#include "listview.h"
#include "../model/entitytype.h"

class EntityTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit EntityTypeForm(EntityType *entity, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // List view
    void addClicked();
    void editClicked();
    void removeClicked();
//    void closeClicked();
    // -
    void contactDetailsChecked(bool checked);
    void organisationDetailsChecked(bool checked);
    void roleChecked(bool checked);
    // -
    void roleFormClosed(Operation op, QVariant value);
private:
    enum EditMode { ContactDetails, OrganisationDetails, Roles };
    void updateListAndButtons();

    QHBoxLayout *m_mainHLayout;
    ListView *m_listView;
    QLineEdit *m_editEntityId;
    QPushButton *m_buttonContactDetails;
    QPushButton *m_buttonOrganisationDetails;
    QPushButton *m_buttonRole;
    EntityType *m_entityType;
    Operation m_op;
    EditMode m_currentEditMode;
};

#endif // ENTITYTYPEFORM_H
