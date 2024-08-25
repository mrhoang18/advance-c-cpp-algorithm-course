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
Hàm này có bốn tham số chính và một tham số cho các tùy chọn bổ sung:

- `CarOptions *car`: Đây là con trỏ trỏ tới một đối tượng `CarOptions`. Thông qua con trỏ này, hàm có thể truy cập và thay đổi các thuộc tính của đối tượng `CarOptions` mà nó trỏ tới.
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

