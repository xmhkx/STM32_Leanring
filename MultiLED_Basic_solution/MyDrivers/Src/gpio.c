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


void gpio_IN_OUT_init(GPIO_TypeDef *port, unsigned char pin_mode){

    




}