# General rules
- use UpperCamelCase
- use Orthodox Canonical Form
- use C++98 standard.
- use these flags: -Wall -Wextra -Werror
- don't use braces for single-line if statements

# ex02: Identify real type

Forbidden functions: std::typeinfo

Implement a Base class that has a public virtual destructor only. Create three empty classes A, B, and C, that publicly inherit from Base. 

These four classes don’t have to be designed in the Orthodox Canonical Form. 

Implement the following functions:

Base * generate(void); 
It randomly instantiates A, B, or C and returns the instance as a Base pointer. Feel free to use anything you like for the random choice implementation. 

void identify(Base* p); 
It prints the actual type of the object pointed to by p: "A", "B", or "C". 

void identify(Base& p);
It prints the actual type of the object referenced by p: "A", "B", or "C". Using a pointer inside this function is forbidden.

Including the typeinfo header is forbidden.

Write a program to test that everything works as expected.