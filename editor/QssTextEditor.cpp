#include "QssTextEditor.h"
#include <QDebug>
#include <QWidget>

QssTextEditor::QssTextEditor(QWidget *parent) : QPlainTextEdit(parent) 
{
    setPlainText("QssTextEditor");
}

QssTextEditor::~QssTextEditor()
{
    qDebug() << "Destructor";
}

void QssTextEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    /*lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));*/
}
