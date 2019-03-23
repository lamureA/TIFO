#include <iostream>

#include "image.hh"
#include "image_io.hh"
#include "tools.hh"
#include "histogram.hh"


void exo1(char *filename)
{
    // load image in RGB24
    tifo::rgb24_image *rgb_img = tifo::load_image(filename);
    // transform to GRAY8
    auto *gray_img = tifo::rgb_to_gray(*rgb_img);

    // transform back to RGB24 and save
    auto *rgb_img2 = tifo::gray_to_rgb(*gray_img);
    tifo::save_image(*rgb_img2, "results/out.tga");
    delete rgb_img2;

    // compute and save histo and cumulate histo
    auto histo = tifo::Histogram_1d(*gray_img);
    histo.print("results/histo.csv");
    histo.print_hc("results/hc.csv");
    // egalize histo and save
    histo.egalize(*gray_img);
    histo = tifo::Histogram_1d(*gray_img);
    histo.print("results/histo-egalized.csv");
    histo.print_hc("results/hc-egalized.csv");

    // save the egalized image
    rgb_img2 = tifo::gray_to_rgb(*gray_img);
    tifo::save_image(*rgb_img2, "results/out-egalized.tga");
    delete rgb_img;
    delete rgb_img2;
    delete gray_img;
}

void exo1_2_rgb(char *filename)
{
    // load image in RGB24
    tifo::rgb24_image *rgb24_img = tifo::load_image(filename);
    // transform to RGB
    auto rgb_img = tifo::rgb_image(*rgb24_img);

    // save each color
    auto *rgb24_img_r = tifo::gray_to_rgb(*rgb_img.r_img);
    auto *rgb24_img_g = tifo::gray_to_rgb(*rgb_img.g_img);
    auto *rgb24_img_b = tifo::gray_to_rgb(*rgb_img.b_img);
    tifo::save_image(*rgb24_img_r, "results/out-r.tga");
    tifo::save_image(*rgb24_img_g, "results/out-g.tga");
    tifo::save_image(*rgb24_img_b, "results/out-b.tga");
    // transform back to RGB24 and save
    auto *rgb24_img2 = new tifo::rgb24_image(rgb_img);
    tifo::save_image(*rgb24_img2, "results/out-rgb.tga");
    delete rgb24_img2;

    // compute and save histo and cumulate histo
    auto histo_r = tifo::Histogram_1d(*rgb_img.r_img);
    histo_r.print("results/histo_r.csv");
    histo_r.print_hc("results/hc_r.csv");
    auto histo_g = tifo::Histogram_1d(*rgb_img.g_img);
    histo_g.print("results/histo_g.csv");
    histo_g.print_hc("results/hc_g.csv");
    auto histo_b = tifo::Histogram_1d(*rgb_img.b_img);
    histo_b.print("results/histo_b.csv");
    histo_b.print_hc("results/hc_b.csv");

    // egalize histo and save
    histo_r.egalize(*rgb_img.r_img);
    histo_r = tifo::Histogram_1d(*rgb_img.r_img);
    histo_r.print("results/histo_r-egalized.csv");
    histo_r.print_hc("results/hc_r-egalized.csv");
    histo_g.egalize(*rgb_img.g_img);
    histo_g = tifo::Histogram_1d(*rgb_img.g_img);
    histo_g.print("results/histo_g-egalized.csv");
    histo_g.print_hc("results/hc_g-egalized.csv");
    histo_b.egalize(*rgb_img.b_img);
    histo_b = tifo::Histogram_1d(*rgb_img.b_img);
    histo_b.print("results/histo_b-egalized.csv");
    histo_b.print_hc("results/hc_b-egalized.csv");

    // save the egalized image
    rgb24_img2 = new tifo::rgb24_image(rgb_img);
    tifo::save_image(*rgb24_img2, "results/out-rgb-egalized.tga");
    delete rgb24_img;
    delete rgb24_img2;
    delete rgb24_img_r;
    delete rgb24_img_g;
    delete rgb24_img_b;
}

