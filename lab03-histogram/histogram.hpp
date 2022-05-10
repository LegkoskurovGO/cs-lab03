#ifndef histogram_hpp
#define histogram_hpp

#include <stdio.h>
#include <vector>

using namespace std;

void find_minmax(const vector<double>& numbers, double& min, double& max);

struct Input {
    vector<double> numbers;
    size_t bin_count;
};

#endif /* histogram_hpp */
