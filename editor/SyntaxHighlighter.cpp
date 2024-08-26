#include "SyntaxHighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(Qt::blue);
    keywordFormat.setFontWeight(QFont::Bold);

    QStringList keywordPatterns = {"\\bQPushButton\\b",
        "\\bQComboBox\\b", "\\bQLabel\\b",
                                   "\\bQDial\\b", "\\bQRadioButton\\b"};

    for (const QString &pattern : keywordPatterns)
    {
        rules.append({QRegularExpression(pattern), keywordFormat});
    }

    QTextCharFormat quotationFormat;
    quotationFormat.setForeground(Qt::darkGreen);
    rules.append({QRegularExpression("\".*\""), quotationFormat});

    QTextCharFormat commentFormat;
    commentFormat.setForeground(Qt::darkGray);
    commentFormat.setFontItalic(true);
    rules.append({QRegularExpression("//[^\n]*"), commentFormat});
}

SyntaxHighlighter::~SyntaxHighlighter()
{

}

void SyntaxHighlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : qAsConst(rules))
    {
        QRegularExpression expression(rule.pattern);
        QRegularExpressionMatchIterator matchIterator =
            expression.globalMatch(text);
        while (matchIterator.hasNext())
        {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(),
                      rule.format);
        }
    }
}
