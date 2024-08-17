### Định nghĩa kiểu dữ liệu có cấu trúc (struct) và đặt tên tắt cho kiểu dữ liệu đó:
  ```bash
   typedef struct {
     char ten[50];
     float diemTrungBinh;
     int id;
  } SinhVien;
  ```
`struct` này là một kiểu dữ liệu tự đinh nghĩa bởi người dùng. Cho phép nhóm các biến có kiểu dữ liệu khác nhau lại với nhau dưới một tên chung.

Cụ thể, cấu trúc SinhVien đã định nghĩa có ba thành phần:

  - `char ten[50]`: Một mảng ký tự (chuỗi) để lưu tên của sinh viên. Mảng này có thể chứa tối đa 49 ký tự cộng thêm một ký tự kết thúc chuỗi '\0'.
  - `float diemTrungBinh`: Một biến kiểu float để lưu điểm trung bình của sinh viên.
  - `int id`:  Một biến kiểu int để lưu mã số sinh viên (ID).
    
`typedef` là từ khóa cho phép người dùng thêm tên mới cho kiểu có sẵn. Trong trường hợp này tên mới là `SinhVien` với kiểu `struct`. 
Nhờ `typedef`, không cần phải viết từ khóa `struct` mỗi khi khai báo. 

### Khởi tạo mảng cấu trúc:
  ```bash
  SinhVien danhSachSV[] = {
          {  
              .ten = "Hoang",
              .diemTrungBinh = 7.5,
              .id = 100
          },
          {
              .ten = "Tuan",
              .diemTrungBinh = 4.5,
              .id = 101
          },
          {
              .ten = "Vy",
              .diemTrungBinh = 6.8,
              .id = 102},
          {  
              .ten = "Ngan",
              .diemTrungBinh = 5.6,
              .id = 99
          },
      }; 
  ```
Khởi tạo `SinhVien danhSachSV[]` là một mảng có kiểu dữ liệu là `SinhVien`.

Mỗi phần tử trong mảng `danhSachSV` là một biến cấu trúc kiểu `SinhVien`, nghĩa là mỗi phần tử có các thành viên `ten`, `diemTrungBinh` và `id`.

Gán các giá trị cho các thành viên của phần tử trong mảng, ví dụ tại phần tử thứ nhất của mảng:
  ```bash
  {  
    .ten = "Hoang",
    .diemTrungBinh = 7.5,
    .id = 100
  }
  ```
### Tính toán số lượng phần tử trong mảng `danhSachSV`:
  ```bash
  size_t size = sizeof(danhSachSV) / sizeof(danhSachSV[0]);
  ```
Cụ thể:
  - `sizeof(danhSachSV)`: Kích thước toàn bộ mảng `danhSachSV` tính bằng byte.
  - `sizeof(danhSachSV[0]`): Kích thước của một phần tử trong mảng `danhSachSV` (ở đây là một `SinhVien`).

