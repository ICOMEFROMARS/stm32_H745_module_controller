#include "ad7533.h"

static GPIO_TypeDef* data_ports[10] = {
    GPIOA, GPIOA, GPIOA, GPIOA, GPIOA,
    GPIOA, GPIOC, GPIOC, GPIOC, GPIOC
};

static const uint16_t data_pins[10] = {
    GPIO_PIN_13, GPIO_PIN_12, GPIO_PIN_11, GPIO_PIN_10, GPIO_PIN_9,
    GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_8, GPIO_PIN_7, GPIO_PIN_6
};

#define AD7533_WR_GPIO_Port GPIOG
#define AD7533_WR_Pin       GPIO_PIN_7

#define AD7533_CS_GPIO_Port GPIOG
#define AD7533_CS_Pin       GPIO_PIN_8

void AD7533_Init(void) {
    // DAC pasif duruma getirilir yani CS ve WR pinleri HIGH yapýlýr
    HAL_GPIO_WritePin(AD7533_CS_GPIO_Port, AD7533_CS_Pin, GPIO_PIN_SET);				
    HAL_GPIO_WritePin(AD7533_WR_GPIO_Port, AD7533_WR_Pin, GPIO_PIN_SET); 			
}

void AD7533_Write(uint16_t value) {                                                     // 10 bitlik veriyi pinlere bit bit yaz

    for (int i = 0; i < 10; i++) {
        if (value & (1 << i)) {
            data_ports[i]->ODR |= data_pins[i]; 																			// ilgili pin high
        } else {
            data_ports[i]->ODR &= ~data_pins[i]; 																			// ilgili pin low
        }
    }

    // DAC üzerinde veri yazmak için gerekli pulse yani WR ve CS pinleri
    AD7533_CS_GPIO_Port->BSRR = (uint32_t)AD7533_CS_Pin << 16; // CS low
    AD7533_WR_GPIO_Port->BSRR = (uint32_t)AD7533_WR_Pin << 16; // WR low
    for (volatile int i = 0; i < 10; i++);                     // kisa gecikme
    AD7533_WR_GPIO_Port->BSRR = AD7533_WR_Pin;                 // WR high
    AD7533_CS_GPIO_Port->BSRR = AD7533_CS_Pin;                 // CS high
}



