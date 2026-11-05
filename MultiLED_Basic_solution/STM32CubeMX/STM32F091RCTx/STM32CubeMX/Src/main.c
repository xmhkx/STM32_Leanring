#include "RTE_Components.h"
#include <stdint.h>
#include <stm32f091xc.h>
#include "gpio.h"

#define GPIOA_PIN_5 5
#define GPIOA_PIN_5_HIGH true
#define GPIOA_PIN_5_LOW false
 
#define GPIOA_PIN_6 6
#define GPIOA_PIN_6_HIGH true
#define GPIOA_PIN_6_LOW false

#define GPIOA_PIN_7 7
#define GPIOA_PIN_7_HIGH true
#define GPIOA_PIN_7_LOW false 


int main(void){

  gpio_clock_init(GPIOA);
  gpio_IN_OUT_init(GPIOA,GPIOA_PIN_5, OUTPUT);
  gpio_IN_OUT_init(GPIOA, GPIOA_PIN_6, OUTPUT);
  gpio_IN_OUT_init(GPIOA, GPIOA_PIN_7, OUTPUT);

  int counter_interval = 100000;

  while(1){

    gpio_OUTPUT_data(GPIOA, GPIOA_PIN_5, GPIOA_PIN_5_HIGH);

      for(int  i = 0; i < counter_interval; i++){
        asm("NOP"); // do nothing just wait
      }

    gpio_OUTPUT_data(GPIOA, GPIOA_PIN_6, GPIOA_PIN_6_HIGH); 

      for(int  i = 0; i < counter_interval; i++){
        asm("NOP"); 
      }     
      
    gpio_OUTPUT_data(GPIOA, GPIOA_PIN_7, GPIOA_PIN_7_HIGH);

      for(int  i = 0; i < counter_interval; i++){
        asm("NOP"); 
      }

    gpio_OUTPUT_data(GPIOA, GPIOA_PIN_5, GPIOA_PIN_5_LOW);

      for(int  i = 0; i < counter_interval; i++){
        asm("NOP"); 
      }

    gpio_OUTPUT_data(GPIOA, GPIOA_PIN_6, GPIOA_PIN_6_LOW);

      for(int  i = 0; i < counter_interval; i++){
        asm("NOP"); 
      }

    gpio_OUTPUT_data(GPIOA, GPIOA_PIN_7, GPIOA_PIN_7_LOW);

      for(int  i = 0; i < counter_interval; i++){
        asm("NOP"); 
      }
      
    counter_interval -= 9500;

    if(counter_interval < 1000){

      counter_interval = 100000;
    } 

  }

}