#include "ScalarConverter.hpp"

int main(int ac, char** av) {
    if (ac != 2) {
        cout << "Usage: " << av[0] << " <literal>" << endl;
        cout << endl << "input: 42" << endl;
        ScalarConverter::convert("42");
        cout << endl << "input: nanf" << endl;
        ScalarConverter::convert("nanf");
        cout << endl << "input: a" << endl;
        ScalarConverter::convert("a");
        cout << endl << "input: 3.14" << endl;
        ScalarConverter::convert("3.14");
        cout << endl << "input: 42.0f" << endl;
        ScalarConverter::convert("42.0f");
        cout << endl << "input: 0" << endl;
        ScalarConverter::convert("0");
        cout << endl << "input: -3.1f" << endl;
        ScalarConverter::convert("-3.1f");
        return 1;
    }
    ScalarConverter::convert(av[1]);
    return 0;
}