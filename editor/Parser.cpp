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
        if (((start_comm < open_brace) || (open_brace < 0)) &&
            (start_comm >= 0))
        {
            // parse comment
            if ((end_comm >= 0) && (start_comm < end_comm))
            {
                QString comm = text.mid(start_comm, end_comm + 2 - start_comm);
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
            QString select = text.mid(cur_pos, open_brace - cur_pos).trimmed();

            auto rule = std::make_shared<RuleNode>(
                std::make_shared<SelectorNode>(select));
            int close = text.indexOf("}", cur_pos);
            QString properies =
                text.mid(open_brace + 1, close - open_brace - 1);

            int error = parseProperties(rule, text, open_brace, close);

            if (error < 0)
                break;
            styleSheet->addChild(rule);
            cur_pos = close + 1;
        }
        if (cur_pos >= text.size())
            break;
    }

    parsed_text = styleSheet->toString();

    return tokens;
}

int Parser::parseProperties(std::shared_ptr<RuleNode> rule, const QString &text,
                            int start, int end)
{
    // QStringList props = text.mid(start + 1, end - start - 1).split(';');
    // for (auto &p : props)
    // {
    //     QStringList k_v = p.trimmed().split(':');
    //     qDebug() << "k_b = " << k_v;
    //     if (k_v.size() != 2)
    //         continue;
    //     QString propert = k_v.first().trimmed();
    //     QString value = k_v.last().trimmed();
    //     auto pr = std::make_shared<PropertyNode>(propert, value);
    //     rule->addChild(pr);
    // }
    int pos = start + 1;
    while (true)
    {
        if (pos >= end)
            break;
        int start_comm = text.indexOf("/*", pos);
        if (start_comm > end)
            start_comm = -1;
        int end_comm = text.indexOf("*/", pos);
        if (end_comm > end)
            end_comm = -1;
        int prop_sep = text.indexOf(":", pos);
        if (prop_sep > end)
            prop_sep = -1;
        int prop_end = text.indexOf(";", pos);
        if (prop_end > end)
            prop_end = -1;

        if ((prop_sep < 0) || (prop_end < 0))
            break; // no properties
        if ((start_comm < 0) && (end_comm > 0))
        {
            // TODO: Syntax error
            qDebug() << "Syntax ERROR: missing opening comment";
            return -1;
        }
        if (((start_comm < 0) && (end_comm < 0)) ||
            ((prop_end < start_comm) && (prop_end < end_comm)))
        {
            // no comments in property section or comment not in current
            // propery:value section
            QString p = text.mid(pos, prop_sep - pos).trimmed();
            QString value =
                text.mid(prop_sep + 1, prop_end - prop_sep - 1).trimmed();
            auto pr = std::make_shared<PropertyNode>(p, value);
            rule->addChild(pr);
            pos = prop_end + 1;

            continue;
        }
        else if (((start_comm < prop_sep) && (end_comm < prop_sep)) ||
                 ((start_comm < prop_sep) && (end_comm > prop_sep)))
        {
            // comment in property name section
            QString left = text.mid(pos, start_comm - pos).trimmed();
            QString right =
                text.mid(end_comm + 2, prop_sep - end_comm - 2).trimmed();

            if (!left.isEmpty() && !right.isEmpty())
            {
                // forbid  property name separation
                qDebug() << "SYNAX ERROR: property name separated by comment";
                return -2;
            }
            if (!left.isEmpty())
            {
                // TODO: maybe delete in future
                //  forbid using comments after property name
                //  example:
                //  QPushButton {
                //  property /*some commentary*/; value;
                //  }
                qDebug() << "SYNTAX ERROR: comment after property name";
                return -3;
            }
            QString comm = text.mid(start_comm, end_comm + 2 - start_comm);
            qDebug() << "comment:" << comm;
            auto commentNode = std::make_shared<CommentNode>(comm);
            rule->addChild(commentNode);
            pos = end_comm + 2;
            continue;
        }
        if ((prop_sep < start_comm) && (start_comm < prop_end) &&
            (prop_sep < end_comm) && (end_comm < prop_end))
        {
            // TODO: maybe delete in future
            // forbid value separation
            // example:
            // QPushButton{
            // property: /* test */ value;
            // }
            qDebug() << "SYNTAX ERROR: value section separated by commentary";
            return -4;
        }
    }

    return 0;
}
