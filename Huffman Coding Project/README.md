# Huffman Coding – Chương trình nén dữ liệu

Chương trình cài đặt thuật toán **Huffman Coding** bằng C++, áp dụng chiến lược tham lam (Greedy Algorithm) để xây dựng cây mã hóa tối ưu, nén và giải nén dữ liệu văn bản không mất mát thông tin (lossless compression).

---

## 📋 Mục lục

- [Giới thiệu](#-giới-thiệu)
- [Tính năng](#-tính-năng)
- [Cấu trúc project](#-cấu-trúc-project)
- [Hai giao diện của chương trình](#-hai-giao-diện-của-chương-trình)
- [Yêu cầu hệ thống](#-yêu-cầu-hệ-thống)
- [Hướng dẫn cài đặt](#-hướng-dẫn-cài-đặt)
- [Hướng dẫn biên dịch và chạy](#-hướng-dẫn-biên-dịch-và-chạy)
- [Hướng dẫn sử dụng](#-hướng-dẫn-sử-dụng)
- [Ví dụ kết quả](#-ví-dụ-kết-quả)
- [Nguyên lý thuật toán](#-nguyên-lý-thuật-toán)
- [Đánh giá thuật toán](#-đánh-giá-thuật-toán)

---

## 🔎 Giới thiệu

Huffman Coding là thuật toán nén dữ liệu do David Huffman phát triển, dựa trên nguyên tắc: ký tự xuất hiện càng nhiều thì được gán mã nhị phân càng ngắn, ký tự xuất hiện càng ít thì mã càng dài. Đây là một ứng dụng tiêu biểu của **chiến lược tham lam (Greedy Algorithm)** kết hợp với cấu trúc **cây nhị phân** và **hàng đợi ưu tiên (Priority Queue / Min-Heap)**.

Chương trình cho phép:
- Xây dựng cây Huffman từ dữ liệu đầu vào.
- Sinh bảng mã nhị phân cho từng ký tự.
- Mã hóa (nén) và giải mã (giải nén) văn bản.
- Kiểm tra tính đúng đắn của quá trình giải mã.
- Tính toán tỷ lệ nén dữ liệu.

---

## ✨ Tính năng

| STT | Chức năng | Mô tả |
|---|---|---|
| 1 | Nhập dữ liệu từ bàn phím | Người dùng gõ trực tiếp chuỗi cần nén |
| 2 | Đọc dữ liệu từ file `.txt` | Đọc nội dung file văn bản để nén |
| 3 | Chạy bộ dữ liệu mẫu | Kiểm thử nhanh với nhiều bộ dữ liệu có sẵn |
| 4 | Hiển thị bảng mã Huffman | In ra ký tự, tần suất, mã nhị phân tương ứng |
| 5 | Kiểm tra giải mã | So sánh văn bản giải mã với văn bản gốc |
| 6 | Tính tỷ lệ nén | Hiển thị % dung lượng tiết kiệm được |

---

## 📁 Cấu trúc project

```
HuffmanCoding_Project/
├── huffman.h        # Khai báo lớp HuffmanCoding và cấu trúc Node
├── huffman.cpp       # Cài đặt thuật toán: xây cây, mã hóa, giải mã
├── main.cpp           # Giao diện console chính thức (C++)
├── index.html          # Giao diện minh họa trực quan (HTML/CSS/JS)
├── data1.txt           # File dữ liệu mẫu để kiểm thử (tùy chọn)
└── README.md          # Tài liệu hướng dẫn (file này)
```

**Nguyên tắc tách file:**
- `huffman.h` / `huffman.cpp` chứa toàn bộ **logic thuật toán**, độc lập với giao diện.
- `main.cpp` chỉ gọi các hàm public từ `HuffmanCoding` để xây dựng giao diện, không xử lý thuật toán trực tiếp.

---

## 🖥 Hai giao diện của chương trình

Đồ án cung cấp **2 giao diện độc lập** cho cùng một thuật toán:

| | `main.cpp` | `index.html` |
|---|---|---|
| Ngôn ngữ | C++ | HTML / CSS / JavaScript |
| Vai trò | **Giao diện chính thức nộp bài**, đúng yêu cầu đề bài "lập trình bằng C++" | Giao diện minh họa trực quan, hỗ trợ trình bày/demo sinh động hơn |
| Cách chạy | Biên dịch bằng `g++`, chạy trong terminal | Mở trực tiếp bằng trình duyệt, không cần cài đặt |
| Thuật toán | Cài đặt gốc trong `huffman.h` / `huffman.cpp` | Cài đặt lại **y hệt logic** bằng JavaScript (do trình duyệt không thể gọi trực tiếp file `.exe` của C++) |

> **Lưu ý:** hai giao diện chạy độc lập, không kết nối trực tiếp với nhau. Phần thuật toán C++ (`huffman.h`/`huffman.cpp`) mới là phần được chấm điểm theo đúng yêu cầu đề bài; `index.html` là phần mở rộng giúp trình bày trực quan, sinh động hơn khi báo cáo/demo trước lớp.

---

## 💻 Yêu cầu hệ thống

- Trình biên dịch hỗ trợ **C++17** trở lên (khuyến nghị: **g++** từ MinGW-w64 hoặc GCC trên Linux/Mac).
- **Visual Studio Code** (khuyến nghị) hoặc bất kỳ IDE C++ nào khác.
- Hệ điều hành: Windows / macOS / Linux.

---

## ⚙️ Hướng dẫn cài đặt

### Windows
1. Cài **MSYS2**: [https://www.msys2.org](https://www.msys2.org)
2. Mở **MSYS2 MinGW64**, chạy:
   ```bash
   pacman -S mingw-w64-x86_64-gcc
   ```
3. Thêm đường dẫn `C:\msys64\mingw64\bin` vào biến môi trường `PATH`.
4. Kiểm tra cài đặt:
   ```bash
   g++ --version
   ```

### macOS
```bash
xcode-select --install
```

### Linux
```bash
sudo apt install g++
```

---

## 🔧 Hướng dẫn biên dịch và chạy

Mở **Terminal** trong VS Code (`` Ctrl + ` ``), đảm bảo đang ở đúng thư mục chứa các file `.cpp` / `.h`.

**Biên dịch:**
```bash
g++ -std=c++17 -o huffman huffman.cpp main.cpp
```

**Chạy chương trình:**

| Hệ điều hành | Lệnh chạy |
|---|---|
| Windows (Git Bash / MinGW64) | `./huffman.exe` |
| Windows (CMD/PowerShell) | `.\huffman.exe` |
| macOS / Linux | `./huffman` |

> ⚠️ **Lưu ý:** Không gõ dấu `$` khi nhập lệnh — dấu `$` chỉ là ký hiệu prompt có sẵn của terminal, không phải một phần của câu lệnh.

---

## 📖 Hướng dẫn sử dụng

Sau khi chạy, chương trình hiển thị menu:

```
==================================================
        CHUONG TRINH NEN DU LIEU - HUFFMAN CODING   
==================================================
 [1] Nhap chuoi tu ban phim
 [2] Doc du lieu tu file .txt
 [3] Chay nhanh bo du lieu mau
 [0] Thoat chuong trinh
--------------------------------------------------
Lua chon cua ban:
```

| Lựa chọn | Hành động |
|---|---|
| `1` | Nhập một chuỗi ký tự bất kỳ để nén thử |
| `2` | Nhập tên file `.txt` (đặt cùng thư mục project) để nén nội dung file |
| `3` | Tự động chạy 3 bộ dữ liệu mẫu dựng sẵn để kiểm thử nhanh |
| `0` | Thoát chương trình |

---

## 📊 Ví dụ kết quả

**Đầu vào:** `"aaaaaaaaaabbbbbbcccdd"`

```
+----------------+------------+------------------+
| Ky tu          | Tan suat   | Ma Huffman       |
+----------------+------------+------------------+
| a              | 10         | 0                |
| b              | 6          | 11               |
| c              | 3          | 101              |
| d              | 2          | 100              |
+----------------+------------+------------------+

Kiem tra giai ma: dung khop voi ban goc

Kich thuoc goc      : 168 bit
Sau khi nen         : 37 bit
Ty le nen           : 77.98%
```

---

## 🧠 Nguyên lý thuật toán

1. **Đếm tần suất** xuất hiện của từng ký tự trong văn bản.
2. **Xây dựng cây Huffman** bằng chiến lược tham lam:
   - Đưa tất cả ký tự vào hàng đợi ưu tiên (min-heap) theo tần suất.
   - Lặp lại: lấy ra 2 nút có tần suất nhỏ nhất, ghép thành một nút cha, đưa lại vào hàng đợi.
   - Dừng khi chỉ còn 1 nút — đó chính là gốc của cây Huffman.
3. **Sinh mã nhị phân**: duyệt cây từ gốc, rẽ trái ghi `0`, rẽ phải ghi `1`; mã của mỗi ký tự là đường đi từ gốc đến lá tương ứng.
4. **Mã hóa**: thay từng ký tự trong văn bản gốc bằng mã nhị phân tương ứng.
5. **Giải mã**: duyệt chuỗi bit theo cây Huffman, khi gặp nút lá thì xuất ký tự và quay lại gốc.

Độ phức tạp: **O(n log n)**, với *n* là số ký tự phân biệt trong văn bản.

---

## ✅ Đánh giá thuật toán

**Ưu điểm:**
- Là thuật toán nén không mất dữ liệu (lossless).
- Cài đặt đơn giản, độ phức tạp đa thức O(n log n).
- Hiệu quả cao với dữ liệu có phân bố tần suất lệch (văn bản tự nhiên).

**Nhược điểm:**
- Cần lưu kèm bảng mã / cây để giải mã, gây thêm chi phí lưu trữ.
- Với dữ liệu có tần suất ký tự gần như đồng đều, hiệu quả nén rất thấp.
- Không tối ưu bằng các thuật toán nén hiện đại hơn (Arithmetic Coding, LZ77...).

---

## 📌 Ghi chú

Đây là sản phẩm bài tập lớn môn học, phục vụ mục đích học tập và minh họa thuật toán tham lam trong chương trình môn học.