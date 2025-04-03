#ifndef INC_ADG508_H_
#define INC_ADG508_H_

#include "stm32h7xx_hal.h"

void ADG508_Init(void);
void ADG508_SelectChannel(uint8_t channel);  // 0–7 arası geçerli

#endif /* INC_ADG508_H_ */
