#pragma once
#ifndef QSSTEXTEDITOR_H
#define QSSTEXTEDITOR_H

#include "qevent.h"
#include "qobjectdefs.h"
#include <QPlainTextEdit>
#include <qt5/QtCore/qobjectdefs.h>
/*#include "LineNumberArea.h"*/
#include "SyntaxHighlighter.h"

class QssTextEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    QssTextEditor(QWidget *parent = nullptr);

    virtual ~QssTextEditor();

    void lineNumberAreaPaintEvent(QPaintEvent *ev);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *e) override;

private:
    QWidget *lineNumberArea;
    SyntaxHighlighter *highlighter;
private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);
};

#endif /* QSSTEXTEDITOR_H */
