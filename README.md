# COMPILER-MACRO
<details><summary>Chi tiết</summary>
<p>
  
## Compiler
Compiler (trình biên dịch) là chương trình có nhiệm vụ xử lý chương trình ngôn ngữ bậc cao (C/C++, Python,...) thành ngôn ngữ bậc thấp hơn để máy tính thực thi (thường là ngôn ngữ máy).

Quá trình biên dịch gồm các giai đoạn như sau:

<img src="https://github.com/user-attachments/assets/68c4be2c-ee5b-41ab-9aeb-bd986aac8a4f" alt="Compiler Macro" width="500">

- Giai đoạn Preprocessor (Tiền xử lý): thực hiện nhận source code (bao gồm các file: .c,.h,.cpp,.hpp,...), xóa bỏ comment và xử lý các chỉ thị tiền xử lý và đầu ra là file .i.

  Lệnh thực hiện trên terminal:
  ```bash
  gcc -E main.c -o main.i
  ```
- Giai đoạn Compiler: chuyển từ ngôn ngữ bậc cao sang ngôn ngữ bậc thấp assembly, đầu vào là file .i đầu ra là file .s.

    Lệnh thực hiện trên terminal:
  ```bash
  gcc main.i -S -o main.s
  ```
- Giai đoạn Assembler: dịch chương trình sang mã máy 0 và 1, đầu vào là file .s đầu ra là file .o hay còn gọi là file Object.
  
  Lệnh thực hiện trên terminal:
  ```bash
  gcc - c main.s -o main.o
  ```
- Giai đoạn Linker: liên kết các file Object .0 lại thành một chương trình duy nhất.

   Lệnh thực hiện và chạy file trên terminal:
  ```bash
  gcc test1.o test2.o main.o -o main
  ./main
  ```
## Macro
### Các chỉ thị tiền xử lý
<details><summary></summary>
<p>
Chỉ thị tiền xử lý là những chỉ thị cung cấp cho bộ tiền xử lý để xử lý những thông tin trước khi bắt đầu quá trình biên dịch. Các chỉ thị tiền xử lý bắt đầu với #:
- #include: mang toàn bộ mã nguồn của file được include vào file .i mà không cần viết lại, giúp chương trình dễ quản lý do phân chia thành các module.
   ```bash
   #include <stdio.h>
   #incldue "test1.h"
- #define: thay thế một đoạn chương trình bị lặp lại, không có kiểu dữ liệu. Việc sử dụng từ khóa #define để định nghĩa được gọi là Macro.
  ```bash
  #define PI 3.14
- #undef: để hủy định nghĩa một #define đã được định nghĩa trước đó.
  ```bash
  #include <stdio.h>
  #define MAX_SIZE 100
  
  int main() {
      printf("MAX_SIZE is defined as: %d\n", MAX_SIZE);
  
      // Bỏ định nghĩa của MAX_SIZE
      #undef MAX_SIZE
  
      // Định nghĩa lại MAX_SIZE với giá trị khác
      #define MAX_SIZE 50
  
      printf("MAX_SIZE is now redefined as: %d\n", MAX_SIZE);
  
      return 0;
  }
- #if, #elif, #else: để kiểm tra điều kiện của Macro.
  ```bash
  #include <stdio.h>

  // Định nghĩa một macro
  #define VERSION 3
  
  int main() {
      // Sử dụng #if, #elif, #else
      #if VERSION == 1                               // Điều kiện #if sai, nếu không còn kiểm tra điều kiện nào nữa đi tới #endif luôn
          printf("This is version 1.\n");
      #elif VERSION == 2                             // Tiếp tục kiểm tra với #elif
          printf("This is version 2.\n");            
      #else                                          // Không có điều kiện nào ở trên đúng
          printf("This is another version.\n");
      #endif
  
      return 0;
  }

- #ifdef, #ifndef: kiểm tra xem macro này đã hoặc chưa được định nghĩa ("đã" ứng với #ifdef và "chưa" ứng với #ifndef) hay chưa nếu đúng như vậy thì mã phía sau sẽ được biên dịch.
  ```bash
  #include <stdio.h>

  // Định nghĩa một macro
  #define FEATURE_ENABLED
  
  int main() {
      // Kiểm tra xem FEATURE_ENABLED đã được định nghĩa đúng không?
      #ifdef FEATURE_ENABLED
          printf("Feature is enabled.\n");
      #endif
  
      // Kiểm tra xem ANOTHER_FEATURE chưa được định nghĩa đúng không?
      #ifndef ANOTHER_FEATURE
          printf("Another feature is not enabled.\n");
      #endif
  
      return 0;
  }
  ```
