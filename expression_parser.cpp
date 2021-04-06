//
// Created by Dima on 06/04/21.
//

#include "expression_parser.h"
#include <exception>
#include <stack>

namespace Nodes {
    Operation::Operation(char op) : op_(op) {
        priority_ = op_ == '+' or op_ == '-' ? 1 : 2;
    }
    double Operation::Calc(double x) const {
        double left = left_->Calc(x), right = right_->Calc(x);
        switch (op_) {
            case '+':
                return left + right;
            case '-':
                return left - right;
            case '*':
                return left * right;
            case '/':
                if (abs(right) < eps) throw std::runtime_error("division by zero");
                return left / right;
            default:
                throw std::runtime_error("unknown operation");
        }
    }
    void Operation::SetLeft(std::shared_ptr<Node> left) {
        left_= move(left);
    }
    void Operation::SetRight(std::shared_ptr<Node> right) {
        right_ = move(right);
    }
    int Operation::GetPriority() const {
        return priority_;
    }
    bool Operation::IsMinus() const {
        return op_ == '-';
    }
    void Operation::SetPlus() {
        op_ = '+';
    }

    Value::Value(double val) : val_(val) {}
    double Value::Calc(double x) const {
        return val_;
    }

    Variable::Variable(bool mul_minus_one) : mul_minus_one_(mul_minus_one) {}
    double Variable::Calc(double x) const {
        return mul_minus_one_ ? -x : x;
    }
}

expression_parser::expression_parser(std::string s) : expr_(move(s)) {
    if (expr_.empty()) throw std::invalid_argument("expression in empty");

    using namespace Nodes;
    std::stack<std::shared_ptr<Node>> values;
    std::stack<std::shared_ptr<Operation>> operations;
    for (auto it = expr_.cbegin(); it != expr_.cend(); ++it) {
        if (*it == ' ') continue;
        if (*it == '+' or *it == '-' or *it == '*' or *it == '/') {
            if (*it == '+' or *it == '-') {
                while (not operations.empty() and operations.top()->GetPriority() == 2) {
                    std::shared_ptr<Node> right = values.top();
                    values.pop();
                    std::shared_ptr<Node> left = values.top();
                    values.pop();
                    std::shared_ptr<Operation> op = operations.top();
                    operations.pop();
                    op->SetLeft(left), op->SetRight(right);
                    values.push(op);
                }
            }
            operations.push(std::make_shared<Operation>(*it));
        } else if (isdigit(*it)) {
            int value = *it - '0';
            while (it + 1 != expr_.cend() and isdigit(*(it + 1))) {
                ++it;
                value *= 10;
                value += *it - '0';
            }
            if (not operations.empty() and operations.top()->IsMinus()) {
                value *= -1;
                operations.top()->SetPlus();
            }
            values.push(std::make_shared<Value>(value));
        } else if (*it == 'x') {
            if (not operations.empty() and operations.top()->IsMinus()) {
                values.push(std::make_shared<Variable>(true));
                operations.top()->SetPlus();
            } else {
                values.push(std::make_shared<Variable>(false));
            }
        } else {
            throw std::runtime_error("unknown character : " + std::to_string(*it));
        }
    }
    while (not operations.empty()) {
        std::shared_ptr<Node> right = values.top();
        values.pop();
        std::shared_ptr<Node> left = values.top();
        values.pop();
        std::shared_ptr<Operation> op = operations.top();
        operations.pop();
        op->SetLeft(left), op->SetRight(right);
        values.push(op);
    }
    if (values.size() != 1) throw std::runtime_error("head is not unique");
    head_ = values.top();
}
double expression_parser::calc(double x) {
    return head_->Calc(x);
}