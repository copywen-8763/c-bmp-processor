
#include <stdio.h>    
#include <stdlib.h>   
#include <stdbool.h>    
#include <string.h>     


#include "bmp_handler.h"
#include "info.h"
#include "rotate.h"
#include "rgb.h"
#include "resize.h"


#define INFO   1
#define ROTATE 2
#define RGB    4
#define RESIZE 8


int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("使用方式: %s <input.bmp> <output.bmp> <mode> [options]\n", argv[0]);
        printf("mode 列表:\n");
        printf("  1 = info\n");
        printf("  2 = rotate\n");
        printf("  4 = rgb\n");
        printf("  8 = resize (需要第5個參數: 'double' 或 'half')\n");
        printf("  可組合, 例如 12 = rgb + resize\n");
        return 1;
    }

    const char* input_file = argv[1];
    const char* output_file = argv[2];
    int mode = atoi(argv[3]);

    // 如果模式包含 resize，檢查是否有第5個參數
    if ((mode & RESIZE) && argc < 5) {
        printf("錯誤: resize 模式需要第5個參數 ('double' 或 'half').\n");
        return 1;
    }

    BmpImage *current_image = (BmpImage*)malloc(sizeof(BmpImage));
    if (!current_image) return 1;

    // --- 1. 讀取檔案 ---
    if (read_bmp(input_file, current_image) != 0) {
        printf("Failed to read BMP file: %s\n", input_file);
        free(current_image);
        return 1;
    }
    
    bool needs_write = false;

    // --- 2. 模式處理 (在記憶體中) ---
    if (mode & INFO) {
        printf("--- 執行 Info 功能 ---\n");
        process_bmp_info(current_image);
    }

    if (mode & RESIZE) {
        printf("--- 執行 Resize 功能 ---\n");
        const char* resize_opt = argv[4];
        BmpImage *resized_image = NULL;

        if (strcmp(resize_opt, "double") == 0) {
            resized_image = resize_double(current_image);
        } else if (strcmp(resize_opt, "half") == 0) {
            resized_image = resize_half(current_image);
        } else {
            printf("錯誤: 無效的 resize 選項 '%s'. 請使用 'double' 或 'half'.\n", resize_opt);
        }

        if (resized_image) {
            free_bmp(current_image);
            free(current_image);
            current_image = resized_image;
            needs_write = true;
        }
    }

    if (mode & ROTATE) {
        printf("--- 執行 Rotate 功能 ---\n");
        BmpImage *rotated_image = rotate_bmp_90(current_image);
        
        free_bmp(current_image);
        free(current_image);
        current_image = rotated_image;
        needs_write = true;
    }

    if (mode & RGB) {
        printf("--- 執行 RGB 功能 ---\n");
        swap_color_channels(current_image);
        needs_write = true;
    }


    if (needs_write) {
        if (write_bmp(output_file, current_image) == 0) {
            printf("Output saved to %s\n", output_file);
        } else {
            printf("Failed to write BMP file: %s\n", output_file);
        }
    } else if (!(mode & INFO)) {
         printf("模式 %d 不需要寫入輸出檔案。\n", mode);
    }
    

    free_bmp(current_image);
    free(current_image);
    
    return 0;
}