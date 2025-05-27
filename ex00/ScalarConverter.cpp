#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}

// ...existing detectType, isSpecialFloat, isSpecialDouble methods...

void ScalarConverter::convertFromInt(int value) {
    // char conversion
    if (value >= 0 && value <= 127)
    {
        if (value >= 32 && value <= 126)
            cout << "char: '" << static_cast<char>(value) << "'" << endl;
        else
            cout << "char: Non displayable" << endl;
    }
    else
        cout << "char: impossible" << endl;

    cout << "int: " << value << endl;
    
    // Format float and double properly
    if (value == static_cast<int>(value)) {
        cout << "float: " << value << ".0f" << endl;
        cout << "double: " << value << ".0" << endl;
    } else {
        cout << "float: " << static_cast<float>(value) << "f" << endl;
        cout << "double: " << static_cast<double>(value) << endl;
    }
}

void ScalarConverter::convertFromFloat(float value) {
    // Handle special values
    if (isnan(value))
    {
        cout << "char: impossible" << endl;
        cout << "int: impossible" << endl;
        cout << "float: nanf" << endl;
        cout << "double: nan" << endl;
        return;
    }
    if (isinf(value))
    {
        cout << "char: impossible" << endl;
        cout << "int: impossible" << endl;
        cout << "float: " << (value > 0 ? "+inff" : "-inff") << endl;
        cout << "double: " << (value > 0 ? "+inf" : "-inf") << endl;
        return;
    }

    // char conversion
    if (value >= 0 && value <= 127 && value == static_cast<int>(value))
    {
        int intVal = static_cast<int>(value);
        if (intVal >= 32 && intVal <= 126)
            cout << "char: '" << static_cast<char>(intVal) << "'" << endl;
        else
            cout << "char: Non displayable" << endl;
    }
    else
        cout << "char: impossible" << endl;

    // int conversion
    if (value >= numeric_limits<int>::min() && value <= numeric_limits<int>::max() && value == static_cast<int>(value))
        cout << "int: " << static_cast<int>(value) << endl;
    else
        cout << "int: impossible" << endl;

    // Format float output
    cout << "float: ";
    if (value == static_cast<int>(value)) {
        cout << static_cast<int>(value) << ".0f" << endl;
    } else {
        cout << value << "f" << endl;
    }
    
    // Format double output
    cout << "double: ";
    if (value == static_cast<int>(value)) {
        cout << static_cast<int>(value) << ".0" << endl;
    } else {
        cout << static_cast<double>(value) << endl;
    }
}

void ScalarConverter::convertFromDouble(double value) {
    // Handle special values
    if (isnan(value))
    {
        cout << "char: impossible" << endl;
        cout << "int: impossible" << endl;
        cout << "float: nanf" << endl;
        cout << "double: nan" << endl;
        return;
    }
    if (isinf(value))
    {
        cout << "char: impossible" << endl;
        cout << "int: impossible" << endl;
        cout << "float: " << (value > 0 ? "+inff" : "-inff") << endl;
        cout << "double: " << (value > 0 ? "+inf" : "-inf") << endl;
        return;
    }

    // char conversion
    if (value >= 0 && value <= 127 && value == static_cast<int>(value))
    {
        int intVal = static_cast<int>(value);
        if (intVal >= 32 && intVal <= 126)
            cout << "char: '" << static_cast<char>(intVal) << "'" << endl;
        else
            cout << "char: Non displayable" << endl;
    }
    else
        cout << "char: impossible" << endl;

    // int conversion
    if (value >= numeric_limits<int>::min() && value <= numeric_limits<int>::max() && value == static_cast<int>(value))
        cout << "int: " << static_cast<int>(value) << endl;
    else
        cout << "int: impossible" << endl;

    // float conversion
    if (value >= -numeric_limits<float>::max() && value <= numeric_limits<float>::max())
    {
        cout << "float: ";
        if (value == static_cast<int>(value)) {
            cout << static_cast<int>(value) << ".0f" << endl;
        } else {
            cout << static_cast<float>(value) << "f" << endl;
        }
    }
    else
        cout << "float: impossible" << endl;

    // Format double output
    cout << "double: ";
    if (value == static_cast<int>(value)) {
        cout << static_cast<int>(value) << ".0" << endl;
    } else {
        cout << value << endl;
    }
}