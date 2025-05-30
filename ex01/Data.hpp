#ifndef DATA_HPP
#define DATA_HPP

#include <string>

using std::string;

struct Data {
    int id;
    string name;
    double value;
    
    Data();
    Data(int id, const string& name, double value);
};

#endif
