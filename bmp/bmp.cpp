#include "bmp.h"

#include <cstring>
#include <fstream>
#include <iterator>
#include <iostream>

using namespace std;

namespace bmp {

Image::~Image()
{
    ::memset(&m_bfh, 0x00, sizeof m_bfh);
    ::memset(&m_bih, 0x00, sizeof m_bih);
    ::memset(&m_data, 0x00, sizeof m_data);
}

void Image::load()
{
    ifstream stream(m_filename, ios::binary);
    if (!stream.is_open())
        return;

    ::memset(&m_bfh, 0x00, sizeof m_bfh);
    ::memset(&m_bih, 0x00, sizeof m_bih);

    stream.read(reinterpret_cast<char*>(&m_bfh), sizeof m_bfh);
    stream.read(reinterpret_cast<char*>(&m_bih), sizeof m_bih);

    m_width = m_bih.width;
    m_height = m_bih.height;

    m_bpp = m_bih.color_depth >> 3;

    m_row_inc = m_width * m_bpp;
    m_data.resize(m_height * m_row_inc);

    int padding = (4 - ((m_bpp * m_width) % 4)) % 4;
    char padding_data[4] = {0,0,0,0};

    for (unsigned int i; i < m_height; ++i) {
        int row_index = m_height - i - 1;
        unsigned char* data = const_cast<unsigned char*>(&m_data[m_row_inc * row_index]);

        stream.read(reinterpret_cast<char*>(data), sizeof(char) * m_bpp * m_width);
        stream.read(padding_data, padding);
    }

    stream.close();
}

void Image::save(const std::string& filename)
{
    ofstream stream(filename, ios::binary);
    if (!stream.is_open())
        return;

    stream.write(reinterpret_cast<char*>(&m_bfh), sizeof m_bfh);
    stream.write(reinterpret_cast<char*>(&m_bih), sizeof m_bih);

    int padding = (4 - ((m_bpp * m_width) % 4)) % 4;
    char padding_data[4] = {0x00,0x00,0x00,0x00};

    for (unsigned int i = 0; i < m_height; i++) {
        int row_index = m_height - i - 1;
        const unsigned char* data = &m_data[m_row_inc * row_index];

        stream.write(reinterpret_cast<const char*>(data), sizeof(unsigned char) * m_bpp * m_width);
        stream.write(padding_data, padding);
    }

    stream.close();
}

}
