#include "img.hh"

#include <fstream>

unsigned char get_2bits(unsigned char byte, int position) // position in range 0-7
{
    return (byte >> position) & 0x3;
}

IMG::IMG(std::string filename)
{

    width = 3280;
    height = 2464;
    data = std::vector<std::vector<double>>(height);

    std::ifstream file_in(filename, std::ios::binary);
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(file_in), {});

    size_t index = 0;
    for (size_t i = 0; i < height; ++i)
    {
        data[i] = std::vector<double>(width);
        for (size_t j = 0; j < width; j+=4)
        {
            int c1 = buffer[index];
            c1 = c1 << 2 | get_2bits(buffer[index + 4], 0);
            int c2 = buffer[index + 1];
            c2 = c2 << 2 | get_2bits(buffer[index + 4], 2);
            int c3 = buffer[index + 2];
            c3 = c3 << 2 | get_2bits(buffer[index + 4], 4);
            int c4 = buffer[index + 3];
            c4 = c4 << 2 | get_2bits(buffer[index + 4], 6);
            //data[i][j] = Pixel(r, g1, g2, b);
            data[i][j] = c1;
            data[i][j+1] = c2;
            data[i][j+2] = c3;
            data[i][j+3] = c4;
            index += 5;
        }
    }
}

void IMG::to_ppm()
{
    std::ofstream file_out;
    file_out.open("samples/img.ppm");
    file_out << "P3\n";
    file_out << width/2 << " " << height/2 << "\n";
    file_out << "1023\n";
    for (size_t i = 0; i < height; i+=2)
    {
        for (size_t j = 0; j < width; j+=2)
        {
            file_out << data[i][j] << " " << data[i][j+1] << " " << data[i+1][j+1];
            if (j < width - 2)
                file_out << " ";
        }
        file_out << "\n";
    }
    file_out.close();
}

void IMG::bp_detection()
{
    // search min
    double min_r = 1024;
    double min_g = 1024;
    double min_b = 1024;
    for (size_t i = 0; i < height; ++i)
    {
        for (size_t j = 0; j < width; ++j)
        {
            if (i % 2 == 0)
            {
                if (j % 2 == 0) // Blue
                {
                    if (data[i][j] < min_b)
                        min_b = data[i][j];
                }
                else // Green
                {
                    if (data[i][j] < min_g)
                        min_g = data[i][j];
                }
            }
            else
            {
                if (j % 2 == 0) // Green
                {
                    if (data[i][j] < min_g)
                        min_g = data[i][j];
                }
                else // Red
                {
                    if (data[i][j] < min_r)
                        min_r = data[i][j];
                }
            }
        }
    }


    // Substract with min
    for (size_t i = 0; i < height; ++i)
    {
        for (size_t j = 0; j < width; ++j)
        {
            if (i % 2 == 0)
            {
                if (j % 2 == 0) // Blue
                    data[i][j] -= min_b;
                else // Green
                    data[i][j] -= min_g;
            }
            else
            {
                if (j % 2 == 0) // Green
                    data[i][j] -= min_g;
                else // Red
                    data[i][j] -= min_r;
            }
        }
    }
}
