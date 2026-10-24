#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stm32f091xc.h>
#include <stdbool.h>

// this is for gpio output type function
#define OPEN_DRAIN false
#define PUSH_PULL true


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
    uint8_t pin_number,
    GPIO_PIN_MODER_MODE pin_mode
    );
//END FOR PIN IN / OUT INIT

void gpio_OUTPUT_type_init(
    GPIO_TypeDef *port, 
    uint8_t pin_number, 
    bool is_open_drain);




void gpio_bit_select_set(GPIO_TypeDef *port, uint8_t pin_number);
void gpio_bit_select_reset(GPIO_TypeDef *port, uint8_t pin_number);


// START FOR OUTPUT SPEED INIT

// config your output speed
typedef enum{

    PIN_OUTPUT_LOW_SPEED_BITS = 0b00 , // used for 
    PIN_OUTPUT_MEDIUM_SPEED_BITS = 0b10,
    PIN_OUTPUT_HIGH_SPEED_BITS = 0b11

}PIN_OUTPUT_SPEED;

void pin_output_speed_init(
    GPIO_TypeDef *port, 
    uint8_t pin_number, 
    PIN_OUTPUT_SPEED pin_speed_select_bits);


#endif // GPIO_H