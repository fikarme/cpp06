#include "ScalarConverter.hpp"

int main(int ac, char** av) {
    if (ac != 2) {
        cout << "Usage: " << av[0] << " <literal>" << endl;
        cout << "---42" << endl;
        ScalarConverter::convert("42");
        cout << "---nanf" << endl;
        ScalarConverter::convert("nanf");
        cout << "---a" << endl;
        ScalarConverter::convert("a");
        cout << "---3.14" << endl;
        ScalarConverter::convert("3.14");
        cout << "---42.0f" << endl;
        ScalarConverter::convert("42.0f");
        cout << "---0" << endl;
        ScalarConverter::convert("0");
        cout << "---" << endl;
        return 1;
    }
    ScalarConverter::convert(av[1]);
    return 0;
}