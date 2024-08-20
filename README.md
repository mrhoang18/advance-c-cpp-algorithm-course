# BÀI 1: COMPILER-MACRO
<details><summary>Chi tiết</summary>
<p>
  
## 1. Compiler
<details><summary>Chi tiết</summary>
<p>
  
Compiler (trình biên dịch) là chương trình có nhiệm vụ xử lý chương trình ngôn ngữ bậc cao (C/C++, Python,...) thành ngôn ngữ bậc thấp hơn để máy tính thực thi (thường là ngôn ngữ máy).

Quá trình biên dịch gồm các giai đoạn như sau:

<p align="center">
  <img src="https://github.com/user-attachments/assets/68c4be2c-ee5b-41ab-9aeb-bd986aac8a4f" alt="Compiler Macro" width="500">
</p>

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
</p>
</details>

## 2. Macro
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

# BÀI 2: STDARG-ASSERT
<details><summary>Chi tiết</summary>
<p>
  
## 1. Thư viện STDARG
<details><summary>Chi tiết</summary>
<p>
	
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
</p>
</details>

## 2. Thư viện ASSERT
<details><summary>Chi tiết</summary>
<p>
	
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

</p>
</details>

# BÀI 3: POINTER
<details><summary>Chi tiết</summary>
<p>
  
## 1. Định nghĩa con trỏ
<details><summary>Chi tiết</summary>
<p>
  
Con trỏ (pointer) là một biến chứa địa chỉ của một đối tượng khác (đối tượng ở đây có thể là: biến, hàm, mảng,...).

**Cú pháp:**
   ```bash
  int   *ptr;        // con trỏ kiểu int
  char  *ptr_char;   // con trỏ kiểu char
  float *ptr_float;  // con trỏ kiểu float
  ```
**Ví dụ:**
   ```bash
  #include <stdio.h>
  
  int a = 10;
  int *ptr = &a;                 // toán tử lấy địa chỉ &
  int *ptr1 = (int*)0x01101010;  // phải ép kiểu khi gán trực tiếp cho địa chỉ
  
  int main(int argc, char const*argv[]){
      printf("Dia chi a: %p\n", &a);
      printf("Gia tri ptr: %p\n", ptr); 
      printf("Gia tri ptr1: %p\n", ptr1); 
      return 0;
  }
  ```
**Kết quả:**
  ```bash
  > Dia chi a: 00007FF7960F3000  
  > Gia tri ptr: 00007FF7960F3000
  > Gia tri ptr1: 0000000001101010
  ```
**Kích thước của con trỏ phụ thuộc vào kiến trúc vi xử lý.**

Hệ thống 32 – bit, kích thước của con trỏ là 4 byte.

Hệ thống 64 – bit, kích thước của con trỏ là 8 byte.

  ```bash
  #include <stdio.h>
  #include <stdbool.h>
  
  int main(int argc, char const *argv[]){
      printf("%d bytes\n", sizeof(int *));              // 8bytes
      printf("%d bytes\n", sizeof(char *));             // 8bytes
      printf("%d bytes\n", sizeof(float *));            // 8bytes
      printf("%d bytes\n", sizeof(double *));           // 8bytes
      printf("%d bytes\n", sizeof(long *));             // 8bytes
      printf("%d bytes\n", sizeof(short *));            // 8bytes
      printf("%d bytes\n", sizeof(long long *));        // 8bytes
      printf("%d bytes\n", sizeof(bool *));             // 8bytes
      return 0;
  }
  ```
</p>
</details>

## 2. Các kiểu con trỏ
### Function pointer (Con trỏ hàm)
<details><summary>Chi tiết</summary>
<p>
  
Con trỏ hàm là một biến giữ địa chỉ của hàm.

**Cú pháp:**
  ```bash
  void (*ptr)(int, double);  
  ```
  - Con trỏ ptr trỏ đến hàm kiểu trả về là `void` (ngoài ra còn có thể là `int`,...), tham số truyền vào là kiểu `int` và `double`.
  - Các hàm nào có cùng cú pháp trong cùng một chương trình, con trỏ đều trỏ đến được.
    
**Ví dụ:**
  ```bash
  #include <stdio.h>
  #include <assert.h>
  
  void chao() {
      printf("Hello!\n");
  }
  
  void chia(int a, int b) {
      assert(b != 0);
      printf("Thuong %d va %d: %f\n", a, b, (double)a / (double)b);
  }
  
  int main(int argc, char const *argv[]){
      // Khai báo con trỏ hàm
      void (*ptr0)();
      void (*ptr1)(int, int);
  
      // Gán địa chỉ của hàm cho con trỏ hàm
      ptr0 = chao;
      ptr1 = &chia;
  
      // Gọi hàm ra
      ptr0();
      ptr1(8, 2);

      // Gọi hàm ra
      (*ptr0)();
      (*ptr1)(8, 2);
  
      return 0;
  }
  ```
