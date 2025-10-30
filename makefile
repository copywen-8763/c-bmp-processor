# ----------------------------------------------------
# Makefile for BMP 影像處理器
# ----------------------------------------------------

# 編譯器設定
CC = gcc
# CFLAGS:
# -Wall: 顯示所有警告
# -Wextra: 顯示額外的警告
# -g: 產生除錯資訊
# -O2: 等級 2 的優化
# -std=c99: 使用 C99 標準
CFLAGS = -Wall -Wextra -g -O2 -std=c99

# 執行檔名稱
TARGET = bmp_processor

# 專案所需的原始碼檔案
# 我們明確列出需要的檔案，以避免編譯到測試檔 (如 pixel_test.c)
SRCS = main.c bmp_handler.c info.c rotate.c rgb.c resize.c

# 根據原始碼檔案名稱產生對應的 .o 物件檔案名稱
OBJS = $(SRCS:.c=.o)

# --- 規則 (Rules) ---

# 預設規則：第一個規則是 `make` 指令的預設目標
all: $(TARGET)

# 連結規則：將所有的 .o 物件檔案連結成最終的執行檔
$(TARGET): $(OBJS)
	@echo "正在連結執行檔 -> $@"
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "編譯完成！執行檔為: $(TARGET)"

# 編譯規則：將每個 .c 檔案編譯成對應的 .o 檔案
# $< 代表第一個依賴項目 (即 .c 檔案)
# $@ 代表目標 (即 .o 檔案)
%.o: %.c
	@echo "正在編譯 -> $<"
	$(CC) $(CFLAGS) -c $< -o $@

# 清除規則：移除所有編譯產生的檔案
clean:
	@echo "正在清除已編譯的檔案..."
	rm -f $(TARGET) $(OBJS)
	@echo "清除完成。"

# .PHONY 宣告了 "all" 和 "clean" 是虛擬目標，
# 它們不代表實際的檔案名稱，以避免與同名檔案衝突。
.PHONY: all clean


#made by gpt :))