#pragma once

#include <string>
#include <vector>

namespace bmp {
    class Image {

    public:
        Image(const std::string& filename)
            : m_filename(filename)
            , m_width(0)
            , m_height(0)
            , m_row_inc(0)
        { load(); }
        ~Image();
        void save(const std::string& filename);
        unsigned int width() { return m_width; }
        unsigned int height() { return m_height; }

    private:
        void load();

        struct __attribute__((packed)) BitmapFileHeader {
            uint16_t signature;
            uint32_t size;
            uint16_t reserved_1;
            uint16_t reserved_2;
            uint32_t offset;
        };

        struct __attribute__((packed)) BitmapInformationHeader {
            uint32_t size;
            uint32_t width;
            uint32_t height;
            uint16_t planes;
            uint16_t color_depth;
            uint32_t compression;
            uint32_t image_size;
            uint32_t x_ppm;
            uint32_t y_ppm;
            uint32_t n_colors;
            uint32_t n_colors_important;
        };

        std::string m_filename;
        unsigned int m_width;
        unsigned int m_height;
        unsigned int m_bpp;
        unsigned int m_row_inc;
        std::vector<unsigned char> m_data;

        BitmapFileHeader m_bfh;
        BitmapInformationHeader m_bih;
    };
}