</p>
</details>

### Macro function
<details><summary></summary>
<p>
Macro function là khi đoạn chương trình #define là một hàm có tham số truyền vào. Nếu macro function có nhiều dòng thì cuối các dòng kết thúc bằng kí tự \ và dòng cuối cùng không cần.
  
  ```bash
  #include <stdio.h>
  
  #define DISPLAY_SUM(a,b)                        \
  printf("This is macro to sum 2 number\n");      \
  printf("Result is: %d", a+b);
  
  int main() {
      DISPLAY_SUM(5,6);
      return 0;
  }
  ```
- Ưu điểm của macro function so với một function là không tối ưu về bộ nhớ trên RAM nhưng tối ưu về tốc độ. Cụ thể hơn khi viết một function, thì function đó sẽ được lưu vào một vùng nhớ. Khi function được gọi ra trong main(), programe counter sẽ lưu địa chỉ hiện tại vào stack pointer và trỏ đến từng địa chỉ của vùng nhớ chứa function. Còn macro function thì thay thế trực tiếp vô luôn, tuy chiếm một bộ nhớ trên RAM và không cần các các bước như trên nhưng tốc độ lại nhanh hơn.

</p>
</details>

### Toán tử trong macro
<details><summary></summary>
<p>
Toán tử #: tự chuẩn hóa kiểu chuỗi cho tham số nhập vào.

Toán tử ##: nối các chuỗi lại với nhau.
```bash
  #include <stdio.h>
  
  // Sử dụng toán tử tự chuẩn hóa 
  #define CREATE_FUNC(func, cmd)  \
  void func() {                   \
      printf(#cmd);               \
      printf("\n");               \
  }
  
  // Sử dụng toán tử nối chuỗi
  #define CREATE_VAR(name)        \
  int int_##name;                 
  
  CREATE_FUNC (test1, this is function test1); 
  CREATE_VAR(test);
  
  int main() {
      return 0;
  }
```
Kết quả trong file .i:
```bash
void test1() { printf("this is function test1"); printf("\n"); };
int int_test;
```
</p>
</details>

### Variadic macro
<details><summary></summary>
<p>
Là loại macro có thể chấp nhận một số lượng tham số không xác định, cho phép bạn truyền vào bất kỳ số lượng đối số nào khi sử dụng macro.
  
```bash
#include <stdio.h>

// Định nghĩa một variadic macro
#define PRINT_ARGS(format, ...) printf(format, __VA_ARGS__)

int main() {
    // Sử dụng variadic macro để in ra các giá trị
    PRINT_ARGS("This is a variadic macro example: %d, %f\n", 42, 3.14);

    return 0;
}
```

</p>
</details>

</p>
</details>

# STDARG-ASSERT
<details><summary>Chi tiết</summary>
<p>
## 1. Thư viện STDARG
Thư viện stdarg.h hỗ trợ viết function với số lượng tham số không xác định. Thư viện này cung cấp một số từ khóa như sau:
- va_list va: va_list là một kiểu dữ liệu của tập hợp các đối số không xác định được đặt tên là va. (Bản chất nó giống như con trỏ lưu kiểu dữ liệu: typedef char* va_list;).

