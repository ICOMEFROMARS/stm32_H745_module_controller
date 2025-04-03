#ifndef INC_ADG506_H_
#define INC_ADG506_H_

#include "stm32h7xx_hal.h"

void ADG506_Init(void);
void ADG506_SelectChannel(uint8_t channel);  // 0–15 arası geçerli

#endif /* INC_ADG506_H_ */
