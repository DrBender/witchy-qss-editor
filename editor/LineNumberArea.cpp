#include "LineNumberArea.h"

LineNumberArea::LineNumberArea(QssTextEditor *ed) : QWidget(ed), editor(ed) {}

LineNumberArea::~LineNumberArea() {}

void LineNumberArea::paintEvent(QPaintEvent *ev)
{
    editor->lineNumberAreaPaintEvent(ev);
}
