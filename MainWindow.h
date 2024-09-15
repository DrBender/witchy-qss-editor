#pragma once
#include <qchar.h>
#include <qfileinfo.h>
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QssTextEditor.h"
#include "QssWidgetsPreview.h"
#include <QMainWindow>

class Session
{
    QString currentFilePath;
    QFileInfo info;

public:
    Session() : currentFilePath(""), info("") {}
    void setCurrentFilePath(const QString &path)
    {
        if (QFileInfo(path).exists())
        {
            currentFilePath = path;
            info = QFileInfo(currentFilePath);
        }
        else
        {
            qDebug() << "Session: file path " << path << " doesn't exist";
        }
    }
    QString fileName() { return info.fileName(); }
    QString currentDir() { return info.path(); }
    QString getCurrentFilePath() { return currentFilePath; }
    /*void closeCurrentFile();*/
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
public slots:

    void openNewFile();
    void openQssFile();
    void saveQssFile();
    void applyQssFile();
    void clearWidgetsQss();
    void reformatQssFile();
    void showColorsPanel(bool checked);
    void saveSettings();
    void loadSettings();

protected:
    QString windowTitle;
    QWidget *editorPanel;
    QssWidgetsPreview *elementsPanel;

    QssTextEditor *editor;

    Session session;

    void setTexts();
    void setupMenuBar();
    void setupEditorPanel();
    void setupElementsPanel();

    void closeEvent(QCloseEvent *event) override;
};
#endif
