
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

class QssWidgetsPreview : public QWidget
{
    Q_OBJECT

public:
    QssWidgetsPreview(QWidget *parent);
    virtual ~QssWidgetsPreview();

    void setupWidgetsLayout();
    void setTexts();
protected:
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
    QDial *testDial;
    QCalendarWidget *testCalendar;
};
