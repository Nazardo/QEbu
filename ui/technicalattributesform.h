#ifndef TECHNICALATTRIBUTESFORM_H
#define TECHNICALATTRIBUTESFORM_H

#include "stackablewidget.h"

class TechnicalAttributes;
class QPushButton;
class ListView;

class TechnicalAttributesForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit TechnicalAttributesForm(TechnicalAttributes *technicalAttributes,
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
    void stringFormChecked(bool checked);
    void byteFormChecked(bool checked);
    void shortFormChecked(bool checked);
    void integerFormChecked(bool checked);
    void longFormChecked(bool checked);
    void unsignedByteFormChecked(bool checked);
    void unsignedShortFormChecked(bool checked);
    void unsignedIntegerFormChecked(bool checked);
    void unsignedLongFormChecked(bool checked);
    void booleanFormChecked(bool checked);
    void floatFormChecked(bool checked);
    void rationalFormChecked(bool checked);
    void uriFormChecked(bool checked);
    // -
    void stringFormClosed(Operation op, QVariant value);
    void byteFormClosed(Operation op, QVariant value);
    void shortFormClosed(Operation op, QVariant value);
    void integerFormClosed(Operation op, QVariant value);
    void longFormClosed(Operation op, QVariant value);
    void unsignedByteFormClosed(Operation op, QVariant value);
    void unsignedShortFormClosed(Operation op, QVariant value);
    void unsignedIntegerFormClosed(Operation op, QVariant value);
    void unsignedLongFormClosed(Operation op, QVariant value);
    void booleanFormClosed(Operation op, QVariant value);
    void floatFormClosed(Operation op, QVariant value);
    void rationalFormClosed(Operation op, QVariant value);
    void uriFormClosed(Operation op, QVariant value);
private:
    enum EditMode { StringMode, Byte, Short, Integer, Long, UnsignedByte, UnsignedShort, UnsignedInteger, UnsignedLong, BooleanMode, FloatMode, Rational, Uri };
    void updateListAndButtons();

    ListView *m_listView;
    QPushButton *m_buttonString;
    QPushButton *m_buttonByte;
    QPushButton *m_buttonShort;
    QPushButton *m_buttonInteger;
    QPushButton *m_buttonLong;
    QPushButton *m_buttonUnsignedByte;
    QPushButton *m_buttonUnsignedShort;
    QPushButton *m_buttonUnsignedInteger;
    QPushButton *m_buttonUnsignedLong;
    QPushButton *m_buttonBoolean;
    QPushButton *m_buttonFloat;
    QPushButton *m_buttonRational;
    QPushButton *m_buttonUri;
    TechnicalAttributes *m_technicalAttributes;
    EditMode m_currentEditMode;
};

#endif // TECHNICALATTRIBUTESFORM_H
