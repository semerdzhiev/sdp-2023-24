#pragma once

#include <exception>
#include <iostream>
#include <string>

// An exception that is thrown by simulate_bar when it detects an invalid state or data
class incorrect_simulation : public std::runtime_error {
public:
    incorrect_simulation(const std::string& what_arg)
        : runtime_error(what_arg)
    {
        // Nothing to do here        
    }
};

void simulate_bar(std::istream& input, std::ostream& output);
