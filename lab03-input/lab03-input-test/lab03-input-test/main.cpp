#include "inputing.hpp"

#include <cassert>
#include <iostream>
#include <ios>
using namespace std;

void
test_first() {
    string input;
    getline(cin, input);
    stringstream source(input);
    
    
    string s("123.45");
    double amt;
    istringstream myString(s);
    myString >> amt;

}

int
main() {
    test_first();
    
}

// int number_count;
// cerr << "Enter number count: ";
// cerr << "Enter numbers: ";
// const auto numbers = input_numbers(number_count);