**Kết quả:**
  ```bash
  > Hello!
  > Thuong 8 va 2: 4.000000
  > Hello!
  > Thuong 8 va 2: 4.000000
  ```
**Ví dụ sử dụng mảng lưu địa chỉ nhiều con trỏ hàm:**
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
  
  int main(int argc, char const *argv[]){
      // Khai báo con trỏ hàm
      void (*array[])(int, int)={&tong,&hieu,&tich,&thuong};
      //void (*array[4])(int, int)={&tong,&hieu,&tich,&thuong};
  
      // Tính
      array[0](1,1);
      array[1](1,1);
      return 0;
  }
  ```
**Kết quả:**
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
  
  int main(int argc, char const *argv[]){
      // Gọi hàm
      tinhToan(&tong, 5, 3);
      return 0;
  }
  ```
</p>
</details>

### Void pointer (Con trỏ void)
<details><summary>Chi tiết</summary>
<p>

Void pointer là một con trỏ có thể trỏ đến bất kỳ kiểu dữ liệu nào. 

**Cú pháp:**
  ```bash
  void *ptr; 
  ```

Khi in ra giá trị được void point trỏ đến, do nó không biết kiểu dữ liệu của giá trị được trỏ đến nên phải ép kiểu con trỏ void thành con trỏ kiểu đó trước rồi mới giải tham chiếu (Vd: `*(int*)ptr`).
  
