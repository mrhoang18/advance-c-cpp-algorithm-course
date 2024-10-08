#include <stdio.h>

typedef struct {
   void (*start)(int gpio);
   void (*stop)(int gpio);
   void (*changeSpeed)(int gpio, int speed);
} MotorController;

typedef int PIN;

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

// Macro để khởi tạo GPIO và MotorController
#define INIT_MOTOR(motorName, pinNumber) \
   PIN PIN_##motorName = pinNumber; \
   MotorController motorName = {startMotor, stopMotor, changeSpeedMotor};

int main() {
   // Sử dụng macro để khởi tạo
   INIT_MOTOR(motorA, 1);
   INIT_MOTOR(motorB, 2);

   // Sau tiền xử lí, kết quả trong file .i
   // PIN PIN_motorA = 1; 
   // MotorController motorA = {startMotor, stopMotor, changeSpeedMotor};
   // PIN PIN_motorB = 2; 
   // MotorController motorB = {startMotor, stopMotor, changeSpeedMotor};

   // Khởi tạo biến PIN cho motorC
   PIN PIN_motorC = 3;
   // Khởi tạo một đối tượng MotorController
   MotorController motorC_instance = {&startMotor, &stopMotor, &changeSpeedMotor};
   // Gán địa chỉ của đối tượng đó cho con trỏ motorC
   MotorController *motorC = &motorC_instance;

   // Sử dụng motorA
   motorA.start(PIN_motorA);
   motorA.changeSpeed(PIN_motorA, 50);
   motorA.stop(PIN_motorA);

   // Sử dụng motorB
   motorB.start(PIN_motorB);
   motorB.changeSpeed(PIN_motorB, 75);
   motorB.stop(PIN_motorB);

   // Sử dụng motorC
   motorC->start(PIN_motorC);
   motorC->changeSpeed(PIN_motorC, 100);
   motorC->stop(PIN_motorC);

   return 0;
}
