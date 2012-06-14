/****************************************************************************
** Copyright (C) 2012 by
**  Mauro Levra  (nazardo)     mauro@nazardo.it
**  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it
**  Denis Patti  (dextp3)      denis.patti@studenti.polito.it
**  Giovanni Pessiva           giovanni.pessiva@gmail.com
**  Stefano Ricossa            stefano.ricossa@gmail.com
**
** This file is part of QEbu.
** QEbu is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, in the version 3 of the License.
**
** QEbu is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with QEbu.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#ifndef EXTENDEDVALIDATOR_H
#define EXTENDEDVALIDATOR_H

#include <QValidator>

class UnsignedValidator : public QValidator
{
    Q_OBJECT

public:
    UnsignedValidator(QObject *parent = 0) : QValidator(parent) {
        m_bottom = 0;
        m_top = 0;
    }

    UnsignedValidator(quint64 minimum, quint64 maximum, QObject * parent = 0)
        : QValidator(parent)
    {
        m_bottom = minimum;
        m_top = maximum;
    }

    ~UnsignedValidator() {}

    void setRange(quint64 bottom, quint64 top)
    {
        setBottom(bottom);
        setTop(top);
    }

    void setBottom(quint64 bottom)
    {
        m_bottom = bottom;
    }

    void setTop(quint64 top)
    {
        m_top = top;
    }

    quint64 top() const
    {
        return m_top;
    }

    quint64 bottom() const
    {
        return m_bottom;
    }

    QValidator::State validate(QString &input, int &pos) const
    {
        (void) pos;
        bool ok = false;
        int c = 0;

        while (c < input.length()) {
            if ((input[c].isDigit()) || ((c == 0) && (input[c] == '-')))
                c++;
            else
                input.remove(c,1);
        }

        quint64 value = input.toULongLong(&ok, 10);

        if (ok) {
            if ((value >= m_bottom) && (value <= m_top)) {
                return QValidator::Acceptable;
            }
        } else if ((input.length() == 0) || (input == "-")) {
            return QValidator::Intermediate;
        }
        return QValidator::Invalid;
    }

private:

    quint64 m_bottom;
    quint64 m_top;
};

class SignedValidator : public QValidator
{
    Q_OBJECT

public:
    SignedValidator(QObject *parent = 0) : QValidator(parent) {
        m_bottom = 0;
        m_top = 0;
    }

    SignedValidator(qint64 minimum, qint64 maximum, QObject * parent = 0)
        : QValidator(parent)
    {
        m_bottom = minimum;
        m_top = maximum;
    }

    ~SignedValidator() {}

    void setRange(qint64 bottom, qint64 top)
    {
        setBottom(bottom);
        setTop(top);
    }

    void setBottom(qint64 bottom)
    {
        m_bottom = bottom;
    }

    void setTop(qint64 top)
    {
        m_top = top;
    }

    qint64 top() const
    {
        return m_top;
    }

    qint64 bottom() const
    {
        return m_bottom;
    }

    QValidator::State validate(QString &input, int &pos) const
    {
        (void) pos;
        bool ok = false;
        int c = 0;

        while (c < input.length()) {
            if ((input[c].isDigit()) || ((c == 0) && (input[c] == '-')))
                c++;
            else
                input.remove(c,1);
        }

        qint64 value = input.toLongLong(&ok, 10);

        if (ok) {
            if ((value >= m_bottom) && (value <= m_top)) {
                return QValidator::Acceptable;
            }
        } else if ((input.length() == 0) || (input == "-")) {
            return QValidator::Intermediate;
        }
        return QValidator::Invalid;
    }

private:

    qint64 m_bottom;
    qint64 m_top;
};

#endif // EXTENDEDVALIDATOR_H
