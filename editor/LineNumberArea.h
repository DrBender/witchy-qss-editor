#pragma once
#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H
#include "qevent.h"
#include "qobjectdefs.h"
#include "qwidget.h"
#include <QWidget>
#include "QssTextEditor.h"

class LineNumberArea : public QWidget
{
    Q_OBJECT

public:
    LineNumberArea(QssTextEditor * ed);
    ~LineNumberArea();
    QSize sizeHint() const override
    {
        return QSize(editor->lineNumberAreaWidth(), 0);
    }
protected:
    void paintEvent(QPaintEvent *ev) override;

private:
    QssTextEditor *editor;
};
#endif /* LINENUMBERAREA_H */
