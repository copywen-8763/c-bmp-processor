#include <stdlib.h>
#include <string.h>
#include "resize.h"

static void update_bmp_header(BmpImage *image, u32 new_width, u32 new_height) {
    image->width = new_width;
    image->height = new_height;

    *(u32*)&image->header[18] = new_width;
    *(u32*)&image->header[22] = new_height;

    // 更新檔案大小和圖像大小
    // 每行的 byte 數需為 4 的倍數
    u32 row_size = new_width * 3;
    u32 padding = (4 - (row_size % 4)) % 4;
    u32 image_data_size = (row_size + padding) * new_height;
    u32 file_size = 54 + image_data_size;
    
    *(u32*)&image->header[2] = file_size;      
    *(u32*)&image->header[34] = image_data_size; 
}


BmpImage* resize_double(const BmpImage *src_image) {
    u32 new_width = src_image->width * 2;
    u32 new_height = src_image->height * 2;

   
    BmpImage *new_image = (BmpImage*)malloc(sizeof(BmpImage));
    if (!new_image) return NULL;

    memcpy(new_image->header, src_image->header, 54);
    update_bmp_header(new_image, new_width, new_height);
    
    new_image->pixels = (Pixel**)malloc(new_height * sizeof(Pixel*));
    for (u32 i = 0; i < new_height; i++) {
        new_image->pixels[i] = (Pixel*)malloc(new_width * sizeof(Pixel));
    }

    for (u32 y = 0; y < src_image->height; y++) {
        for (u32 x = 0; x < src_image->width; x++) {
            Pixel p = src_image->pixels[y][x];
            
            u32 y_new = y * 2;
            u32 x_new = x * 2;

            new_image->pixels[y_new][x_new]       = p; // 左上
            new_image->pixels[y_new][x_new + 1]   = p; // 右上
            new_image->pixels[y_new + 1][x_new]   = p; // 左下
            new_image->pixels[y_new + 1][x_new + 1] = p; // 右下
        }
    }
    
    printf("Image doubled in size successfully in memory.\n");
    return new_image;
}


BmpImage* resize_half(const BmpImage *src_image) {
    u32 new_width = src_image->width / 2;
    u32 new_height = src_image->height / 2;

    if (new_width == 0 || new_height == 0) return NULL;

    BmpImage *new_image = (BmpImage*)malloc(sizeof(BmpImage));
    if (!new_image) return NULL;
    
    memcpy(new_image->header, src_image->header, 54);
    update_bmp_header(new_image, new_width, new_height);

    new_image->pixels = (Pixel**)malloc(new_height * sizeof(Pixel*));
    for (u32 i = 0; i < new_height; i++) {
        new_image->pixels[i] = (Pixel*)malloc(new_width * sizeof(Pixel));
    }

    for (u32 y = 0; y < new_height; y++) {
        for (u32 x = 0; x < new_width; x++) {
            u32 src_y = y * 2;
            u32 src_x = x * 2;
            
            new_image->pixels[y][x] = src_image->pixels[src_y][src_x];
        }
    }
    
    printf("Image halved in size successfully in memory.\n");
    return new_image;
}