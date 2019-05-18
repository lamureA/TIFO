#pragma once

#include <vector>

#include "image.hh"

namespace tifo
{
    gray8_image *rgb_to_gray(const rgb24_image& rgb_img);
    rgb24_image *gray_to_rgb(const gray8_image& gray_img);

    gray8_image *convolution(const gray8_image& gray_img,
                             std::vector<std::vector<float>> kernel);
}
