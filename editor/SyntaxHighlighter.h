#pragma once
#ifndef SYNTAX_HIGHLIGHTER_H

#include "qobjectdefs.h"
#include "qsyntaxhighlighter.h"
#include <QRegularExpression>
#include <QSyntaxHighlighter>
#include <QTextDocument>

class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    SyntaxHighlighter(QTextDocument *parent = nullptr);
    ~SyntaxHighlighter();

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> rules;
};

#endif
