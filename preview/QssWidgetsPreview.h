#pragma once
#include "qgroupbox.h"
#include "qplaintextedit.h"
#include "qpushbutton.h"
#include "qtextedit.h"
#include "qtoolbar.h"
#ifndef QSSWIDGETSPREVIEW_H
#define QSSWIDGETSPREVIEW_H

#include "qobjectdefs.h"

#include "qwidget.h"

#include <QCalendarWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QDial>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenuBar>
#include <QTabWidget>
#include <QToolBar>
#include <QPlainTextEdit>
#include <QGroupBox>
#include <QListView>
#include <QListWidget>
#include <QTreeView>
#include <QTreeWidget>
#include <QTableView>
#include <QTableWidget>

class QssWidgetsPreview : public QWidget
{
    Q_OBJECT

public:
    QssWidgetsPreview(QWidget *parent);
    virtual ~QssWidgetsPreview();

    void setupWidgetsLayout();
    void setTexts();
protected:
    QMdiArea * testMdiArea;
    QMdiSubWindow * testSubWindow;

    QPushButton *testButton;
    QCheckBox *testCheckBox_1;
    QLabel *testLabel;
    QLineEdit *testLineEdit;
    /*QTextEdit *testTextEdit;*/
    QRadioButton *testRadioButton_1;
    QComboBox *testComboBox;
    /*QSlider * */
    QProgressBar *testProgressBar;
    QSpinBox *testSpinBox;
    QDial *testDial;
    QCalendarWidget *testCalendar;

    QMenuBar * testMenuBar;
    QTabWidget * testTabWidget;

    QToolBar * testToolBar;
    QTextEdit * testTextEdit;
    QPlainTextEdit * testPlainTextEdit;

    QGroupBox * messageGroup;
    QPushButton * questionButton;
    QPushButton * infoButton;
    QPushButton * warningButton;
    QPushButton * errorButton;

     QListView * testListView;

     QListWidget * testListWidget;

     QTreeView * testTreeView;
     QTreeWidget * testTreeWidget;
     QTableView * testTableView;
     QTableWidget * testTableWidget;
};
#endif /* QSSWIDGETSPREVIEW_H */
