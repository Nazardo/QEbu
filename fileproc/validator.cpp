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

#include "validator.h"
#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>
#include <QFile>
#include <QRegExp>
#include <QString>
#include <QFile>
#include <QProcess>
#include <QStringList>

Validator::Validator()
{
    m_error = Unknown;
    m_errorRow = -1;
}

bool Validator::validate(const QString &file, const QString &schema)
{
    m_stderrOutput = QString();
    m_validationErrorMessage = QString();
    m_returnMessage = QString();
    m_inputFile = file;
    m_error = Unknown;
    m_errorRow = -1;

    QStringList args;
    args << "--noout"; // Don't print the xml tree
    args << "--schema" << schema;
    args << m_inputFile;

    QProcess p;
    p.start("xmllint", args);

    int result=0;
    if (p.waitForStarted(200)) {
        p.waitForFinished(400);
        m_stderrOutput = QString(p.readAllStandardError());
        result = p.exitCode();
    } else {
        m_error = ValidatorNotFound;
        return false;
    }

    switch (result) {
    case 0: // No error
        m_returnMessage = QObject::tr("Success");
        m_error = DocumentValid;
        return true;
        break;
    case 1: // Unclassified
        m_returnMessage = QObject::tr("Unclassified");
        m_error = DocumentValid;
        break;
    case 2: // Error in DTD
        m_returnMessage = QObject::tr("error in DTD");
        break;
    case 3: // Validation error
    case 4: // idem
        m_returnMessage = QObject::tr("Validation error");
        m_error = DocumentNotValid;
        parseOutput();
        return false;
    case 5: // Error in schema compilation
        m_returnMessage = QObject::tr("Error in schema compilation");
        break;
    case 6: // Error writing output
        m_returnMessage = QObject::tr("Error writing output");
        break;
    case 7: // Error in pattern (generated when [--pattern] option is used)
        m_returnMessage = QObject::tr("Error in pattern");
        break;
    case 8: // Error in Reader registration (generated when [--chkregister] option is used)
        m_returnMessage = QObject::tr("Error in Reader registration");
        break;
    case 9: // Out of memory error
        m_returnMessage = QObject::tr("Out of memory error");
        break;

    case -1: // Starting error
        m_returnMessage = QObject::tr("Starting error - no validation performed");
        break;

    default:
        m_returnMessage = QObject::tr("Undocumented error code");
    }

    return false;
}

Validator::ValidatorError Validator::error() const
{
    return m_error;
}

QString Validator::returnMessage() const
{
    return m_returnMessage;
}

QString Validator::validationErrorMessage() const
{
    return m_validationErrorMessage;
}

int Validator::errorRow() const
{
    return m_errorRow;
}

void Validator::parseOutput()
{
    QString msg(m_stderrOutput);
    msg.chop(2);


    if (msg.endsWith("validates")) {
        msg = "The file is valid";

    } else if (msg.endsWith("fails to validate")) {

        int n = msg.indexOf(m_inputFile) + m_inputFile.length();
        if (n == -1) {
            m_validationErrorMessage = QObject::tr("Error while parsing output: path not found at start");
            return;
        }

        msg = msg.remove(0,n);

        n = msg.indexOf(QRegExp(":[0-9]+:")) + 1;
        int n2 = msg.indexOf(':',n);
        if (n == -1 || n2 == -1) {
            m_validationErrorMessage = QObject::tr("Error while parsing output: error row not found");
            return;
        }

        m_errorRow = msg.mid(n,n2-n).toInt();
        msg.remove(0,n2+2);

        n = msg.indexOf(m_inputFile);
        if (n == -1)
            msg = QObject::tr("Error while parsing output: path not found at end");
        msg.truncate(n - 2);
        if (m_errorRow >= 0)
            msg.prepend(QObject::tr("Error at row %1.\n").arg(m_errorRow));

    } else {
        msg = QObject::tr("Error while parsing output: unexpected ending");
    }

    m_validationErrorMessage = msg;
}
