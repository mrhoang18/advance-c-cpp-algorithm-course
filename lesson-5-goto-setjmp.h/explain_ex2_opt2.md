Đoạn code này sử dụng để xử lý ngoại lệ (exception handling) đơn giản.
# Khai báo kiểu dữ liệu và biến toàn cục
```c
typedef enum  { 
    NO_ERROR, 
    FILE_ERROR, 
    NETWORK_ERROR, 
    CALCULATION_ERROR 
} ErrorCodes;

jmp_buf buf;
ErrorCodes errorcodes;
```
# Macro
```c
#define TRY if ((setjmp(buf)) == 0) 
#define CATCH(x) else if (errorcodes == (x)) 

#define THROW(x, msg){                                              \
    errorcodes = x;                                                 \
    longjmp(buf, x);                                                \
}
```
# Hàm lưu trữ thông điệp lỗi
```c
const char* getErrorMessage(ErrorCodes code) {
    const char *errorTable[] = {
        "No error.",
        "Lỗi đọc file: File không tồn tại.",
        "Lỗi kết nối: Kết nối không ổn định.",
        "Lỗi tính toán: Số liệu không hợp lệ."
    };
    if (code >= NO_ERROR && code <= CALCULATION_ERROR) {
        return errorTable[code];
    }
    return "Unknown error.";
}
```
# Các àm mô phỏng lỗi 
```c
void readFile() {
    printf("Đọc file...\n");
    THROW(FILE_ERROR, "Lỗi đọc file: File không tồn tại.");
}
void networkOperation() {
    THROW(NETWORK_ERROR, "Lỗi kết nối: Kết nối không ổn định.");
}
void calculateData() {
    THROW(CALCULATION_ERROR , "Lỗi tính toán: Tính toán lỗi.");
}
```

