# Bài 1: Tính tổng với số lượng đầu vào bất kì
Sử dụng Variadic macro nhận một số lượng biến tham số có thể thay đổi. 

Đồng thời gọi hàm `sum(__VA_ARGS__,0)`, với các đối số truyền vào: `__VA_ARGS__` là các tham số đã nhập vào từ input(...) ứng với int count và số 0 ứng với `...`

```bash
#define input(...) sum(__VA_ARGS__,0)
int sum(int count, ...){
    va_list va;

    int sum = count;

    va_start(va, count);

    int value;

    while ((value=va_arg(va, int))!=0)
    {
        sum+=value;
    }
    
    va_end(va);

    return sum;
}
```

