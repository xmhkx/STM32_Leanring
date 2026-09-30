#include "RTE_Components.h"
#include <stdint.h>
#undef USE_HAL_DRIVER
#include CMSIS_device_header
#include <stm32f091xc.h>

#define BIT_MASK_B17 (1UL << 17)

void clock_init(void){
    //RCC is reset and clock control register, AHBENER is AHB peripheral clock enable register
    RCC->AHBENR |= BIT_MASK_B17; // Enable GPIOA 
    // this is the same as *(volatile uint32_t *)(0x40021014) |= BIT_MASK_B17;
}

int main() {
    clock_init();
    for (;;) {
        

    }
}
