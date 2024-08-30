#include "Parser.h"
#include "Ast.h"
#include "qchar.h"
#include <memory>

Parser::Parser() { styleSheet = std::make_shared<StyleSheetNode>(); }

QVector<Token> Parser::parse(QString &text)
{
    // clear AST
    styleSheet.reset(new StyleSheetNode());
    qDebug() << "START PARSE";
    QVector<Token> tokens;
    int pos = 0;
    int line_pos = 0;
    int cur_pos = 0;
    QTextStream in(&text);
    QString token;
    QString comment_block;
    QString prev_line = "";
    QStringList doc_lines = text.split('\n');
    // for (const auto &line : doc_lines)
    // {
    while (true)
    {

        int start_comm = text.indexOf("/*", cur_pos);
        int end_comm = text.indexOf("*/", cur_pos);
        int open_brace = text.indexOf("{", cur_pos);
        if ((start_comm < 0) && (end_comm < 0) && (open_brace < 0))
            // there is nothing to parse
            break;
        if (((start_comm < open_brace)|| (open_brace < 0)) && (start_comm >= 0))
        {
            // parse comment
            qDebug() << "comment:" << start_comm << ":" << end_comm;
            if ((end_comm >= 0) && (start_comm < end_comm))
            {
                QString comm = text.mid(start_comm, end_comm + 2 - start_comm);
                qDebug() << "comment:"<<comm;
                auto commentNode = std::make_shared<CommentNode>(comm);
                styleSheet->addChild(commentNode);
                cur_pos = end_comm + 2;
            }
            else
            {
                // TODO: syntax error
                qDebug() << "Syntax ERROR: missing closing comment";
                break;
            }

            continue; // check if there is another comment
        }
        // getting selector
        if (open_brace > 0)
        {
            qDebug() << "j = " << open_brace << " cur_pos = " << cur_pos << "text.size =" <<text.size();
            QString select = text.mid(cur_pos, open_brace - cur_pos).trimmed();
            qDebug() << "select =" << select << "|";
            auto rule = std::make_shared<RuleNode>(
                std::make_shared<SelectorNode>(select));
            int close = text.indexOf("}", cur_pos);
            QString properies =
                text.mid(open_brace + 1, close - open_brace - 1);

            parseProperties(rule, properies);

            styleSheet->addChild(rule);
            cur_pos = close;
        }
        if (cur_pos >= text.size())
            break;
    }

    parsed_text = styleSheet->toString();

    return tokens;
}

void Parser::parseProperties(std::shared_ptr<RuleNode> rule, QString &prop_text)
{
    QStringList props = prop_text.split(';');
    for (auto &p : props)
    {
        QStringList k_v = p.trimmed().split(':');
        qDebug() << "k_b = " << k_v;
        if (k_v.size() != 2)
            continue;
        QString propert = k_v.first().trimmed();
        QString value = k_v.last().trimmed();
        auto pr = std::make_shared<PropertyNode>(propert, value);
        rule->addChild(pr);
    }
}
