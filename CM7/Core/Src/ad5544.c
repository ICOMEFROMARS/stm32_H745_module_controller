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
                                             // SPI ile gonderilecek veri buffer'i hazirlaniyor
    uint8_t data[3];
    data[0] = (channel & 0x03) << 6;         // komut byte'i: kanal secimi 0-3
    data[1] = (value >> 8) & 0xFF;           // MSB
    data[2] = value & 0xFF;                  // LSB

    AD5544_CS_Low();                         // DAC ile SPI baglantisi baslat

                                             // 3 byte SPI ile gonderiliyor
    for (int i = 0; i < 3; i++) {
        while (!(SPI1->SR & (1 << 1)));      // TX buffer bos olana kadar bekle
        SPI1->TXDR = data[i];                // byte gonder
    }

    while ((SPI1->SR & (1 << 0)));           // SPI gonderim tamamlanana kadar bekle

    AD5544_CS_High();                        // SPI iletisimi sonlandir
}

void AD5544_ClearAll(void) {
    for (uint8_t ch = 0; ch < 4; ch++) {     // tum DAC kanallarina sifir degeri gonderilir
        AD5544_WriteChannel(ch, 0x0000);
    }
}


