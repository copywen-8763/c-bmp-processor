#ifndef RESIZE_H
#define RESIZE_H

#include "bmp_handler.h" 

BmpImage* resize_double(const BmpImage *src_image);
BmpImage* resize_half(const BmpImage *src_image);

#endif 