- va_start(va, count): hàm này mang các kí tự vào chuỗi va. (Cách hoạt động của nó là sẽ tạo một con trỏ có giá trị bằng địa chỉ kí tự đầu tiên của chuỗi không xác định và thực hiện vòng lặp so sánh các kí tự trong chuỗi có giống với từng kí tự của label count không và con trỏ địa chỉ tăng dần dần ứng với địa chỉ của các kí tự tiếp theo của chuỗi . Sau khi xác định được kí tự giống với label count thì mới bắt đầu mang các kí tự sau dấu , vào chuỗi va.
  
- va_arg(va, type): lấy giá trị của tham số tiếp theo từ chuỗi va và ép kiểu nó sang kiểu dữ liệu được chỉ định. Khi gọi hàm va_arg(va, type) thì nó đọc giá trị tại ô phía sau va_start và trỏ tới ô tiếp theo.

- va_end(va_list ap): kết thúc việc sử dụng danh sách đối số biến đổi, giải phóng bộ nhớ.

Ví dụ nhập vào 5 tham số:
  ```bash
  #include <stdio.h>
  #include <stdarg.h>
  
  void display(int count, ...) {
      va_list av;
      va_start(av, count);
     
      for (int i = 0; i < count; i++) {
          printf("Value at %d: %d\n", i, va_arg(av,int)); 
      }
  
      va_end(va);
  }
  
  int main()
  {
      // Số lượng tham số là 5
      display(5, 6, 8, 15, 10, 13);
  
      return 0;
  }
  ```
Output:
  ```bash
  Value at 0: 6
  Value at 1: 8
  Value at 2: 15
  Value at 3: 10
  Value at 4: 13
  ```
## 2. Thư viện ASSERT
Thư viện assert.h là thư viện để hỗ trợ debug chương trình.

- Hàm assert(): dùng để kiểm tra điều kiện, nếu điều kiện đúng thì chương trình tiếp tục thực thi còn sai thì dừng chương trình và báo lỗi. 

Code mẫu báo lỗi chia cho 0: 
  ```bash
  #include <stdio.h>
  #include <assert.h>
  
  double thuong(int a, int b){
      assert( b != 0 && "Mẫu bằng 0");
      return (double) a/b;
  }
  
  int main(int argc, char const*argv[])
  {
      printf("Thuong: %f\n", thuong(6, 0)); 
      return 0;
  }
  ```
Báo lỗi như sau:
  ```bash
  Assertion failed: b != 0 && "Mẫu bằng 0", file tempCodeRunnerFile.c, line 5
  ```
- Thường thấy hơn sẽ sử dụng macro để định nghĩa một lỗi.
  ```bash
  #include <stdio.h>
  #include <assert.h>
  #define LOG(condition, cmd) assert(condition && #cmd)
  
  double thuong(int a, int b){
      LOG(b != 0, "Mau bang bang 0");
  }
  
  int main(int argc, char const *argv[])
  {
      thuong(6,0);
      return 0;
  }
  ```
</p>
</details>

# POINTER
<details><summary>Chi tiết</summary>
<p>
  
## 1. Pointer
Con trỏ (pointer) là một biến chứa địa chỉ của một đối tượng khác (đối tượng ở đây có thể là: biến, hàm, mảng,...).

**Cách khai báo con trỏ:**
   ```bash
  int   *ptr;        // con trỏ đến kiểu int
  char  *ptr_char;   // con trỏ đến kiểu char
  float *ptr_float;  // con trỏ đến kiểu float
  ```
**Các sử dụng con trỏ:**
   ```bash
  #include <stdio.h>
  
  int a = 10;
  int *ptr = &a;                 // toán tử lấy địa chỉ &
  int *ptr1 = (int*)0x01101010;  // phải ép kiểu khi gán trực tiếp cho địa chỉ
  
  int main(int argc, char const*argv[]){
      printf("Dia chi a: %p\n", &a);
      printf("Gia tri ptr: %p\n", ptr); 
      printf("Gia tri ptr: %p\n", ptr1); 
      return 0;
  }
  ```
**Output từ Terminal:**
  ```bash
  > Dia chi a: 00007FF7960F3000  
  > Gia tri ptr: 00007FF7960F3000
  > Gia tri ptr: 0000000001101010
  ```
## 2. Function pointer
Pointer to function (con trỏ hàm) là một biến mà giữ địa chỉ của một hàm.

  **Cách khai báo con trỏ hàm:**
  ```bash
  void (*ptr)(int, double);  
  ```
  - Con trỏ ptr trỏ đến hàm kiểu trả về là `void`(ngoài ra còn có thể là `int`,...) , tham số truyền vào là kiểu `int` và `double`.
  - Tất cả các hàm nào có cùng cú pháp như thế này, con trỏ đều trỏ đến được.
    
**Cách sử dụng con trỏ hàm:**
  ```bash
  #include <stdio.h>
  #include <assert.h>
  
  void chao() {
      printf("Hello!\n");
  }
  
  void thuong(int a, int b) {
      assert(b != 0);
      printf("Thuong %d va %d: %d\n", a, b, (double)a / b);
  }
  
  int main(int argc, char const *argv[])
  {
      // Khai báo con trỏ hàm
      void (*ptr0)();
      void (*ptr1)(int, int);
  
      // Gán địa chỉ của hàm cho con trỏ hàm
      ptr0 = chao;
      ptr1 = &thuong;
  
      // Gọi hàm ra
      ptr0();
      ptr1(8, 2);

      // Gọi hàm ra
      (*ptr0)();
      (*ptr1)(8, 2);
  
      return 0;
  }
  ```
**Output từ Terminal:**
  ```bash
  > Hello!
  > Thuong 8 va 2: 0
  > Hello!
  > Thuong 8 va 2: 0
  ```
**Cách sử dụng mảng lưu địa chỉ nhiều con trỏ hàm:**
  ```bash
  #include <stdio.h>
  #include <assert.h>
  
  void tong(int a, int b) {
      printf("Tong %d va %d: %d\n", a, b, a + b);
  }
  
  void hieu(int a, int b) {
      printf("Hieu %d va %d: %d\n", a, b, a - b);
  }
  
  void tich(int a, int b) {
      printf("Tich %d va %d: %d\n", a, b, a * b);
  }
  
  void thuong(int a, int b) {
      assert(b != 0);
      printf("Thuong %d va %d: %d\n", a, b, a / b);
  }
  
  int main(int argc, char const *argv[])
  {
      // Khai báo con trỏ hàm
      void (*array[])(int, int)={&tong,&hieu,&tich,&thuong};
      //void (*array[4])(int, int)={&tong,&hieu,&tich,&thuong};
  
      // Tính
      array[0](1,1);
      array[1](1,1);
      return 0;
  }
  ```
**Output từ Terminal:**
  ```bash
  > Tong 1 va 1: 2
  > Hieu 1 va 1: 0
  ```
**ỨNG DỤNG CON TRỎ HÀM: Tham số truyền vào hàm là một hàm khác.**
  ```bash
  #include <stdio.h>
  #include <assert.h>
  
  void tong(int a, int b) {
      printf("Tong %d va %d: %d\n", a, b, a + b);
  }
  
  void tinhToan(void (*ptr)(int, int), int a, int b) {
      printf("Thuc hien phep toan duoi:\n");
      ptr(a, b);
  }
  
  int main(int argc, char const *argv[])
  {
      // Gọi hàm
      tinhToan(&tong, 5, 3);
      return 0;
  }
  ```
## 2. Void pointer
Void pointer (con trỏ void) là một con trỏ có thể trỏ đến bất kỳ kiểu dữ liệu nào. 

Khi in ra giá trị được void point trỏ đến, do nó không biết kiểu dữ liệu của giá trị được trỏ đến nên phải ép kiểu con trỏ void thành con trỏ kiểu đó trước rồi mới giải tham chiếu (Vd: `*(int*)ptr`).
  
**Cách sử dụng con trỏ void:**
  ```bash
  #include <stdio.h>
  
  void tong(int a, int b) {
      printf("Tong cua %d va %d la: %d\n", a, b, a + b);
  }
  
  int main() {
      int a = 10;
      double b = 20.5;
      char c = 'X';
  
      void *ptr;
  
      // Trỏ đến biến kiểu int
      ptr = &a;
      printf("Gia tri cua a = %d\n", *(int*)ptr);       // Ép kiểu và giải tham chiếu
  
      // Trỏ đến biến kiểu double
      ptr = &b;
      printf("Gia tri cua b = %.2f\n", *(double*)ptr);  // Ép kiểu và giải tham chiếu
  
      // Trỏ đến biến kiểu char
      ptr = &c;
      printf("Gia tri cua c = %c\n", *(char*)ptr);      // Ép kiểu và giải tham chiếu

      // Trỏ đến hàm
      ptr = &tong;
      ((void (*)(int, int))ptr)(9, 3);                  // Ép kiểu về con trỏ hàm
  
      return 0;
  }
  ```
**Output từ Terminal:**
  ```bash
  > Gia tri cua a = 10
  > Gia tri cua b = 20.50
  > Gia tri cua c = X
  > Tong cua 9 va 3 la: 12
  ```
## 3. NULL pointer
Null Pointer là một con trỏ không trỏ đến đối tượng nào hết. Nó có địa chỉ và giá trị bằng 0.
**Cách khai báo con trỏ NULL:**
  ```bash
  int *ptr = NULL;
   ```
## 4. Pointer to Constant
Con trỏ hằng là con trỏ chỉ được đọc giá trị tại địa chỉ ra nhưng không được phép dùng toán tử giải tham chiếu `*` truy cập đến địa chỉ để thay đổi giá trị.

**Cách khai báo:**
  ```bash
  int const *ptr_const; 
  const int *ptr_const;
  ```
## 5. Constant Pointer
Hằng con trỏ là con trỏ chỉ cho phép dùng toán tử giải tham chiếu `*` truy cập tới địa chỉ của nó để thay đổi giá trị.
**Cách khai báo:**
  ```bash
  int *const const_ptr = &value;
  ```
## 5. Pointer to Pointer

</p>
</details>
