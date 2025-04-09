#include "mx574.h"

#define MX574_DATA_MODE_Port   GPIOE
#define MX574_DATA_MODE_Pin    GPIO_PIN_13

#define MX574_A0_Port          GPIOE
#define MX574_A0_Pin           GPIO_PIN_14

#define MX574_CE_Port          GPIOE
#define MX574_CE_Pin           GPIO_PIN_15

#define MX574_RC_Port          GPIOB
#define MX574_RC_Pin           GPIO_PIN_10

#define MX574_CS_Port          GPIOB
#define MX574_CS_Pin           GPIO_PIN_11

static GPIO_TypeDef* data_ports[12] = {
    GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD,
    GPIOD, GPIOD, GPIOB, GPIOB, GPIOB, GPIOB
};

static uint16_t data_pins[12] = {
    GPIO_PIN_15, GPIO_PIN_14, GPIO_PIN_13, GPIO_PIN_12,
    GPIO_PIN_11, GPIO_PIN_10, GPIO_PIN_9, GPIO_PIN_8,
    GPIO_PIN_15, GPIO_PIN_14, GPIO_PIN_13, GPIO_PIN_12
};

void MX574_Init(void)
{
    MX574_DATA_MODE_Port->ODR |= MX574_DATA_MODE_Pin;                           // ADC modulu 12 bit veri moduna alinir, DATA_MODE = high

    MX574_CE_Port->ODR |= MX574_CE_Pin;                                         // CS ve CE pinleri high yapilarak cihaz devre disi birakilir
    MX574_CS_Port->ODR |= MX574_CS_Pin;
}

uint16_t MX574_Read12Bit(void) {
    uint16_t result = 0;

    MX574_CS_Port->ODR &= ~MX574_CS_Pin;                                        // okuma islemi baslatilir, CS, RC, CE pinleri sirasiyla low yapilir
    MX574_RC_Port->ODR &= ~MX574_RC_Pin;
    MX574_CE_Port->ODR &= ~MX574_CE_Pin;
    for (volatile int i = 0; i < 1000; i++);                                    // kisa gecikme
    MX574_CE_Port->ODR |= MX574_CE_Pin;

    MX574_RC_Port->ODR |= MX574_RC_Pin;											// ADC verisi okunur, RC high yapilir
    MX574_CS_Port->ODR &= ~MX574_CS_Pin;
    MX574_A0_Port->ODR &= ~MX574_A0_Pin;
    MX574_CE_Port->ODR &= ~MX574_CE_Pin;

    /*																			//GERCEK VERI OKUMA (MODUL OLDUGUNDA)
    for (int i = 0; i < 12; i++) {
        if (HAL_GPIO_ReadPin(data_ports[i], data_pins[i]) == GPIO_PIN_SET) {
            result |= (1 << i);
        }
    }

    MX574_CE_Port->ODR |= MX574_CE_Pin;

	return result;
	*/

    static uint16_t fake_result = 0;											// test amacli fake veri uretimi , 12 adimda 0-4095 arasi dongu
    fake_result += 341; 														// 341 * 12 = 4092, 12 adim sonra sifirla
    if (fake_result > 4095) fake_result = 0;

    MX574_CE_Port->ODR |= MX574_CE_Pin;

    return fake_result;

}
