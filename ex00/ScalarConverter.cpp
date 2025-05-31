#include "ScalarConverter.hpp"

ScalarConverter::Type ScalarConverter::detectType(const string& literal) {
    if (literal.empty())
        return INVALID;

    if (literal.length() == 1 && isprint(literal[0]) && !isdigit(literal[0]))
        return CHAR;

    if (literal == "nanf" || literal == "+inff"
        || literal == "-inff" || literal == "inff")
        return FLOAT;

    if ((literal == "nan" || literal == "+inf"
        || literal == "-inf" || literal == "inf"))
        return DOUBLE;

    char* endptr;
    errno = 0;
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

    if (literal.find('.') != string::npos) {
        strtod(literal.c_str(), &endptr);
        if (*endptr == '\0' && errno == 0)
            return DOUBLE;
        return INVALID;
    }

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
            convertFrom(static_cast<int>(strtol(literal.c_str(), NULL, 10)));
            return;
        case FLOAT:
            convertFrom(parseFloat(literal));
            return;
        case DOUBLE:
            convertFrom(parseDouble(literal));
            return;
    }
}

void ScalarConverter::convertFromChar(char c) {
    cout << "char: '"   << c << "'" <<
    endl << "int: "     << static_cast<int>(c) <<
    endl << "float: "   << static_cast<float>(c) << ".0f" <<
    endl << "double: "  << static_cast<double>(c) << ".0" << endl;
}

void ScalarConverter::convertFrom(double value) {
    if (handleSpecialValues(value))
        return;
    printChar(value);
    printInt(value);
    printFloat(value);
    printDouble(value);
}

void ScalarConverter::printChar(double value) {
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
}

void ScalarConverter::printInt(double value) {
    if (value >= numeric_limits<int>::min() && value <= numeric_limits<int>::max() &&
        value == static_cast<int>(value))
        cout << "int: " << static_cast<int>(value) << endl;
    else
        cout << "int: impossible" << endl;
}

void ScalarConverter::printFloat(double value) {
    if (value >= -numeric_limits<float>::max() && value <= numeric_limits<float>::max())
    {
        cout << "float: ";
        if (value == static_cast<int>(value) && !isinf(value) && !isnan(value))
            cout << static_cast<int>(value) << ".0f" << endl;
        else
            cout << static_cast<float>(value) << "f" << endl;
    }
    else
        cout << "float: impossible" << endl;
}

void ScalarConverter::printDouble(double value) {
    cout << "double: ";
    if (value == static_cast<int>(value) && !isinf(value) && !isnan(value))
        cout << static_cast<int>(value) << ".0" << endl;
    else
        cout << value << endl;
}

bool ScalarConverter::handleSpecialValues(double value) {
    if (isnan(value)) {
        cout << "char: impossible" <<
        endl << "int: impossible" <<
        endl << "float: nanf" <<
        endl << "double: nan" << endl;
        return true;
    }
    if (isinf(value)) {
        cout << "char: impossible" <<
        endl << "int: impossible" <<
        endl << "float: " << (value > 0 ? "+inff" : "-inff") <<
        endl << "double: " << (value > 0 ? "+inf" : "-inf") << endl;
        return true;
    }
    return false;
}

float ScalarConverter::parseFloat(const string& literal) {
    if (literal == "nanf")
        return numeric_limits<float>::quiet_NaN();
    if (literal == "+inff" || literal == "inff")
        return numeric_limits<float>::infinity();
    if (literal == "-inff")
        return -numeric_limits<float>::infinity();
    
    string without_f = literal.substr(0, literal.length() - 1);
    return static_cast<float>(strtod(without_f.c_str(), NULL));
}

double ScalarConverter::parseDouble(const string& literal) {
    if (literal == "nan")
        return numeric_limits<double>::quiet_NaN();
    if (literal == "+inf" || literal == "inf")
        return numeric_limits<double>::infinity();
    if (literal == "-inf")
        return -numeric_limits<double>::infinity();
    
    return strtod(literal.c_str(), NULL);
}

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}