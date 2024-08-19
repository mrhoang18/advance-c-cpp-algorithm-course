// Thêm 2 tính năng, giải thích code
#include <stdio.h>
#include <stdarg.h>

typedef enum {
    TURN_ON,
    TURN_OFF,
    SET_LEVEL,
    SEND_MESSAGE,
    GET_STATUS,      // Lệnh mới: Lấy trạng thái thiết bị
    RESTART_DEVICE   // Lệnh mới: Khởi động lại thiết bị
} CommandType;

void sendCommand(CommandType command, ...) {
    va_list args;
    va_start(args, command);

    switch (command) {
        case TURN_ON:
        case TURN_OFF: {
            int deviceID = va_arg(args, int);
            printf("Command: %s Device ID: %d\n", command == TURN_ON ? "Turn On" : "Turn Off", deviceID);
            break;
        }
        case SET_LEVEL: {
            int deviceID = va_arg(args, int);
            int level = va_arg(args, int);
            printf("Set Level of Device ID %d to %d\n", deviceID, level);
            break;
        }
        case SEND_MESSAGE: {
            char* message = va_arg(args, char*);
            printf("Send Message: %s\n", message);
            break;
        }
        case GET_STATUS: {  // Xử lý lệnh GET_STATUS
            int deviceID = va_arg(args, int);
            // Giả sử hàm này sẽ lấy trạng thái và in ra
            printf("Get Status of Device ID %d\n", deviceID);
            // Ở đây bạn có thể thêm mã để thực sự lấy trạng thái từ thiết bị
            break;
        }
        case RESTART_DEVICE: {  // Xử lý lệnh RESTART_DEVICE
            int deviceID = va_arg(args, int);
            printf("Restarting Device ID %d\n", deviceID);
            // Ở đây bạn có thể thêm mã để thực sự khởi động lại thiết bị
            break;
        }
    }

    va_end(args);
}

int main() {
    sendCommand(TURN_ON, 1);
    sendCommand(TURN_OFF, 2);
    sendCommand(SET_LEVEL, 3, 75);
    sendCommand(SEND_MESSAGE, "Hello World");
    sendCommand(GET_STATUS, 4);        // Gọi lệnh GET_STATUS
    sendCommand(RESTART_DEVICE, 5);    // Gọi lệnh RESTART_DEVICE
    return 0;
}

