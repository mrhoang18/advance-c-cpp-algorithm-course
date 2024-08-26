Đoạn mã này xử lý ngoại lệ đơn giản bằng cách sử dụng `setjmp` và `longjmp`.
 
# Định nghĩa cấu trúc và khai báo biến
  ```c
  typedef struct
  {
      int error_code;
      char error_message[52];
  } ErrorList;

  ErrorList error;
  jmp_buf buf;
  ```
Dùng `typedef` để định nghĩa lại `ErrorList` là một cấu trúc dùng để lưu trữ thông tin về lỗi. Nó bao gồm:

  - `int error_code`: Là một số nguyên, đại diện cho mã lỗi.
  - `char[] error_message[52]`: Dùng để lưu trữ thông báo lỗi dưới dạng chuỗi ký tự.
    
`ErrorList error`: Khởi tạo một biến `error` có kiểu dữ liệu `ErrorList`. Biến này được sử dụng để lưu trữ thông tin lỗi hiện tại, bao gồm mã lỗi và thông điệp lỗi.

`jmp_buf buf`: Khởi tạo một bến `buf` có kiểu dữ liệu `jmp_buf`. Biến này được sử dụng để lưu trữ thông tin trạng thái khi `setjmp` được gọi, giúp chương trình có thể nhảy lại vị trí này khi `longjmp` được gọi.

# Macro `TRY`, `CATCH` và `THROW`
  ```c
  #define TRY if (setjmp(buf) == 0)
  #define CATCH(x) else if (error.error_code == (x))
  #define THROW(x, msg){                                              \
      error.error_code = x;                                           \
      int i = 0;                                                      \
      while (msg[i] != '\0' && i < sizeof(error.error_message) - 1) { \
          error.error_message[i] = msg[i];                            \
          i++;                                                        \
      }                                                               \
      error.error_message[i] = '\0';                                  \
      longjmp(buf, x);                                                \
  }
  
  #define MIN_VALUE -32768
  #define MAX_VALUE 32767
  ```

TRY: 
  - Macro này bắt đầu khi lỗi có thể xảy ra. `setjmp` gọi lần đầu trả về `buf` giá trị bằng 0.
  - Nếu `setjmp` trả về 0, chương trình trong TRY sẽ tiếp tục được thực thi.
    
CATCH(x):
  - Macro này bắt một lỗi cụ thể dựa trên mã lỗi `error_code` trong cấu trúc `error`.
  - Nếu mã lỗi trong `error.error_code` khớp với giá trị x, chương trình trong `CATCH(x)` sẽ được thực thi.
    
THROW(x, msg):

  - Khi lỗi xảy ra, Macro function này nhận vào hai tham số mã lỗi `x` và thông điệp lỗi `msg`.
  - Nó gán `x` cho `error.error_code` và sao chép chuỗi `msg` vào `error.error_message`.
  - Sau đó, nó sử dụng `longjmp` để quay trở lại điểm `setjmp` đã được gọi trước đó, với giá trị trả về là `x`.

# Hàm divide
  ```c
  double divide(int a, int b) {   
      if (b == 0) {
          THROW(1, "Divide by zero error"); // Mã lỗi 1 cho lỗi chia cho 0
      }
      if (a < MIN_VALUE || a > MAX_VALUE || b < MIN_VALUE || b > MAX_VALUE) {
          THROW(2, "Overflow error"); // Mã lỗi 2 cho lỗi tràn số
      }
      return (double)a / b;
  }
  ```
Hàm này thực hiện phép chia và kiểm tra các điều kiện lỗi trước khi thực hiện phép chia.

Nếu b bằng 0, nó ném ra lỗi "chia cho 0" (THROW(1, "Divide by zero error")).

Nếu a hoặc b nằm ngoài phạm vi cho phép (MIN_VALUE, MAX_VALUE), nó ném ra lỗi "tràn số" (THROW(2, "Overflow error")).

Nếu không có lỗi nào, nó trả về kết quả phép chia dưới dạng số thực (double).

