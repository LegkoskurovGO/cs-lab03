#include "inputing.hpp"

//vector<double>
//input_numbers(size_t count) {
//    vector<double> result(count);
//    for (size_t i = 0; i < count; i++) {
//        cin >> result[i];
//    }
//    return result;
//}
vector<double>
input_numbers(size_t count, istream& stream) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        stream >> result[i];
    }
    return result;
}
