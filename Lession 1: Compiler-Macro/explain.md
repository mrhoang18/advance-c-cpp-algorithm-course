Sử dụng Variadic macro nhận một số lượng biến tham số có thể thay đổi.
~~
#define in(...) sum(__VA_ARGS__,0)

