#include "MainWindow.h"
#include "config/settings.h"
#include "qboxlayout.h"
#include "qchar.h"
#include "qglobal.h"
#include "qlocale.h"
#include "qobjectdefs.h"
#include "qpushbutton.h"
#include "qwidget.h"
#include <QCheckBox>
#include <QDebug>
#include <QFileDialog>
#include <QFrame>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>
#include <QSplitter>
#include <QVBoxLayout>

MainWindow::MainWindow()
{

    setGeometry(QRect(100, 100, 960, 560));
    windowTitle = "Witchy Qss Editor";
    /*setWindowFlags(Qt::FramelessWindowHint);*/
    currentQssFilePath = "";
    QWidget *central_widget = new QWidget(this);
    QFrame *background_app = new QFrame(central_widget);
    background_app->setFrameShape(QFrame::NoFrame);
    background_app->setFrameShadow(QFrame::Raised);

    QHBoxLayout *h_ly = new QHBoxLayout(background_app);
    h_ly->setSpacing(20);
    h_ly->setContentsMargins(0, 0, 0, 0);
    editorPanel = new QWidget(central_widget);
    elementsPanel = new QssWidgetsPreview(central_widget);
    QSplitter *splitter = new QSplitter(background_app);
    splitter->addWidget(editorPanel);
    splitter->addWidget(elementsPanel);

    h_ly->addWidget(splitter);
    background_app->setLayout(h_ly);

    QVBoxLayout *mainLayout = new QVBoxLayout(central_widget);
    /*mainLayout->addWidget(title_bar);*/
    mainLayout->addWidget(background_app);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    setupMenuBar();
    setupEditorPanel();
    /*setupElementsPanel();*/

    setCentralWidget(central_widget);
    centralWidget()->setLayout(mainLayout);

    setTexts();

    loadSettings();
}

MainWindow::~MainWindow() {}

void MainWindow::setupMenuBar()
{
    QMenuBar *menuBar = this->menuBar();
    QMenu *fileMenu = menuBar->addMenu("&File");
    QAction *newAction = fileMenu->addAction("New");
    QAction *openAction = fileMenu->addAction("Open");

    QMenu *editMenu = menuBar->addMenu("&Edit");
    QAction *cutAction = editMenu->addAction("Cut");
    QAction *copyAction = editMenu->addAction("Copy");
    QAction *pasteAction = editMenu->addAction("Paste");

    QMenu *viewmenu = menuBar->addMenu("&View");
    QAction *showColorsPreview = viewmenu->addAction("Show colors preview");
    showColorsPreview->setCheckable(true);

    QMenu *helpMenu = menuBar->addMenu("&Help");
    QAction *aboutAction = helpMenu->addAction("About");

    /*QToolBar * toolBar = this->toolBar*/
    connect(newAction, &QAction::triggered, this, []()
            { QMessageBox::information(nullptr, "Action", "New selected"); });
    connect(openAction, &QAction::triggered, this, &MainWindow::openQssFile);

    QString aboutText = "<b><center>Witchy Qss Editor</center></b><br><br>";
    aboutText +=
        tr("This is experimental Qss editor and preview tool. Work in "
           "progress, feel free to report bugs on my github page.<br><br> ");
    aboutText += tr("Author: DrBender<br>GitHub: <a "
                    "href='https://github.com/DrBender/witchy-qss-editor'>https"
                    "://github.com/DrBender/witchy-qss-editor</a><br><br>"
                    "Email: drbenderdj@gmail.com ");
    aboutText += "<br>Copyright &copy; 2024, DrBender. All rights reserved.";
    connect(aboutAction, &QAction::triggered, this, [this, aboutText]()
            { QMessageBox::about(this, "About", aboutText); });

    connect(showColorsPreview, &QAction::triggered, this,
            &MainWindow::showColorsPanel);
}

