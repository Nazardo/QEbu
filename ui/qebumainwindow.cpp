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

#include "qebumainwindow.h"
#include "../model/ebucoremaintype.h"
#include "../fileproc/ebuparser.h"
#include "../fileproc/ebuserializer.h"
#include "../fileproc/validator.h"
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
#include <QWizard>
#include <QPixmap>
#include <QDialogButtonBox>
#include <QPushButton>


QEbuMainWindow::QEbuMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_ebuCoreMain = 0;

    m_icon.addFile(":/images/qebu-icon_32.png");
    m_icon.addFile(":/images/qebu-icon_64.png");
    this->setWindowIcon(m_icon);
    qApp->setWindowIcon(m_icon);

    // Central Widget
    QWidget *cw = new QWidget;
    m_mainCentralLayout = new QVBoxLayout;

    m_labelNavigation = new QLabel;
    m_labelNavigation->setFrameStyle(QFrame::Box | QFrame::Raised);
    m_stackedWidget = new QStackedWidget;
    m_stackedWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    //m_stackedWidget->setMinimumSize(640,400);
    m_mainCentralLayout->addWidget(m_labelNavigation);
    m_mainCentralLayout->addWidget(m_stackedWidget);


    // Bottom label -> currentDocument
    m_currentDocument = new QLabel;
    m_mainCentralLayout->addWidget(m_currentDocument);
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
    QMenu *helpMenu = new QMenu(tr("&Help"), this);
    QAction *wizardAction = new QAction(tr("&Getting started..."), this);
    QObject::connect(wizardAction, SIGNAL(triggered()),
                     this, SLOT(actionWizard()));
    helpMenu->addAction(wizardAction);
    helpMenu->addSeparator();
    QAction *aboutQtAction = new QAction(tr("About &Qt..."), this);
    aboutQtAction->setMenuRole(QAction::AboutQtRole);
    QObject::connect(aboutQtAction, SIGNAL(triggered()),
                     qApp, SLOT(aboutQt()));
    helpMenu->addAction(aboutQtAction);
    QAction *aboutAction = new QAction(tr("&About QEbu..."), this);
    aboutQtAction->setMenuRole(QAction::AboutRole);
    QObject::connect(aboutAction, SIGNAL(triggered()),
                     this, SLOT(actionAbout()));
    helpMenu->addAction(aboutAction);

    topMenuBar->addMenu(helpMenu);
    this->setMenuBar(topMenuBar);

    // Prepare main view
    resetView();
}

QEbuMainWindow::~QEbuMainWindow()
{
    delete m_ebuCoreMain;

    for (int i=0;  i<m_maps.keys().size(); i++)
        delete m_maps.value(m_maps.keys()[i]);
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
    if (!m_ebuCoreMain) {
        m_currentDocument->setText(tr("New document created at %1").arg(QTime::currentTime().toString()));
        m_ebuCoreMain = new EbuCoreMainType;
    }

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

    // Validation
    QString schema = qApp->applicationDirPath() + "/data/EBU_CORE_20110915.xsd";
    Validator validator;
    if (!validator.validate(filename, schema)) {
        Validator::ValidatorError error = validator.error();
        switch (error) {
        case Validator::ValidatorNotFound:
            QMessageBox::warning(this, tr("Validator"),
                                 tr("xmllint was not found in the application's PATH,"
                                    "thus no validation has been performed.\n"
                                    "The parsing can bring to unpredictable results."));
            break;
        case Validator::DocumentNotValid:
        {
            QMessageBox validatorWarning(this);
            validatorWarning.setIcon(QMessageBox::Warning);
            validatorWarning.setWindowTitle(tr("Validator"));
            validatorWarning.setText(tr("Invalid input file"));
            validatorWarning.setDetailedText(validator.validationErrorMessage());
            validatorWarning.setStandardButtons(QMessageBox::Ok);
            validatorWarning.setDefaultButton(QMessageBox::Ok);
            validatorWarning.exec();
            return false;
        }
        case Validator::DocumentValid:
            break;
        case Validator::Unknown:
        default:
        {
            QMessageBox validatorWarning(this);
            validatorWarning.setIcon(QMessageBox::Warning);
            validatorWarning.setWindowTitle(tr("Validator"));
            validatorWarning.setText(tr("Unexpected error from validator"));
            validatorWarning.setDetailedText(validator.returnMessage());
            validatorWarning.setStandardButtons(QMessageBox::Ignore |
                                                QMessageBox::Abort);
            validatorWarning.setDefaultButton(QMessageBox::Abort);
            int ret = validatorWarning.exec();
            if (ret == QMessageBox::Abort)
                return false;
        }
        }
    }

    // Parsing
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
    // QFileInfo is used to remove the pathname and extract only the true filename.
    QFileInfo fi(filename);
    m_currentDocument->setText(tr("%1 opened at %2").arg(fi.fileName()).arg(QTime::currentTime().toString()));
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
    // QFileInfo is used to remove the pathname and extract only the true filename.
    QFileInfo fi(filename);
    m_currentDocument->setText(tr("Document saved as %1 at %2").arg(fi.fileName()).arg(QTime::currentTime().toString()));
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
    QDialog *aboutDialog = new QDialog(this);
    aboutDialog->setWindowTitle(tr("About QEbu"));

    QHBoxLayout *hLayout = new QHBoxLayout;

    QPixmap logo(":/images/qebu-icon_256.png");
    QLabel *imageLabel = new QLabel;
    imageLabel->setPixmap(logo);
    hLayout->addWidget(imageLabel, Qt::AlignTop);

    QLabel *text = new QLabel(tr("<h2>About QEbu</h2><br>QEbu is a full-fledged graphical editor that supports creation and editing of documents following the EbuCore metadata specification."
                                 "<br><br>More information on EBU metadata activities is provided on the <a href=\"http://tech.ebu.ch/metadata\">EBU TECHNICAL website</a>."
                                 "<br><br>This program is licensed to you under terms of the GNU General Public License Version 3 as published by Free Software Foundation."
                                 "<br><br>The program is provided AS IS with NO WARRANTY OF ANY KIND."
                                 ));
    text->setOpenExternalLinks(true);
    text->setWordWrap(true);
    text->setAlignment(Qt::AlignJustify);
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(text);
    QDialogButtonBox *dialogButtonBox = new QDialogButtonBox(
                QDialogButtonBox::Ok,
                Qt::Horizontal);
    vLayout->addWidget(dialogButtonBox, Qt::AlignRight);
    hLayout->addLayout(vLayout);
    aboutDialog->setLayout(hLayout);
    dialogButtonBox->button(QDialogButtonBox::Ok)->setDefault(true);
    QObject::connect(dialogButtonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()),
                     aboutDialog, SLOT(close()));
    aboutDialog->exec();
}

