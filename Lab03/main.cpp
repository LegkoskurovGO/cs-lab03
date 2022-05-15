#include "../lab03-histogram/histogram.hpp"
#include "../lab03-svg/svgFunc.hpp"

#include <iostream>
#include <vector>
#include <sstream>
#include <curl/curl.h>
using namespace std;

vector<double> input_numbers(size_t count, istream& in = cin);
vector<size_t> make_histogram(struct Input name);
void show_histogram_text(vector<size_t> bins);

Input
read_input(istream& in, bool prompt) {
   
    Input data;

    if (prompt) {cerr << "Enter number count: ";}
    size_t number_count;
    in >> number_count;

    if (prompt) {cerr << "Enter numbers: ";}
    data.numbers = input_numbers(number_count, in);
    
    if (prompt) {cerr << "Enter column count: ";}
    cin >> data.bin_count;

    return data;
}

int
main (int argc, char* argv[]) {
    
    if (argc > 1) {
        for (int i = 0; i < argc; i++) {
            cout << "argv[" << i << "]= " << argv[i] << endl;
        }
        return 0;
    }
    
    curl_global_init(CURL_GLOBAL_ALL);
    
    const auto input = read_input(cin, true);
    const auto bins = make_histogram(input);
    show_histogram_svg(bins);
    
    //show_histogram_text(bins);
    return 0;
}

vector<double>
input_numbers(size_t count, istream& in) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        in >> result[i];
    }
    return result;
}
vector<size_t>
make_histogram(struct Input name) {
    double min, max;
    find_minmax(name.numbers, min, max);
    vector<size_t> bins(name.bin_count);
    for (double number : name.numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * name.bin_count);
        if (bin == name.bin_count) {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}
void
show_histogram_text(vector<size_t> bins) {
    const size_t SCREEN_HEIGHT = 23;
    const size_t MAX_ASTERISK = SCREEN_HEIGHT - 2 - 1;

    size_t max_count = bins[0];
    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;

    size_t max_count_edit = max_count;
    if (scaling_needed) {
        max_count_edit = (size_t)(MAX_ASTERISK);
    }
    
    for (size_t i = max_count_edit; i > 0; i--) {
        for (size_t bin : bins) {
            size_t height = bin;
            if (scaling_needed) {
                const double scaling_factor = (double)MAX_ASTERISK / max_count;
                height = (size_t)(bin * scaling_factor);
            }
            cout << ' ';
            if (i <= height) {
                cout << "*";
                if (bin >= 10) {
                    cout << "*";
                }
                if (bin >= 100) {
                    cout << "*";
                }
            } else {
                cout << " ";
                if (bin >= 10) {
                    cout << " ";
                }
                if (bin >= 100) {
                    cout << " ";
                }
            }
        }
        cout << "\n";
    }
    for (size_t bin : bins) {
        cout << " _";
        if (bin >= 10) {
            cout << "_";
        }
        if (bin >= 100) {
            cout << "_";
        }
    }
    cout << "\n";
    for (size_t bin : bins) {
        cout << " " << bin;
    }
    cout << "\n";
    
}
