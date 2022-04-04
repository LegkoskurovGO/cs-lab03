#include "histogram.hpp"

#include <cassert>

void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}
void
test_tripleNegative() {
    double min = 0;
    double max = 0;
    vector<double> numbers {-1, -22, -3};
    find_minmax(numbers, min, max);
    assert(min == -22);
    assert(numbers.size() == 3);
    assert(max == -1);
}

void
test_tripleSimilar() {
    double min = 0;
    double max = 0;
    vector<double> numbers {-1, -1, -1};
    find_minmax(numbers, min, max);
    assert(min == max);
    assert(min == -1);
    assert(numbers.size() == 3);
}

void
test_oneNum() {
    double min = 0;
    double max = 0;
    vector<double> numbers {-1};
    find_minmax(numbers, min, max);
    assert(numbers.size() == 1);
    assert(max == -1);
}

void
test_zeroNum() {
    double min = 0;
    double max = 0;
    vector<double> numbers {};
    find_minmax(numbers, min, max);
    assert(numbers.size() == 0);
}
void
test_NegativeAndPositive() {
    double min = 0;
    double max = 0;
    vector<double> numbers {-3, 4, -5, 7, 2, -1};
    find_minmax(numbers, min, max);
    assert(min == -5);
    assert(max == 7);
}
void
test_containsZeroes() {
    double min = 0;
    double max = 0;
    vector<double> numbers {0, 0, 0, 0, 0, 0};
    find_minmax(numbers, min, max);
    assert(min == 0);
    assert(max == 0);
    assert(numbers.size() == 6);
}
void
test_typical() {
    double min = 0;
    double max = 0;
    vector<double> numbers {1.00, -2.96, 3.65, -4.49, 5.00, -6.11};
    find_minmax(numbers, min, max);
    assert(min == -6.11);
    assert(max == 5.00);
}
void
test_typical2() {
    double min = 0;
    double max = 0;
    vector<double> numbers {-3.98654, -6789.856, 1, -4.49, 5.00, 12345};
    find_minmax(numbers, min, max);
    assert(min == -6789.856);
    assert(max == 12345);
}
int
main() {
    test_positive();
    test_tripleNegative();
    test_tripleSimilar();
    test_oneNum();
    test_zeroNum();
    test_NegativeAndPositive();
    test_containsZeroes();
    test_typical();
    test_typical2();
}
