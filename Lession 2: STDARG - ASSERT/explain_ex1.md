# Định nghĩa kiểu dữ liệu liệt kê các cảm biến 
```bash
typedef enum {
    TEMPERATURE_SENSOR,
    PRESSURE_SENSOR,
    // More sensor
    FUEL_SENSOR,
    SPEED_SENSOR   
} SensorType;
```
Định nghĩa một kiểu liệt kê (enumeration) chứa các cảm biến. 

Mỗi phần tử trong enum sẽ được gán một giá trị nguyên bắt đầu từ 0, trừ khi chỉ định giá trị khác.

Từ khóa `typedef` để định nghĩa một tên kiểu dữ liệu mới ở đây là `SensorType` từ các kiểu dữ liệu đã có sẵn.

# Nhận vào nhiều tham số sử dụng variadic macro
```bash
#define inProcessSensorData(...) processSensorData(__VA_ARGS__,0)
```
Variadic macro chấp nhận một số lượng đối số không xác định. Bất kỳ số lượng đối số nào truyền vào sẽ được đặt trong `...` 

`__VA_ARGS__` là một từ khóa macro để đại diện cho tất cả các đối số được truyền vào `...`

Khi macro inProcessSensorData được gọi:
  ```bash
  inProcessSensorData(SPEED_SENSOR, 4, 120.0, "High Speed!", "Call 911!", "Bye!");
  ```
Tất cả các đối số truyền vào sẽ được chèn vào vị trí của `__VA_ARGS__`, và sau đó số 0 sẽ được thêm vào cuối danh sách đối số. 
Cuối cùng, macro sẽ gọi hàm `processSensorData`.
# Hàm xử lý chính
  ```bash
  void processSensorData(SensorType type, ...) {
      va_list args;
      va_start(args, type);

      switch (type) {
          case TEMPERATURE_SENSOR: {
              int numArgs = va_arg(args, int);
              int sensorId = va_arg(args, int);
              float temperature = va_arg(args, double); // float được promote thành double
              printf("Temperature Sensor ID: %d, Reading: %.2f degrees\n", sensorId, temperature);
              if (numArgs > 2) {
                  // Xử lý thêm tham số nếu có
                  char* additionalInfo = va_arg(args, char*);
                  printf("Additional Info: %s\n", additionalInfo);
              }
              break;
          }
          case PRESSURE_SENSOR: {
              int numArgs = va_arg(args, int);
              int sensorId = va_arg(args, int);
              int pressure = va_arg(args, int);
              printf("Pressure Sensor ID: %d, Reading: %d Pa\n", sensorId, pressure);
              if (numArgs > 2) {
                  // Xử lý thêm tham số nếu có
                  char* additionalInfo = va_arg(args, char*);
                  printf("Additional Info: %s\n", additionalInfo);
              }
              break;
          }
          case FUEL_SENSOR: {
              int numArgs = va_arg(args, int);
              int sensorId = va_arg(args, int);
              float fuelLevel = va_arg(args, double);
              printf("Fuel sensor ID: %d, Reading: %.2f litter\n", sensorId, fuelLevel);
  
              if (numArgs > 2) {
                  // Xử lý thêm tham số nếu có
                  char* additionalInfo = va_arg(args, char*);
                  printf("Additional Info: %s\n", additionalInfo);
              }
              break;
          }
          // Cải tiến
          case SPEED_SENSOR: {
              //int numArgs = va_arg(args, int);
              int sensorId = va_arg(args, int);
              float speed = va_arg(args, double);
              printf("Speed Sensor ID: %d, Reading: %.2f km/h\n", sensorId, speed);
                  
              char* additionalInfo;
              while ((additionalInfo = va_arg(args, char*))!=0){
                  // Xử lý thêm tham số nếu có
                  printf("Additional Info: %s\n", additionalInfo);
              }
              break;                        
          }
      }
      va_end(args);
  }
  ```
Hàm  `void processSensorData(SensorType type, ...)` xử lý các cảm biến khác nhau dựa trên giá trị của tham số truyền vào đầu tiên `type` (kiểu SensorType).

`va_list` là một kiểu dữ liệu đặc biệt được sử dụng để xử lý danh sách số lượng các tham số không xác định. Biến args sẽ được sử dụng để lưu trữ thông tin về các tham số này.

`va_start` là một macro có sẵn của `stdarg.h` sử dụng để khởi tạo danh sách. Macro này cần truyền vào hai tham số: biến kiểu `va_list` (ở đây là `args`) và tham số cuối cùng trước `...` (ở đây là `command`).

Vì cách hoạt động nó tương tự nhau, nên sẽ lấy `case SPEED_SENSOR` làm đại diện để giải thích:
```bash
case SPEED_SENSOR: {
    int sensorId = va_arg(args, int);
    float speed = va_arg(args, double);
    printf("Speed Sensor ID: %d, Reading: %.2f km/h\n", sensorId, speed);
      
    char* additionalInfo;
    while ((additionalInfo = va_arg(args, char*))!=0){
      // Xử lý thêm tham số nếu có
      printf("Additional Info: %s\n", additionalInfo);
    }
    break;
}
```
