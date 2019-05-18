#include "tools.hh"

namespace tifo
{
    gray8_image *rgb_to_gray(const rgb24_image& rgb_img)
    {
        gray8_image *gray_img = new gray8_image(rgb_img.sx, rgb_img.sy);
        for (int i = 0; i < rgb_img.length; i += 3)
        {
            const auto& r = rgb_img.get_buffer()[i];
            const auto& g = rgb_img.get_buffer()[i+1];
            const auto& b = rgb_img.get_buffer()[i+2];
            gray_img->get_buffer()[i/3] = r * 0.2989 + g * 0.5870 + b * 0.1140;
        }
        return gray_img;
    }

    rgb24_image *gray_to_rgb(const gray8_image& gray_img)
    {
        rgb24_image *rgb_img = new rgb24_image(gray_img.sx, gray_img.sy);
        for (int i = 0; i < gray_img.length; ++i)
        {
            int j = 3*i;
            rgb_img->get_buffer()[j] = gray_img.get_buffer()[i];
            rgb_img->get_buffer()[j+1] = gray_img.get_buffer()[i];
            rgb_img->get_buffer()[j+2] = gray_img.get_buffer()[i];
        }
        return rgb_img;
    }

    gray8_image *convolution(const gray8_image& gray_img,
                             std::vector<std::vector<float>> kernel)
    {
        auto w = gray_img.sx;
        auto h = gray_img.sy;

        auto res_img = new gray8_image(w, h);

        for (int i = 0; i < h; ++i)
        {
            for (int j = 0; j < w; ++j)
            {
                float sum = 0;
                for (int k = 0; k < kernel.size(); ++k)
                {
                    for (int l = 0; l < kernel[0].size(); ++l)
                    {
                        int index = (i - (kernel.size() / 2) + k) * w + (j - (kernel[0].size() / 2) + l);
                        if (index >= 0 && index < gray_img.length)
                            sum += kernel[k][l] * ((float)gray_img.get_buffer()[index] / 255.0f);
                    }
                }
                if (sum > 1)
                    sum = 1;
                else if (sum < 0)
                    sum = 0;
                res_img->get_buffer()[i * w + j] = sum * 255;

            }
        }
        return res_img;
    }
}
