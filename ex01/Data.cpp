#include "Data.hpp"

Data::Data() : id(0), name(""), value(0.0) {}

Data::Data(int id, const string& name, double value) 
    : id(id), name(name), value(value) {}
