//************************************************
//*                                              *
//*   TP 1&2    (c) 2017 J. FABRIZIO             *
//*                                              *
//*                               LRDE EPITA     *
//*                                              *
//************************************************

#ifndef HISTOGRAM_HH
#define	HISTOGRAM_HH

#include "image.hh"

namespace tifo {

  class Histogram_1d
  {
  public:
    Histogram_1d(const gray8_image& img);
    void print(const char* fileout);
    void print_hc(const char* fileout);
    void egalize(const gray8_image& img);

    unsigned long histogram[IMAGE_NB_LEVELS];
    unsigned long hc[IMAGE_NB_LEVELS];
  };
}

#endif
