# Định nghĩa kiểu dữ liệu `MotorController`, `PIN`
  ```bash
  typedef struct {
     void (*start)(int gpio);
     void (*stop)(int gpio);
     void (*changeSpeed)(int gpio, int speed);
  } MotorController;
  
  typedef int PIN;
  ```
`struct` là một kiểu dữ liệu tự đinh nghĩa bởi người dùng. 
`typedef` là từ khóa cho phép người dùng thêm tên mới cho kiểu có sẵn.

Cụ thể, cấu trúc `MotorController` đã định nghĩa có ba thành phần:

  - `void (*start)(int gpio)`, `void (*stop)(int gpio)`: là con trỏ hàm, nó trỏ đến bất kì địa chỉ của hàm nào mà có kiểu trả về là `void`, tham số truyền vào là `int`.

  - `void (*changeSpeed)(int gpio, int speed)`: tương tự như trên, khác ở chỗ là có hai tham số truyền vào có kiểu là `int`. 

# Các hàm chung
  ```bash
  // Các hàm chung
  void startMotor(PIN pin) {
     printf("Start motor at PIN %d\n", pin);
  }
  
  void stopMotor(PIN pin) {
     printf("Stop motor at PIN %d\n", pin);
  }
  
  void changeSpeedMotor(PIN pin, int speed) {
     printf("Change speed at PIN %d: %d\n", pin, speed);
  }
  ```
Các hàm trên đơn giản là các hàm điều khiển motor và in ra đang điều khiển cái gì.
# Macro khởi tạo GPIO và MotorController
  ```bash
  // Macro function
  #define INIT_MOTOR(motorName, pinNumber)                                       \
     PIN PIN_##motorName = pinNumber;                                            \
     MotorController motorName = {startMotor, stopMotor, changeSpeedMotor};
  ```

Macro function `INIT_MOTOR` nhận vào hai tham `motorName`, `pinNumber`, dùng để khởi tạo:

  - `PIN PIN_##motorName = pinNumber;`: `PIN` là kiểu dữ liệu đã được định nghĩa ở trên, `PIN_##motorName` sẽ tạo ra tên biến bằng cách sử dụng toán tử nối chuỗi `PIN_` với tên của động cơ `motorName` và gán giá trị với chân `pinNumber`.
  
  - `MotorController motorName = {startMotor, stopMotor, changeSpeedMotor};`: Khởi tạo biến `motorName` kiểu dữ liệu đã được định nghĩa ở trên `MotorController` và các con trỏ hàm thành viên được gán với địa chỉ các hàm `startMotor`, `stopMotor`, `changeSpeedMotor`.

Gọi macro function ra để khởi tạo cho hai motor A, B:
  ```bash
  // Gọi macro function để khởi tạo
  // INIT_MOTOR(motorA, 1);
  // INIT_MOTOR(motorB, 2);
  ```
Sau quá trình tiền xử lý, ta được:
  ```bash
   PIN PIN_motorA = 1;
  MotorController motorA = {startMotor, stopMotor, changeSpeedMotor};
   PIN PIN_motorB = 2;
  MotorController motorB = {startMotor, stopMotor, changeSpeedMotor};
  ```
# Sử dụng motor
  ```bash
  // Sử dụng motorA
  motorA.start(PIN_motorA);
  motorA.changeSpeed(PIN_motorA, 50);
  motorA.stop(PIN_motorA);

  // Sử dụng motorB
  motorB.start(PIN_motorB);
  motorB.changeSpeed(PIN_motorB, 75);
  motorB.stop(PIN_motorB);
  ```
Các biến `motorA` sử dụng toán tử `.` (Member access operator) để truy cập tới các biến thành viên.

Hàm `startMotor` được gọi thông qua con trỏ hàm `start` đã được gán địa chỉ của hàm `startMotor` ở trên.

Các hàm ở phía sau tương tự.





