#include "ScalarConverter.hpp"

int main(int ac, char** av) {
    if (ac != 2) {
        cout << "Usage: " << av[0] << " <literal>" << endl;
        return 1;
    }
    ScalarConverter::convert(av[1]);
    return 0;
}