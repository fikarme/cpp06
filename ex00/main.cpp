#include "ScalarConverter.hpp"

int main(int ac, char** av) {
    if (ac != 2) {
        cout << "Usage: " << av[0] << " <literal>" << endl;
        cout << "---" << endl;
        ScalarConverter::convert("42");
        cout << "---" << endl;
        ScalarConverter::convert("nanf");
        cout << "---" << endl;
        ScalarConverter::convert("a");
        cout << "---" << endl;
        ScalarConverter::convert("3.14");
        cout << "---" << endl;
        ScalarConverter::convert("42.0f");
        cout << "---" << endl;
        ScalarConverter::convert("0");
        cout << "---" << endl;
        return 1;
    }
    ScalarConverter::convert(av[1]);
    return 0;
}