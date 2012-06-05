#ifndef TIMEZONEEDITBOX_H
#define TIMEZONEEDITBOX_H

#include <QComboBox>

class TimezoneEditBox : public QComboBox
{
    Q_OBJECT
public:
    explicit TimezoneEditBox(QWidget *parent = 0);
    int getUTCOffset() const;
    void setUTCOffset(int minutes);
    bool isLocal() const;
    void setLocal();

public slots:
    void timezoneSelected(int index);

};

#endif // TIMEZONEEDITBOX_H
