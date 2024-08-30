#pragma once
#include "qchar.h"
#ifndef PARSER_H
#define PARSER_H

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
    QVector<Token> parse(QString &text);
    void parseProperties(std::shared_ptr<RuleNode> rule, QString &prop_text);
};

#endif /* PARSER_H */
