#include "qebumainwindow.h"
#include "../model/ebucoremaintype.h"
#include "../fileproc/ebuparser.h"
#include "../fileproc/ebuserializer.h"
#include "ebucoremainform.h"
#include <QLabel>
#include <QLayout>
#include <QStackedWidget>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>


QEbuMainWindow::QEbuMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_ebuCoreMain = 0;

    // Central Widget
    QWidget *cw = new QWidget;
    m_mainCentralLayout = new QVBoxLayout;
    m_labelNavigation = new QLabel;
    m_stackedWidget = new QStackedWidget;
    m_mainCentralLayout->addWidget(m_labelNavigation);
    m_mainCentralLayout->addWidget(m_stackedWidget);
    cw->setLayout(m_mainCentralLayout);
    this->setCentralWidget(cw);

    // Create top menu bar
    QMenuBar *topMenuBar = new QMenuBar(this);
    QMenu *fileMenu = new QMenu(tr("&File"), this);
    QAction *openAction = new QAction(tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    QObject::connect(openAction, SIGNAL(triggered()),
                     this, SLOT(actionOpen()));
    fileMenu->addAction(openAction);
    QAction *saveAction = new QAction(tr("&Save as..."), this);
    saveAction->setShortcut(QKeySequence::SaveAs);
    QObject::connect(saveAction, SIGNAL(triggered()),
                     this, SLOT(actionSave()));
    fileMenu->addAction(saveAction);
    QAction *closeAction = new QAction(tr("&Close"), this);
    closeAction->setShortcut(QKeySequence::Close);
    QObject::connect(closeAction, SIGNAL(triggered()),
                     this, SLOT(actionClose()));
    fileMenu->addAction(closeAction);
    fileMenu->addSeparator();
    QAction *quitAction = new QAction(tr("&Quit"), this);
    quitAction->setShortcut(QKeySequence::Quit);
    quitAction->setMenuRole(QAction::QuitRole);
    QObject::connect(quitAction, SIGNAL(triggered()),
                     this, SLOT(actionQuit()));
    fileMenu->addAction(quitAction);
    topMenuBar->addMenu(fileMenu);
    QMenu *aboutMenu = new QMenu(tr("&About"), this);
    QAction *aboutQtAction = new QAction(tr("About &Qt..."), this);
    aboutQtAction->setMenuRole(QAction::AboutQtRole);
    QObject::connect(aboutQtAction, SIGNAL(triggered()),
                     qApp, SLOT(aboutQt()));
    aboutMenu->addAction(aboutQtAction);
    QAction *aboutAction = new QAction(tr("&About QEbu..."), this);
    aboutQtAction->setMenuRole(QAction::AboutRole);
    QObject::connect(aboutAction, SIGNAL(triggered()),
                     this, SLOT(actionAbout()));
    aboutMenu->addAction(aboutAction);
    topMenuBar->addMenu(aboutMenu);
    this->setMenuBar(topMenuBar);

    // Prepare main view
    resetView();
}

QEbuMainWindow::~QEbuMainWindow()
{
    delete m_ebuCoreMain;
}

void QEbuMainWindow::pushWidget(StackableWidget *widget)
{
    QString title = widget->toString();
    m_listLabel.append(title);
    updateLabel();
    m_stackedWidget->addWidget(widget);
    m_stackedWidget->setCurrentWidget(widget);
    QObject::connect(widget, SIGNAL(closed(Operation,QVariant)), this, SLOT(childClosed()));
}

EbuCoreMainType *QEbuMainWindow::ebuCoreMain()
{
    return m_ebuCoreMain;
}

void QEbuMainWindow::childClosed()
{
    removeWidgetFromTop();
}

void QEbuMainWindow::resetView()
{
    // Empty current view and prepare another
    while (removeWidgetFromTop());

    // If there is no opened document, create an empty one.
    if (!m_ebuCoreMain)
        m_ebuCoreMain = new EbuCoreMainType;

    // Push first widget on screen
    this->pushWidget(new EbuCoreMainForm(m_ebuCoreMain, this));
}

bool QEbuMainWindow::removeWidgetFromTop()
{
    QWidget *currentWidget = m_stackedWidget->currentWidget();
    if (!currentWidget)
        return false;
    m_stackedWidget->removeWidget(currentWidget);
    m_listLabel.takeLast();
    updateLabel();
    return true;
}

void QEbuMainWindow::updateLabel()
{
    QString title = "";
    int size = m_listLabel.size();

    if (size > 5) {
        title += m_listLabel.at(0) + " > ...";
        for (int i = size - 4; i < size; ++i) {
            title += " > ";
            title += m_listLabel.at(i);
        }
    } else {
        for (int i = 0; i < size; ++i) {
            if (i > 0) title += " > ";
            title += m_listLabel.at(i);
        }
    }
    m_labelNavigation->setText(title);
}

void QEbuMainWindow::actionOpen()
{
    doOpen();
}

