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
    GPIO_PIN_MODER_MODE pin_mode);
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

    PIN_OUTPUT_LOW_SPEED_BITS = 0b00 , // max speed of 2 MHZ
    PIN_OUTPUT_MEDIUM_SPEED_BITS = 0b10, // max speed of 10 MHZ
    PIN_OUTPUT_HIGH_SPEED_BITS = 0b11  // max speed of 50 MHZ

}PIN_OUTPUT_SPEED;

void pin_output_speed_init(
    GPIO_TypeDef *port, 
    uint8_t pin_number, 
    PIN_OUTPUT_SPEED pin_speed_select_bits);
    
//END FOR OUTPUT SPEED


// START OF PULL UP/DOWN 

typedef enum{

    GPIO_NO_PULL_UP_DOWN = 0b00,
    GPIO_PULL_UP_EN = 0b01,
    GPIO_PULL_DOWN_EN = 0b10



}GPIO_PULL_UP_DOWN_TYPE;

void gpio_pull_up_down(
    GPIO_TypeDef *port, 
    uint8_t pin_number, 
    GPIO_PULL_UP_DOWN_TYPE gpio_pull_up_down_select_bits);

// END OF PULL UP/DOWN


//START OF GPIO OUTPUT DATA

void gpio_OUTPUT_data(GPIO_TypeDef *port, uint8_t pin_number, bool output_high);

// END OF GPIO OUTPUT DATA


// START OF GPIO INPUT DATA 

int gpio_INPUT_data(GPIO_TypeDef *port, uint8_t pin_number);

// END OF GPIO INPUT DATA


// START OF GPIO LOCKING

void gpio_lock(GPIO_TypeDef *port, uint8_t pin_number);

int gpio_lock_status(GPIO_TypeDef *port, uint8_t pin_number);

// END OF GPIO LOCKING

// START OF GPIO ALTERNATE FUNCTION

typedef enum{

    ALTERNATE_FUNCTION_NUMBER_SELECTION_AF0 = 0b0000,
    ALTERNATE_FUNCTION_NUMBER_SELECTION_AF1 = 0b0001,
    ALTERNATE_FUNCTION_NUMBER_SELECTION_AF2 = 0b0010,
    ALTERNATE_FUNCTION_NUMBER_SELECTION_AF3 = 0b0011,
    ALTERNATE_FUNCTION_NUMBER_SELECTION_AF4 = 0b0100,
    ALTERNATE_FUNCTION_NUMBER_SELECTION_AF5 = 0b0101,
    ALTERNATE_FUNCTION_NUMBER_SELECTION_AF6 = 0b0110,
    ALTERNATE_FUNCTION_NUMBER_SELECTION_AF7 = 0b0111,

}ALTERNATE_FUNCTION_NUMBER_SELECTION;

void gpio_alternate_function_init(
    GPIO_TypeDef *port, 
    uint8_t pin_number,
    ALTERNATE_FUNCTION_NUMBER_SELECTION alternate_function_number_selection);

// END OF GPIO ALTERNATE FUNCTION


// START OF GPIO BIT PORT RESET

void gpio_port_pin_reset(GPIO_TypeDef *port, uint8_t pin_number);

// END OF GPIO BIT PORT RESET

#endif // GPIO_H