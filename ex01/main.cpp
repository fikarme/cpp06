#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

using std::cout;
using std::endl;

inline void y() {
    cout << "\033[1;33m ---------\033[0m" << endl;
}

int main() {
    // Create a Data object
    Data* original = new Data(42, "Test Data", 3.14);

    cout << "Original Data object:" <<
    endl << "Address: " << original <<
    endl << "ID: " << original->id <<
    endl << "Name: " << original->name <<
    endl << "Value: " << original->value << endl;
    y();

    // Serialize the pointer
    uintptr_t serialized = Serializer::serialize(original);
    cout << "Serialized value: " << serialized << endl;
    y();

    // Deserialize back to pointer
    Data* deserialized = Serializer::deserialize(serialized);

    cout << "Deserialized Data object:" <<
    endl << "Address: " << deserialized <<
    endl << "ID: " << deserialized->id <<
    endl << "Name: " << deserialized->name <<
    endl << "Value: " << deserialized->value << endl;
    y();

    if (original == deserialized)
        cout << "✓ Success: Original and deserialized pointers are equal!" << endl;
    else
        cout << "✗ Error: Original and deserialized pointers are different!" << endl;
    
    delete original;
    
    return 0;
}