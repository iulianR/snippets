#include "bmp.h"

int main()
{
    bmp::Image image("color.bmp");
    image.save("color_out.bmp");
    return 0;
}
