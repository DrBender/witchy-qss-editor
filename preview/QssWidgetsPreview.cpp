#include "QssWidgetsPreview.h"
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QStringListModel>
#include <QVBoxLayout>

QssWidgetsPreview::QssWidgetsPreview(QWidget *parent) : QWidget(parent)
{
    qDebug() << "QssWidgetsPreview";

    //
    testMdiArea = new QMdiArea(this);
    testSubWindow = new QMdiSubWindow();

    testMdiArea->addSubWindow(testSubWindow);
    testSubWindow->showMaximized();
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
    questionButton = new QPushButton(buttonsGroup);
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
    setupTreeWidgets();
    setupTextEditWidgets();
    setupListWidgets();
    QWidget *tableWidgets = new QWidget(testTabWidget);

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

    buttonsGroup->setLayout(new QHBoxLayout(buttonsGroup));
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
    v_ly->addWidget(testLabel);
    v_ly->addWidget(testLineEdit);
    v_ly->addWidget(radioGroup);
    v_ly->addWidget(testComboBox);
    v_ly->addWidget(testProgressBar);
    v_ly->addWidget(testSpinBox);
    v_ly->addWidget(testDial);
    v_ly->addWidget(testCalendar);
    simpleWidgets->setLayout(v_ly);
}

void QssWidgetsPreview::setupTreeWidgets()
{

    treeWidgets = new QWidget(testTabWidget);

    treeWidgets->setLayout(new QVBoxLayout(testTabWidget));
    treeWidgets->layout()->addWidget(testTreeView);
    treeWidgets->layout()->addWidget(testTreeWidget);

    testTreeWidget->setColumnCount(1);
    testTreeWidget->setHeaderLabel("File System");

    QTreeWidgetItem *root = new QTreeWidgetItem(testTreeWidget);
    root->setText(0, QDir::currentPath());

    populateTree(root, QDir::currentPath());

    testTreeWidget->expandAll();
    testTreeWidget->show();

    QFileSystemModel *model = new QFileSystemModel(testTabWidget);
    /*model->setRootPath(QDir::rootPath());*/
    model->setRootPath(QDir::currentPath());

    testTreeView->setModel(model);
    /*testTreeView->setRootIndex(model->index(QDir::rootPath()));*/
    testTreeView->setRootIndex(model->index(QDir::currentPath()));

    testTreeView->show();
}

void QssWidgetsPreview::setupTextEditWidgets()
{
    QString text =
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do "
        "eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim "
        "ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut "
        "aliquip ex ea commodo consequat. Duis aute irure dolor in "
        "reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla "
        "pariatur. Excepteur sint occaecat cupidatat non proident, sunt in "
        "culpa qui officia deserunt mollit anim id est laborum.";
    textEditWidgets = new QWidget(testTabWidget);
    textEditWidgets->setLayout(new QVBoxLayout(textEditWidgets));
    textEditWidgets->layout()->addWidget(testToolBar);
    textEditWidgets->layout()->addWidget(testTextEdit);
    textEditWidgets->layout()->addWidget(testPlainTextEdit);

    testTextEdit->setText(text);
    testPlainTextEdit->setPlainText(text);
}

void QssWidgetsPreview::setupListWidgets()
{

    listWidgets = new QWidget(testTabWidget);

    listWidgets->setLayout(new QHBoxLayout(listWidgets));
    listWidgets->layout()->addWidget(testListView);
    listWidgets->layout()->addWidget(testListWidget);

    QStringList items;
    items << "Item 1" << "Item 2" << "Item 3" << "Item 4";

    QStringListModel *model = new QStringListModel(items);

    testListView->setModel(model);
    testListView->show();

    testListWidget->addItem("Item 1");
    testListWidget->addItem("Item 2");
    testListWidget->addItem("Item 3");

    testListWidget->show();
}

void QssWidgetsPreview::setTexts()
{
    const QStringList comboItems = {tr("Item 1"), tr("Item 2"), tr("Item 3")};
    QString text =
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do "
        "eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim "
        "ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut "
        "aliquip ex ea commodo consequat. Duis aute irure dolor in "
        "reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla "
        "pariatur. Excepteur sint occaecat cupidatat non proident, sunt in "
        "culpa qui officia deserunt mollit anim id est laborum.";
    checkGroup->setTitle(tr("CheckBox Group"));
    testCheckBox_1->setText(tr("Test Check Box 1"));
    testCheckBox_2->setText(tr("Test Check Box 2"));
    testCheckBox_3->setText(tr("Test Check Box 3"));

    testLabel->setText(tr("Test Label"));
    testLineEdit->setText(tr("Test Line Edit"));
    testTextEdit->setText(text);

    radioGroup->setTitle(tr("Radio Group"));
    testRadioButton_1->setText(tr("Test Radio Button 1"));
    testRadioButton_2->setText(tr("Test Radio Button 2"));
    testRadioButton_3->setText(tr("Test Radio Button 3"));

    testProgressBar->setFormat("Test Progress Bar");
    testProgressBar->setValue(10);
    /*testSpinBox->set;*/
    testComboBox->clear();
    testComboBox->addItems(comboItems);

    testPlainTextEdit->setPlainText(text);

    buttonsGroup->setTitle(tr("QT Messages"));

    questionButton->setText(tr("Question"));
    infoButton->setText(tr("Information"));
    warningButton->setText(tr("Warning"));
    errorButton->setText(tr("Error"));
}

void QssWidgetsPreview::populateTree(QTreeWidgetItem *parent,
                                     const QString &path)
{
    QDir dir(path);
    QDirIterator it(path, QDir::NoDotAndDotDot | QDir::AllEntries);
    while (it.hasNext())
    {
        it.next();
        QTreeWidgetItem *item = new QTreeWidgetItem(parent);
        item->setText(0, it.fileName());
        if (it.fileInfo().isDir())
        {
            populateTree(item, it.filePath());
        }
    }
}
