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
  - `sizeof(danhSachSV[0])`: Kích thước của một phần tử trong mảng `danhSachSV` (ở đây là một `SinhVien`).
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
  - `int (*compareFunc)(const void *, const void *)`: là một **con trỏ hàm** giữ địa chỉ của hàm, nó trỏ đến bất kì hàm nào có kiểu trả về là `int` và nhận vào hai tham số `const void*` là **con trỏ hằng** kiểu `void` (là kiểu trỏ tới bất kỳ địa chỉ nào với bất kỳ kiểu dữ liệu của giá trị tại địa chỉ đó).
    
Hàm này sử dụng thuật toán Bubble Sort:
  - Liên tục so sánh 2 phần tử kề nhau, nếu chúng sắp xếp không đúng chổ thì hoán đổi vị trí của chúng.
  - Lặp lại quá trình này nhiều lần, cho đến khi không còn hai phần tử cạnh nhau mà vị trí sắp xếp không đúng thì dừng.

Cụ thể, `compareFunc(array+i, array+j)` sẽ gọi hàm tác vụ tùy vào tham số `int (*compareFunc)(const void *, const void *)` giữ địa chỉ của hàm nào khi khởi tạo hàm `sort`: 
  ```bash
   sort(danhSachSV, size, compareByName);  // Ví dụ, trỏ đến compareByName
  ```
Với `array+i` và `array+j` là địa chỉ phần tử thứ i và thứ j trong mảng `array[]`.

Tùy vào kết quả so sánh trả về của hàm tác vụ sẽ quyết định có đổi chỗ hai phần tử hay không.
# Hàm so sánh theo tên
  ```bash
  int compareByName(const void *a, const void *b) {               
     SinhVien *sv1 = (SinhVien *)a;
     SinhVien *sv2 = (SinhVien *)b;
     return stringCompare(sv1->ten, sv2->ten);
  }
  ```
Hàm `compareByName` nhận hai tham số truyền vào là địa chỉ của phần tử thứ i và thứ j trong mảng `array[]`.

Vì thông tin của các phần tử chỉ có thể đọc giá trị tại địa chỉ mà nó trỏ đến, không được thay đổi giá trị đó nên sử dụng kiểu `con trỏ hằng`.

Phải ép kiểu biến `a` và `b` từ kiểu `void` thành kiểu `SinhVien` trước khi gán cho biến con trỏ `sv1` và `sv2` kiểu `SinhVien`.

Hàm trả về kết quả so sánh từ hàm `stringCompare`, hàm này nhận hai tham số là địa chỉ biến thành viên `sv1->ten`, `sv2->ten`.

Vì `ten` có kiểu `char` và chỉ được đọc giá trị nên khai báo tham số là kiểu `const char *`:
  ```bash
  int stringCompare(const char *str1, const char *str2) {
     while (*str1 && (*str1 == *str2)) {
         str1++;
         str2++;
     }
     return *(const unsigned char*)str1 - *(const unsigned char*)str2;
  }
  ```
Vòng lặp `while(*str1 && (*str1 == *str2))` so sánh hai kí tự đầu tiên có giống nhau không:
  - Nếu giống nhau thì dịch vị trí sang kí tự tiếp theo để kiểm tra.
  - Nếu khác nhau thì lấy hiệu giá trị theo bảng mã ASCII để kiểm tra thứ tự alphabet. Phải ép kiểu về const unsigned char* bởi vì tên có thể có dấu sẽ gây sai sót.

# Hàm so sánh theo điểm trung bình
  ```bash
  int compareByDiemTrungBinh(const void *a, const void *b) {
     SinhVien *sv1 = (SinhVien *)a;
     SinhVien *sv2 = (SinhVien *)b;
     if (sv1->diemTrungBinh > sv2->diemTrungBinh){
         return 1;
     }
     return 0;
  }
  ```
Hàm `compareByDiemTrungBinh` sắp xếp theo thứ tự điểm tăng dần, cách hoạt động cũng giống như hàm `compareByDiemTrungBinh`.
# Hàm so sánh theo ID
  ```bash
  int compareByID(const void *a, const void *b) {
     SinhVien *sv1 = (SinhVien *)a;                   
     SinhVien *sv2 = (SinhVien *)b;
     return sv1->id - sv2->id;
  }
  ```
Hàm `compareByID` cũng tương tự.
# Hàm hiển thị
  ```bash
  void display(SinhVien *array, size_t size) {
     for (size_t i = 0; i < size; i++) {
         printf("ID: %d, Ten: %s, Diem Trung Binh: %.2f\n", array[i].id, array[i].ten, array[i].diemTrungBinh);
     }
     printf("\n");
  }
  ```
Hàm `display` đơn giản chỉ là in ra các phần tử trong mảng sau khi sắp xếp.

# Những chỗ bất ổn
  ```bash
   typedef struct {
     char ten[50];
     float diemTrungBinh;
     int id;                  // sửa
  } SinhVien;
  ```
Vì `id` là số nguyên không âm nên sửa lại kiểu dữ liệu thành `unsigned int` để không lãng phí tài nguyên.

  ```bash
  int compareByDiemTrungBinh(const void *a, const void *b) {
     SinhVien *sv1 = (SinhVien *)a;
     SinhVien *sv2 = (SinhVien *)b;
     if (sv1->diemTrungBinh > sv2->diemTrungBinh){      // sửa
         return 1;                                      // sửa
     }                                                  // sửa
     return 0;                                          // sửa
  }
  ```
Hàm `compareByDiemTrungBinh` chưa được tối ưu, chỉ vô tình đúng khi sắp xếp điểm tăng dần. 

Sửa lại thành:
  ```bash
  // Hàm so sánh theo điểm trung bình
  int compareByDiemTrungBinh(const void *a, const void *b) {
     SinhVien *sv1 = (SinhVien *)a;
     SinhVien *sv2 = (SinhVien *)b;
    return sv1->diemTrungBinh - sv2->diemTrungBinh;
  }
  ```



