#include "QssWidgetsPreview.h"
#include "qboxlayout.h"
#include "qcheckbox.h"
#include "qgroupbox.h"
#include "qhash.h"
#include "qlistview.h"
#include "qlistwidget.h"
#include "qmainwindow.h"
#include "qmdiarea.h"
#include "qplaintextedit.h"
#include "qradiobutton.h"
#include "qtableview.h"
#include "qtablewidget.h"
#include "qtabwidget.h"
#include "qtoolbar.h"
#include "qtreeview.h"
#include "qtreewidget.h"
#include "qwidget.h"
#include <QDebug>
#include <QMessageBox>
#include <QVBoxLayout>

QssWidgetsPreview::QssWidgetsPreview(QWidget *parent) : QWidget(parent)
{
    qDebug() << "QssWidgetsPreview";

    //
    testMdiArea = new QMdiArea(this);
    testSubWindow = new QMdiSubWindow();

    testMdiArea->addSubWindow(testSubWindow);

    testCheckBox_1 = new QCheckBox(this);
    testCheckBox_2 = new QCheckBox(this);
    testCheckBox_3 = new QCheckBox(this);
    testLabel = new QLabel(this);
    testLineEdit = new QLineEdit(this);
    testRadioButton_1 = new QRadioButton(this);
    testRadioButton_2 = new QRadioButton(this);
    testRadioButton_3 = new QRadioButton(this);
    testComboBox = new QComboBox(this);
    /*QSlider * */
    testProgressBar = new QProgressBar(this);
    testSpinBox = new QSpinBox(this);
    testDial = new QDial(this);
    testCalendar = new QCalendarWidget(this);

    testMenuBar = new QMenuBar(testSubWindow);
    testTabWidget = new QTabWidget(testSubWindow);

    testToolBar = new QToolBar(testSubWindow);
    testTextEdit = new QTextEdit(testSubWindow);
    testPlainTextEdit = new QPlainTextEdit(testSubWindow);

    buttonsGroup = new QGroupBox(testSubWindow);
    questionButton = new QPushButton(testSubWindow);
    infoButton = new QPushButton(testSubWindow);
    warningButton = new QPushButton(testSubWindow);
    errorButton = new QPushButton(testSubWindow);

    testListView = new QListView(testSubWindow);
    testListWidget = new QListWidget(testSubWindow);
    testTreeView = new QTreeView(testSubWindow);
    testTreeWidget = new QTreeWidget(testSubWindow);
    testTableView = new QTableView(testSubWindow);
    testTableWidget = new QTableWidget(testSubWindow);

    setupWidgetsLayout();
    setTexts();
}

QssWidgetsPreview::~QssWidgetsPreview() { qDebug() << "~QssWidgetsPreview"; }

void QssWidgetsPreview::setupWidgetsLayout()
{
    // Add QT widgets to preview panel
    //
    QVBoxLayout *mdiLayout = new QVBoxLayout(this);
    mdiLayout->addWidget(testMdiArea);
    QWidget *internalWidget = new QWidget(testSubWindow);
    testSubWindow->setWidget(internalWidget);
    QVBoxLayout *internal_layout = new QVBoxLayout(internalWidget);
    internal_layout->setMargin(0);

    QMenu *fileMenu = testMenuBar->addMenu("File");
    QAction *newAction = fileMenu->addAction("New");
    QAction *openAction = fileMenu->addAction("Open");

    QMenu *editMenu = testMenuBar->addMenu("Edit");
    QAction *cutAction = editMenu->addAction("Cut");
    QAction *copyAction = editMenu->addAction("Copy");
    QAction *pasteAction = editMenu->addAction("Paste");

    // Add actions to QToolBar
    QAction *action1 = testToolBar->addAction("Action 1");
    QAction *action2 = testToolBar->addAction("Action 2");

    /*QWidget *simpleWidgets = new QWidget(testTabWidget);*/
    setupSimpleWidgets();
    QWidget *treeWidgets = new QWidget(testTabWidget);
    QWidget *textEditWidgets = new QWidget(testTabWidget);
    QWidget *tableWidgets = new QWidget(testTabWidget);
    QWidget *listWidgets = new QWidget(testTabWidget);
    testTabWidget->clear();
    testTabWidget->addTab(simpleWidgets, "Simple Widgets");
    testTabWidget->addTab(treeWidgets, "Tree Widgets");
    testTabWidget->addTab(textEditWidgets, "Text Edit");
    testTabWidget->addTab(tableWidgets, "Table Widgets");
    testTabWidget->addTab(listWidgets, "List Widgets");
    /*QScrollBar * test*/
    // QScrollArea
    // QToolButton
    // QTabBar
    // QToolTip
    // QFrame

    // QStatusBar
    // QMessageBox
    // QSplitter
    // QAbstractItemView
    // QDialogButtonBox
    internal_layout->addWidget(testMenuBar);
    internal_layout->addWidget(testTabWidget);

    QVBoxLayout *text_layout = new QVBoxLayout(internalWidget);
    text_layout->addWidget(testToolBar);
    text_layout->addWidget(testTextEdit);
    text_layout->addWidget(testPlainTextEdit);
    textEditWidgets->setLayout(text_layout);

    treeWidgets->setLayout(new QVBoxLayout(internalWidget));
    treeWidgets->layout()->addWidget(testTreeView);
    treeWidgets->layout()->addWidget(testTreeWidget);

    listWidgets->setLayout(new QHBoxLayout(internalWidget));
    listWidgets->layout()->addWidget(testListView);
    listWidgets->layout()->addWidget(testListWidget);

    tableWidgets->setLayout(new QVBoxLayout(internalWidget));
    tableWidgets->layout()->addWidget(testTableView);
    tableWidgets->layout()->addWidget(testTableWidget);

    internalWidget->setLayout(internal_layout);
    /*this->setLayout(v_ly);*/
    this->setLayout(mdiLayout);
}

