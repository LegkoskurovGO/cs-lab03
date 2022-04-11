#include "inputing.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

void
triplePositive() {
    stringstream stream("1 1 2");
    double str;
    
    size_t number_count = 3;
    
    auto numbers = input_numbers(number_count, stream);
    
    stream.seekg(ios_base::beg);
    for (size_t i = 0; i < number_count; i++) {
        stream >> str;
        assert(numbers[i] == str);
    }
}

void
tripleNegative() {
    stringstream stream("-1 -10 -2");
    double str;
    
    size_t number_count = 3;
    
    auto numbers = input_numbers(number_count, stream);
    
    stream.seekg(ios_base::beg);
    for (size_t i = 0; i < number_count; i++) {
        stream >> str;
        //cout << "numbers is " << numbers[i] << "\tand str is " << str << endl;
        assert(numbers[i] == str);
    }
}
void
tripleOne() {
    stringstream stream("1 1 1");
    double str;
    
    size_t number_count = 3;
    
    auto numbers = input_numbers(number_count, stream);
    
    stream.seekg(ios_base::beg);
    for (size_t i = 0; i < number_count; i++) {
        stream >> str;
        //cout << "numbers is " << numbers[i] << "\tand str is " << str << endl;
        assert(numbers[i] == str);
    }
}
void
onlyZeroes() {
    stringstream stream("0 0 0 0");
    double str;
    
    size_t number_count = 4;
    
    auto numbers = input_numbers(number_count, stream);
    
    stream.seekg(ios_base::beg);
    for (size_t i = 0; i < number_count; i++) {
        stream >> str;
        //cout << "numbers is " << numbers[i] << "\tand str is " << str << endl;
        assert(numbers[i] == str);
    }
}
void
empty() {
    stringstream stream("");
    double str;
    
    size_t number_count = 0;
    
    auto numbers = input_numbers(number_count, stream);
    
    stream.seekg(ios_base::beg);
    for (size_t i = 0; i < number_count; i++) {
        stream >> str;
        //cout << "numbers is " << numbers[i] << "\tand str is " << str << endl;
        assert(numbers[i] == str);
    }
}
void
quadroDifferent() {
    stringstream stream("1 -2 3 -4");
    double str;
    
    size_t number_count = 4;
    
    auto numbers = input_numbers(number_count, stream);
    
    stream.seekg(ios_base::beg);
    for (size_t i = 0; i < number_count; i++) {
        stream >> str;
        //cout << "numbers is " << numbers[i] << "\tand str is " << str << endl;
        assert(numbers[i] == str);
    }
}

void
cinfunc() {
    stringstream stream("1 1 2");
    double str;
    
    size_t number_count = 3;
    
    cout << "Enter numbers: ";
    auto numbers = input_numbers(number_count, cin);
    
    stream.seekg(ios_base::beg);
    for (size_t i = 0; i < number_count; i++) {
        stream >> str;
        assert(numbers[i] == str);
    }
}
int
main() {
    triplePositive();
    tripleNegative();
    tripleOne();
    onlyZeroes();
    empty();
    quadroDifferent();
    //cinfunc();
}
