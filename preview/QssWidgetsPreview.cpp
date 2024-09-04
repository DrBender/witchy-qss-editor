#include "QssWidgetsPreview.h"
#include "qboxlayout.h"
#include "qcheckbox.h"
#include "qgroupbox.h"
#include "qmainwindow.h"
#include "qmdiarea.h"
#include "qplaintextedit.h"
#include "qtabwidget.h"
#include "qtoolbar.h"
#include "qwidget.h"
#include <QDebug>
#include <QVBoxLayout>

QssWidgetsPreview::QssWidgetsPreview(QWidget *parent) : QWidget(parent)
{
    qDebug() << "QssWidgetsPreview";

    //
    testMdiArea = new QMdiArea(this);
    testSubWindow = new QMdiSubWindow();

    testMdiArea->addSubWindow(testSubWindow);

    testButton = new QPushButton(this);
    testCheckBox_1 = new QCheckBox(this);
    testLabel = new QLabel(this);
    testLineEdit = new QLineEdit(this);
    testRadioButton_1 = new QRadioButton(this);
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

    messageGroup = new QGroupBox(testSubWindow);
    questionButton = new QPushButton(testSubWindow);
    infoButton = new QPushButton(testSubWindow);
    warningButton = new QPushButton(testSubWindow);
    errorButton = new QPushButton(testSubWindow);

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
    QVBoxLayout *v_ly = new QVBoxLayout(internalWidget);

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

    QWidget *simpleWidgets = new QWidget(testTabWidget);
    QWidget *treeWidgets = new QWidget(testTabWidget);
    QWidget *textEditWidgets = new QWidget(testTabWidget);
    QWidget *tableWidgets = new QWidget(testTabWidget);
    QWidget *groupWidgets = new QWidget(testTabWidget);
    testTabWidget->clear();
    testTabWidget->addTab(simpleWidgets, "Simple Widgets");
    testTabWidget->addTab(treeWidgets, "Tree Widgets");
    testTabWidget->addTab(textEditWidgets, "Text Edit");
    testTabWidget->addTab(tableWidgets, "Table Widgets");
    testTabWidget->addTab(groupWidgets, "Group Widgets");
    /*QScrollBar * test*/
    // QScrollArea
    // QToolButton
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

    // QToolBar
    // QStatusBar
    // QMessageBox
    // QSplitter
    // QAbstractItemView
    // QDialogButtonBox
    internal_layout->addWidget(testMenuBar);
    internal_layout->addWidget(testTabWidget);

    v_ly->addWidget(testButton);
    v_ly->addWidget(testCheckBox_1);
    v_ly->addWidget(testLabel);
    v_ly->addWidget(testLineEdit);
    v_ly->addWidget(testRadioButton_1);
    v_ly->addWidget(testComboBox);
    v_ly->addWidget(testProgressBar);
    v_ly->addWidget(testSpinBox);
    v_ly->addWidget(testDial);
    v_ly->addWidget(testCalendar);
    simpleWidgets->setLayout(v_ly);

    QVBoxLayout *text_layout = new QVBoxLayout(internalWidget);
    text_layout->addWidget(testToolBar);
    text_layout->addWidget(testTextEdit);
    text_layout->addWidget(testPlainTextEdit);
    textEditWidgets->setLayout(text_layout);

    internalWidget->setLayout(internal_layout);
    /*this->setLayout(v_ly);*/
    this->setLayout(mdiLayout);
}

void QssWidgetsPreview::setTexts()
{
    const QStringList comboItems = {tr("Item 1"), tr("Item 2"), tr("Item 3")};

    testButton->setText(tr("Test Button"));
    testCheckBox_1->setText(tr("Test Check Box"));

    testLabel->setText(tr("Test Label"));
    testLineEdit->setText(tr("Test Line Edit"));
    testTextEdit->setText(tr("Test Text Edit"));
    testRadioButton_1->setText(tr("Test Radio Button 1"));
    testProgressBar->setFormat("Test Progress Bar");
    testProgressBar->setValue(10);
    /*testSpinBox->set;*/
    testComboBox->clear();
    testComboBox->addItems(comboItems);

    testPlainTextEdit->setPlainText("Plain Text Edit");
}
