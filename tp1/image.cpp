//************************************************
//*                                              *
//*   TP 1&2    (c) 2017 J. FABRIZIO             *
//*                                              *
//*                               LRDE EPITA     *
//*                                              *
//************************************************

#include "image.hh"
#include <cstdlib>
#include <algorithm>
#include <iostream>

namespace tifo {

gray8_image::gray8_image(int _sx, int _sy) {
    sx = _sx;
    sy = _sy;

    length = sx*sy;
    pixels = (GRAY8)aligned_alloc(TL_IMAGE_ALIGNMENT, length);
}

gray8_image::~gray8_image() {
  free(pixels);
}

const GRAY8& gray8_image::get_buffer() const {
    return pixels;
}

GRAY8& gray8_image::get_buffer() {
    return pixels;
}

rgb24_image::rgb24_image(int _sx, int _sy) {
    sx = _sx;
    sy = _sy;

    length = sx*sy*3;
    pixels = (RGB8)aligned_alloc(TL_IMAGE_ALIGNMENT, length);
}

rgb24_image::rgb24_image(rgb_image& img) {
    sx = img.r_img->sx;
    sy = img.r_img->sy;
    length = sx * sy * 3;
    pixels = (RGB8)aligned_alloc(TL_IMAGE_ALIGNMENT, length);

    for (int i = 0; i < img.r_img->length; ++i)
    {
        pixels[i*3] = img.r_img->get_buffer()[i];
        pixels[i*3+1] = img.g_img->get_buffer()[i];
        pixels[i*3+2] = img.b_img->get_buffer()[i];
    }
}

rgb24_image::rgb24_image(hsv_image& img) {
    sx = img.h_img->sx;
    sy = img.h_img->sy;
    length = sx * sy * 3;
    pixels = (RGB8)aligned_alloc(TL_IMAGE_ALIGNMENT, length);

    for (int i = 0; i < img.h_img->length; ++i)
    {
        float h = ((float)img.h_img->get_buffer()[i] / 255.0f) * 360;
        float s = img.s_img->get_buffer()[i] / 255.0f;
        float v = img.v_img->get_buffer()[i] / 255.0f;

        int ti = (int)(h / 60) % 6;
        float f = h / 60 - ti;
        float l = v * (1 - s);
        float m = v * (1 - f * s);
        float n = v * (1 - (1 - f) * s);

        v *= 255;
        n *= 255;
        m *= 255;
        l *= 255;

        switch (ti)
        {
            case 0:
                pixels[i*3] = v;
                pixels[i*3+1] = n;
                pixels[i*3+2] = l;
                break;
            case 1:
                pixels[i*3] = m;
                pixels[i*3+1] = v;
                pixels[i*3+2] = l;
                break;
            case 2:
                pixels[i*3] = l;
                pixels[i*3+1] = v;
                pixels[i*3+2] = n;
                break;
            case 3:
                pixels[i*3] = l;
                pixels[i*3+1] = m;
                pixels[i*3+2] = v;
                break;
            case 4:
                pixels[i*3] = n;
                pixels[i*3+1] = l;
                pixels[i*3+2] = v;
                break;
            default:
                pixels[i*3] = v;
                pixels[i*3+1] = l;
                pixels[i*3+2] = m;
        }
    }
}

rgb24_image::~rgb24_image() {
  free(pixels);
}

const RGB8& rgb24_image::get_buffer() const {
    return pixels;
}

RGB8& rgb24_image::get_buffer() {
    return pixels;
}

rgb_image::rgb_image(rgb24_image& img)
{
    r_img = new gray8_image(img.sx, img.sy);
    g_img = new gray8_image(img.sx, img.sy);
    b_img = new gray8_image(img.sx, img.sy);
    for (int i = 0; i < img.length; i += 3)
    {
        r_img->get_buffer()[i/3] = img.get_buffer()[i];
        g_img->get_buffer()[i/3] = img.get_buffer()[i+1];
        b_img->get_buffer()[i/3] = img.get_buffer()[i+2];
    }
}

rgb_image::~rgb_image()
{
    free(r_img);
    free(g_img);
    free(b_img);
}

hsv_image::hsv_image(rgb24_image& img, float s_coef)
{
    h_img = new gray8_image(img.sx, img.sy);
    s_img = new gray8_image(img.sx, img.sy);
    v_img = new gray8_image(img.sx, img.sy);
    for (int i = 0; i < img.length; i += 3)
    {
        float r = img.get_buffer()[i] / 255.0f;
        float g = img.get_buffer()[i+1] / 255.0f;
        float b = img.get_buffer()[i+2] / 255.0f;
        auto min = std::min({r, g, b});
        auto max = std::max({r, g, b});

        float h = 0;
        float s = 0;
        float v = 0;
        // set hue
        if (min == max)
            h = 0;
        else if (max == r)
            h = (int)((60.0f * ((g - b) / (max - min))) + 360.0f) % 360;
        else if (max == g)
            h = (60 * ((b - r) / (max - min))) + 120;
        else if (max == b)
            h = (60 * (r - g) / (max - min)) + 240;
        h_img->get_buffer()[i/3] = h / 360.0f * 255.0f;

        // set saturation
        if (max == 0)
            s = 0;
        else
            s = (1.0f - (min / max)) * 255;
        s *= s_coef;
        s_img->get_buffer()[i/3] = s;

        // set v
        v_img->get_buffer()[i/3] = max * 255.0f;
    }
}

hsv_image::~hsv_image()
{
    free(h_img);
    free(s_img);
    free(v_img);
}

}
