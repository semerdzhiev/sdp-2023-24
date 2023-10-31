#pragma once

#include <istream>
#include <exception>

// An exception that is thrown by evaluate when it detects an incorrect expression
class incorrect_expression : public std::invalid_argument {
public:
    incorrect_expression(const std::string& what_arg)
        : invalid_argument(what_arg)
    {
        // Nothing to do here        
    }
};

double evaluate(const char* expression, std::istream& ops);