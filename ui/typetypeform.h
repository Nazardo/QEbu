#ifndef TYPETYPEFORM_H
#define TYPETYPEFORM_H

#include "stackablewidget.h"

class TypeType;
class ListView;
class QTextEdit;
class QPushButton;

class TypeTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit TypeTypeForm(TypeType *type,
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
    void typeChecked(bool checked);
    void genreChecked(bool checked);
    void objectTypeChecked(bool checked);
    void targetAudienceChecked(bool checked);
    // -
    void typeFormClosed(Operation op, QVariant value);
    void genreFormClosed(Operation op, QVariant value);
    void objectTypeFormClosed(Operation op, QVariant value);
    void targetAudienceFormClosed(Operation op, QVariant value);
private:
    bool eventFilter(QObject *obj, QEvent *event);
    enum EditMode { Type, Genre, ObjectType, TargetAudience };
    void updateListAndButtons();

    ListView *m_listView;
    QTextEdit *m_textNote;
    QPushButton *m_buttonType;
    QPushButton *m_buttonGenre;
    QPushButton *m_buttonObjectType;
    QPushButton *m_buttonTargetAudience;
    TypeType *m_type;
    EditMode m_currentEditMode;
};

#endif // TYPETYPEFORM_H
