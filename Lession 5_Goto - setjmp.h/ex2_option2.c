#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;

typedef enum  { 
    NO_ERROR, 
    FILE_ERROR, 
    NETWORK_ERROR, 
    CALCULATION_ERROR 
}ErrorCodes;

ErrorCodes errorcodes;

typedef struct {
    ErrorCodes code;
    const char *message;
} ErrorInfo;

#define TRY if ((setjmp(buf)) == 0) 
#define CATCH(x) else if (errorcodes == (x)) 

#define THROW(x, msg){                                              \
    errorcodes = x;                                                 \
    longjmp(buf, x);                                                \
}

const char* getErrorMessage(ErrorCodes code) {
    static ErrorInfo errorTable[] = {
        {NO_ERROR, "No error."},
        {FILE_ERROR, "Lỗi đọc file: File không tồn tại."},
        {NETWORK_ERROR, "Lỗi kết nối: Kết nối không ổn định."},
        {CALCULATION_ERROR, "Lỗi tính toán: Số liệu không hợp lệ."}
    };
    for (int i = 0; i < sizeof(errorTable)/sizeof(ErrorInfo); i++) {
        if (errorTable[i].code == code) {
            return errorTable[i].message;
        }
    }
    return "Unknown error.";
}

void readFile() {
    printf("Đọc file...\n");
    THROW(FILE_ERROR, "Lỗi đọc file: File không tồn tại.");
}

void networkOperation() {
    // Bổ sung chương trình
    THROW(NETWORK_ERROR, "Lỗi kết nối: Kết nối không ổn định.");
}

void calculateData() {
   // Bổ sung chương trình
    THROW(CALCULATION_ERROR , "Lỗi tính toán: Tính toán lỗi.");

}

int main() {
    TRY {
        //readFile();
        //networkOperation();
        //calculateData();
    } 
    
    CATCH(FILE_ERROR) {
        printf("%s\n", getErrorMessage(FILE_ERROR));
    } 

    CATCH(NETWORK_ERROR) {
        printf("%s\n", getErrorMessage(NETWORK_ERROR));
    }

    CATCH(CALCULATION_ERROR) {
        printf("%s\n", getErrorMessage(CALCULATION_ERROR));
    }

    // CATCH mặc định nếu có lỗi nào khác
    else {
        printf("Một lỗi không xác định đã xảy ra.\n");
    }

    return 0;
}



