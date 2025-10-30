// rgb.c
#include "rgb.h"

void swap_color_channels(BmpImage *image) {
    for (uint32_t y = 0; y < image->height; y++) {
        // for (uint32_t x = 0; x < image->width; x++) {
        //     // BGR -> GBR,  B->G, G->R, R->B
        //     unsigned char temp_b = image->pixels[y][x].b;
        //     image->pixels[y][x].b = image->pixels[y][x].g; // Blue <- Green
        //     image->pixels[y][x].g = image->pixels[y][x].r; // Green <- Red
        //     image->pixels[y][x].r = temp_b;                // Red <- Blue
        // }
        for (uint32_t x = 0; x < image->width; x++) {
        // BGR -> RGB (箭頭反轉)
        // B <- R, G <- B, R <- G
            unsigned char temp_r = image->pixels[y][x].r; // 先把原始的紅色存起來
            image->pixels[y][x].r = image->pixels[y][x].g; // Red <- Green
            image->pixels[y][x].g = image->pixels[y][x].b; // Green <- Blue
            image->pixels[y][x].b = temp_r;                // Blue <- 原始的 Red
        }
    }
    printf("Color channels swapped successfully in memory.\n");
}