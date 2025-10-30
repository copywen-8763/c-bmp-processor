# BMP 影像處理器

這是一個 C 語言編寫的命令列工具，用於讀取、處理和寫入 24-bit BMP 影像檔案。

## 功能

* **讀取資訊 (Info):** 顯示 BMP 檔案的標頭資訊，如寬高、檔案大小等。
* **旋轉 (Rotate):** 將影像逆時針旋轉 90 度。
* **色彩通道交換 (RGB):** 變更像素的色彩通道。
* **調整大小 (Resize):** 將影像放大兩倍或縮小一半。
* **功能組合:** 可以使用數字代碼組合多個功能。

## 如何編譯

本專案使用 `make` 進行編譯。

1.  **編譯主程式:**
    ```bash
    make
    ```
    這將會產生一個名為 `bmp_processor` 的執行檔。

2.  **清除已編譯的檔案:**
    ```bash
    make clean
    ```
    這會移除 `bmp_processor` 執行檔和所有的 `.o` 物件檔案。

## 如何執行

程式透過命令列參數執行。

### 基本語法

```bash
./bmp_processor <input.bmp> <output.bmp> <mode> [options]
```


### 模式 (Mode) 參數

`mode` 是一個數字，用來指定要執行的操作。您可以將數字相加來組合多個功能：

* `1`: 讀取資訊 (Info)
* `2`: 旋轉 (Rotate)
* `4`: 色彩通道交換 (RGB)
* `8`: 調整大小 (Resize)

**注意:** 當 `mode` 包含 `8` (Resize) 時，必須提供第 5 個參數：
* `double`: 放大兩倍
* `half`: 縮小一半

### 範例

假設您有一個名為 `input.bmp` 的檔案：

* **僅讀取資訊 (Info):**
    ```bash
    ./bmp_processor input.bmp output.bmp 1
    ```
    (此模式不會寫入 `output.bmp`)

* **將影像旋轉 90 度:**
    ```bash
    ./bmp_processor input.bmp rotated.bmp 2
    ```

* **交換 RGB 色彩通道:**
    ```bash
    ./bmp_processor input.bmp swapped.bmp 4
    ```

* **將影像放大兩倍:**
    ```bash
    ./bmp_processor input.bmp doubled.bmp 8 double
    ```

* **將影像縮小一半:**
    ```bash
    ./bmp_processor input.bmp halved.bmp 8 half
    ```

* **組合功能：先縮小一半，再旋轉，最後交換 RGB:**
    (Resize = 8, Rotate = 2, RGB = 4) -> 8 + 2 + 4 = **14**
    ```bash
    ./bmp_processor input.bmp processed.bmp 14 half
    ```
    (程式會依照 Resize -> Rotate -> RGB 的順序執行)