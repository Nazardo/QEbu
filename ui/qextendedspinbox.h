#ifndef QEXTENDEDSPINBOX_H
#define QEXTENDEDSPINBOX_H

#include <QAbstractSpinBox>
#include "extendedvalidator.h"
#include <QLineEdit>
#include <QDebug>

class QUnsignedSpinBox : public QAbstractSpinBox
{
    Q_OBJECT

public:
    explicit QUnsignedSpinBox(QWidget *parent = 0, quint64 value = 0, quint64 min = 0, quint64 max = 99)
        : QAbstractSpinBox(parent)
    {
        m_validator = new UnsignedValidator(min, max);
        setRange(min, max);
        setValue(value);
        QObject::connect(lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(onTextChanged()));
        lineEdit()->setValidator(m_validator);
    }

    ~QUnsignedSpinBox() {
    }

    quint64 value()
    {
        return m_value;
    }

    void setValue(quint64 val)
    {
        if (val < minimum() || val > maximum())
            val = value();
        m_value = val;
        lineEdit()->setText(QString::number(m_value, 10));
    }

    quint64 minimum() const
    {
        return m_min;
    }

    quint64 maximum() const
    {
        return m_max;
    }

    void setRange(quint64 min, quint64 max)
    {
        if (min >= max)
            return;
        m_min = min;
        m_max = max;
        if (m_validator)
            m_validator->setRange(min, max);
    }

signals:
    void valueChanged();

private slots:

    void onTextChanged()
    {
        if (lineEdit()->hasAcceptableInput()) {
            m_value = lineEdit()->text().toULongLong();
            emit valueChanged();
        }
    }

private:

    void focusOutEvent(QFocusEvent *event)
    {
        QAbstractSpinBox::focusOutEvent(event);
        lineEdit()->setText(QString::number(m_value, 10));
    }

    StepEnabled stepEnabled() const
    {
        if (m_value > minimum() && m_value < maximum())
            return (StepUpEnabled | StepDownEnabled);
        if (m_value > minimum())
            return StepDownEnabled;
        if (m_value < maximum())
            return StepUpEnabled;
        return StepNone;
    }

    void stepBy(int steps)
    {
        if(steps < 0)
            stepDown();
        else
            stepUp();
    }

    void stepUp()
    {
        if(m_value+1 > m_max)
            return;
        lineEdit()->setText(QString::number(++m_value, 10));
    }

    void stepDown() {
        if(m_value-1 < m_min)
            return;
        lineEdit()->setText(QString::number(--m_value, 10));
    }

    void showEvent(QShowEvent* event)
    {
        QWidget::showEvent(event);
    }

    quint64 m_value;
    quint64 m_max;
    quint64 m_min;
    UnsignedValidator *m_validator;
};

class QSignedSpinBox : public QAbstractSpinBox
{
    Q_OBJECT

public:
    explicit QSignedSpinBox(QWidget *parent = 0, qint64 value = 0, qint64 min = -50, qint64 max = 49)
        : QAbstractSpinBox(parent)
    {
        m_validator = new SignedValidator(min, max);
        setRange(min, max);
        setValue(value);
        QObject::connect(lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(onTextChanged()));
        lineEdit()->setValidator(m_validator);
    }

    ~QSignedSpinBox() {
    }

    qint64 value()
    {
        return m_value;
    }

    void setValue(qint64 val)
    {
        if (val < minimum() || val > maximum())
            val = value();
        m_value = val;
        lineEdit()->setText(QString::number(m_value, 10));
    }

    qint64 minimum() const
    {
        return m_min;
    }

    qint64 maximum() const
    {
        return m_max;
    }

    void setRange(qint64 min, qint64 max)
    {
        if (min >= max)
            return;
        m_min = min;
        m_max = max;
        if (m_validator)
            m_validator->setRange(min, max);
    }

signals:
    void valueChanged();

private slots:

    void onTextChanged()
    {
        if (lineEdit()->hasAcceptableInput()) {
            m_value = lineEdit()->text().toLongLong();
            emit valueChanged();
        }
    }

private:

    void focusOutEvent(QFocusEvent *event)
    {
        QAbstractSpinBox::focusOutEvent(event);
        lineEdit()->setText(QString::number(m_value, 10));
    }

    StepEnabled stepEnabled() const
    {
        if (m_value > minimum() && m_value < maximum())
            return (StepUpEnabled | StepDownEnabled);
        if (m_value > minimum())
            return StepDownEnabled;
        if (m_value < maximum())
            return StepUpEnabled;
        return StepNone;
    }

    void stepBy(int steps)
    {
        if(steps < 0)
            stepDown();
        else
            stepUp();
    }

    void stepUp()
    {
        if(m_value+1 > m_max)
            return;
        lineEdit()->setText(QString::number(++m_value, 10));
    }

    void stepDown() {
        if(m_value-1 < m_min)
            return;
        lineEdit()->setText(QString::number(--m_value, 10));
    }

    void showEvent(QShowEvent* event)
    {
        QWidget::showEvent(event);
    }

    qint64 m_value;
    qint64 m_max;
    qint64 m_min;
    SignedValidator *m_validator;
};


#endif // QEXTENDEDSPINBOX_H
