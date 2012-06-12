#include "validator.h"
#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>
#include <QFile>
#include <QRegExp>
#include <QString>
#include <QDebug>
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
    m_error = Unknown;
    m_errorRow = -1;

    QStringList args;
    args << "--noout"; // Don't print the xml tree
    args << "--schema" << schema;
    args << file;

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

        QString path = QApplication::applicationDirPath().replace(QString("/"),QString("\\"));

        int n = msg.indexOf("file:///"+path+"/") + (10 + path.length());
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

        n = msg.indexOf(path);
        if (n == -1)
            msg = QObject::tr("Error while parsing output: path not found at end");
        msg.truncate(n - 2);

    } else {
        msg = QObject::tr("Error while parsing output: unexpected ending");
    }

    m_validationErrorMessage = msg;
}
