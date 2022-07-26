#include <stdio.h>
#include "STM32F7xx.h"
int temp=0;

int main (void)
{
	RCC->AHB1ENR |= 0xFF; //Puertos A,B,C,D,E,F,G,H
	RCC->APB2ENR |= 0X400; //ENCENDER ADC 3

	GPIOC->MODER |=  0x3; //analogo para el pin A3

	GPIOB->MODER |=  0x1000400D;        //colocar en salida para encender los leds (0-7-14)
	GPIOB->OTYPER = 0;
	GPIOB->OSPEEDR =0x10004001;       //medium speed
	GPIOB->PUPDR |=0x10004001;       //pull up

	ADC3 -> CR1	|=	0X0; //RESOLUCION DE 12 BITS (POR DEFECTO)
  ADC3 -> CR2	|=	0X1; //ENCENDER EL ADC;
	ADC3 ->SMPR1=0X7FFFFFF; //TIEMPO DE  MUESTREI EN CICLOS
	ADC3 ->SMPR2=0X37777777; //TIEMPO PARA MUESTREO EN CICLOS
	ADC3 ->SQR3= 3; //CANAL 10 DEL ADC

while (1){
	ADC3 -> CR2|=0X40000000; //INICIAR LA CONVERSACION EN CANALES REGULARES
	if(ADC3 -> DR == 2048){
		GPIOB ->ODR= 0X4000;
	}
	if(ADC3 -> DR == 4095){
		GPIOB ->ODR= 0X1;
	}
	if(ADC3 -> DR == 0){
		GPIOB ->ODR= 0X80;
	}
 }
}