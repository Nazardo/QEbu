#include <QtGui/QApplication>
#include <QDebug>
#include "fileproc/ebuparser.h"
#include "fileproc/ebuserializer.h"
#include "ui/qebumainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*EbuParser parser;
    QFile ifile("D:\\Documenti\\Politecnico\\MultimediaArchivalTechniques\\EBU_CORE_20110915\\prova\\NewFile.xml");
    ifile.open(QFile::ReadOnly);
    if (!ifile.isOpen()) {
        qDebug("Invalid file");
    } else if (!parser.parseFromFile(ifile)) {
        qDebug("%s", qPrintable(parser.errorMsg()));
        return 1;
    }
    EbuCoreMainType *t = parser.root();

    EbuSerializer s(t);
    QFile ofile("D:\\Documenti\\Politecnico\\MultimediaArchivalTechniques\\QEbu\\out.xml");
    ofile.open(QFile::WriteOnly);
    s.serializeToFile(ofile);

    return 0;*/

    QEbuMainWindow mainWindow;
    mainWindow.show();
    return a.exec();
}
