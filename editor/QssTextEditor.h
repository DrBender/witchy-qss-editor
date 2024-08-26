#include "qobjectdefs.h"
#include <QPlainTextEdit>
#include <qt5/QtCore/qobjectdefs.h>

class QssTextEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    QssTextEditor(QWidget *parent = nullptr);

    virtual ~QssTextEditor();

protected:
    void resizeEvent(QResizeEvent *e) override;
private:
    QWidget *lineNumberArea;
};
