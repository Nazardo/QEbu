#ifndef RATINGTYPEFORM_H
#define RATINGTYPEFORM_H

#include "stackablewidget.h"
#include "../model/ebucoremaintype.h"
#include "typegroupeditbox.h"
#include "elementtypeeditbox.h"
#include "formatgroupeditbox.h"
#include <QTextEdit>

class RatingTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit RatingTypeForm(RatingType *rating, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // -
    void ratingProviderRemoveClicked();
    void ratingProviderClicked();
    void ratingProviderClosed(Operation op, QVariant value);
private:
    TypeGroupEditBox *m_editTypeGroup;
    FormatGroupEditBox *m_editFormatGroup;
    QLineEdit *m_editRatingValue;
    QLineEdit *m_editRatingScaleMaxValue;
    QLineEdit *m_editRatingScaleMinValue;
    QLineEdit *m_editRatingProvider;
    RatingType *m_rating;
    Operation m_op;
};

#endif // RATINGTYPEFORM_H
