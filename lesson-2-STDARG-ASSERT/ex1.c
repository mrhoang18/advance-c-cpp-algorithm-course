#include <stdio.h>
#include <stdarg.h>

typedef enum {
    TEMPERATURE_SENSOR,
    PRESSURE_SENSOR,
    // More sensor
    FUEL_SENSOR,
    SPEED_SENSOR

} SensorType;

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
        case SPEED_SENSOR: {
            int numArgs = va_arg(args, int);
            int sensorId = va_arg(args, int);
            float speed = va_arg(args, double);
            printf("Speed Sensor ID: %d, Reading: %.2f km/h\n", sensorId, speed);
                
            for (int i = 2; i < numArgs; i++) {
                char* additionalInfo = va_arg(args, char*);
                printf("Additional Info: %s\n", additionalInfo);
            }
            break;                        
        }
    }
    va_end(args);
}

int main() {
    //func(_SENSOR, Number of parameters, ID, Param1, Param2,...)
    processSensorData(TEMPERATURE_SENSOR, 3, 1, 36.5, "Room Temperature.");
    processSensorData(PRESSURE_SENSOR, 2, 2, 101325);
    processSensorData(FUEL_SENSOR, 3, 3, 50.0, "Fuel tank half full.");

    processSensorData(SPEED_SENSOR, 5, 4, 120.0, "High Speed!", "Call 911!", "Bye!");
    return 0;
}


