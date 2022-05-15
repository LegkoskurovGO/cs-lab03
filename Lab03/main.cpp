#include "../lab03-histogram/histogram.hpp"
#include "../lab03-svg/svgFunc.hpp"

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <curl/curl.h>
using namespace std;

vector<double> input_numbers(size_t count, istream& in = cin);
vector<size_t> make_histogram(struct Input name);
void show_histogram_text(vector<size_t> bins);
Input read_input(istream& in, bool prompt);
Input download(const string& address);
size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx);
string sort_through_argv(int argc, char* argv[], int& url, bool& existStroke);

extern string stroke = "#EECCC1";

int
main (int argc, char* argv[]) {
    
    int url;
    bool fault;
    Input input;
    switch (argc) {
        case 1:
            input = read_input(cin, true);
            break;
        case 2:
            input = download(argv[1]);
            break;
        case 4:
            stroke = sort_through_argv(argc, argv, url, fault);
            if (fault) {
                cout << "В следующий раз после -stroke укажите любой цвет" << endl;
                return 1;
            }
            input = download(argv[url]);
            break;
        default:
            cerr << "Параметры введены неверно" << endl;
            return 2;
            break;
    }
    const auto bins = make_histogram(input);
    show_histogram_svg(bins);

    //show_histogram_text(bins);
    return 0;
}

string
sort_through_argv(int argc, char* argv[], int& url, bool& existStroke) {
    string result;
    existStroke = true;
    for (int i = 1; i < argc; i++) {
        bool flag = strstr(argv[i] ,"http") != NULL || strstr(argv[i] ,"://") != NULL;
        if (strstr(argv[i] ,"-stroke") != NULL) {
            if ( i+1 != argc) {
                result = argv[i+1];
                existStroke = false;
            }
        }
        else if (flag) {
            url = i;
        }
    }
    return result;
}
Input
read_input(istream& in, bool prompt) {
   
    Input data;

    if (prompt) {cerr << "Enter number count: ";}
    size_t number_count;
    in >> number_count;

    if (prompt) {cerr << "Enter numbers: ";}
    data.numbers = input_numbers(number_count, in);
    
    if (prompt) {cerr << "Enter column count: ";}
    in >> data.bin_count;

    return data;
}
Input
download(const string& address) {
    stringstream buffer;

    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();
    
    if(curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&buffer);
        res = curl_easy_perform(curl);
        
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
            curl_easy_cleanup(curl);
            exit(1);
        }
        
      curl_easy_cleanup(curl);
    }
    return read_input(buffer, false);
}
size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    size_t data_size = item_size * item_count;
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    char* itemsChar = reinterpret_cast<char*>(items);
    buffer->write(itemsChar, data_size);
    return data_size;
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
