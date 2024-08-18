# Định nghĩa kiểu dữ liệu `SinhVien`
  ```bash
   typedef struct {
     char ten[50];
     float diemTrungBinh;
     int id;
  } SinhVien;
  ```
`struct` là một kiểu dữ liệu tự đinh nghĩa bởi người dùng. Cho phép nhóm các biến có kiểu dữ liệu khác nhau lại với nhau dưới một tên chung.

Cụ thể, cấu trúc SinhVien đã định nghĩa có ba thành phần:

  - `char ten[50]`: Một mảng ký tự (chuỗi) để lưu tên của sinh viên. Mảng này có thể chứa tối đa 49 ký tự cộng thêm một ký tự kết thúc chuỗi '\0'.
  - `float diemTrungBinh`: Một biến kiểu float để lưu điểm trung bình của sinh viên.
  - `int id`:  Một biến kiểu int để lưu mã số sinh viên (ID).
    
`typedef` là từ khóa cho phép người dùng thêm tên mới cho kiểu có sẵn. Trong trường hợp này tên mới là `SinhVien` với kiểu `struct`. 
Nhờ `typedef`, không cần phải viết từ khóa `struct` mỗi khi khai báo. 

# Khởi tạo mảng cấu trúc
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
              .id = 102
          },
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
# Tính số lượng phần tử trong mảng `danhSachSV`
  ```bash
  size_t size = sizeof(danhSachSV) / sizeof(danhSachSV[0]);
  ```
Cụ thể:
  - `sizeof(danhSachSV)`: Kích thước toàn bộ mảng `danhSachSV` tính bằng byte.
  - `sizeof(danhSachSV[0]`): Kích thước của một phần tử trong mảng `danhSachSV` (ở đây là một `SinhVien`).
# Hàm sắp xếp chung
  ```bash
  void sort(SinhVien array[], size_t size, int (*compareFunc)(const void *, const void *)) {
     int i, j;
     SinhVien temp;
     for (i = 0; i < size-1; i++)    
         for (j = i+1; j < size; j++)
             if (compareFunc(array+i, array+j)>0) {
                 temp = array[i];
                 array[i] = array[j];
                 array[j] = temp;
             }
  }
  ```
Hàm `sort` nhận ba tham số truyền vào:
  - `SinhVien array[]`: mảng cần sắp xếp chứa các phần tử có kiểu dữ liệu `SinhVien`.
  - `size_t size`: số lượng phần tử trong mảng (`size_t` là kiểu không âm và thường được sử dụng để biểu diễn số lượng phần tử       trong mảng).
  - `int (*compareFunc)(const void *, const void *)`: so sánh hai phần tử trong mảng tùy theo tác vụ (theo tên, theo điểm trung      bình, theo ID), là một **con trỏ hàm** giữ địa chỉ của hàm, nó trỏ đến bất kì hàm nào có kiểu trả về là `int` và nhận vào hai 
  tham số `const void*` là **con trỏ hằng** kiểu `void` (là kiểu trỏ tới bất kỳ địa chỉ nào với bất kỳ kiểu dữ liệu của giá trị 
  tại địa chỉ đó).
    
Hàm này sử dụng thuật toán Bubble Sort:
  - Liên tục so sánh 2 phần tử kề nhau, nếu chúng sắp xếp không đúng chổ thì hoán đổi vị trí của chúng.
  - Lặp lại quá trình này nhiều lần, cho đến khi không còn hai phần tử cạnh nhau mà vị trí sắp xếp không đúng thì dừng.

Cụ thể, `compareFunc(array+i, array+j)>0` sẽ gọi hàm tác vụ so sánh
# Hàm so sánh theo tên
  ```bash
  int compareByName(const void *a, const void *b) {               
     SinhVien *sv1 = (SinhVien *)a;
     SinhVien *sv2 = (SinhVien *)b;
     return stringCompare(sv1->ten, sv2->ten);
  }
  ```
Hàm này được khởi tạo khi tham số thứ ba truyền vào hàm `sort` là `compareByName`:
  ```bash
   sort(danhSachSV, size, compareByName);
  ```
Khi đó biến `int (*compareFunc)(const void *, const void *)` giữ địa chỉ của hàm `int compareByName(const void *a, const void *b)`.

Và nó được gọi ra trong hàm `sort` ở:
  ```bash
  compareFunc(array+i, array+j);
  ```
Khi  `compareByName` nhận hai tham số truyền vào:
  - `const void*a`, `const void*b` là **con trỏ hằng** kiểu `void` (là kiểu trỏ tới bất kỳ địa chỉ nào với bất kỳ kiểu dữ liệu của   giá trị tại địa chỉ đó).
# Hàm so sánh theo điểm trung bình
# Hàm so sánh theo ID



