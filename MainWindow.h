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

protected:
    QWidget *editorPanel;
    QssWidgetsPreview *elementsPanel;

    QssTextEditor *editor;

    void setTexts();
    void setupEditorPanel();
    void setupElementsPanel();
};
#endif
