#ifndef svgFunc_hpp
#define svgFunc_hpp

#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

void show_histogram_svg(const vector<size_t>& bins);
void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height, string stroke, string fill = "#F4BF4F");

#endif /* svgFunc_hpp */
