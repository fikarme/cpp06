#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}

ScalarConverter::Type ScalarConverter::detectType(const string& literal) {
    if (literal.empty())
        return INVALID;

    // Check for char literal
    if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
        return CHAR;

    // Check for special float values
    if (isSpecialFloat(literal))
        return FLOAT;

    // Check for special double values
    if (isSpecialDouble(literal))
        return DOUBLE;

    // Check for float (ends with 'f')
    if (literal.length() > 1 && literal[literal.length() - 1] == 'f')
    {
        string without_f = literal.substr(0, literal.length() - 1);
        char* endptr;
        errno = 0;
        strtod(without_f.c_str(), &endptr);
        if (*endptr == '\0' && errno == 0)
            return FLOAT;
        return INVALID;
    }

    // Check for int or double
    char* endptr;
    errno = 0;
    long value = strtol(literal.c_str(), &endptr, 10);
    
    if (*endptr == '\0' && errno == 0 && value >= numeric_limits<int>::min() && value <= numeric_limits<int>::max())
        return INT;

    errno = 0;
    strtod(literal.c_str(), &endptr);
    if (*endptr == '\0' && errno == 0)
        return DOUBLE;

    return INVALID;
}

bool ScalarConverter::isSpecialFloat(const string& literal) {
    return (literal == "nanf" || literal == "+inff" || literal == "-inff" || literal == "inff");
}

bool ScalarConverter::isSpecialDouble(const string& literal) {
    return (literal == "nan" || literal == "+inf" || literal == "-inf" || literal == "inf");
}

void ScalarConverter::convertFromChar(char c) {
    cout << "char: '" << c << "'" << endl;
    cout << "int: " << static_cast<int>(c) << endl;
    cout << "float: " << static_cast<float>(c) << ".0f" << endl;
    cout << "double: " << static_cast<double>(c) << ".0" << endl;
}

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
    cout << "float: " << static_cast<float>(value) << ".0f" << endl;
    cout << "double: " << static_cast<double>(value) << ".0" << endl;
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

    cout << "float: " << value << "f" << endl;
    cout << "double: " << static_cast<double>(value) << endl;
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
        cout << "float: " << static_cast<float>(value) << "f" << endl;
    else
        cout << "float: impossible" << endl;

    cout << "double: " << value << endl;
}

void ScalarConverter::convert(const string& literal) {
    Type type = detectType(literal);

    switch (type)
    {
        case CHAR:
            convertFromChar(literal[1]);
            break;
        case INT:
            convertFromInt(static_cast<int>(strtol(literal.c_str(), NULL, 10)));
            break;
        case FLOAT:
            if (isSpecialFloat(literal))
            {
                if (literal == "nanf")
                    convertFromFloat(numeric_limits<float>::quiet_NaN());
                else if (literal == "+inff" || literal == "inff")
                    convertFromFloat(numeric_limits<float>::infinity());
                else
                    convertFromFloat(-numeric_limits<float>::infinity());
            }
            else
            {
                string without_f = literal.substr(0, literal.length() - 1);
                convertFromFloat(static_cast<float>(strtod(without_f.c_str(), NULL)));
            }
            break;
        case DOUBLE:
            if (isSpecialDouble(literal))
            {
                if (literal == "nan")
                    convertFromDouble(numeric_limits<double>::quiet_NaN());
                else if (literal == "+inf" || literal == "inf")
                    convertFromDouble(numeric_limits<double>::infinity());
                else
                    convertFromDouble(-numeric_limits<double>::infinity());
            }
            else
                convertFromDouble(strtod(literal.c_str(), NULL));
            break;
        default:
            cout << "Invalid input" << endl;
    }
}