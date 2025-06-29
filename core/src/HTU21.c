#include "HTU21.h"  // Include the header file properly

void HTU21_Reset(void) {
    uint8_t Data = HTU21_RESET;  // Reset command
    HAL_Delay(15);               // Wait for 15 ms

    // Transmit reset command to HTU21
    HAL_I2C_Master_Transmit(&hi2c1, HTU21_I2CADDR, &Data, 1, 1000);

    HAL_Delay(15);  // Wait for reset to complete
}

char HTU21_Init(void) {
    uint8_t check;
    uint8_t Data = HTU21_READREG;

    // Request the register value from HTU21
    HAL_I2C_Master_Transmit(&hi2c1, HTU21_I2CADDR, &Data, 1, 1000);

    // Receive the check value
    HAL_I2C_Master_Receive(&hi2c1, HTU21_I2CADDR, &check, 1, 1000);

    return check;  // Return the check value (typically used to verify if the sensor is responding)
}

float HTU21_GetTemp(void) {
    uint8_t TempData[2];  // Array to store temperature data
    uint8_t Data = HTU21_READTEMP;

    // Request temperature data
    HAL_I2C_Master_Transmit(&hi2c1, HTU21_I2CADDR, &Data, 1, 1000);

    // Receive temperature data
    HAL_I2C_Master_Receive(&hi2c1, HTU21_I2CADDR, TempData, 2, 1000);

    // Combine the two bytes to form a 16-bit value
    uint16_t RawTemp = (TempData[0] << 8) | (TempData[1] & 0xFC);  // Mask the last two bits of the second byte

    // Calculate the temperature value
    float Temp = (RawTemp * 175.72f) / 65536.0f - 46.85f;

    return Temp;
}

float HTU21_GetHumidity(void) {
    uint8_t HumData[2];  // Array to store humidity data
    uint8_t Data = HTU21_READHUM;

    // Request humidity data
    HAL_I2C_Master_Transmit(&hi2c1, HTU21_I2CADDR, &Data, 1, 1000);

    // Receive humidity data
    HAL_I2C_Master_Receive(&hi2c1, HTU21_I2CADDR, HumData, 2, 1000);

    // Combine the two bytes to form a 16-bit value
    uint16_t RawHum = (HumData[0] << 8) | (HumData[1] & 0xFC);  // Mask the last two bits of the second byte

    // Calculate the humidity value
    float Hum = (RawHum * 125.0f) / 65536.0f - 6.0f;

    return Hum;
}
