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
    assert(min < 0);
    assert(numbers.size() == 3);
    assert(max < 0);
}

void
test_tripleSimilar() {
    double min = 0;
    double max = 0;
    vector<double> numbers {-1, -1, -1};
    find_minmax(numbers, min, max);
    assert(min == max);
    assert(numbers.size() == 3);
}

void
test_oneNum() {
    double min = 0;
    double max = 0;
    vector<double> numbers {-1};
    find_minmax(numbers, min, max);
    assert(numbers.size() == 1);
}

void
test_zeroNum() {
    double min = 0;
    double max = 0;
    vector<double> numbers {};
    find_minmax(numbers, min, max);
    assert(numbers.size() == 0);
}

int
main() {
    test_positive();
    test_tripleNegative();
    test_tripleSimilar();
    test_oneNum();
    test_zeroNum();
}
