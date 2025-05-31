#include "ScalarConverter.hpp"

ScalarConverter::Type ScalarConverter::detectType(const string& literal) {
    if (literal.empty())
        return INVALID;

    // Check for char literal
    if (literal.length() == 1 && isprint(literal[0]) && !isdigit(literal[0]))
        return CHAR;

    // Check for special float values
    if (isSpecialFloat(literal))
        return FLOAT;

    // Check for special double values
    if (isSpecialDouble(literal))
        return DOUBLE;

    char* endptr;
    errno = 0;
    // Check for float (ends with 'f')
    if (literal.length() > 1 && *literal.rbegin() == 'f') {
        string without_f = literal.substr(0, literal.length() - 1);
        strtod(without_f.c_str(), &endptr);
        if (*endptr == '\0' && errno == 0)
            return FLOAT;
        return INVALID;
    }

// "42.0f"  → FLOAT   (valid float)
// "42.0ff" → INVALID (strtod fails on "42.0f")
// "42f"    → INVALID (strtod fails on "42")
// "f42.0"  → INVALID (doesn't end with 'f')
// "42.0"   → DOUBLE  (no 'f', has decimal point)
// "nanf"   → FLOAT   (handled by isSpecialFloat)
// "f"      → INVALID (length() > 1 fails)
// "42.5f"  → FLOAT   (valid)
// "42..f"  → INVALID (strtod fails on "42..")
// "abc.f"  → INVALID (strtod fails on "abc.")
// "42.0ff" → INVALID (doesn't end with single 'f')

    // Check if it contains a decimal point
    if (literal.find('.') != string::npos) {
        strtod(literal.c_str(), &endptr);
        if (*endptr == '\0' && errno == 0)
            return DOUBLE;
        return INVALID;
    }

    // Check for int
    long value = strtol(literal.c_str(), &endptr, 10);
    
    if (value >= numeric_limits<int>::min() && value <= numeric_limits<int>::max() &&
        *endptr == '\0' && errno == 0)
        return INT;

    return INVALID;
}

void ScalarConverter::convert(const string& literal) {
    Type type = detectType(literal);

    switch (type)
    {
        case INVALID:
            cout << "Invalid input" << endl;
            return;
        case CHAR:
            convertFromChar(literal[0]);
            return;
        case INT:
            convertFromInt(static_cast<int>(strtol(literal.c_str(), NULL, 10)));
            return;
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
            return;
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
            return;
    }
}

void ScalarConverter::convertFromChar(char c) {
    cout << "char: '"   << c << "'" <<
    endl << "int: "     << static_cast<int>(c) <<
    endl << "float: "   << static_cast<float>(c) << ".0f" <<
    endl << "double: "  << static_cast<double>(c) << ".0" << endl;
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
    
    // Format float and double properly
    if (value == static_cast<int>(value)) {
        cout << "float: " << value << ".0f" <<
        endl << "double: " << value << ".0" << endl;
    }
    else {
        cout << "float: " << static_cast<float>(value) << "f" <<
        endl << "double: " << static_cast<double>(value) << endl;
    }
}

void ScalarConverter::convertFromFloat(float value) {
    // Handle special values
    if (isnan(value)) {
        cout << "char: impossible" <<
        endl << "int: impossible" <<
        endl << "float: nanf" <<
        endl << "double: nan" << endl;
        return;
    }
    if (isinf(value)) {
        cout << "char: impossible" <<
        endl << "int: impossible" <<
        endl << "float: " << (value > 0 ? "+inff" : "-inff") <<
        endl << "double: " << (value > 0 ? "+inf" : "-inf") << endl;
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
    if (value >= numeric_limits<int>::min() && value <= numeric_limits<int>::max() &&
        value == static_cast<int>(value))
        cout << "int: " << static_cast<int>(value) << endl;
    else
        cout << "int: impossible" << endl;

    // Format float output - check if it's a whole number
    cout << "float: ";
    if (value == static_cast<int>(value) && !isinf(value) && !isnan(value))
        cout << static_cast<int>(value) << ".0f" << endl;
    else
        cout << value << "f" << endl;
    
    // Format double output
    cout << "double: ";
    if (value == static_cast<int>(value) && !isinf(value) && !isnan(value))
        cout << static_cast<int>(value) << ".0" << endl;
    else
        cout << static_cast<double>(value) << endl;
}

void ScalarConverter::convertFromDouble(double value) {
    // Handle special values
    if (isnan(value)) {
        cout << "char: impossible" <<
        endl << "int: impossible" <<
        endl << "float: nanf" <<
        endl << "double: nan" << endl;
        return;
    }
    if (isinf(value)) {
        cout << "char: impossible" <<
        endl << "int: impossible" <<
        endl << "float: " << (value > 0 ? "+inff" : "-inff") <<
        endl << "double: " << (value > 0 ? "+inf" : "-inf") << endl;
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
    if (value >= numeric_limits<int>::min() && value <= numeric_limits<int>::max() &&
        value == static_cast<int>(value))
        cout << "int: " << static_cast<int>(value) << endl;
    else
        cout << "int: impossible" << endl;

    // float conversion
    if (value >= -numeric_limits<float>::max() && value <= numeric_limits<float>::max())
    {
        cout << "float: ";
        if (value == static_cast<int>(value))
            cout << static_cast<int>(value) << ".0f" << endl;
        else
            cout << static_cast<float>(value) << "f" << endl;
    }
    else
        cout << "float: impossible" << endl;

    // Format double output
    cout << "double: ";
    if (value == static_cast<int>(value))
        cout << static_cast<int>(value) << ".0" << endl;
    else
        cout << value << endl;
}

bool ScalarConverter::isSpecialFloat(const string& literal) {
    return (literal == "nanf" || literal == "+inff"
        || literal == "-inff" || literal == "inff");
}

bool ScalarConverter::isSpecialDouble(const string& literal) {
    return (literal == "nan" || literal == "+inf"
        || literal == "-inf" || literal == "inf");
}

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}