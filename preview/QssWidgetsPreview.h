#pragma once
#ifndef QSSWIDGETSPREVIEW_H
#define QSSWIDGETSPREVIEW_H

#include <QCalendarWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QDial>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QListWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenuBar>
#include <QPlainTextEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QTabWidget>
#include <QTableView>
#include <QTableWidget>
#include <QTextEdit>
#include <QToolBar>
#include <QTreeView>
#include <QTreeWidget>

class QssWidgetsPreview : public QWidget
{
    Q_OBJECT

public:
    QssWidgetsPreview(QWidget *parent);
    virtual ~QssWidgetsPreview();

    void setupWidgetsLayout();
    void setupSimpleWidgets();
    void setupTreeWidgets();
    void setupTextEditWidgets();
    void setupListWidgets();
    void setTexts();
    void populateTree(QTreeWidgetItem *parent, const QString &path);

protected:
    QMdiArea *testMdiArea;
    QMdiSubWindow *testSubWindow;
    QWidget *simpleWidgets;
    QWidget *treeWidgets;
    QWidget *textEditWidgets;
    QWidget *listWidgets;

    QGroupBox *checkGroup;
    QCheckBox *testCheckBox_1;
    QCheckBox *testCheckBox_2;
    QCheckBox *testCheckBox_3;

    QLabel *testLabel;
    QLineEdit *testLineEdit;

    QGroupBox *radioGroup;
    QRadioButton *testRadioButton_1;
    QRadioButton *testRadioButton_2;
    QRadioButton *testRadioButton_3;
    QComboBox *testComboBox;
    /*QSlider * */
    QProgressBar *testProgressBar;
    QSpinBox *testSpinBox;
    QDial *testDial;
    QCalendarWidget *testCalendar;

    QMenuBar *testMenuBar;
    QTabWidget *testTabWidget;

    QToolBar *testToolBar;
    QTextEdit *testTextEdit;
    QPlainTextEdit *testPlainTextEdit;

    QGroupBox *buttonsGroup;
    QPushButton *questionButton;
    QPushButton *infoButton;
    QPushButton *warningButton;
    QPushButton *errorButton;

    QListView *testListView;

    QListWidget *testListWidget;

    QTreeView *testTreeView;
    QTreeWidget *testTreeWidget;
    QTableView *testTableView;
    QTableWidget *testTableWidget;
};
#endif /* QSSWIDGETSPREVIEW_H */
