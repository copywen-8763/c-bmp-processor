
#include <stdio.h>
#include "info.h"

void process_bmp_info(BmpImage *image) {
    printf("BMP Info:\n");
    printf("  File size: %u bytes\n", read_u32(image->header, 2));
    printf("  Offset to pixels: %u bytes\n", read_u32(image->header, 10));
    printf("  Width: %d\n", image->width);
    printf("  Height: %d\n", image->height);
    printf("  Bit depth: %u\n", image->bit_depth);
}