#include "MainWindow.h"
#include "qboxlayout.h"
#include "qglobal.h"
#include "qlocale.h"
#include "qobjectdefs.h"
#include "qpushbutton.h"
#include "qwidget.h"
#include <QCheckBox>
#include <QDebug>
#include <QFileDialog>
#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow()
{
    setGeometry(QRect(100, 100, 960, 560));

    /*setWindowFlags(Qt::FramelessWindowHint);*/

    QWidget *central_widget = new QWidget(this);
    QFrame *background_app = new QFrame(central_widget);
    background_app->setFrameShape(QFrame::NoFrame);
    background_app->setFrameShadow(QFrame::Raised);

    QHBoxLayout *h_ly = new QHBoxLayout(background_app);
    h_ly->setSpacing(20);
    h_ly->setContentsMargins(0, 0, 0, 0);
    editorPanel = new QWidget(central_widget);
    elementsPanel = new QWidget(central_widget);
    h_ly->addWidget(editorPanel);
    h_ly->addWidget(elementsPanel);
    background_app->setLayout(h_ly);

    QVBoxLayout *mainLayout = new QVBoxLayout(central_widget);
    /*mainLayout->addWidget(title_bar);*/
    mainLayout->addWidget(background_app);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    setupEditorPanel();
    setupElementsPanel();

    setCentralWidget(central_widget);
    centralWidget()->setLayout(mainLayout);

    setTexts();
}

MainWindow::~MainWindow() {}
void MainWindow::setupEditorPanel()
{
    editorPanel->setLayout(new QVBoxLayout(editorPanel));
    qssEditor = new QTextEdit(editorPanel);

    QWidget *pbPanel = new QWidget(editorPanel);
    pbPanel->setLayout(new QHBoxLayout(editorPanel));
    QPushButton *open = new QPushButton(editorPanel);
    QPushButton *save = new QPushButton(editorPanel);
    QPushButton *apply_style = new QPushButton(editorPanel);

    open->setText(tr("Open"));
    save->setText(tr("Save"));
    apply_style->setText(tr("Apply Style"));

    pbPanel->layout()->addWidget(open);
    pbPanel->layout()->addWidget(save);
    pbPanel->layout()->addWidget(apply_style);

    editorPanel->layout()->addWidget(pbPanel);
    editorPanel->layout()->addWidget(qssEditor);

    connect(open, SIGNAL(clicked()), this, SLOT(openQssFile()));
    connect(save, SIGNAL(clicked()), this, SLOT(saveQssFile()));
    connect(apply_style, SIGNAL(clicked()), this, SLOT(applyQssFile()));
}
void MainWindow::setupElementsPanel()
{
    // Add QT widgets to preview panel
    QVBoxLayout *v_ly = new QVBoxLayout(elementsPanel);

    testButton = new QPushButton(elementsPanel);
    testCheckBox_1 = new QCheckBox(elementsPanel);
    /*QWidget*/
    testLabel = new QLabel(elementsPanel);
    testLineEdit = new QLineEdit(elementsPanel);
    testTextEdit = new QTextEdit(elementsPanel);
    testRadioButton_1 = new QRadioButton(elementsPanel);
    testComboBox = new QComboBox(elementsPanel);
    /*QSlider * */
    testProgressBar = new QProgressBar(elementsPanel);
    testSpinBox = new QSpinBox(elementsPanel);
    testDial = new QDial(elementsPanel);
    testCalendar = new QCalendarWidget(elementsPanel);
    /*QScrollBar * test*/
    // QScrollArea
    // QToolButton
    // QMenu
    // QMenuBar
    // QTabWidget
    // QTabBar
    // QToolTip
    // QGroupBox
    // QFrame
    // QListView
    // QListWidget
    // QTreeView
    // QTreeWidget
    // QTableView
    // QTableWidget
    // QHeaderView
    // QToolBar
    // QStatusBar
    // QCalendarWidget
    // QMessageBox
    // QSplitter
    // QPlainTextEdit
    // QAbstractItemView
    // QAbstractButton
    // QDialogButtonBox
    v_ly->addWidget(testButton);
    v_ly->addWidget(testCheckBox_1);
    v_ly->addWidget(testLabel);
    v_ly->addWidget(testLineEdit);
    v_ly->addWidget(testTextEdit);
    v_ly->addWidget(testRadioButton_1);
    v_ly->addWidget(testComboBox);
    v_ly->addWidget(testProgressBar);
    v_ly->addWidget(testSpinBox);
    v_ly->addWidget(testDial);
    v_ly->addWidget(testCalendar);

    elementsPanel->setLayout(v_ly);
}
void MainWindow::setTexts()
{
    testButton->setText(tr("Test Button"));
    testCheckBox_1->setText(tr("Test Check Box"));

    testLabel->setText(tr("Test Label"));
    testLineEdit->setText(tr("Test Line Edit"));
    testTextEdit->setText(tr("Test Text Edit"));
    testRadioButton_1->setText(tr("Test Radio Button 1"));
    /*testComboBox->setText(tr("Test Combo BOx"));*/
    testProgressBar->setFormat("Test Progress Bar");
    testProgressBar->setValue(10);
    /*testSpinBox->set;*/
}

void MainWindow::openQssFile() { 
    qDebug() << "open Qss File"; 
    QString fileName = QFileDialog::getOpenFileName(this, 
                        "Open file", 
                        "", 
                        "Qss Files (*.qss);;All Files (*)");

    if (fileName.isEmpty()) {
        return; 
    }

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Couldn't open file for reading.");
        return;
    }

    QTextStream in(&file);
    QString fileContent = in.readAll();

    file.close();
    
    qssEditor->setText(fileContent);
}
void MainWindow::saveQssFile()
{
    qDebug() << "save Qss File";
    // QFileDialog dialog(this);
    // dialog.setNameFilter(tr("QSS (*.qss)"));
    QString fileName = QFileDialog::getSaveFileName(this, 
                        "Save file", 
                        "", 
                        "Qss Files (*.qss);;All Files (*)");

    if (fileName.isEmpty()) {
        return; 
    }

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Couldn't open file for writing.");
        return;
    }

    QTextStream out(&file);
    QString text = qssEditor->toPlainText();
    out << text;

    file.close();
}

void MainWindow::applyQssFile()
{
    qDebug() << "Apply Style";
    QString text = qssEditor->toPlainText();
    elementsPanel->setStyleSheet(text);
}