**Ví dụ:**
  ```bash
  #include <stdio.h>
  
  void tong(int a, int b) {
      printf("Tong cua %d va %d la: %d\n", a, b, a + b);
  }
  
  int main(int argc, char const *argv[]) {
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
**Kết quả:**
  ```bash
  > Gia tri cua a = 10
  > Gia tri cua b = 20.50
  > Gia tri cua c = X
  > Tong cua 9 va 3 la: 12
  ```
</p>
</details>

### NULL pointer (Con trỏ NULL)
<details><summary>Chi tiết</summary>
<p>

Con trỏ NULL  là một con trỏ không trỏ đến đối tượng nào hết. Nó có địa chỉ và giá trị bằng 0.

Khi khai báo con trỏ mà chưa sử dụng ngay hoặc sử dụng xong thì phải gán NULL.

**Cú pháp:**
  ```bash
  int *ptr_null = NULL;
  //  ptr_null = 0x00: địa chỉ khởi tạo
  // *ptr_null = 0   : giá trị tại địa chỉ khởi tạo
  ```

</p>
</details>

### Pointer to constant (Con trỏ hằng)
<details><summary>Chi tiết</summary>
<p>

Con trỏ hằng là con trỏ **chỉ có thể đọc giá trị tại địa chỉ mà nó trỏ đến**, nghĩa là không được phép dùng toán tử giải tham chiếu `*` truy cập đến địa chỉ để thay đổi giá trị.

**Cú pháp:**
  ```bash
  <data_type> const *ptr_const; 
  const <data_type> *ptr_const;
  ```
**Ví dụ**
  ```bash
  #include <stdio.h>
  
  int value = 10;
  const int *ptr_const = &value;
  
  int main(int argc, char const *argv[]){
      printf("%p\n", ptr_const);
      printf("%d\n", *ptr_const);

      // Lỗi: Không được phép thay đổi giá trị của con trỏ hằng!
      *ptr_const = 20;
      printf("%d\n", *ptr_const);
      return 0;
  }
  ```
Kết quả sau khi chạy sẽ gặp lỗi: ```assignment of read-only location '*ptr_const'```

</p>
</details>

### Constant pointer (Hằng con trỏ)
<details><summary>Chi tiết</summary>
<p>
  
Hằng con trỏ là một con trỏ mà **trỏ đến 1 địa chỉ cố định**, nghĩa là khi con trỏ này được khởi tạo thì nó sẽ không thể trỏ tới địa chỉ khác.

Hằng con trỏ cho phép dùng toán tử giải tham chiếu `*` để thay đổi giá trị.

**Cú pháp:**
  ```bash
  <data_type> *const const_ptr = &value;
  ```
**Ví dụ**
  ```cpp
  #include <stdio.h>
  
  int value1 = 10;
  int value2 = 20;
  int *const const_ptr = &value1;
  
  int main(int argc, char const *argv[]){
      printf("%p\n", const_ptr);
      printf("%d\n", *const_ptr);
  
      const_ptr = &value2;
      printf("%p\n", const_ptr);
      return 0;
  }
  ```
Kết quả sau khi chạy sẽ gặp lỗi: ```assignment of read-only variable 'const_ptr'```

</p>
</details>

### Pointer to pointer (Con trỏ trỏ đến con trỏ)
<details><summary>Chi tiết</summary>
<p>

Con trỏ đến con trỏ là một kiểu dữ liệu trong ngôn ngữ lập trình cho phép bạn lưu trữ địa chỉ của một con trỏ.

Con trỏ đến con trỏ cung cấp một cấp bậc trỏ mới, cho phép bạn thay đổi giá trị của con trỏ gốc.

Cấp bậc này có thể hữu ích trong nhiều tình huống, đặc biệt là khi bạn làm việc với các hàm cần thay đổi giá trị của con trỏ.

**Cú pháp:**
  ```bash
  int **ptp = &p;
  ```
**Ví dụ:**
  ```bash
  #include <stdio.h>
  
  int main() {
      int value = 42;
      int *ptr1 = &value;  // Con trỏ thường trỏ đến một biến
  
      int **ptr2 = &ptr1;  // Con trỏ đến con trỏ
  
      /*
          **ptr2 = &ptr1
          ptr2 = &ptr1;
          *ptr2 = ptr1 = &value;
          **ptr2 = *ptr1 = value
      */
  
      printf("address of value: %p\n", &value);
      printf("value of ptr1: %p\n", ptr1);
  
      printf("address of ptr1: %p\n", &ptr1);
      printf("value of ptr2: %p\n", ptr2);
  
      printf("dereference ptr2 first time: %p\n", *ptr2);
      printf("dereference ptr2 second time: %d\n", **ptr2);
  
      return 0;
  }
  ```
**Kết quả:**
  ```bash
  address of value: 000000E6425FF904
  value of ptr1: 000000E6425FF904
  address of ptr1: 000000E6425FF8F8
  value of ptr2: 000000E6425FF8F8
  dereference ptr2 first time: 000000E6425FF904
  dereference ptr2 second time: 42
  ```

</p>
</details>

</p>
</details>

# BÀI 4: EXTERN - STATIC - VOLATILE - REGISTER
<details><summary>Chi tiết</summary>
<p>

## 1. Extern
<details><summary>Chi tiết</summary>
<p>
  
Từ khóa `extern` được sử dụng để khai báo rằng một **biến hoặc một hàm** được định nghĩa ở một nơi khác (thường là trong một tệp khác). 

Từ khóa `extern` không tạo ra một biến mới mà chỉ thông báo cho trình biên dịch rằng **biến hoặc một hàm** này đã được định nghĩa ở nơi khác và có thể được sử dụng trong tệp hiện tại.

**Ví dụ file main.c:**
  ```bash
  #include <stdio.h>
  
  int value = 90;
  extern void display();
  
  int main(){
  	printf("hello\n");
  	display();
  }
  ```
**Ở file other.c:**
  ```bash
  #include <stdio.h>
  
  extern int value;
  void display()
  {
  	printf("value: %d\n", value);
  }
  ```
</p>
</details>

## 2. Static
### Static local variables
<details><summary>Chi tiết</summary>
<p>
	
Biến cục bộ tĩnh (Static local variables) là các biến được khai báo với từ khóa `static` ở **trong phạm vi của một hàm**. Nó có những tính chất đặc biệt như sau:

  - **Tồn tại trong suốt vòng đời của chương trình**: Biến cục bộ tĩnh được khai báo bên trong một hàm và chỉ có thể truy cập được từ trong hàm đó, sau khi hàm kết thúc nó không bị phóng bộ nhớ. Thay vào đó, nó vẫn tồn tại trong suốt thời gian chạy của chương trình và giữ lại giá trị của nó giữa các lần gọi hàm.
    
  - **Chỉ khởi tạo một lần**: Biến cục bộ tĩnh chỉ được khởi tạo một lần duy nhất, vào lần đầu tiên hàm được gọi. Sau đó, biến này sẽ giữ nguyên giá trị của nó từ lần cuối cùng hàm được gọi và không được khởi tạo lại trong các lần gọi tiếp theo.

**Ví dụ biến cục bộ tĩnh:**
  ```bash
  #include <stdio.h>
  
  void exampleFunction() {
      static int count = 0;  // Biến static giữ giá trị qua các lần gọi hàm
      count++;
      printf("Count: %d\n", count);
  }
  
  int main() {
      exampleFunction();  // In ra lần 1
      exampleFunction();  // In ra lần 2
      exampleFunction();  // In ra lần 3
      return 0;
  }
  ```
**Kết quả:**
  ```bash
  > Count: 1
  > Count: 2
  > Count: 3
  ```

</p>
</details>

### Static global
<details><summary>Chi tiết</summary>
<p>
	
Biến toàn cục tĩnh (Static global variables) là các biến được khai báo với từ khóa `static` ở **ngoài tất cả các hàm** (tức là trong phạm vi toàn cục của file). Nó có những tính chất đặc biệt như sau:
  - **Phạm vi truy cập chỉ giới hạn trong file**: Biến toàn cục tĩnh chỉ có thể truy cập được trong file nơi nó được khai báo. Có nghĩa là các biến này không thể được sử dụng bởi các file khác, ngay cả khi chúng được khai báo là `extern`. Khác với biến toàn cục không có từ khóa `static`, có thể được truy cập từ các file khác nếu được khai báo `extern`.
  - **Thời gian tồn tại**: Biến toàn cục tĩnh có thời gian tồn tại từ khi chương trình bắt đầu cho đến khi chương trình kết thúc, tương tự như các biến toàn cục thông thường. Giá trị của chúng được duy trì trong suốt thời gian chạy của chương trình. Chỉ khởi tạo một lần duy nhất trước khi chương trình bắt đầu thực thi.

**Ví dụ file main.c:**
  ```bash
  #include <stdio.h>
  
  extern void display();
  //extern int s_g_value;      // Không được phép, vì s_g_value là biến toàn cục tĩnh của file other.c!!
  extern int g_value;
  
  int main()
  {
  	printf("hello\n");
  	g_value = 40;
  	
  	display();
  
  	return 0;
  }
  ```
**Ở file other.c:**
```bash
#include <stdio.h>

