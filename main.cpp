#include <iostream>
using std::cout;
using std::endl;

int main() {

    int x = 5;
    int y = 2;
    double z;

    z = static_cast<double>(x) / y;
    cout << "static_cast<double>(x) / y -> " << z << endl;

    z = x / static_cast<double>(y);
    cout << "x / static_cast<double>(y) -> " << z << endl;

    z = static_cast<double>(x) / static_cast<double>(y);
    cout << "static_cast<double>(x) / static_cast<double>(y) -> " << z << endl;

    z = x / y;
    cout << "x / y -> " << z << endl;

    z = static_cast<double>(x / y);
    cout << "static_cast<double>(x / y) -> " << z << endl;

}

/*

#include <iomanip>
cout << "float: " << std::setprecision(1) << std::fixed << value << "f" << endl;
// Forces exactly 1 decimal place: "42.0f"



*/