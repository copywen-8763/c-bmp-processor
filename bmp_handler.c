#include <stdlib.h>
#include "bmp_handler.h"



// int read_bmp(const char* filename, BmpImage *image);
// int write_bmp(const char* filename, BmpImage *image);
// void free_bmp(BmpImage *image);
// uint32_t read_u32(unsigned char *buf, int offset);
// uint16_t read_u16(unsigned char *buf, int offset);


//for 16byte內容，將2*字串8byte組合成完整的32byte
u32 read_u32(unsigned char *buf, int offset)
{
    return buf[offset] | (buf[offset+1] << 8) |
           (buf[offset+2] << 16) | (buf[offset+3] << 24);
            //offset:要讀取的起點
}

//for 32byte內容，將4*字串8byte組合成完整的32byte
u16 read_u16(unsigned char *buf, int offset)
{
    return buf[offset] | (buf[offset+1] << 8);
}


int read_bmp(const char* filename, BmpImage *image) 
{
    FILE *fp = fopen(filename, "rb");
    if(!fp)
    {
        perror("fopen");
        return 1;
    }

    if(fread(image->header, 1, 54, fp) != 54)
    {
        printf("Failed to read BMP header\n");
        fclose(fp);
        return 1;
    }


    image->width = read_u32(image->header, 18);
    image->height = read_u32(image->header, 22);
    image->bit_depth = read_u16(image->header, 28);

    if(image->bit_depth != 24)
    {

        printf("Only 24-bit BMP is supported.\n");
        fclose(fp);
        return 1;
    }


    // 動態分配記憶體給像素陣列 不然會OUT OF MEMORY
    //將void malloc強轉為Pixel** malloc才能將數值給image->pixels這個同為Pixel**的變數
    //其中malloc分配的大小為圖片列數*（電腦地址位元數的空間）
    //
    image->pixels = (Pixel**)malloc(image->height * sizeof(Pixel*));
    if (!image->pixels)
    {
        printf("Memory allocation failed for pixel rows.\n");
        fclose(fp);
        return 1;
    }
    for (int i = 0; i < image->height; i++)
    {
        image->pixels[i] = (Pixel*)malloc(image->width * sizeof(Pixel));
        if (!image->pixels[i])
        {
            printf("Memory allocation failed for pixel columns.\n");

            for (int j = 0; j < i; j++) free(image->pixels[j]);
            free(image->pixels);
            fclose(fp);
            return 1;
        }
    }


    int padding = (4 - (image->width * 3) % 4) % 4;
    
    uint32_t data_offset = read_u32(image->header, 10);
    fseek(fp, data_offset, SEEK_SET);

    for (int y = image->height - 1; y >= 0; y--)
    {
        fread(image->pixels[y], sizeof(Pixel), image->width, fp);
        fseek(fp, padding, SEEK_CUR);
    }

    fclose(fp);
    return 0;
}


int write_bmp(const char* filename, BmpImage *image) {
    FILE *fo = fopen(filename, "wb");
    if (!fo)
    {
        perror("fopen output");
        return 1;
    }

    fwrite(image->header, 1, 54, fo);

    int padding = (4 - (image->width * 3) % 4) % 4;
    unsigned char pad[3] = {0x00, 0x00, 0x00};

  
    for (int y = image->height - 1; y >= 0; y--)
    {
        fwrite(image->pixels[y], sizeof(Pixel), image->width, fo);
        if (padding > 0)
        {
            fwrite(pad, 1, padding, fo);
        }
    }

    fclose(fo);
    return 0;
}

void free_bmp(BmpImage *image) {
    if (image && image->pixels)
    {
        for (int i = 0; i < image->height; i++)
        {
            free(image->pixels[i]);
        }
        free(image->pixels);
        image->pixels = NULL;
    }
}