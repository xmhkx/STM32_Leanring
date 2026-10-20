#include "gpio.h"


void gpio_clock_init(GPIO_TypeDef *port){

/*
takes in gpio port (from) and pin number and sets clock

*/
    if(port == GPIOA){
        RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 
    } else if(port == GPIOB){
        RCC->AHBENR |= RCC_AHBENR_GPIOBEN; 
    } else if(port == GPIOC){
        RCC->AHBENR |= RCC_AHBENR_GPIOCEN; 
    }else if(port == GPIOD){
        RCC->AHBENR |= RCC_AHBENR_GPIODEN;
    }else if(port == GPIOE){
        RCC->AHBENR |= RCC_AHBENR_GPIOEEN;
    }else if(port == GPIOF){
        RCC->AHBENR |= RCC_AHBENR_GPIOFEN;
    }



}


void gpio_IN_OUT_init(GPIO_TypeDef *port, GPIO_PIN_MODER_MODE pin_mode, uint8_t pin_number){

    if(pin_number > 15){
        //invalid pin number
        return;
    }

    uint32_t shift_amount = (pin_number * 2); // each moder incremts by 2 bits for each pin
    uint32_t clear_bits = 0x3; // 0b11 << shift_amount
    uint32_t set_output_bits = 0x1; // 0b01 << shift_amount
    uint32_t set_alt_function_bits = 0x2; // 0b10 << shift_amount
    uint32_t set_analog_bits = 0x3; // 0b11 << shift_amount

    switch(pin_mode){

        case INPUT:
            // clear specific pin bits first and sets it to input mode (00)
            port->MODER &= ~(clear_bits << shift_amount);

        break;

        case OUTPUT:
            // clear specific pin bits first
            port->MODER &= ~(clear_bits << shift_amount);

            port->MODER |= (set_output_bits << shift_amount);

        break;

        case ALT_FUNCTION:
            // clear specific pin bits first
            port->MODER &= ~(clear_bits << shift_amount);

            port->MODER |= (set_alt_function_bits << shift_amount);
            
        break;

        case ANALOG:
            // clear specific pin bits first
            port->MODER &= ~(clear_bits << shift_amount);
            // set specific pin bits to analog mode (11)
            port->MODER |= (set_analog_bits << shift_amount);
        break;
    }


   void gpio_bit_select_set(GPIO_TypeDef *port, uint8_t pin_number){
    
    if(pin_number > 15){
        //invalid pin number
        return;
    }

    uint32_t set_bit = (1UL << pin_number); // create a mask for the specific pin

    // Set the specific pin high
    port->BSRR = set_bit;

   }


   void gpio_bit_select_reset(GPIO_TypeDef *port, uint8_t pin_number){


    if(pin_number > 15){

    }

    uint32_t reset_bit = (1UL << (pin_number + 16)); //(reset bit is at offset 16)`

    port->BSRR = reset_bit;

   }

}