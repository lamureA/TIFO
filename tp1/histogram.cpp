//************************************************
//*                                              *
//*   TP 1&2    (c) 2017 J. FABRIZIO             *
//*                                              *
//*                               LRDE EPITA     *
//*                                              *
//************************************************

#include <iostream>
#include <fstream>

#include "histogram.hh"


namespace tifo {
    Histogram_1d::Histogram_1d(const gray8_image& img)
    {
        for (int i = 0; i < IMAGE_NB_LEVELS; ++i)
            histogram[i] = 0;
        for (int i = 0; i < img.length; ++i)
            histogram[img.get_buffer()[i]]++;

        // histogramme cumulé
        hc[0] = histogram[0];
        for (int i = 1; i < IMAGE_NB_LEVELS; ++i)
            hc[i] = hc[i-1] + histogram[i];
    }

    void Histogram_1d::print(const char* fileout)
    {
        std::ofstream myfile;
        myfile.open (fileout);
        for (int i = 0; i < IMAGE_NB_LEVELS; ++i)
        {
            myfile << histogram[i] << "\n";
        }
        myfile.close();
    }

    void Histogram_1d::print_hc(const char* fileout)
    {
        std::ofstream myfile;
        myfile.open (fileout);
        for (int i = 0; i < IMAGE_NB_LEVELS; ++i)
        {
            myfile << hc[i] << "\n";
        }
        myfile.close();
    }

    void Histogram_1d::egalize(const gray8_image& img)
    {
        float ratio = (float)IMAGE_MAX_LEVEL / (float)img.length;
        for (int i = 0; i < img.length; ++i)
        {
            img.get_buffer()[i] = hc[img.get_buffer()[i]] * ratio;
        }
    }
}
