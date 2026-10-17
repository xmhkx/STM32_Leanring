#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stm32f091xc.h>



// GPIO_TypeDef is from stm32f091xc.h and represents a GPIO port (like GPIOA, GPIOB, etc.)
void gpio_clock_init(GPIO_TypeDef *port);

void gpio_IN_OUT_init(GPIO_TypeDef *port, unsigned char pin_mode);

void gpio_reset_pin();

void gpio_toggle_pin();


#endif // GPIO_H