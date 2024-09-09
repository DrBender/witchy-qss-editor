#pragma once
#ifndef QSSTEXTEDITOR_H
#define QSSTEXTEDITOR_H

#include <QPlainTextEdit>
#include "Parser.h"
#include "SyntaxHighlighter.h"

class QssTextEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    QssTextEditor(QWidget *parent = nullptr);

    virtual ~QssTextEditor();

    void lineNumberAreaPaintEvent(QPaintEvent *ev);
    int lineNumberAreaWidth();
    Parser parser;

protected:
    void resizeEvent(QResizeEvent *e) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QWidget *lineNumberArea;
    QWidget *colorPreviewArea;
    SyntaxHighlighter *highlighter;

    void drawColorPreview(QPainter &painter, const QString &text,
                          int yPosition);

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);

    void highlightColors();
};

#endif /* QSSTEXTEDITOR_H */
