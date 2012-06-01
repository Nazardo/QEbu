#ifndef ENTITYTYPEFORM_H
#define ENTITYTYPEFORM_H

#include "stackablewidget.h"

class EntityType;
class ListView;
class QPushButton;
class QLineEdit;

class EntityTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit EntityTypeForm(EntityType *entity,
                            QEbuMainWindow *mainWindow,
                            QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // List view
    void addClicked();
    void editClicked();
    void removeClicked();
    // -
    void contactDetailsChecked(bool checked);
    void organisationDetailsChecked(bool checked);
    void roleChecked(bool checked);
    // -
    void contactDetailsFormClosed(Operation op, QVariant value);
    void organisationDetailsFormClosed(Operation op, QVariant value);
    void roleFormClosed(Operation op, QVariant value);
private:
    enum EditMode {
        ContactDetails,
        OrganisationDetails,
        Roles
    };
    void updateListAndButtons();

    ListView *m_listView;
    QLineEdit *m_editEntityId;
    QPushButton *m_buttonContactDetails;
    QPushButton *m_buttonOrganisationDetails;
    QPushButton *m_buttonRole;
    EntityType *m_entity;
    EditMode m_currentEditMode;
};

#endif // ENTITYTYPEFORM_H
