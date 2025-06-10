#include "Base.hpp"

Base::~Base() {}

Base* generate(void) {
    static bool seeded = false;
    if (!seeded) {
        srand(time(NULL));
        seeded = true;
    }
    
    int random = rand() % 3;
    
    if (random == 0)
        return new A();
    else if (random == 1)
        return new B();
    else
        return new C();
}

void identify(Base* p) {
    if (dynamic_cast<A*>(p))
        cout << "A" << endl;
    else if (dynamic_cast<B*>(p))
        cout << "B" << endl;
    else if (dynamic_cast<C*>(p))
        cout << "C" << endl;
}

void identify(Base& p) {
    try {
        (void)dynamic_cast<A&>(p);
        cout << "A" << endl;
        return;
    }
    catch (...) {}

    try {
        (void)dynamic_cast<B&>(p);
        cout << "B" << endl;
        return;
    }
    catch (...) {}

    try {
        (void)dynamic_cast<C&>(p);
        cout << "C" << endl;
        return;
    }
    catch (...) {}
}
