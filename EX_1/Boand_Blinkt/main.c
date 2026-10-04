#include "RTE_Components.h"
#include <stdint.h>
#undef USE_HAL_DRIVER
#include CMSIS_device_header
#include <stm32f091xc.h>



void button_LED_init(void){
    //RCC is reset and clock control register, AHBENER is AHB peripheral clock enable register
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // Enable GPIOA 
    ////#define BIT_MASK_B17 (1UL << 17)
    // this is the same as *(volatile uint32_t *)(0x40021014) |= BIT_MASK_B17;


    // Configure PA5 in output mode (01=1)
    GPIOA->MODER &= ~GPIO_MODER_MODER5;
    GPIOA->MODER |= (1UL << GPIO_MODER_MODER5_Pos); 

    // Enable GPIOC
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN; // Enable GPIOC
    
    // make PC13(button) input mode (00=0)
    GPIOC->MODER &= ~GPIO_MODER_MODER13;  
    
}

void LED_ON(void){

    GPIOA->BSRR = GPIO_BSRR_BS_5; // Set PA5 high

}

void LED_OFF(void){
    
    GPIOA->BSRR = GPIO_BSRR_BR_5; // Set PA5 low
}

unsigned char button_pressed(void){
    // Return true if button is pressed (active low)
    return (GPIOC->IDR & GPIO_IDR_13) == 0;

}


int main() {
    button_LED_init();

    LED_OFF();

    while(1) {
        
        //yes this is polling, but its the first test/example
        if(button_pressed()) {
            LED_ON();
        } else {
            LED_OFF();
        }

    }
}
