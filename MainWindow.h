#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QssTextEditor.h"
#include "qobjectdefs.h"
#include <QMainWindow>
#include "QssWidgetsPreview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
public slots:
    void openQssFile();
    void saveQssFile();
    void applyQssFile();
    void reformatQssFile();

protected:
    QWidget *editorPanel;
    QssWidgetsPreview *elementsPanel;

    QssTextEditor *editor;
    QString currentQssFile;

    void setTexts();
    void setupEditorPanel();
    void setupElementsPanel();

    void saveSettings();
    void loadSettings();


    void closeEvent(QCloseEvent *event) override; 
};
#endif
