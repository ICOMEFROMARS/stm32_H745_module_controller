#include "ad5544.h"
#include <stdio.h>

#define AD5544_CS_GPIO_Port GPIOB
#define AD5544_CS_Pin GPIO_PIN_8

extern SPI_HandleTypeDef hspi1;

static void AD5544_CS_Low() {
    HAL_GPIO_WritePin(AD5544_CS_GPIO_Port, AD5544_CS_Pin, GPIO_PIN_RESET);
}

static void AD5544_CS_High() {
    HAL_GPIO_WritePin(AD5544_CS_GPIO_Port, AD5544_CS_Pin, GPIO_PIN_SET);
}

void AD5544_Init(void) {
    AD5544_CS_High();
}

void AD5544_WriteChannel(uint8_t channel, uint16_t value) {
    uint8_t data[3];
    data[0] = (channel & 0x03) << 6;
    data[1] = (value >> 8) & 0xFF;
    data[2] = value & 0xFF;

    AD5544_CS_Low();

    for (int i = 0; i < 3; i++) {
        while (!(SPI1->SR & (1 << 1)));
        SPI1->TXDR = data[i];
    }

    while ((SPI1->SR & (1 << 0)));

    AD5544_CS_High();
}

void AD5544_ClearAll(void) {
    for (uint8_t ch = 0; ch < 4; ch++) {
        AD5544_WriteChannel(ch, 0x0000);
    }
}