void MainWindow::setupEditorPanel()
{
    editorPanel->setLayout(new QVBoxLayout(editorPanel));
    editor = new QssTextEditor(editorPanel);

    QWidget *pbPanel = new QWidget(editorPanel);
    pbPanel->setLayout(new QHBoxLayout(editorPanel));
    QPushButton *open = new QPushButton(editorPanel);
    QPushButton *save = new QPushButton(editorPanel);
    QPushButton *apply_style = new QPushButton(editorPanel);
    QPushButton *reformat = new QPushButton(editorPanel);

    open->setText(tr("Open"));
    save->setText(tr("Save"));
    apply_style->setText(tr("Apply Style"));
    reformat->setText(tr("Reformat"));

    pbPanel->layout()->addWidget(open);
    pbPanel->layout()->addWidget(save);
    pbPanel->layout()->addWidget(apply_style);
    pbPanel->layout()->addWidget(reformat);

    editorPanel->layout()->addWidget(pbPanel);
    editorPanel->layout()->addWidget(editor);

    connect(open, SIGNAL(clicked()), this, SLOT(openQssFile()));
    connect(save, SIGNAL(clicked()), this, SLOT(saveQssFile()));
    connect(apply_style, SIGNAL(clicked()), this, SLOT(applyQssFile()));
    connect(reformat, &QPushButton::clicked, this,
            &MainWindow::reformatQssFile);
}
void MainWindow::setupElementsPanel() {}
void MainWindow::setTexts() {}

void MainWindow::openQssFile()
{
    qDebug() << "open Qss File";
    QString fileName = QFileDialog::getOpenFileName(
        this, "Open file", "", "Qss Files (*.qss);;All Files (*)");

    if (fileName.isEmpty())
    {
        return;
    }

    QFile file(fileName);
    currentQssFilePath = fileName;
    QString name = QFileInfo(currentQssFilePath).fileName();
    this->setWindowTitle(windowTitle + " - " + name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Error", "Couldn't open file for reading.");
        return;
    }

    QTextStream in(&file);
    QString fileContent = in.readAll();

    file.close();

    editor->setPlainText(fileContent);
}
void MainWindow::saveQssFile()
{
    qDebug() << "save Qss File";
    // QFileDialog dialog(this);
    // dialog.setNameFilter(tr("QSS (*.qss)"));
    QString fileName = QFileDialog::getSaveFileName(
        this, "Save file", "", "Qss Files (*.qss);;All Files (*)");

    if (fileName.isEmpty())
    {
        return;
    }

    QFile file(fileName);
    currentQssFilePath = fileName;
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Error", "Couldn't open file for writing.");
        return;
    }

    QTextStream out(&file);
    QString text = editor->toPlainText();
    out << text;

    file.close();
}

void MainWindow::applyQssFile()
{
    qDebug() << "Apply Style";
    QString text = editor->toPlainText();
    elementsPanel->setStyleSheet(text);

    QString copy_text = text;

    editor->parser.parse(copy_text);
}

void MainWindow::reformatQssFile()
{
    QString plain_text = editor->toPlainText();
    editor->parser.parse(plain_text);
    QString text = editor->parser.parsed_text;
    editor->setPlainText(text);
}

void MainWindow::showColorsPanel()
{

    qDebug() << "MainWindow::showColorsPanel()";
}

void MainWindow::saveSettings()
{
    Settings &set = Settings::instance();
    set.win_width = this->width();
    set.win_height = this->height();
    set.lastFile = currentQssFilePath;
    set.saveSettings();
}

void MainWindow::loadSettings()
{
    Settings &set = Settings::instance();
    set.loadSettings();

    currentQssFilePath = set.lastFile;
    if (currentQssFilePath.isEmpty())
    {
        return;
    }
    QFile file(currentQssFilePath);
    qDebug() << "cur " << currentQssFilePath;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Error",
                             QString("Couldn't open file %1 for reading.")
                                 .arg(currentQssFilePath));
        return;
    }
    QTextStream in(&file);
    QString fileContent = in.readAll();

    file.close();

    editor->setPlainText(fileContent);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();
    event->accept();
}
