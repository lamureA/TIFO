#pragma once

#include <string>
#include <vector>

#include "pixel.hh"

class IMG
{
public:
    IMG(std::string filename);
    void to_ppm();
    void bp_detection();

    size_t width;
    size_t height;
    std::vector<std::vector<double>> data;
};
