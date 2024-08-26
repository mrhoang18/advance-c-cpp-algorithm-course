Đoạn mã này mô phỏng cách quản lý cấu hình của một chiếc xe bằng kỹ thuật bitmask nhằm tiết kiệm bộ nhớ.
# Các macro
```c
// Màu sắc
#define COLOR_RED 0	        //00
#define COLOR_BLUE 1        //01
#define COLOR_BLACK 2       //10
#define COLOR_WHITE 3       //11

// Công suất động cơ
#define POWER_100HP 0
#define POWER_150HP 1
#define POWER_200HP 2

// Dung tích động cơ
#define ENGINE_1_5L 0
#define ENGINE_2_0L 1

// Tùy chọn thêm
#define SUNROOF_MASK 1 << 0     // 0001
#define PREMIUM_AUDIO_MASK 1 << 1 // 0010
#define SPORTS_PACKAGE_MASK 1 << 2 // 0100
```

Vì `color` được lưu trữ trong 2 bits, các giá trị số nguyên từ 0 đến 3 sẽ được biểu diễn như sau trong hệ nhị phân:
- COLOR_RED = 0 = 00 (2-bit)
- COLOR_BLUE = 1 = 01 (2-bit)
- COLOR_BLACK = 2 = 10 (2-bit)
- COLOR_WHITE = 3 = 11 (2-bit)
  
Tương tự với các thuộc tính khác.
  
# Định nghĩa các kiểu dữ liệu 
```c
typedef uint8_t CarColor;
typedef uint8_t CarPower;
typedef uint8_t CarEngine;
```
Sử dụng typedef định nghĩa lại, mỗi thuộc tính là 8 bits.

```c
typedef struct {
    uint8_t additionalOptions : 3; // 3 bits cho các tùy chọn bổ sung
    CarColor color : 2;
    CarPower power : 2;
    CarEngine engine : 1;
} CarOptions;
```
`CarOptions` là một cấu trúc (struct) được định nghĩa để lưu trữ các thông tin liên quan đến cấu hình của một chiếc xe, bao gồm màu sắc, công suất, động cơ, và các tùy chọn bổ sung.

`CarOptions` có dạng `0bxxxx xxxx` từ phải qua trái:

  - `additionalOptions` sử dụng 3 bits để lưu trữ các tùy chọn thêm.
  - `color` sử dụng 2 bits để lưu trữ màu sắc của xe.
  - `power` sử dụng 2 bits để lưu trữ công suất của động cơ.
  - `engine` sử dụng 1 bit để lưu trữ dung tích động cơ.

# Hàm `configureCar`
```c
void configureCar(CarOptions *car, CarColor color, CarPower power, CarEngine engine, uint8_t options) {
    car->color = color;
    car->power = power;
    car->engine = engine;
    car->additionalOptions = options;
}
```
Hàm `configureCar` sử dụng để cấu hình một đối tượng CarOptions, bao gồm việc thiết lập màu sắc, công suất động cơ, dung tích động cơ, và các tùy chọn bổ sung cho một chiếc xe.

Hàm này nhận vào năm tham số:

  - `CarOptions *car`: Đây là con trỏ trỏ tới một đối tượng `CarOptions`. Thông qua con trỏ này, hàm có thể truy cập và thay đổi các thuộc tính của đối tượng mà nó trỏ tới.
  - `CarColor color`: Đây là giá trị màu sắc của xe. Kiểu `CarColor` là một `typedef` của `uint8_t`, và giá trị này được lấy từ các hằng số như (COLOR_RED, COLOR_BLUE).
  - `CarPower power`: Đây là giá trị công suất của động cơ xe. Kiểu `CarPower` cũng là một `typedef` của `uint8_t`, và giá trị này được lấy từ các hằng số như (POWER_100HP, POWER_150HP).
  - `CarEngine engine`: Đây là giá trị dung tích động cơ của xe. Kiểu `CarEngine` cũng là một `typedef` của `uint8_t`, và giá trị này được lấy từ các hằng số như (ENGINE_1_5L, ENGINE_2_0L).
  - uint8_t options: Đây là giá trị chứa các tùy chọn bổ sung cho xe. Mỗi bit trong giá trị này đại diện cho một tùy chọn thêm như (SUNROOF_MASK, PREMIUM_AUDIO_MASK, SPORTS_PACKAGE_MASK).

Hàm này sẽ gán giá trị cho thuộc tính, ví dụ với `color`:
```c
car->color = color;
```
Giá trị `color` được truyền vào hàm sẽ được gán cho thuộc tính `color` trong đối tượng `CarOptions` mà `car` trỏ tới.

