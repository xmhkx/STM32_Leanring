#include "gpio.h"
#include <stdint.h>


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


void gpio_IN_OUT_init(
    GPIO_TypeDef *port, 
    uint8_t pin_number,
    GPIO_PIN_MODER_MODE pin_mode)
    {

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

        return;
    }

    uint32_t reset_bit = (1UL << (pin_number + 16)); //(reset bit is at offset 16)`

    port->BSRR = reset_bit;

   }



void gpio_OUTPUT_type_init(
    GPIO_TypeDef *port, 
    uint8_t pin_number, 
    bool is_open_drain)
    {
        if(pin_number > 15){
            //invalid pin number
            return;
        }

        if(!is_open_drain){
            // set the output type to push-pull (0)
            port->OTYPER &= ~(1UL << pin_number);

        }else{
            // set the output type to open-drain (1)
            port->OTYPER |= (1UL << pin_number);
        }


    }

void pin_output_speed_init(
        GPIO_TypeDef *port, 
        uint8_t pin_number, 
        PIN_OUTPUT_SPEED pin_speed_select_bits)
        {
            if(pin_number > 15){

                return;
            }

        uint32_t shift_amount = (pin_number * 2);
        uint32_t clear_bits = 3UL;

        port->OSPEEDR &= ~(clear_bits << shift_amount); // clears first 

        port->OSPEEDR |= (pin_speed_select_bits << shift_amount); // sets pins output speed


        }


void gpio_pull_up_down(
    GPIO_TypeDef *port, 
    uint8_t pin_number, 
    GPIO_PULL_UP_DOWN_TYPE gpio_pull_up_down_select_bits)
    {


    if(pin_number > 15){
        return;
    }

    uint32_t shift_amount = (pin_number * 2);
    uint32_t clear_bits = 3UL;

    port->PUPDR &= ~(clear_bits << shift_amount);

    port->PUPDR |= (gpio_pull_up_down_select_bits << shift_amount);

    }

int gpio_INPUT_data(GPIO_TypeDef *port, uint8_t pin_number){

    if(pin_number > 15){
        // doing this cause 1 and 0 are for output and input
        return -1;
        
    }

    uint32_t shift_amount = pin_number; 


    //checks if that IDR reg is 1, since its read only
    uint32_t HIGH_INPUT = port->IDR & (1UL << shift_amount);


    if(HIGH_INPUT){
        return 1;
    }
    else{
        return 0;
    }

}

//only word access(32-bit long) is allowed during this locking sequence.

void gpio_lock(GPIO_TypeDef *port, uint8_t pin_number){

    if(pin_number > 15){
        return;

    }

    uint32_t shift_amount = pin_number;
    uint32_t lock_key_bit = (1UL << 16); // bit 16 is the lock key
    
    // from data sheet; HAS TO DO THIS: 
    /*

    LOCK key write sequence:
    WR LCKR[16] = 1 + LCKR[15:0]
    WR LCKR[16] = 0 + LCKR[15:0]
    WR LCKR[16] = 1 + LCKR[15:0]
    RD LCKR    
    
    */

    // set the lock key bit and the pin bit 1st iteration of three
    port->LCKR = lock_key_bit | (1UL << shift_amount); 

    // clear the lock key bit and set the pin bit 2nd iteration of three
    port->LCKR = (1UL << shift_amount);

    // set the lock key bit and the pin bit 3rd iteration of three
    port->LCKR = lock_key_bit | (1UL << shift_amount);

    //final read to confirm the lock is active
    uint32_t lock_status = port->LCKR;

}


int gpio_lock_status(GPIO_TypeDef *port, uint8_t pin_number){

    if(pin_number > 15){
        return -1;
    }

    uint32_t shift_amount = pin_number;

    // check if the lock bit for the specific pin is set
    uint32_t lock_bit_status = port->LCKR & (1UL << shift_amount);

    if(lock_bit_status){
        return 1; // locked
    } else {
        return 0; // not locked
    }


}

