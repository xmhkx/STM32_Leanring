#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stm32f091xc.h>
#include <stdbool.h>


// GPIO_TypeDef is from stm32f091xc.h and represents a GPIO port (like GPIOA, GPIOB, etc.)
void gpio_clock_init(GPIO_TypeDef *port);


//END FOR CLOCK INIT

// START FOR PIN IN / OUT INIT
 typedef enum{
        
        INPUT,
        OUTPUT,
        ALT_FUNCTION,
        ANALOG

    }GPIO_PIN_MODER_MODE;




void gpio_IN_OUT_init(
    GPIO_TypeDef *port, 
    GPIO_PIN_MODER_MODE pin_mode, 
    uint8_t pin_number
    );

void gpio_reset_pin();

void gpio_toggle_pin();


#endif // GPIO_H