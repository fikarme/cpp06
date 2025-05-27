#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <limits>
#include <cstdlib>
#include <cerrno>
#include <cmath>

using std::string;
using std::cout;
using std::endl;
using std::isnan;
using std::isinf;
using std::numeric_limits;

class ScalarConverter {
private:
    ScalarConverter();
    ScalarConverter(const ScalarConverter& other);
    ScalarConverter& operator=(const ScalarConverter& other);
    ~ScalarConverter();

    enum Type {
        CHAR,
        INT,
        FLOAT,
        DOUBLE,
        INVALID
    };

    static Type detectType(const std::string& literal);
    static void convertFromChar(char c);
    static void convertFromInt(int value);
    static void convertFromFloat(float value);
    static void convertFromDouble(double value);
    static bool isSpecialFloat(const std::string& literal);
    static bool isSpecialDouble(const std::string& literal);

public:
    static void convert(const std::string& literal);
};

#endif