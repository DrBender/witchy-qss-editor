#pragma once
#ifndef AST_H
#define AST_H

#include "qchar.h"
#include "qglobal.h"
#include "qlist.h"
#include <qt5/QtCore/qchar.h>
#include <QDebug>
#include <QString>
#include <QTextStream>
#include <QVector>
#include <memory>

// Base class for all ATS nodes
class ASTNode
{
public:
    virtual ~ASTNode() = default;
    virtual QString toString() const = 0;
};

// Node for selectors (QPushButton, QWidget#myWidget etc.)
class SelectorNode : public ASTNode
{
    QString selector;

public:
    SelectorNode(const QString &selector) : selector(selector) {}

    QString toString() const override { return selector; }
};

// Node for properties (color, font-size etc.)
class PropertyNode : public ASTNode
{
    QString property;
    QString value;

public:
    PropertyNode(const QString &property, const QString &value)
        : property(property), value(value)
    {
    }

    QString toString() const override { return property + ": " + value + ";"; }
};

// Node for rule (selector + properties/comments)
class RuleNode : public ASTNode
{
    std::shared_ptr<SelectorNode> selector;
    QVector<std::shared_ptr<ASTNode>> children;

public:
    RuleNode(std::shared_ptr<SelectorNode> selector) : selector(selector) {}

    void addChild(std::shared_ptr<ASTNode> child)
    {
        children.append(child);
    }

    QString toString() const override
    {
        QString result = selector->toString() + " {\n";
        for (const auto &prop : children)
        {
            result += "    " + prop->toString() + "\n";
        }
        result += "}\n";
        return result;
    }
};

class CommentNode : public ASTNode
{
    QString comment;

public:
    CommentNode(const QString &comm) : comment(comm){};
    QString toString() const override { return comment; }
};

class StyleSheetNode : public ASTNode
{
    QVector<std::shared_ptr<ASTNode>> children;

public:
    void addChild(std::shared_ptr<ASTNode> child) { children.append(child); }

    QString toString() const override
    {
        QString result;
        for (const auto &child : children)
        {
            result += child->toString() + "\n";
        }
        return result;
    }
};

#endif /* AST_H */
