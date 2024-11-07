# Định nghĩa kiểu dữ liệu liệt kê các lệnh
  ```bash
  typedef enum {
      TURN_ON,
      TURN_OFF,
      SET_LEVEL,
      SEND_MESSAGE,
      GET_STATUS,      // Lệnh mới: Lấy trạng thái thiết bị
      RESTART_DEVICE   // Lệnh mới: Khởi động lại thiết bị
  } CommandType;
  ```

Định nghĩa một kiểu liệt kê (enumeration) chứa các lệnh của một hệ thống nào đó. 

Mỗi phần tử trong enum mặc định sẽ được gán một giá trị nguyên bắt đầu từ 0, trừ khi chỉ định giá trị cụ thể khác.

Từ khóa `typedef` để định nghĩa một tên kiểu dữ liệu mới ở đây là `CommandType` từ các kiểu dữ liệu đã có sẵn. 

Câu hỏi đặt ra: **Vì sao không đem đại các số 0, 1, 2 vô làm điều kiện cho các cấu trúc rẽ nhánh luôn?**

Vì: Khi định nghĩa bằng các label có nghĩa thì người khác có thể hiểu được đoạn code hoạt động như thế nào.

# Hàm xử lý chính 
  ```bash
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
  ```
Hàm  `void sendCommand(CommandType command, ...)` xử lý các lệnh khác nhau dựa trên giá trị của tham số truyền vào đầu tiên `command` (kiểu CommandType).

`va_list` là một kiểu dữ liệu đặc biệt được sử dụng để xử lý danh sách số lượng các tham số không xác định. Biến args sẽ được sử dụng để lưu trữ thông tin về các tham số này.

`va_start` là một macro có sẵn của `stdarg.h` sử dụng để khởi tạo danh sách. Macro này cần truyền vào hai tham số: biến kiểu `va_list` (ở đây là `args`) và tham số cuối cùng trước `...` (ở đây là `command`).

Vì cách hoạt động nó tương tự nhau, nên sẽ lấy `case SET_LEVEL` làm đại diện để giải thích:

  ```bash
  case SET_LEVEL: {
      int deviceID = va_arg(args, int);            // Hàm va_arg(args, int) gọi lần 1
      int level = va_arg(args, int);               // Hàm va_arg(args, int) gọi lần 2
      printf("Set Level of Device ID %d to %d\n", deviceID, level);
      break;
  }
  ```
Hàm `va_arg(args, type)`: Được sử dụng để lấy từng tham số tiếp theo trong danh sách `...` sau mỗi lần gọi, với type là kiểu dữ liệu của tham số.

# Gửi lệnh đi
  ```bash
  sendCommand(TURN_ON, 1);                  // Bật thiết bị 1
  sendCommand(TURN_OFF, 2);                 // Tắt thiết bị 2
  sendCommand(SET_LEVEL, 3, 75);            // Set mực nước của thiết bị 3 là 75
  sendCommand(SEND_MESSAGE, "Hello World"); // Cho màn hình in ra Hello
  sendCommand(GET_STATUS, 4);               // Lấy trạng thái thiết bị 4
  sendCommand(RESTART_DEVICE, 5);           // Khởi động lại thiết bị 5
  ```  
Gọi hàm `sendCommand` với các lệnh và tham số khác nhau để thực hiện các hành động  như bật, tắt thiết bị, đặt mức độ, gửi thông điệp, lấy trạng thái, và khởi động lại thiết bị. 

