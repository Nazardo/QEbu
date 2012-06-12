#ifndef DATAFORMATTYPEFORM_H
#define DATAFORMATTYPEFORM_H

#include "stackablewidget.h"

class DataFormatType;
class QLineEdit;
class QPushButton;
class ListView;

class DataFormatTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit DataFormatTypeForm(DataFormatType *dataFormat,
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
    void captioningFormatChecked(bool checked);
    void ancillaryDataFormatChecked(bool checked);
    void technicalAttributesChecked(bool checked);
    // -
    void captioningFormatFormClosed(Operation op, QVariant value);
    void ancillaryDataFormatFormClosed(Operation op, QVariant value);
    void technicalAttributesFormClosed(Operation op, QVariant value);
private:
    enum EditMode {
        CaptioningFormat,
        AncillaryDataFormat,
        TechnicalAttributesMode
    };
    void updateListAndButtons();
    bool eventFilter(QObject *, QEvent *);
    QLineEdit *m_editDataFormatId;
    QLineEdit *m_editDataFormatName;
    QLineEdit *m_editDataFormatDefinition;
    QPushButton *m_buttonCaptioningFormat;
    QPushButton *m_buttonAncillaryDataFormat;
    QPushButton *m_buttonTechnicalAttributes;
    ListView *m_listView;
    DataFormatType *m_dataFormat;
    EditMode m_currentEditMode;
};

#endif // DATAFORMATTYPEFORM_H
