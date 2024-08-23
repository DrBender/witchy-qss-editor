#include "qlocale.h"
#include "qobjectdefs.h"
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QDial>
#include <QCalendarWidget>

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
    QWidget *elementsPanel;

    QTextEdit *qssEditor;

    QPushButton *testButton;
    QCheckBox *testCheckBox_1;
    QLabel *testLabel;
    QLineEdit *testLineEdit;
    QTextEdit *testTextEdit;
    QRadioButton *testRadioButton_1;
    QComboBox *testComboBox;
    /*QSlider * */
    QProgressBar *testProgressBar;
    QSpinBox *testSpinBox;
    QDial * testDial;
    QCalendarWidget * testCalendar;

    void setTexts();
    void setupEditorPanel();
    void setupElementsPanel();
};
