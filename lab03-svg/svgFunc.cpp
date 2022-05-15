#include "svgFunc.hpp"

extern string stroke;

void
show_histogram_svg(const vector<size_t>& bins) {
    
    const auto IMAGE_WIDTH = 200;
          auto IMAGE_HEIGHT = 360;
    const auto TEXT_LEFT = 20;
    const auto TEXT_HEIGHT = 20;
    const auto TOP_ALIGN = 20;
    const auto BLOCK_HEIGHT = 8;
    const auto RECT_WIDTH = 20;
    const auto MAX_LENGTH_OF_BIN = 40;
    
    size_t max_bin = bins[0];
        for (size_t bin : bins ) {
            if (bin > max_bin) {
                max_bin = bin;
            }
        }
    
    double left = TEXT_LEFT;
    const bool scaling_needed = max_bin > MAX_LENGTH_OF_BIN;
    const double scaling_factor = (double)MAX_LENGTH_OF_BIN / max_bin;
    if (!scaling_needed)
    {
        IMAGE_HEIGHT = TEXT_HEIGHT + TOP_ALIGN + BLOCK_HEIGHT * max_bin;
    }
    const auto BIN_HEIGHT = IMAGE_HEIGHT - TEXT_HEIGHT + TOP_ALIGN;
    const auto RECT_HEIGHT = BIN_HEIGHT - TEXT_HEIGHT;
    
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    
    for (size_t bin : bins) {
        double scaling_width_factor = 1;
        double bin_height = BLOCK_HEIGHT * bin;
        
        if (scaling_needed) {
            bin_height *= scaling_factor;
            if (bin >= 10) {
                scaling_width_factor = 1.5;
            }
            if (bin >= 100) {
                scaling_width_factor = 2;
            }
        }
        svg_text(left + 6, BIN_HEIGHT, to_string(bin));
        svg_rect(left, RECT_HEIGHT - bin_height, RECT_WIDTH * scaling_width_factor, bin_height, stroke);
        left += RECT_WIDTH * scaling_width_factor;
    }
    svg_end();
}
void
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}
void
svg_end() {
    cout << "</svg>\n";
}
void
svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}
void
svg_rect(double x, double y, double width, double height, string stroke, string fill) {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />";
}
