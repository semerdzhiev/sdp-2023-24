#pragma once

#include <stdexcept>

inline bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

inline bool isOperation(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

inline int priority(char op)
{
    switch(op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            throw std::invalid_argument("incorrect operation");
    }
}

enum class Associativity { Left, Right };

bool verify(const std::string& expression);
std::string toRpn(const std::string& expression, Associativity associativity);