#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::endl;

// Base class with virtual destructor (enables RTTI)
class Base {
public:
    virtual ~Base() { cout << "  [Base destructor called]" << endl; }
    virtual void whoAmI() const { cout << "I am Base"; }
};

// Derived classes
class A : public Base {
public:
    void whoAmI() const { cout << "I am A"; }
    void specificA() const { cout << "A-specific function called!"; }
};

class B : public Base {
public:
    void whoAmI() const { cout << "I am B"; }
    void specificB() const { cout << "B-specific function called!"; }
};

class C : public Base {
public:
    void whoAmI() const { cout << "I am C"; }
    void specificC() const { cout << "C-specific function called!"; }
};

// Generate random object
Base* generate() {
    static bool seeded = false;
    if (!seeded) {
        srand(time(NULL));
        seeded = true;
    }
    
    int random = rand() % 3;
    cout << "  [Generating type " << (random == 0 ? "A" : random == 1 ? "B" : "C") << "]" << endl;
    
    if (random == 0)
        return new A();
    else if (random == 1)
        return new B();
    else
        return new C();
}

// Type identification functions
void identifyByPointer(Base* p) {
    cout << "  Identifying with pointer..." << endl;
    
    if (dynamic_cast<A*>(p)) {
        cout << "  ✅ Type is A" << endl;
        A* aPtr = dynamic_cast<A*>(p);
        cout << "  Calling A-specific function: ";
        aPtr->specificA();
        cout << endl;
    }
    else if (dynamic_cast<B*>(p)) {
        cout << "  ✅ Type is B" << endl;
        B* bPtr = dynamic_cast<B*>(p);
        cout << "  Calling B-specific function: ";
        bPtr->specificB();
        cout << endl;
    }
    else if (dynamic_cast<C*>(p)) {
        cout << "  ✅ Type is C" << endl;
        C* cPtr = dynamic_cast<C*>(p);
        cout << "  Calling C-specific function: ";
        cPtr->specificC();
        cout << endl;
    }
    else {
        cout << "  ❌ Unknown type" << endl;
    }
}

void identifyByReference(Base& p) {
    cout << "  Identifying with reference..." << endl;
    
    try {
        A& aRef = dynamic_cast<A&>(p);
        cout << "  ✅ Type is A (caught by reference)" << endl;
        cout << "  Calling A-specific function: ";
        aRef.specificA();
        cout << endl;
        return;
    }
    catch (std::bad_cast&) {
        cout << "  ❌ Not type A" << endl;
    }
    
    try {
        B& bRef = dynamic_cast<B&>(p);
        cout << "  ✅ Type is B (caught by reference)" << endl;
        cout << "  Calling B-specific function: ";
        bRef.specificB();
        cout << endl;
        return;
    }
    catch (std::bad_cast&) {
        cout << "  ❌ Not type B" << endl;
    }
    
    try {
        C& cRef = dynamic_cast<C&>(p);
        cout << "  ✅ Type is C (caught by reference)" << endl;
        cout << "  Calling C-specific function: ";
        cRef.specificC();
        cout << endl;
        return;
    }
    catch (std::bad_cast&) {
        cout << "  ❌ Not type C" << endl;
    }
}

