#include "adg506.h"


#define ADG506_A0_Port GPIOE
#define ADG506_A0_Pin  GPIO_PIN_2

#define ADG506_A1_Port GPIOE
#define ADG506_A1_Pin  GPIO_PIN_3

#define ADG506_A2_Port GPIOE
#define ADG506_A2_Pin  GPIO_PIN_4

#define ADG506_A3_Port GPIOE
#define ADG506_A3_Pin  GPIO_PIN_5

#define ADG506_EN_Port GPIOE
#define ADG506_EN_Pin  GPIO_PIN_6

void ADG506_Init(void)
{
    ADG506_EN_Port->ODR &= ~ADG506_EN_Pin;  // analog anahtar aktif yani EN low
}

void ADG506_SelectChannel(uint8_t channel)
{
    if (channel < 1 || channel > 16) return;                                                                // gecersiz kanal kontrolu (artik 1–16 arasi)

    channel -= 1;                                                                                           // donanim 0–15 bekledigi icin 1 eksiltilir

    (channel & 0x01) ? (ADG506_A0_Port->ODR |= ADG506_A0_Pin) : (ADG506_A0_Port->ODR &= ~ADG506_A0_Pin);
    (channel & 0x02) ? (ADG506_A1_Port->ODR |= ADG506_A1_Pin) : (ADG506_A1_Port->ODR &= ~ADG506_A1_Pin);
    (channel & 0x04) ? (ADG506_A2_Port->ODR |= ADG506_A2_Pin) : (ADG506_A2_Port->ODR &= ~ADG506_A2_Pin);
    (channel & 0x08) ? (ADG506_A3_Port->ODR |= ADG506_A3_Pin) : (ADG506_A3_Port->ODR &= ~ADG506_A3_Pin);
}
