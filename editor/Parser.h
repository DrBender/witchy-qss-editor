#pragma once
#ifndef PARSER_H
#define PARSER_H

#include "qchar.h"
#include "Ast.h"
#include <QString>
#include <QVector>

class Token
{
public:
    enum Type
    {
        Selector,
        Property,
        Value,
        Comment
    };
    Type type;
    int startPos, endPos;

    Token(Type type, int startPos, int endPos)
        : type(type), startPos(startPos), endPos(endPos)
    {
    }
};
class Parser
{
    std::shared_ptr<StyleSheetNode> styleSheet;

public:
    Parser();
    QString parsed_text;

    QVector<Token> tokens;
    QVector<Token> parse(QString &text);
    int parseProperties(std::shared_ptr<RuleNode> rule,
                        const QString &prop_text, int start, int end);
};

#endif /* PARSER_H */
