#ifndef LOCATIONTYPEFORM_H
#define LOCATIONTYPEFORM_H

#include "stackablewidget.h"
#include "../model/coremetadatatype.h"
#include "typegroupeditbox.h"
#include <QTextEdit>
#include <QLineEdit>

class LocationTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit LocationTypeForm(LocationType *location, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
private slots:
    void cancelClicked();
    void applyClicked();
    // -
    void coordinatesClicked();
    void coordinatesRemoveClicked();
    void coordinatesClosed(Operation op, QVariant value);
private:
    QVBoxLayout *m_mainVLayout;
    TypeGroupEditBox *m_editTypeGroup;
    QLineEdit *m_editLocationId;
    QTextEdit *m_textNote;
    QLineEdit *m_editName;
    QLineEdit *m_editCoordinates;
    QLineEdit *m_editCode;
    LocationType *m_location;
    Operation m_op;
};

#endif // LOCATIONTYPEFORM_H
