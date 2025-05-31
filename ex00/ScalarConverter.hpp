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

    static Type detectType(const string& literal);
    static void convertFromChar(char c);
    static void convertFrom(double value);
    static float parseFloat(const string& literal);
    static double parseDouble(const string& literal);
    static void printChar(double value);
    static void printInt(double value);
    static void printFloat(double value);
    static void printDouble(double value);
    static bool handleSpecialValues(double value);
public:
    static void convert(const string& literal);
};

#endif