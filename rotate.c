// rotate.c
#include <stdlib.h>
#include <string.h>
#include "rotate.h"

BmpImage* rotate_bmp_90(BmpImage *input_image) {
    BmpImage *output_image = (BmpImage*)malloc(sizeof(BmpImage));
    if (!output_image) return NULL;

    memcpy(output_image->header, input_image->header, 54);
    output_image->width = input_image->height;
    output_image->height = input_image->width;
    
    *(u32*)&output_image->header[18] = output_image->width;
    *(u32*)&output_image->header[22] = output_image->height;

    // 分配新圖片的記憶體
    output_image->pixels = (Pixel**)malloc(output_image->height * sizeof(Pixel*));
    for (int i = 0; i < output_image->height; i++) {
        output_image->pixels[i] = (Pixel*)malloc(output_image->width * sizeof(Pixel));
    }

    // 執行旋轉 (逆時針90度)
    for (u32 y = 0; y < input_image->height; y++) {
        for (u32 x = 0; x < input_image->width; x++) {
            output_image->pixels[input_image->width - 1 - x][y] = input_image->pixels[y][x];
        }
    }
    printf("Image rotated successfully in memory.\n");
    return output_image;
}