void QEbuMainWindow::actionWizard()
{
    QWizard *wizard = new QWizard(this);
    wizard->setWindowTitle(QObject::tr("Getting started"));
    wizard->setWizardStyle(QWizard::ModernStyle);
    wizard->adjustSize();

    // INTRO
    QWizardPage *intro = new QWizardPage;
    {
        intro->setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));
        intro->setTitle(QObject::tr("Introduction"));
        QVBoxLayout *layout = new QVBoxLayout;
        QLabel *label = new QLabel(QObject::tr("This brief tutorial will give an overview "
                              "of the main components of the editor and their "
                              "meaning. A couple of aspects of the GUI are pointed out "
                              "in every page and small insight is given about the most "
                              "relevant elements."));
        label->setWordWrap(true);
        layout->addWidget(label);
        intro->setLayout(layout);
    }


    // FIRST PAGE - Basic Layout Description I
    // Breadcrumb
    // Grouping attributes/elements

    QWizardPage *page1 = new QWizardPage;
    {
        page1->setPixmap(QWizard::BannerPixmap, QPixmap(":/images/banner.png").scaled(560, 49, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        page1->setTitle(QObject::tr("Basic Layout I"));
        page1->setSubTitle(QObject::tr("Breadcrumb and grouping"));
        QVBoxLayout *layout = new QVBoxLayout;
        QLabel *image = new QLabel;
        image->setPixmap(QPixmap(":/images/page0.png"));
        image->setAlignment(Qt::AlignHCenter);
        QLabel *firstParagraph = new QLabel("(1) A simple to read breadcrumb at the top of each page will help you remember at which level of the tree you are");
        firstParagraph->setWordWrap(true);
        QLabel *secondParagraph = new QLabel("(2) All the fields within a form are grouped together, or at least sorted in a meaningful way. For any given types all the attributes are stacked at the top of the page, whereas inner elements occupy lower positions.");
        secondParagraph->setWordWrap(true);
        layout->addWidget(image);
        layout->addWidget(firstParagraph);
        layout->addWidget(secondParagraph);
        page1->setLayout(layout);
    }


    // SECOND PAGE - Basic Layout Description II
    // [0..1]
    // TAB

    QWizardPage *page2 = new QWizardPage;
    {
        page2->setPixmap(QWizard::BannerPixmap, QPixmap(":/images/banner.png").scaled(560, 49, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        page2->setTitle(QObject::tr("Basic Layout II"));
        page2->setSubTitle(QObject::tr("Simple elements and Tabs"));
        QVBoxLayout *layout = new QVBoxLayout;
        QLabel *image = new QLabel;
        image->setPixmap(QPixmap(":/images/page1.png"));
        image->setAlignment(Qt::AlignHCenter);
        QLabel *firstParagraph = new QLabel("(1) Inner elements with cardinality of [0..1] are hadlled with a couple of buttons to add the element, or edit the existing one, and to remove it. An immutable edit box gives a direct feedback of the status of said element.");
        firstParagraph->setWordWrap(true);
        QLabel *secondParagraph = new QLabel("(2) To have a nicer and tidier appearence, in case of very rich panels, the content is divided among several tabs, with the aim to keep together correlated elements.");
        secondParagraph->setWordWrap(true);
        layout->addWidget(image);
        layout->addWidget(firstParagraph);
        layout->addWidget(secondParagraph);
        page2->setLayout(layout);
    }

    // THIRD PAGE - Basic Layout Description III
    // The Amazing ListView
    // Mention to New Form vs Simple Dialog

    QWizardPage *page3 = new QWizardPage;
    {
        page3->setPixmap(QWizard::BannerPixmap, QPixmap(":/images/banner.png").scaled(560, 49, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        page3->setTitle(QObject::tr("Basic Layout III"));
        page3->setSubTitle(QObject::tr("Listview"));
        QVBoxLayout *layout = new QVBoxLayout;
        QLabel *image = new QLabel;
        image->setPixmap(QPixmap(":/images/page2.png"));
        image->setAlignment(Qt::AlignHCenter);
        QLabel *firstParagraph = new QLabel("In case of inner elements with [0..*] cardinality a custom list manager is provided, to manage the contents.");
        firstParagraph->setWordWrap(true);
        QLabel *secondParagraph = new QLabel("In presence of both single and multiple cardinality elements within the same form, to keep a coherent appearence all the items are managed with the proposed list view, that automatically forbids the insertion of more than one element, if needed.");
        secondParagraph->setWordWrap(true);
        layout->addWidget(image);
        layout->addWidget(firstParagraph);
        layout->addWidget(secondParagraph);
        page3->setLayout(layout);
    }

    // FOURTH PAGE - Dates & Numbers
    // Optional fields
    // Checkboxes
    // Compliance Check

    QWizardPage *page4 = new QWizardPage;
    {
        page4->setPixmap(QWizard::BannerPixmap, QPixmap(":/images/banner.png").scaled(560, 49, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        page4->setTitle(QObject::tr("About data"));
        page4->setSubTitle(QObject::tr("Dates, numbers and validation"));
        QVBoxLayout *layout = new QVBoxLayout;
        QLabel *image = new QLabel;
        image->setPixmap(QPixmap(":/images/page3.png").scaledToWidth(500, Qt::SmoothTransformation));
        image->setAlignment(Qt::AlignHCenter);
        QLabel *firstParagraph = new QLabel("(1) Unlike simple text fields, data and numeric related fields come with a checkbox to enable/disable its content from being saved to the XML files in creation. Upon a change of the represented value the checkboxes are automatically ticked off, whilst if unchecked their value is ignored or cleared if previusly modified.");
        firstParagraph->setWordWrap(true);
        QLabel *secondParagraph = new QLabel("(2) Upon clicking Apply a compliance check is run on the form contents, and an error message, preventing the user from continuing, appears in case of mistakes or shortcomings.");
        secondParagraph->setWordWrap(true);
        layout->addWidget(image);
        layout->addWidget(firstParagraph);
        layout->addWidget(secondParagraph);
        page4->setLayout(layout);
    }

    // END OF TUTORIAL

    wizard->addPage(intro);
    wizard->addPage(page1);
    page1->setFixedHeight(420);
    wizard->addPage(page2);
    wizard->addPage(page3);
    wizard->addPage(page4);
    wizard->exec();
}

QMap<QString, QString> *QEbuMainWindow::getMap(QString name)
{
    if (m_maps.contains(name)) {
        return m_maps.value(name);
    } else {
        // Dynamical load from file
        QMap<QString, QString> *map = new QMap<QString, QString>();

        QFile file(".\\debug\\XML_autoComp\\"+name+".xml");
        QString baseUrl;
        QString currentTerm;

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            // NO FILE FOUND, SKIP MAP COMPLETION
        } else {
            QXmlStreamReader *xml = new QXmlStreamReader(&file);
            while (!xml->atEnd() && !xml->hasError()) {
                if(xml->readNextStartElement()) {
                    if (xml->name() == "ClassificationScheme") {
                        // Get the uri attribute to define base url
                        baseUrl = xml->attributes().value("uri").toString();
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
                        //map->insert(currentTerm, val);
                        map->insert(baseUrl+"#"+currentTerm, val);
                        continue;
                    }
                }
            }
        }
        m_maps.insert(name,map);
        return map;
    }
}

QIcon QEbuMainWindow::ebuIcon() const
{
    return m_icon;
}
