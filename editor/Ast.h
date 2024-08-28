#pragma once
#ifndef AST_H
#define AST_H

#include <memory>
#include <QString>
#include <QVector>

// Base class for all ATS nodes
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual QString toString() const = 0;
};

// Node for selectors (QPushButton, QWidget#myWidget etc.)
class SelectorNode : public ASTNode {
    QString selector;

public:
    SelectorNode(const QString& selector) : selector(selector) {}

    QString toString() const override {
        return selector;
    }
};

// Node for properties (color, font-size etc.)
class PropertyNode : public ASTNode {
    QString property;
    QString value;

public:
    PropertyNode(const QString& property, const QString& value)
        : property(property), value(value) {}

    QString toString() const override {
        return property + ": " + value + ";";
    }
};

// Node for rule (selector + properties)
class RuleNode : public ASTNode {
    std::shared_ptr<SelectorNode> selector;
    QVector<std::shared_ptr<PropertyNode>> properties;

public:
    RuleNode(std::shared_ptr<SelectorNode> selector) : selector(selector) {}

    void addProperty(std::shared_ptr<PropertyNode> property) {
        properties.append(property);
    }

    QString toString() const override {
        QString result = selector->toString() + " {\n";
        for (const auto& prop : properties) {
            result += "  " + prop->toString() + "\n";
        }
        result += "}";
        return result;
    }
};


class StyleSheetNode : public ASTNode {
    QVector<std::shared_ptr<RuleNode>> rules;

public:
    void addRule(std::shared_ptr<RuleNode> rule) {
        rules.append(rule);
    }

    QString toString() const override {
        QString result;
        for (const auto& rule : rules) {
            result += rule->toString() + "\n";
        }
        return result;
    }
};


class Token {
public:
    enum Type { Selector, Property, Value, Comment };
    Type type;
    int startPos, endPos;

    Token(Type type, int startPos, int endPos)
        : type(type), startPos(startPos), endPos(endPos) {}
};

class Parser {
public:
    QVector<Token> parse(const QString& text, std::shared_ptr<StyleSheetNode> styleSheet) {
        QVector<Token> tokens;
        int pos = 0;
        // Пример простого парсера. Нужно реализовать разбор и построение AST
        // на основе текста QSS. Добавляем найденные токены в список.

        // Здесь будут функции для обработки селекторов, свойств и т.д.
        // Например:
        // - распознать селектор и добавить его как SelectorNode
        // - распознать свойства и их значения как PropertyNode

        return tokens;
    }
};

#endif /* AST_H */