int main() {
    cout << "=== Dynamic Cast Demo ===" << endl << endl;
    
    // 1. Basic concept explanation
    cout << "1. What is dynamic_cast?" << endl;
    cout << "   - Runtime type checking for polymorphic classes" << endl;
    cout << "   - Safe downcasting from Base* to Derived*" << endl;
    cout << "   - Returns nullptr for pointers, throws exception for references" << endl;
    cout << "   - Requires virtual functions (RTTI enabled)" << endl;
    cout << endl;
    
    // 2. Create known objects and demonstrate casting
    cout << "2. Basic Dynamic Cast with Known Types:" << endl;
    cout << "   Creating A, B, C objects directly..." << endl;
    
    A* directA = new A();
    B* directB = new B();
    C* directC = new C();
    
    // Store as base pointers
    Base* baseA = directA;
    Base* baseB = directB;
    Base* baseC = directC;
    
    cout << "   Base* pointing to A: ";
    baseA->whoAmI();
    cout << endl;
    cout << "   Base* pointing to B: ";
    baseB->whoAmI();
    cout << endl;
    cout << "   Base* pointing to C: ";
    baseC->whoAmI();
    cout << endl;
    cout << endl;
    
    // 3. Demonstrate successful dynamic_cast
    cout << "3. Successful Dynamic Casts:" << endl;
    
    A* castedA = dynamic_cast<A*>(baseA);
    if (castedA) {
        cout << "   ✅ Successfully cast Base* to A*: ";
        castedA->specificA();
        cout << endl;
    }
    
    B* castedB = dynamic_cast<B*>(baseB);
    if (castedB) {
        cout << "   ✅ Successfully cast Base* to B*: ";
        castedB->specificB();
        cout << endl;
    }
    
    C* castedC = dynamic_cast<C*>(baseC);
    if (castedC) {
        cout << "   ✅ Successfully cast Base* to C*: ";
        castedC->specificC();
        cout << endl;
    }
    cout << endl;
    
    // 4. Demonstrate failed dynamic_cast
    cout << "4. Failed Dynamic Casts (returns nullptr):" << endl;
    
    B* wrongCast1 = dynamic_cast<B*>(baseA);  // A* to B* - should fail
    C* wrongCast2 = dynamic_cast<C*>(baseA);  // A* to C* - should fail
    A* wrongCast3 = dynamic_cast<A*>(baseB);  // B* to A* - should fail
    
    cout << "   Trying to cast A* to B*: " << (wrongCast1 ? "SUCCESS" : "FAILED (nullptr)") << endl;
    cout << "   Trying to cast A* to C*: " << (wrongCast2 ? "SUCCESS" : "FAILED (nullptr)") << endl;
    cout << "   Trying to cast B* to A*: " << (wrongCast3 ? "SUCCESS" : "FAILED (nullptr)") << endl;
    cout << endl;
    
    // 5. Reference casting with exceptions
    cout << "5. Reference Casting (throws exceptions on failure):" << endl;
    
    try {
        A& refA = dynamic_cast<A&>(*baseA);
        cout << "   ✅ Successfully cast Base& to A&: ";
        refA.specificA();
        cout << endl;
    }
    catch (std::bad_cast& e) {
        cout << "   ❌ Failed to cast to A&" << endl;
    }
    
    try {
        B& refB = dynamic_cast<B&>(*baseA);  // This should fail
        cout << "   ✅ Successfully cast Base& to B&: ";
        refB.specificB();
        cout << endl;
    }
    catch (std::bad_cast& e) {
        cout << "   ❌ Failed to cast A& to B& (threw std::bad_cast)" << endl;
    }
    cout << endl;
    
    // Clean up known objects
    delete directA;
    delete directB;
    delete directC;
    
    // 6. Random object generation and identification
    cout << "6. Random Object Generation and Identification:" << endl;
    
    for (int i = 0; i < 4; i++) {
        cout << "   Test " << (i + 1) << ":" << endl;
        Base* randomObj = generate();
        
        cout << "   Virtual function call: ";
        randomObj->whoAmI();
        cout << endl;
        
        identifyByPointer(randomObj);
        cout << endl;
        
        delete randomObj;
    }
    
    // 7. Reference identification
    cout << "7. Reference-based Identification:" << endl;
    Base* testObj = generate();
    cout << "   Object created, identifying by reference:" << endl;
    identifyByReference(*testObj);
    delete testObj;
    cout << endl;
    
    // 8. Performance and safety comparison
    cout << "8. Dynamic Cast vs Other Casting:" << endl;
    cout << "   dynamic_cast<T*>:     ✅ Safe, runtime checked, returns nullptr on failure" << endl;
    cout << "   static_cast<T*>:      ⚠️  Fast, compile-time, NO runtime checking" << endl;
    cout << "   reinterpret_cast<T*>: ❌ Dangerous, bit reinterpretation, no checking" << endl;
    cout << "   (T*)ptr:              ❌ C-style, no checking, can crash" << endl;
    cout << endl;
    
    // 9. RTTI requirement demonstration
    cout << "9. RTTI (Runtime Type Information) Requirements:" << endl;
    cout << "   - Base class MUST have virtual functions" << endl;
    cout << "   - Enables runtime type checking" << endl;
    cout << "   - Without virtual functions, dynamic_cast won't work" << endl;
    cout << "   - Our Base class has virtual destructor: ✅" << endl;
    cout << endl;
    
    // 10. Real-world usage patterns
    cout << "10. Real-world Usage Patterns:" << endl;
    cout << "    // Safe downcasting pattern:" << endl;
    cout << "    if (DerivedType* derived = dynamic_cast<DerivedType*>(base)) {" << endl;
    cout << "        derived->specificFunction();  // Safe to use" << endl;
    cout << "    } else {" << endl;
    cout << "        // Handle case where cast failed" << endl;
    cout << "    }" << endl;
    cout << endl;
    
    // 11. Memory visualization
    cout << "11. Memory Layout Understanding:" << endl;
    A* memTestA = new A();
    Base* memTestBase = memTestA;
    
    cout << "    A* pointer:    " << memTestA << endl;
    cout << "    Base* pointer: " << memTestBase << endl;
    cout << "    Same object?   " << (memTestA == memTestBase ? "YES" : "NO") << endl;
    cout << "    dynamic_cast back: " << dynamic_cast<A*>(memTestBase) << endl;
    cout << "    Successful?    " << (dynamic_cast<A*>(memTestBase) == memTestA ? "YES" : "NO") << endl;
    
    delete memTestA;
    cout << endl;
    
    cout << "Key takeaway: dynamic_cast enables safe, runtime-checked type conversion!" << endl;
    cout << "=== tengri yardımcın olsun ===" << endl;

    return 0;
}