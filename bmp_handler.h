
#ifndef BMP_HANDLER_H
#define BMP_HANDLER_H

#include <stdint.h>
#include <stdio.h>

typedef uint16_t u16;
typedef uint32_t u32;

typedef struct {
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Pixel;

 
typedef struct {
    unsigned char header[54];
    u32 width;
    u32 height;
    u16 bit_depth;
    Pixel **pixels; 
    // 指向 Pixel 指標的指標，用於建立 2D 陣列
} BmpImage;

int read_bmp(const char* filename, BmpImage *image);
int write_bmp(const char* filename, BmpImage *image);
void free_bmp(BmpImage *image);
u32 read_u32(unsigned char *buf, int offset);
u16 read_u16(unsigned char *buf, int offset);


#endif 
