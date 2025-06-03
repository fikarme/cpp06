#include <iostream>
#include <string>
#include <stdint.h>

using std::cout;
using std::endl;
using std::string;

struct Data {
    int id;
    string name;
    double value;
    
    Data() : id(0), name(""), value(0.0) {}
    Data(int i, const string& n, double v) : id(i), name(n), value(v) {}
    
    void print() const {
        cout << "Data { id: " << id << ", name: \"" << name << "\", value: " << value << " }";
    }
};

uintptr_t serialize(Data* ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
}

Data* deserialize(uintptr_t raw) {
    return reinterpret_cast<Data*>(raw);
}

int main() {
    cout << "=== Serialization Demo ===" << endl << endl;
    
    // 1. Create original data
    cout << "1. Creating Data object..." << endl;
    Data* original = new Data(42, "Test Data", 3.14);
    cout << "Original: ";
    original->print();
    cout << endl;
    cout << "Address: " << original << " (hex)" << endl;
    cout << "Address: " << reinterpret_cast<uintptr_t>(original) << " (decimal)" << endl;
    cout << endl;
    
    // 2. Demonstrate pointer is just a number
    cout << "2. Pointer as different representations:" << endl;
    Data* ptr = original;
    cout << "Pointer type: " << ptr << endl;
    cout << "As uintptr_t: " << reinterpret_cast<uintptr_t>(ptr) << endl;
    cout << "Same address? " << (ptr == original ? "YES" : "NO") << endl;
    cout << endl;
    
    // 3. Serialize (Pointer → Integer)
    cout << "3. Serializing (Pointer → Integer)..." << endl;
    uintptr_t serialized = serialize(original);
    cout << "Serialized value: " << serialized << endl;
    cout << "Original address: " << reinterpret_cast<uintptr_t>(original) << endl;
    cout << "Same value? " << (serialized == reinterpret_cast<uintptr_t>(original) ? "YES" : "NO") << endl;
    cout << endl;
    
    // 4. Deserialize (Integer → Pointer)
    cout << "4. Deserializing (Integer → Pointer)..." << endl;
    Data* deserialized = deserialize(serialized);
    cout << "Deserialized: ";
    deserialized->print();
    cout << endl;
    cout << "Address: " << deserialized << endl;
    cout << endl;
    
    // 5. Verification
    cout << "5. Verification:" << endl;
    cout << "Original == Deserialized? " << (original == deserialized ? "YES" : "NO") << endl;
    cout << "Same memory address? " << (original == deserialized ? "YES" : "NO") << endl;
    cout << "Same data content? " << 
            (original->id == deserialized->id && 
             original->name == deserialized->name && 
             original->value == deserialized->value ? "YES" : "NO") << endl;
    cout << endl;
    
    // 6. Type safety demonstration
    cout << "6. Type Safety Demo:" << endl;
    cout << " Data* ptr = new Data();" << endl;
    cout << " int* wrong = ptr;  \n ❌ Would cause compile error" << endl;
    cout << " uintptr_t addr = reinterpret_cast<uintptr_t>(ptr); \n ✅ Explicit cast" << endl;
    cout << endl;
    
    // 7. Bit-level demonstration
    cout << "7. Bit-level Analysis:" << endl;
    cout << "Memory address: " << original << endl;
    cout << "As integer:     " << reinterpret_cast<uintptr_t>(original) << endl;
    cout << "As hex:         0x" << std::hex << reinterpret_cast<uintptr_t>(original) << std::dec << endl;
    cout << "Explanation: Same bits, different interpretation!" << endl;
    cout << endl;
    
    // 8. Multiple serialization/deserialization
    cout << "8. Multiple Operations:" << endl;
    uintptr_t serialized1 = serialize(original);
    Data* deserialized1 = deserialize(serialized1);
    uintptr_t serialized2 = serialize(deserialized1);
    Data* deserialized2 = deserialize(serialized2);
    
    cout << "Original:       " << original << endl;
    cout << "Deserialized1:  " << deserialized1 << endl;
    cout << "Deserialized2:  " << deserialized2 << endl;
    cout << "All same?       " << (original == deserialized1 && deserialized1 == deserialized2 ? "YES" : "NO") << endl;
    cout << endl;
    
    // 9. Real-world context
    cout << "9. Real-world Context:" << endl;
    cout << "This demonstrates the CONCEPT of serialization:" << endl;
    cout << "- Converting between different representations" << endl;
    cout << "- Preserving information across conversions" << endl;
    cout << "- Foundation for network/file serialization" << endl;
    cout << endl;
    cout << "In practice, you'd serialize the DATA, not the pointer:" << endl;
    cout << "JSON: {\"id\":" << original->id << ",\"name\":\"" << original->name << "\",\"value\":" << original->value << "}" << endl;
    
    delete original;
    cout << endl << "tengri zihin açıklığı versin" << endl;
}