void QssWidgetsPreview::setupSimpleWidgets()
{

    simpleWidgets = new QWidget(testTabWidget);

    /*QVBoxLayout *v_ly = new QVBoxLayout(internalWidget);*/

    QVBoxLayout *v_ly = new QVBoxLayout(testTabWidget);
    radioGroup = new QGroupBox(testTabWidget);
    radioGroup->setLayout(new QVBoxLayout);

    radioGroup->layout()->addWidget(testRadioButton_1);
    radioGroup->layout()->addWidget(testRadioButton_2);
    radioGroup->layout()->addWidget(testRadioButton_3);

    checkGroup = new QGroupBox(testTabWidget);
    checkGroup->setLayout(new QHBoxLayout);

    checkGroup->layout()->addWidget(testCheckBox_1);
    checkGroup->layout()->addWidget(testCheckBox_2);
    checkGroup->layout()->addWidget(testCheckBox_3);

    buttonsGroup->setLayout(new QHBoxLayout);
    buttonsGroup->layout()->addWidget(questionButton);
    buttonsGroup->layout()->addWidget(infoButton);
    buttonsGroup->layout()->addWidget(warningButton);
    buttonsGroup->layout()->addWidget(errorButton);
    connect(
        questionButton, &QPushButton::clicked, this, [this]()
        { QMessageBox::question(this, "Question Message", "Some question?"); });
    connect(infoButton, &QPushButton::clicked, this,
            [this]() {
                QMessageBox::information(this, "Info Message",
                                         "Some Information");
            });
    connect(warningButton, &QPushButton::clicked, this,
            [this]() {
                QMessageBox::warning(this, "Warning Message", "Some warning!");
            });
    connect(errorButton, &QPushButton::clicked, this,
            [this]() {
                QMessageBox::critical(this, "Error Message", "Some error!!!!");
            });

    v_ly->addWidget(buttonsGroup);
    v_ly->addWidget(checkGroup);
    /*v_ly->addWidget(testCheckBox_1);*/
    v_ly->addWidget(testLabel);
    v_ly->addWidget(testLineEdit);
    /*v_ly->addWidget(testRadioButton_1);*/
    v_ly->addWidget(radioGroup);
    v_ly->addWidget(testComboBox);
    v_ly->addWidget(testProgressBar);
    v_ly->addWidget(testSpinBox);
    v_ly->addWidget(testDial);
    v_ly->addWidget(testCalendar);
    simpleWidgets->setLayout(v_ly);
}

void QssWidgetsPreview::setTexts()
{
    const QStringList comboItems = {tr("Item 1"), tr("Item 2"), tr("Item 3")};

    checkGroup->setTitle(tr("CheckBox Group"));
    testCheckBox_1->setText(tr("Test Check Box 1"));
    testCheckBox_2->setText(tr("Test Check Box 2"));
    testCheckBox_3->setText(tr("Test Check Box 3"));

    testLabel->setText(tr("Test Label"));
    testLineEdit->setText(tr("Test Line Edit"));
    testTextEdit->setText(tr("Test Text Edit"));

    radioGroup->setTitle(tr("Radio Group"));
    testRadioButton_1->setText(tr("Test Radio Button 1"));
    testRadioButton_2->setText(tr("Test Radio Button 2"));
    testRadioButton_3->setText(tr("Test Radio Button 3"));

    testProgressBar->setFormat("Test Progress Bar");
    testProgressBar->setValue(10);
    /*testSpinBox->set;*/
    testComboBox->clear();
    testComboBox->addItems(comboItems);

    testPlainTextEdit->setPlainText(tr("Plain Text Edit"));

    buttonsGroup->setTitle(tr("QT Messages"));

    questionButton->setText(tr("Question"));
    infoButton->setText(tr("Information"));
    warningButton->setText(tr("Warning"));
    errorButton->setText(tr("Error"));
}
