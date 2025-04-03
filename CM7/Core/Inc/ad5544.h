#ifndef INC_AD5544_H_
#define INC_AD5544_H_

#include "stm32h7xx_hal.h"

void AD5544_Init(void);
void AD5544_WriteChannel(uint8_t channel, uint16_t value);
void AD5544_ClearAll(void);

#endif /* INC_AD5544_H_ */
