# Tính tổng với số lượng đầu vào bất kì

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
va_list va;: Khai báo một biến va để lưu trữ thông tin về danh sách các tham số biến động.

int sum = count;: Khởi tạo biến sum bằng giá trị count, là tham số đầu tiên được truyền vào hàm.

va_start(va, count);: Khởi tạo va để bắt đầu truy cập các tham số biến động, bắt đầu từ tham số thứ hai (sau count).

Vòng lặp while ((value=va_arg(va, int))!=0):

Sử dụng va_arg(va, int) để lấy từng giá trị trong danh sách.

Vòng lặp tiếp tục cho đến khi gặp giá trị 0, lúc này vòng lặp sẽ dừng lại.

Mỗi giá trị được lấy ra sẽ được cộng vào sum.

va_end(va);: Giải phóng bộ nhớ.
