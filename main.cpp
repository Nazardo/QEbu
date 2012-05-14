#include <QtGui/QApplication>
#include <QDebug>
#include "fileproc/ebuparser.h"
#include "fileproc/ebuserializer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EbuParser parser;
    QFile ifile("C:\\Users\\Pas\\Desktop\\MAT\\raiexample001_2011.xml");
    ifile.open(QFile::ReadOnly);
    if (!ifile.isOpen()) {
        qDebug("Invalid file");
    } else if (!parser.parseFromFile(ifile)) {
        qDebug("%s", qPrintable(parser.errorMsg()));
        return 1;
    }
    EbuCoreMainType *t = parser.root();

    EbuSerializer s(t);
    QFile ofile("C:\\Users\\Pas\\Desktop\\MAT\\out.xml");
    ofile.open(QFile::WriteOnly);
    s.serializeToFile(ofile);

    return 0;
}
