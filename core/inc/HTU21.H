#ifndef SRC_HTU21_H_
#define SRC_HTU21_H_

#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c1;

/** Default I2C address for the HTU21D. */
#define HTU21_I2CADDR (0x80)

/** Read temperature register. */
#define HTU21_READTEMP (0xE3)

/** Read humidity register. */
#define HTU21_READHUM (0xE5)

/** Write register command. */
#define HTU21_WRITEREG (0xE6)

/** Read register command. */
#define HTU21_READREG (0xE7)

/** Reset command. */
#define HTU21_RESET (0xFE)

#ifdef __cplusplus
extern "C" {
#endif

char HTU21_Init(void);
float HTU21_GetTemp(void);
float HTU21_GetHumidity(void);  // Assuming a function to get humidity exists.
void HTU21_Reset(void);

#ifdef __cplusplus
}
#endif

#endif /* SRC_HTU21_H_ */
