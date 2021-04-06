//
// Created by Dima on 06/04/21.
//

#ifndef EXPRESSION_PARSER_EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_EXPRESSION_PARSER_H


#include <memory>
#include <string>

class Node {
public:
    virtual double Calc(double x) const = 0;
};


namespace Nodes {
    const double eps = 0.000001;

    class Operation : public Node {
    public:
        Operation(char op);
        double Calc (double x) const override;
        void SetLeft(std::shared_ptr<Node>);
        void SetRight(std::shared_ptr<Node>);
        int GetPriority() const;
        bool IsMinus() const;
        void SetPlus();

    private:
        std::shared_ptr<Node> left_{nullptr}, right_{nullptr};
        char op_;
        int priority_;
    };

    class Value : public Node {
    public:
        Value(double val);
        double Calc (double x) const override;

    private:
        double val_;
    };

    class Variable : public Node {
    public:
        Variable (bool mul_minus_one);
        double Calc (double x) const override;

    private:
        bool mul_minus_one_{false};
    };

}

class expression_parser {
public:
    expression_parser(std::string s);
    double calc(double x);

private:
    std::shared_ptr<Node> head_;
    std::string expr_;
};




#endif //EXPRESSION_PARSER_EXPRESSION_PARSER_H
