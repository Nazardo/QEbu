#ifndef HASTRACKPARTTYPEFORM_H
#define HASTRACKPARTTYPEFORM_H

#include "stackablewidget.h"

class HasTrackPartType;
class QLineEdit;

class HasTrackPartTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit HasTrackPartTypeForm(HasTrackPartType *hasTrackPart,
                                  QEbuMainWindow *mainWindow,
                                  QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
private slots:
    void cancelClicked();
    void applyClicked();
    // -
    void trackPartTitleRemoveClicked();
    void trackPartTitleClicked();
    void trackPartTitleClosed(Operation op, QVariant value);
    void destinationStartRemoveClicked();
    void destinationStartClicked();
    void destinationStartClosed(Operation op, QVariant value);
    void destinationEndRemoveClicked();
    void destinationEndClicked();
    void destinationEndClosed(Operation op, QVariant value);
    void sourceStartRemoveClicked();
    void sourceStartClicked();
    void sourceStartClosed(Operation op, QVariant value);
    void sourceEndRemoveClicked();
    void sourceEndClicked();
    void sourceEndClosed(Operation op, QVariant value);
    void relationRemovedClicked();
    void relationClicked();
    void relationClosed(Operation op, QVariant value);

private:
    bool eventFilter(QObject *obj, QEvent *event);
    QLineEdit *m_editRelation;
    QLineEdit *m_editTrackPartTitle;
    QLineEdit *m_editDestinationStart;
    QLineEdit *m_editDestinationEnd;
    QLineEdit *m_editSourceStart;
    QLineEdit *m_editSourceEnd;
    HasTrackPartType *m_hasTrackPart;
};

#endif // HASTRACKPARTTYPEFORM_H
