#pragma once
#include "qchar.h"
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QssTextEditor.h"
#include "QssWidgetsPreview.h"
#include "qobjectdefs.h"
#include <QMainWindow>

class Session
{
    QString currentFilePath;
};

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
    void showColorsPanel();

protected:
    QString windowTitle;
    QWidget *editorPanel;
    QssWidgetsPreview *elementsPanel;

    QssTextEditor *editor;
    QString currentQssFilePath;

    void setTexts();
    void setupMenuBar();
    void setupEditorPanel();
    void setupElementsPanel();

    void saveSettings();
    void loadSettings();

    void closeEvent(QCloseEvent *event) override;
};
#endif
