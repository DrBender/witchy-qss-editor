#pragma once
#include "qradiobutton.h"
#ifndef QSSWIDGETSPREVIEW_H
#define QSSWIDGETSPREVIEW_H

#include "qobjectdefs.h"

#include "qwidget.h"

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
    void setTexts();

protected:
    QMdiArea *testMdiArea;
    QMdiSubWindow *testSubWindow;

    QPushButton *testButton;
    QCheckBox *testCheckBox_1;
    QLabel *testLabel;
    QLineEdit *testLineEdit;

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

    QGroupBox *messageGroup;
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
