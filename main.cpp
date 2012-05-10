#include <QtGui/QApplication>
#include <QDebug>
#include "fileproc/ebuparser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EbuParser parser;
    QFile file("C:\\Documents\\Dropbox\\ProgettoMAT\\EBUCore\\Example\\raiexample001_2011.xml");
    file.open(QFile::ReadOnly);
    if (!file.isOpen()) {
        qDebug("Invalid file");
    } else if (!parser.parseFromFile(file)) {
        qDebug("%s", qPrintable(parser.errorMsg()));
        return 1;
    }
    EbuCoreMainType *t = parser.root();
    return 0;
}
