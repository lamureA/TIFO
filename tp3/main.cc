#include <iostream>

#include "img.hh"

int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;
    IMG img(argv[1]);
    img.bp_detection();
    img.to_ppm();
    return 0;
}