void exo1_2_hsv(char *filename, float s_coef)
{
    // load image in RGB24
    tifo::rgb24_image *rgb24_img = tifo::load_image(filename);
    // transform to RGB
    auto hsv_img = tifo::hsv_image(*rgb24_img, s_coef);

    // save each color
    auto *rgb24_img_h = tifo::gray_to_rgb(*hsv_img.h_img);
    auto *rgb24_img_s = tifo::gray_to_rgb(*hsv_img.s_img);
    auto *rgb24_img_v = tifo::gray_to_rgb(*hsv_img.v_img);
    tifo::save_image(*rgb24_img_h, "results/out-h.tga");
    tifo::save_image(*rgb24_img_s, "results/out-s.tga");
    tifo::save_image(*rgb24_img_v, "results/out-v.tga");
    // transform back to RGB24 and save
    auto *rgb24_img2 = new tifo::rgb24_image(hsv_img);
    tifo::save_image(*rgb24_img2, "results/out-hsv.tga");
    delete rgb24_img2;

    // compute and save histo and cumulate histo
    auto histo_v = tifo::Histogram_1d(*hsv_img.v_img);
    histo_v.print("results/histo_v.csv");
    histo_v.print_hc("results/hc_v.csv");

    // egalize histo and save
    histo_v.egalize(*hsv_img.v_img);
    histo_v = tifo::Histogram_1d(*hsv_img.v_img);
    histo_v.print("results/histo_v-egalized.csv");
    histo_v.print_hc("results/hc_v-egalized.csv");

    // save the egalized image
    rgb24_img2 = new tifo::rgb24_image(hsv_img);
    tifo::save_image(*rgb24_img2, "results/out-hsv-egalized.tga");
    delete rgb24_img;
    delete rgb24_img2;
    delete rgb24_img_h;
    delete rgb24_img_s;
    delete rgb24_img_v;
}

void exo3_hsv(char *filename)
{
    // load image in RGB24
    tifo::rgb24_image *rgb24_img = tifo::load_image(filename);
    // transform to RGB
    auto hsv_img = tifo::hsv_image(*rgb24_img);

    // save each color
    auto *rgb24_img_h = tifo::gray_to_rgb(*hsv_img.h_img);
    auto *rgb24_img_s = tifo::gray_to_rgb(*hsv_img.s_img);
    auto *rgb24_img_v = tifo::gray_to_rgb(*hsv_img.v_img);
    tifo::save_image(*rgb24_img_h, "results/out-h.tga");
    tifo::save_image(*rgb24_img_s, "results/out-s.tga");
    tifo::save_image(*rgb24_img_v, "results/out-v.tga");

    std::vector<std::vector<float>> blur_kernel(
        // BOX BLUR
        {{1.0/9.0, 1.0/9.0, 1.0/9.0},
         {1.0/9.0, 1.0/9.0, 1.0/9.0},
         {1.0/9.0, 1.0/9.0, 1.0/9.0}});
    std::vector<std::vector<float>> laplacian_kernel(
        // LAPLCIAN
        {{0, -1, 0},
         {-1, 5, -1},
         {0, -1, 0}});
    auto *v_img_blur = convolution(*hsv_img.v_img, blur_kernel);
    auto *v_img_laplace = convolution(*hsv_img.v_img, laplacian_kernel);
    delete v_img_blur;
    auto *rgb24_img_v_laplace = tifo::gray_to_rgb(*v_img_laplace);
    tifo::save_image(*rgb24_img_v_laplace, "results/out-v-laplace.tga");
    delete hsv_img.v_img;
    hsv_img.v_img = v_img_laplace;

    // transform back to RGB24 and save
    auto *rgb24_img2 = new tifo::rgb24_image(hsv_img);
    tifo::save_image(*rgb24_img2, "results/out-hsv.tga");

    delete rgb24_img;
    delete rgb24_img2;
    delete rgb24_img_h;
    delete rgb24_img_s;
    delete rgb24_img_v;
}

int main(int argc, char **argv)
{
    exo3_hsv(argv[1]);
    return 0;
}
