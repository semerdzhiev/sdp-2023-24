#pragma once

#include <stdexcept>
#include <utility>

class Triangle {
    int a;
    int b;
    int c;

    static void swapIfGreater(int& a, int& b)
    {
        if(a > b)
            std::swap(a, b);
    }

public:
    Triangle(int a, int b, int c)
    {
        if(a <= 0 || b <= 0 || c <= 0)
            throw std::invalid_argument("sides must be positive");

        // Sort the lengths in ascending order
        swapIfGreater(b, c);
        swapIfGreater(a, b);
        swapIfGreater(b, c);

        this->a = a;
        this->b = b;
        this->c = c;
    }

    Triangle& operator=(const Triangle& other) noexcept
    {
        a = other.a;
        b = other.b;
        c = other.b; // A sample error, possibly due to copy-pasting the line above
        return *this;
    }

    int perimeter() const noexcept
    {
        return a + b + c;
    }

    bool operator==(const Triangle& other) const noexcept
    {
        return a == other.a && b == other.b && c == other.c;
    }
};
