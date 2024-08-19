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

  - `void (*start)(int gpio)`, `void (*stop)(int gpio)`: 
  - `void (*changeSpeed)(int gpio, int speed)`:     

# Macro khởi tạo GPIO và MotorController
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
# Macro khởi tạo GPIO và MotorController
  ```bash
  // Macro function
  #define INIT_MOTOR(motorName, pinNumber)                                       \
     PIN PIN_##motorName = pinNumber;                                            \
     MotorController motorName = {startMotor, stopMotor, changeSpeedMotor};

  // Gọi macro function để khởi tạo
  // INIT_MOTOR(motorA, 1);
  // INIT_MOTOR(motorB, 2);
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





