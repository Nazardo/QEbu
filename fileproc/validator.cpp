#include "validator.h"

QString Validator::m_statusMsg;
QString Validator::m_errorMsg;
int Validator::m_errorRow;

Validator::Validator()
{
}

bool Validator::isValid(const QString &file)
{
    m_statusMsg = "";
    m_errorMsg = "";
    m_errorRow = -1;

    QString path = QApplication::applicationDirPath().replace(QString("/"),QString("\\"));

    QStringList args;
    args <<"--noout"; // Don't print the xml tree
    args <<"--schema" <<QString(path+"\\validator\\EBU_CORE_20110915.xsd");
    args <<QString(path+"\\"+file);

    QProcess p;
    p.start("validator\\xmllint.exe", args);

    int result=0;
    if (p.waitForStarted(200)) {
        p.waitForFinished(400);
        m_statusMsg = QString(p.readAllStandardError());
        result=p.exitCode();
    } else {
        m_statusMsg = "Process not started ";
        result=-1;
    }


    switch (result) {
    case 0: // No error
        m_errorMsg = "";
        return true;
        break;
    case 1: // Unclassified
        m_errorMsg = "Unclassified";
        break;
    case 2: // Error in DTD
        m_errorMsg = "error in DTD";
        break;
    case 3: // Validation error
        m_errorMsg = "validation error 1";
        break;
    case 4: // Validation error
        m_errorMsg = "validation error 2";
        break;
    case 5: // Error in schema compilation
        m_errorMsg = "error in schema compilation";
        break;
    case 6: // Error writing output
        m_errorMsg = "error writing output";
        break;
    case 7: // Error in pattern (generated when [--pattern] option is used)
        m_errorMsg = "error in pattern";
        break;
    case 8: // Error in Reader registration (generated when [--chkregister] option is used)
        m_errorMsg = "error in Reader registration";
        break;
    case 9: // Out of memory error
        m_errorMsg = "out of memory error";
        break;

    case -1: // Starting error
        m_errorMsg = "Starting error - no validation performed";
        break;

    default:
        m_errorMsg = "Undocumented error code!";
    }

    return false;
}

QString Validator::statusMsg()
{
    return m_statusMsg;
}

QString Validator::parsedStatusMsg()
{
    if(m_statusMsg.isEmpty())
        return QString();

    QString msg(m_statusMsg);
    msg.chop(2);


    if (msg.endsWith("validates")) {
        msg = "The file is valid";

    } else if (msg.endsWith("fails to validate")) {

        QString path = QApplication::applicationDirPath().replace(QString("/"),QString("\\"));

        int n = msg.indexOf("file:///"+path+"/") + (10 + path.length());
        if (n == -1)
            return QString("Error while parsing output: path not found at start");

        msg = msg.remove(0,n);

        n = msg.indexOf(QRegExp(":[0-9]+:")) + 1;
        int n2 = msg.indexOf(':',n);
        if (n == -1 || n2 == -1)
            return QString("Error while parsing output: error row not found");

        m_errorRow = msg.mid(n,n2-n).toInt();
        msg.remove(0,n2+2);

        n = msg.indexOf(path);
        if (n == -1)
            msg = "Error while parsing output: path not found at end";
        msg.truncate(n - 2);

    } else {
        msg = "Error while parsing output: unexpected ending";
    }

    return msg;
}

QString Validator::errorMsg()
{
    return m_errorMsg;
}

int Validator::errorRow()
{
    if (m_errorRow == -1) {
        if (!m_statusMsg.isEmpty()) {
            // Parse the message to find the row
            int n = m_statusMsg.indexOf(QRegExp(":[0-9]+:")) + 1;
            int n2 = m_statusMsg.indexOf(':',n);
            if (n != -1 && n2 != -1)
                m_errorRow = m_statusMsg.mid(n,n2-n).toInt();
        }
    }
    return m_errorRow;
}
