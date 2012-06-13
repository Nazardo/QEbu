/****************************************************************************
** Copyright (C) 2012 by
**  Mauro Levra  (nazardo)     mauro@nazardo.it
**  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it
**  Denis Patti  (dextp3)      denis.patti@studenti.polito.it
**  Giovanni Pessiva           giovanni.pessiva@gmail.com
**  Stefano Ricossa            stefano.ricossa@studenti.polito.it
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

#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QString>

class Validator
{
public:
    Validator();
    enum ValidatorError {
        Unknown = 0,
        ValidatorNotFound,
        DocumentNotValid,
        DocumentValid
    };

    bool validate(const QString &file, const QString &schema);
    ValidatorError error() const;
    QString returnMessage() const;
    QString validationErrorMessage() const;
    int errorRow() const;

private:
    void parseOutput();
    ValidatorError m_error;
    QString m_stderrOutput;
    QString m_returnMessage;
    QString m_validationErrorMessage;
    int m_errorRow;
};

#endif // VALIDATOR_H
