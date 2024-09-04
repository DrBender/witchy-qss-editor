#include "QssWidgetsPreview.h"
#include "qcheckbox.h"
#include "qwidget.h"
#include <QDebug>
#include <QVBoxLayout>

QssWidgetsPreview::QssWidgetsPreview(QWidget *parent) : QWidget(parent)
{
    qDebug() << "QssWidgetsPreview";

    //
    testButton = new QPushButton(this);
    testCheckBox_1 = new QCheckBox(this);
    testLabel = new QLabel(this);
    testLineEdit = new QLineEdit(this);
    testTextEdit = new QTextEdit(this);
    testRadioButton_1 = new QRadioButton(this);
    testComboBox = new QComboBox(this);
    /*QSlider * */
    testProgressBar = new QProgressBar(this);
    testSpinBox = new QSpinBox(this);
    testDial = new QDial(this);
    testCalendar = new QCalendarWidget(this);


    setupWidgetsLayout();
    setTexts();
}

QssWidgetsPreview::~QssWidgetsPreview() { qDebug() << "~QssWidgetsPreview"; }

void QssWidgetsPreview::setupWidgetsLayout()
{
    // Add QT widgets to preview panel
    QVBoxLayout *v_ly = new QVBoxLayout(this);

    /*QWidget*/
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

    // QToolBar
    // QStatusBar
    // QMessageBox
    // QSplitter
    // QPlainTextEdit
    // QAbstractItemView
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

    this->setLayout(v_ly);
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
}
