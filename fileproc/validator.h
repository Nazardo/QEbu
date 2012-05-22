#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>
#include <QFile>
#include <QRegExp>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QProcess>
#include <QStringList>

class Validator
{
public:
    static bool isValid(const QString &file);
    static QString statusMsg();
    static QString parsedStatusMsg();
    static QString errorMsg();
    static int errorRow();


private:
    Validator();
    static QString m_statusMsg; // Validation output produced by xmllite.exe
    static QString m_errorMsg; // Error message received from xmllite.exe
    static int m_errorRow; // Row where an error has been found
};

#endif // VALIDATOR_H
