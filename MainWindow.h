#include "QssTextEditor.h"
#include "qobjectdefs.h"
#include <QCalendarWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QDial>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QTextEdit>
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
