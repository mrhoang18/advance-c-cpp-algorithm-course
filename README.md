# Bài 1: COMPILER-MACRO
## 1. Compiler-biên dịch một chương trình C/C++
IDE-Integrated Development Environment là môi trường để viết code hỗ trợ các tính năng như Compiler, Debugger. 

Text Editor là một trình soạn thảo (Ví dụ: Notepad++, VScode,...) không tích hợp sẵn trình biên dịch, muốn chạy được code phải dùng riêng Compiler bên ngoài với C/C++ thường là GCC/G++. 

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
## 2. Macro
### 2.1. Các chỉ thị tiền xử lý
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
### 2.1. Macro function
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
### 2.1. Toán tử trong macro
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
### 2.1. Variadic macro
Là loại macro có thể chấp nhận một số lượng tham số không xác định, cho phép bạn truyền vào bất kỳ số lượng đối số nào khi sử dụng macro.

# Bài 2: STDARG-ASSERT
## 1. Thư viện STDARG
Thư viện stdarg.h hỗ trợ viết function với số lượng tham số không xác định. Thư viện này cung cấp một số từ khóa như sau:
- va_list va: va_list là một kiểu dữ liệu của tập hợp các đối số không xác định được đặt tên là va. (Bản chất nó giống như con trỏ lưu kiểu dữ liệu: typedef char* va_list;).

- va_start(va, count): hàm này mang các kí tự vào chuỗi va. (Cách hoạt động của nó là sẽ tạo một con trỏ có giá trị bằng địa chỉ kí tự đầu tiên của chuỗi không xác định và thực hiện vòng lặp so sánh các kí tự trong chuỗi có giống với từng kí tự của label count không và con trỏ địa chỉ tăng dần dần ứng với địa chỉ của các kí tự tiếp theo của chuỗi . Sau khi xác định được kí tự giống với label count thì mới bắt đầu mang các kí tự sau dấu , vào chuỗi va.
  
- va_arg(va, type): lấy giá trị của tham số tiếp theo từ chuỗi va và ép kiểu nó sang kiểu dữ liệu được chỉ định. Khi gọi hàm va_arg(va, type) thì nó đọc giá trị tại ô phía sau va_start và trỏ tới ô tiếp theo.

- va_end(va_list ap): Kết thúc việc sử dụng danh sách đối số biến đổi.

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