int g_value = 30;
static int s_g_value = 20;

void display()
{
	printf("static global value: %d\n", s_g_value);
	printf("global value: %d\n", g_value);
}
```

</p>
</details>

## 3. Volatile 
<details><summary>Chi tiết</summary>
<p>
  
Từ khóa `volatile` được sử dụng để thông báo cho trình biên dịch rằng giá trị của một biến có thể thay đổi bất kỳ lúc nào, trình biên dịch không được tối ưu hóa hoặc xóa bỏ các thao tác trên biến đó.

Sau đây là một trường hợp đơn giản trong nhúng mà việc khai báo biến `volatile` rất cần thiết để tránh những lỗi sai khó phát hiện do tính năng optimization của compiler:

**Thanh ghi ngoại vi có ánh xạ đến ô nhớ**

Các thiết bị ngoại vi (GPIO, UART, ...) chứa các thanh ghi mà giá trị của nó có thể thay đổi ngoài ý muốn của dòng chương trình, đặc biệt là những thanh ghi trạng thái.

Ví dụ: đợi một nút bấm, với địa chỉ thanh ghi GPIO tương ứng nút bấm được định nghĩa như sau:

```bash
/* Input data register address */
volatile uint32_t* button = (volatile uint32_t*)0x40020810;
...
while ((*button & (1 << 13)) == 0);
```

Ở đây nếu không có `volatile`, con trỏ button sẽ đọc giá trị tại địa chỉ `0x40020810` (và giá trị này mắc định đang là 0).

Khi đó compiler sẽ tối ưu - optimize điều kiện trong câu lệnh sau trở thành `while ((0 & (1 << 13)) == 0);`

Tức là `while (1);`

Vòng lặp này đương nhiên không bao giờ dừng lại => Bug!

</p>
</details>

## 4. Register
<details><summary>Chi tiết</summary>
<p>
  
 Từ khóa `register` được sử dụng để yêu cầu trình biên dịch lưu trữ một biến trong các thanh ghi của bộ xử lý thay vì trong bộ nhớ RAM. 
  
<p align="center">
  <img src="https://github.com/user-attachments/assets/6fad29a3-47b2-41f3-98dd-cb39a7b65f8f" alt="Image description">
</p>

Cơ chế tính toán của máy tính:

  - ALU (Arithmetic Logic Unit) nhận dữ liệu từ các thanh ghi (register) hoặc từ bộ nhớ (RAM).
  - ALU thực hiện phép toán.
  - Kết quả của phép toán được gửi và lưu lại về thanh ghi hoặc RAM.
    
Từ khóa `register` làm tăng tốc độ truy cập biến, vì truy cập vào các thanh ghi nhanh hơn nhiều so với truy cập vào bộ nhớ RAM.

**Kiểm tra tốc độ chương trình khi lưu biến trong thanh ghi và trong RAM:**
  ```bash
  #include <stdio.h>
  #include <time.h>
  
  int main(int argc, char const *argv[])
  {
      unsigned long i;                // Lưu trong RAM
      //register unsigned long i;     // Lưu trong thanh ghi
  
      clock_t start, end;
  
      start = clock();
  
      for ( i = 0; i < 99999999; i++);
  
      end = clock();
  
      printf("Time: %f\n", (double)(end - start)/1000);
      
      return 0;
  }
  ```
**Kết quả:**
  ```bash
  > Time: 0.144000    // Lưu trong RAM
  > Time: 0.054000    // Lưu trong thanh ghi
  ```
</p>
</details>

</p>
</details>
