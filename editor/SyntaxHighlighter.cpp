#include "SyntaxHighlighter.h"
#include <QFont>
#include <QDebug>

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(Qt::blue);
    keywordFormat.setFontWeight(QFont::Bold);

    QTextCharFormat modifFormat;
    modifFormat.setForeground(Qt::magenta);
    /*modifFormat.setFontWeight(QFont::italic);*/

    QStringList keywordPatterns = {"\\bQPushButton\\b",
                                   "\\bQComboBox\\b",
                                   "\\bQLabel\\b",
                                   "\\bQCheckBox\\b",
                                   "\\bQProgressBar\\b",
                                   "\\bQSlider\\b",
                                   "\\bQAbstractSpinBox\\b",
                                   "\\bQTabBar\\b",
                                   "\\bQTableView\\b",
                                   "\\bQHeaderView\\b",
                                   "\\bQAbstractItemView\\b",
                                   "\\bQAbstractButton\\b",
                                   "\\bQScrollBar\\b",
                                   "\\bQGroupBox\\b",
                                   "\\bQWidget\\b",
                                   "\\bQDial\\b",
                                   "\\bQRadioButton\\b"};
    QStringList modificatorPattrens = {};
    modificatorPattrens
        // alignment
        << "top" << "bottom" << "left" << "right"
        << "center"

        // attachment
        << "scroll"
        << "fixed"

        // border image
        << "none" << "stretch"
        << "repeat"

        // border style
        << "dashed" << "dot-dash" << "dot-dot-dash" << "dotted" << "double"
        << "inset" << "outset" << "ridge" << "solid"
        << "none"

        // font
        << "normal" << "italic" << "oblique"
        << "bold"

        // gradients
        << "qlineargradient" << "qradialgradient"
        << "qconicalgradient"

        // origin
        << "margin" << "border" << "padding"
        << "content"

        // palette role
        << "alternate-base" << "base" << "bright-text" << "button"
        << "button-text" << "dark" << "highlight" << "highlighted-text"
        << "light" << "link" << "link-visited" << "mid" << "midlight"
        << "shadow" << "text" << "window"
        << "window-text"

        // repeat
        << "repeat" << "repeat-x" << "repeat-y" << "no-repeat";
    for (const QString &pattern : keywordPatterns)
    {
        rules.append({QRegularExpression(pattern), keywordFormat});
    }

    for (const QString &pattern : modificatorPattrens)
        rules.append({QRegularExpression(pattern), modifFormat});

    QTextCharFormat quotationFormat;
    quotationFormat.setForeground(Qt::darkGreen);
    rules.append({QRegularExpression("\".*\""), quotationFormat});

    QTextCharFormat commentFormat;
    commentFormat.setForeground(Qt::darkGray);
    commentFormat.setFontItalic(true);
    rules.append({QRegularExpression("//[^\n]*"), commentFormat});
}

SyntaxHighlighter::~SyntaxHighlighter() {}

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
