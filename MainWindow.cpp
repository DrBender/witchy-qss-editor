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
#include <QVBoxLayout>

MainWindow::MainWindow()
{

    setGeometry(QRect(100, 100, 960, 560));

    /*setWindowFlags(Qt::FramelessWindowHint);*/
    currentQssFile = "";
    QWidget *central_widget = new QWidget(this);
    QFrame *background_app = new QFrame(central_widget);
    background_app->setFrameShape(QFrame::NoFrame);
    background_app->setFrameShadow(QFrame::Raised);

    QHBoxLayout *h_ly = new QHBoxLayout(background_app);
    h_ly->setSpacing(20);
    h_ly->setContentsMargins(0, 0, 0, 0);
    editorPanel = new QWidget(central_widget);
    elementsPanel = new QssWidgetsPreview(central_widget);
    h_ly->addWidget(editorPanel);
    h_ly->addWidget(elementsPanel);
    background_app->setLayout(h_ly);

    QVBoxLayout *mainLayout = new QVBoxLayout(central_widget);
    /*mainLayout->addWidget(title_bar);*/
    mainLayout->addWidget(background_app);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    setupEditorPanel();
    /*setupElementsPanel();*/

    setCentralWidget(central_widget);
    centralWidget()->setLayout(mainLayout);

    setTexts();

    loadSettings();
}

MainWindow::~MainWindow() {}
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
    currentQssFile = fileName;
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
    currentQssFile = fileName;
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

void MainWindow::saveSettings()
{
    Settings &set = Settings::instance();
    set.win_width = this->width();
    set.win_height = this->height();
    set.lastFile = currentQssFile;
    set.saveSettings();
}

void MainWindow::loadSettings()
{
    Settings &set = Settings::instance();
    set.loadSettings();

    currentQssFile = set.lastFile;
    if (currentQssFile.isEmpty())
    {
        return;
    }
    QFile file(currentQssFile);
    qDebug() << "cur "<< currentQssFile;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Error", QString("Couldn't open file %1 for reading.").arg(currentQssFile));
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
