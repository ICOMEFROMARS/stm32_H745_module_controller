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
    MX574_DATA_MODE_Port->ODR |= MX574_DATA_MODE_Pin;				// 12 bit modunda calis (high)
    MX574_CE_Port->ODR |= MX574_CE_Pin;		// devre disi
    MX574_CS_Port->ODR |= MX574_CS_Pin;		// devre disi
}

uint16_t MX574_Read12Bit(void) {
    uint16_t result = 0;

    MX574_CS_Port->ODR &= ~MX574_CS_Pin;
    MX574_RC_Port->ODR &= ~MX574_RC_Pin;
    MX574_CE_Port->ODR &= ~MX574_CE_Pin;
    for (volatile int i = 0; i < 1000; i++);
    MX574_CE_Port->ODR |= MX574_CE_Pin;

    MX574_RC_Port->ODR |= MX574_RC_Pin;													// veri oku
    MX574_CS_Port->ODR &= ~MX574_CS_Pin;
    MX574_A0_Port->ODR &= ~MX574_A0_Pin;
    MX574_CE_Port->ODR &= ~MX574_CE_Pin;

    /*																																																//GERCEK VERI OKUMA (MODUL OLDUGUNDA)
    for (int i = 0; i < 12; i++) {
        if (HAL_GPIO_ReadPin(data_ports[i], data_pins[i]) == GPIO_PIN_SET) {
            result |= (1 << i);
        }
    }

    MX574_CE_Port->ODR |= MX574_CE_Pin;

	return result;
	*/

    static uint16_t fake_result = 0;																																			// TEST AMACLI, SILINECEK
    fake_result += 341; 																																								// 341 * 12 = 4092, 12 adim sonra sifirla
    if (fake_result > 4095) fake_result = 0;

    MX574_CE_Port->ODR |= MX574_CE_Pin;

    return fake_result;

}
