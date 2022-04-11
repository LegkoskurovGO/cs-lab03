#include "../lab03-histogram/histogram.hpp"
#include "../lab03-svg/svgFunc.hpp"
#include "../lab03-input/inputing.hpp"

#include <iostream>
#include <vector>
using namespace std;

vector<size_t> make_histogram(size_t bin_count, const vector<double>& numbers);
void show_histogram_text(vector<size_t> bins);

int main() {

    int number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    if (number_count <= 0)
    {
        cerr << "Try again\n";
        return 400;
    }
    cerr << "Enter numbers: ";
    const auto numbers = input_numbers(number_count, cin);
    if (numbers.size() != number_count)
    {
        cerr << "Try again\n";
        return 400;
    }

    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;

    auto bins = make_histogram(bin_count, numbers);
    
    //show_histogram_text(bins);
    
    show_histogram_svg(bins);

    return 0;
}

vector<size_t>
make_histogram(size_t bin_count, const vector<double>& numbers) {
    double min, max;
    find_minmax(numbers, min, max);
    vector<size_t> bins(bin_count);
    for (double number : numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * bin_count);
        if (bin == bin_count) {
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