# Hàm `setOption` và `unsetOption`
```c
void setOption(CarOptions *car, uint8_t optionMask) {
    car->additionalOptions |= optionMask;
}
```

```c
void unsetOption(CarOptions *car, uint8_t optionMask) {
    car->additionalOptions &= ~optionMask;
}
```
Hai hàm `setOption` và `unsetOption` sử dụng để thao tác các tùy chọn bổ sung `additionalOptions` của đối tượng `CarOptions`. 

Hàm này nhận vào hai tham số:

  - `CarOptions *car`: Đây là con trỏ trỏ tới đối tượng CarOptions mà bạn muốn cấu hình.
  - `uint8_t optionMask`: Đây là một bitmask đại diện cho một hoặc nhiều tùy chọn như (SUNROOF_MASK, PREMIUM_AUDIO_MASK, SPORTS_PACKAGE_MASK) mà người dùng muốn bật hoặc tắt.

Bật tùy chọn bổ sung bằng cách sử dụng toán tử OR (|=) và tắt thì sử dụng toán tử AND với phủ định (&= ~).

# Hàm `displayCarOptions`
```c
void displayCarOptions(const CarOptions car) {
    const char *colors[] = {"Red", "Blue", "Black", "White"};
    const char *powers[] = {"100HP", "150HP", "200HP"};
    const char *engines[] = {"1.5L", "2.0L"};

    printf("Car Configuration: \n");
    printf("Color: %s\n", colors[car.color]);
    printf("Power: %s\n", powers[car.power]);
    printf("Engine: %s\n", engines[car.engine]);
    printf("Sunroof: %s\n", (car.additionalOptions & SUNROOF_MASK) ? "Yes" : "No");
    printf("Premium Audio: %s\n", (car.additionalOptions & PREMIUM_AUDIO_MASK) ? "Yes" : "No");
    printf("Sports Package: %s\n", (car.additionalOptions & SPORTS_PACKAGE_MASK) ? "Yes" : "No");
}
```
Hàm `displayCarOptions` được sử dụng để hiển thị cấu hình thuộc tính của chiếc xe.
Hàm nhận vào một tham số:
   - `const CarOptions car`: Đây là đối tượng CarOptions chứa thông tin cấu hình của xe. Thuộc tính const đảm bảo rằng đối tượng car không bị thay đổi bên trong hàm. Hàm sử dụng đối tượng này để truy xuất thông tin .

Hàm khai báo các mảng hằng số `const char *colors[]`, `const char *powers[]`,` const char *engines[]`. Lấy `const char *colors[]` làm đại diện giải thích:

  - Đây là một mảng chứa các chuỗi ký tự đại diện cho các màu sắc của xe, tương ứng với các giá trị trong thuộc tính `color` của CarOptions.

  - Mảng này có thứ tự tương ứng với các giá trị số nguyên được định nghĩa trước đó như COLOR_RED, COLOR_BLUE, COLOR_BLACK, COLOR_WHITE.

Mục đích khai báo các mảng hằng số:
  - Các thuộc tính như `color`, `power`, và `engine` trong cấu trúc `CarOptions` được lưu trữ dưới dạng số nguyên (uint8_t). Mỗi giá trị số nguyên này đại diện cho một thuộc tính cụ thể (ví dụ: 0 là COLOR_RED, 1 là COLOR_BLUE,...).
  - Tuy nhiên, khi hiển thị thông tin cho người dùng, chúng ta không muốn hiển thị các giá trị số nguyên mà thay vào đó là các chuỗi ký tự có ý nghĩa như "Red", "Blue", "100HP", "1.5L",...
  - Mảng hằng số cho phép ánh xạ giá trị số nguyên của mỗi thuộc tính thành một chuỗi ký tự tương ứng, ví dụ khi in ra thuộc tính `color` trong `CarOptions` với giá trị 2, tương ứng với `COLOR_BLACK`. Chỉ cần truy xuất mảng colors tại vị trí 2 là "Black":
    ```c
    printf("Color: %s\n", colors[car.color]);
    ```
  - Sử dụng thuộc tính `const`: ý là báo với trình biên dịch rằng các giá trị trong mảng này không được phép thay đổi sau khi chúng được khởi tạo.

Cuối cùng là hiển thị các tùy chọn thêm:
  ```c
  printf("Sunroof: %s\n", (car.additionalOptions & SUNROOF_MASK) ? "Yes" : "No");
  ```
  - Sử dụng toán tử AND `&` để kiểm tra xem bit tương ứng với SUNROOF_MASK trong additionalOptions có được bật hay không.
  - Nếu bit đó là 1, in "Yes"; nếu không, in "No".
