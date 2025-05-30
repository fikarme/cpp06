#include "Base.hpp"
#include <iostream>

using std::cout;
using std::endl;

inline void y() {cout << "\033[1;33m ---------\033[0m" << endl;}

int main() {
    cout << "Testing type identification with pointers:" << endl;
    y();
    
    // Generate random objects and test identification
    for (int i = 0; i < 6; i++) {
        Base* obj = generate();
        cout << "Generated object " << i + 1 << " (pointer): ";
        identify(obj);
        delete obj;
    }
    
    y();
    cout << "Testing type identification with references:" << endl;
    y();
    
    // Test with references
    for (int i = 0; i < 6; i++) {
        Base* obj = generate();
        cout << "Generated object " << i + 1 << " (reference): ";
        identify(*obj);
        delete obj;
    }
    
    y();
    cout << "Testing with specific types:" << endl;
    y();
    
    // Test specific known types
    A* aObj = new A();
    B* bObj = new B();
    C* cObj = new C();
    
    cout << "A object (pointer): ";
    identify(aObj);
    cout << "B object (pointer): ";
    identify(bObj);
    cout << "C object (pointer): ";
    identify(cObj);
    
    cout << "A object (reference): ";
    identify(*aObj);
    cout << "B object (reference): ";
    identify(*bObj);
    cout << "C object (reference): ";
    identify(*cObj);
    
    delete aObj;
    delete bObj;
    delete cObj;
    
    return 0;
}