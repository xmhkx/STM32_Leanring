#include "RTE_Components.h"
#include <stdint.h>
#undef USE_HAL_DRIVER
#include CMSIS_device_header
#include <stm32f091xc.h>

// Definitions for bit positions
#define LD2_POS (5)
#define B1_POS (13)
#define MASK(x) (1UL<<(x))

void button_init(void){
    //RCC is reset and clock control register, AHBENER is AHB peripheral clock enable register
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // Enable GPIOA 
    ////#define BIT_MASK_B17 (1UL << 17)
    // this is the same as *(volatile uint32_t *)(0x40021014) |= BIT_MASK_B17;


    // Configure PA5 in output mode (01=1)
    GPIOA->MODER &= ~GPIO_MODER_MODER5;
    GPIOA->MODER |= (1UL << GPIO_MODER_MODER5_Pos); 


}



int main() {
    button_init();

    while(1) {
        

    }
}
