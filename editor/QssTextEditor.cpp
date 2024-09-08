#include "QssTextEditor.h"
#include "LineNumberArea.h"
#include <QDebug>
#include <QPainter>
#include <QTextBlock>
#include <QWidget>

QssTextEditor::QssTextEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    setPlainText("QssTextEditor");
    lineNumberArea = new LineNumberArea(this);
    /*colorPreviewArea = new */
    connect(this, &QssTextEditor::blockCountChanged, this,
            &QssTextEditor::updateLineNumberAreaWidth);
    connect(this, &QssTextEditor::updateRequest, this,
            &QssTextEditor::updateLineNumberArea);
    connect(this, &QssTextEditor::cursorPositionChanged, this,
            &QssTextEditor::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();

    highlighter = new SyntaxHighlighter(this->document());

    connect(this, &QPlainTextEdit::textChanged, this,
           &QssTextEditor::highlightColors);
}

QssTextEditor::~QssTextEditor() { qDebug() << "Destructor"; }

void QssTextEditor::lineNumberAreaPaintEvent(QPaintEvent *ev)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(ev->rect(), Qt::lightGray);

    QTextBlock block = this->firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top =
        qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= ev->rect().bottom())
    {
        if (block.isVisible() && bottom >= ev->rect().top())
        {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(),
                             fontMetrics().height(), Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

int QssTextEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10)
    {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void QssTextEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(
        QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}
void QssTextEditor::paintEvent(QPaintEvent *event)
{
    QPlainTextEdit::paintEvent(event);

    QPainter painter(viewport());

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = static_cast<int>(
        blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + static_cast<int>(blockBoundingRect(block).height());

    while (block.isValid() && top <= viewport()->rect().bottom())
    {
        if (block.isVisible() && bottom >= viewport()->rect().top())
        {
            QString text = block.text();
            drawColorPreview(painter, text, top);
        }

        block = block.next();
        top = bottom;
        bottom = top + static_cast<int>(blockBoundingRect(block).height());
        ++blockNumber;
    }
}
void QssTextEditor::drawColorPreview(QPainter &painter, const QString &text,
                                     int yPosition)
{
    QRegularExpression hexColorRegex("#([A-Fa-f0-9]{6}|[A-Fa-f0-9]{3})");
    QRegularExpressionMatch match = hexColorRegex.match(text);

    if (match.hasMatch())
    {
        QString hexColor = match.captured(0);
        QColor color(hexColor);

        if (color.isValid())
        {
            QRect colorRect(viewport()->width() - 30, yPosition, 20,
                            20); // Позиция и размер квадрата
            painter.fillRect(colorRect, color);
            painter.drawRect(colorRect);
        }
    }
}

void QssTextEditor::updateLineNumberAreaWidth(int newBlockCount)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void QssTextEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly())
    {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void QssTextEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(),
                               rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void QssTextEditor::highlightColors() { viewport()->update(); }
