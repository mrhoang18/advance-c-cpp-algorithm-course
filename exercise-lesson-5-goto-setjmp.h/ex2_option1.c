#include <stdio.h>
#include <setjmp.h>

typedef struct
{
    int error_code;
    char error_message[52];
} ErrorList;

jmp_buf buf;
ErrorList error;  

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

double divide(int a, int b) {   
    if (b == 0) {
        THROW(1, "Divide by zero error"); // Lỗi chia cho 0
    }
    if (a < MIN_VALUE || a > MAX_VALUE || b < MIN_VALUE || b > MAX_VALUE) {
        THROW(2, "Overflow error"); // Lỗi tràn số
    }
    return (double)a / b;
}

int main() {
    int a = -32767; 
    int b = 0;
    double result = 0.0;

    TRY {
        result = divide(a, b);
        printf("Result: %f\n", result);
    } CATCH(1) {
        printf("Error: %s\n", error.error_message); // Lỗi chia cho 0
    } CATCH(2) {
        printf("Error: %s\n", error.error_message); // Lỗi tràn
    }

    return 0;
}