bool QEbuMainWindow::doOpen()
{
    // Close before open!
    if (!doClose())
        return false;

    QString filename = QFileDialog::getOpenFileName(this, tr("Open Metadata File"),
                                            QDir::homePath(),
                                            tr("XML Files (*.xml)"), 0);
    if (filename.isEmpty()) {
        // User pressed "Cancel"
        return false;
    }

    QFile inputFile(filename);
    if (!inputFile.open(QFile::ReadOnly)) {
        QMessageBox openWarning(QMessageBox::Warning, tr("QEbu Parser"),
                                tr("Input file cannot be opened"),
                                QMessageBox::Ok, this);
        openWarning.setDetailedText(inputFile.errorString());
        openWarning.exec();
        return false;
    }

    EbuParser parser;
    if (!parser.parseFromFile(inputFile)) {
        QMessageBox parserWarning(this);
        parserWarning.setIcon(QMessageBox::Warning);
        parserWarning.setWindowTitle(tr("QEbu Parser"));
        parserWarning.setText(tr("Invalid input file"));
        parserWarning.setDetailedText(parser.errorMsg());
        parserWarning.setStandardButtons(QMessageBox::Ok);
        parserWarning.setDefaultButton(QMessageBox::Ok);
        parserWarning.exec();
        return false;
    }

    // All has gone well (we hope).
    QMessageBox::information(this, tr("QEbu Parser"),
                             tr("Metadata imported successfully."));
    if (m_ebuCoreMain)
        delete m_ebuCoreMain;
    m_ebuCoreMain = parser.root();
    resetView();
    return true;
}


void QEbuMainWindow::actionSave()
{
    doSave();
}

bool QEbuMainWindow::doSave()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Open Metadata File"),
                                            QDir::homePath(),
                                            tr("XML Files (*.xml)"), 0);
    if (filename.isEmpty()) {
        // User pressed "Cancel"
        return false;
    }

    QFile outputFile(filename);
    if (!outputFile.open(QFile::WriteOnly)) {
        QMessageBox openWarning(QMessageBox::Warning, tr("QEbu Serializer"),
                                tr("Output file cannot be opened"),
                                QMessageBox::Ok, this);
        openWarning.setDetailedText(outputFile.errorString());
        openWarning.exec();
        return false;
    }

    EbuSerializer serializer(m_ebuCoreMain);
    if (!serializer.serializeToFile(outputFile)) {
        // In the current version the serializer always returns true, so
        // this is dead code never to be reached.
        QMessageBox serializerWarning(QMessageBox::Warning, tr("QEbu Serializer"),
                                  tr("Error while serializing to file"),
                                  QMessageBox::Ok, this);
        serializerWarning.exec();
        return false;
    }

    // All has gone well (we hope).
    QMessageBox::information(this, tr("QEbu Serializer"),
                             tr("Metadata saved successfully."));
    return true;
}

void QEbuMainWindow::actionClose()
{
    doClose();
}

bool QEbuMainWindow::doClose()
{
    // If there is a document opened prompt the user to save his work.
    if (m_ebuCoreMain) {
        QMessageBox question(QMessageBox::Question, tr("QEbu"),
                             tr("Save current metadata file?"),
                             QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                             this);
        question.setDefaultButton(QMessageBox::Yes);
        int userChoice = question.exec();
        if (userChoice == QMessageBox::Yes) {
            if (!doSave())
                return false;
        } else if (!(userChoice == QMessageBox::No)) {
            // The user may have pressed ESC or the Cancel button
            return false;
        }
    }
    delete m_ebuCoreMain;
    m_ebuCoreMain = 0;
    resetView();
    return true;
}

void QEbuMainWindow::actionQuit()
{
    if (!doClose())
        return;
    this->close();
}

void QEbuMainWindow::actionAbout()
{
    /// @todo Real about dialog, maybe using the designer this time.
    QMessageBox::about(this, tr("About QEbu"),
                       tr("QEbu about text goes here."));
}

QMap<QString, QString> QEbuMainWindow::getMap(QString name)
{
    if (m_maps.contains(name)) {
        return m_maps.value("name");
    } else {
        // Dynamical load from file
        QMap<QString, QString> map;

        QFile file(".\\debug\\XML_autoComp\\"+name+".xml");
        QString baseUrl;
        QString currentTerm;

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            // NO FILE FOUND, SKIP MAP COMPLETION
            qDebug() <<"autocompletion file not found:" <<QString(".\\debug\\XML_autoComp\\"+name+".xml");
        } else {
            QXmlStreamReader *xml = new QXmlStreamReader(&file);
            while (!xml->atEnd() && !xml->hasError()) {
                if(xml->readNextStartElement()) {
                    if (xml->name() == "ClassificationScheme") {
                        // Get the uri attribute to define base url
                        baseUrl = xml->attributes().value("uri").toString();
                        qDebug() << baseUrl;
                        continue;
                    }
                    if (xml->name() == "Term") {
                        // Get the termId attribute to define the key
                        currentTerm = xml->attributes().value("termID").toString();
                        continue;
                    }
                    if (xml->name() == "Name") {
                        // Get the text to define the value
                        QString val = xml->readElementText();
                        map.insert(currentTerm, val);
                        qDebug() << currentTerm << val;
                        continue;
                    }
                }
            }
        }

        m_maps.insert(name,map);
        return map;
    }
}
