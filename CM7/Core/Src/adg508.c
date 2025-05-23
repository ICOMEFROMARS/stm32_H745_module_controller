#include "adg508.h"

#define ADG508_A0_Port GPIOC
#define ADG508_A0_Pin  GPIO_PIN_10

#define ADG508_A1_Port GPIOC
#define ADG508_A1_Pin  GPIO_PIN_11

#define ADG508_A2_Port GPIOC
#define ADG508_A2_Pin  GPIO_PIN_12

#define ADG508_EN_Port GPIOA
#define ADG508_EN_Pin  GPIO_PIN_15

void ADG508_Init(void)
{
    ADG508_EN_Port->ODR &= ~ADG508_EN_Pin;  				// analog anahtar aktif yani EN low
}

void ADG508_SelectChannel(uint8_t channel)
{
    if (channel < 1 || channel > 8) return;                 // 1�8 kabul et
    channel -= 1;                                           // 0�7�e �evir

    if (channel & 0x01)                                     // kanal numarasinin bitlerini secim pinlerine yaz
        ADG508_A0_GPIO_Port->ODR |= ADG508_A0_Pin;
    else
        ADG508_A0_GPIO_Port->ODR &= ~ADG508_A0_Pin;

    if (channel & 0x02)
        ADG508_A1_GPIO_Port->ODR |= ADG508_A1_Pin;
    else
        ADG508_A1_GPIO_Port->ODR &= ~ADG508_A1_Pin;

    if (channel & 0x04)
        ADG508_A2_GPIO_Port->ODR |= ADG508_A2_Pin;
    else
        ADG508_A2_GPIO_Port->ODR &= ~ADG508_A2_Pin;
}

