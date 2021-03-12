/*
 * Author: Kevin Tom (https://sites.google.com/view/kevintom)
 *
 * Microcontroller : STM32F446RE-NUCLEO
 * 					 ARM CORTEX M4 core at 180 MHz
 * 					 512 Kb Flash
 * 					 128 Kb SRAM
 *
 * Description
 * ```````````
 *
 * UART Details
 * ````````````
 * Used				 : 	USART2
 * Pins				 :	PA2 (TX)
 * 		 				PA3 (RX)
 * Baudrate 		 : 	115200
 * No. Of Stop Bits  : 	1
 *
 * GPIO
 * ````
 * Used 			 : GPIOA, GPIOC
 * Pins 			 : PA5, PC13
 *
 */

//Header files
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
			
//Function prototypes
static void prvSetupHardware(void);
static void prvSetupUART(void);
static void prvSetupGPIO(void);


TaskHandle_t xTaskHandle1=NULL;
TaskHandle_t xTaskHandle2=NULL;



char usr_msg[100];


int main(void)
{
	//For enabling cycle counter(SEGGER)
	DWT->CTRL |= (1<<0);

	//DeIntialzing the 180MHz clock to default(disabling the PLL), because we do not need such high speed.
	//HSI ON, PLL OFF,HSE OFF, system clock=16Mhz, cpu_clock = 16Mhz
	RCC_DeInit();

	//Update the SystemCoreClock variable
	SystemCoreClockUpdate();

	prvSetupHardware();

	sprintf(usr_msg,"Task Deletion API Project");
	printmsg(usr_msg);

	SEGGER_SYSVIEW_Conf();
	SEGGER_SYSVIEW_Start();

	xTaskCreate(vtask_led_delete_handler, "Delete Task", 500, NULL, 1, &xTaskHandle1);
	xTaskCreate(vtask_led_handler, "Led Blink Task", 500, NULL, 2, &xTaskHandle2);

	for(;;);
}


static void prvSetupHardware(void)
{
	prvSetupUART();
	prvSetupGPIO();
}

static void prvSetupUART(void)
{

	GPIO_InitTypeDef gpio_uart_pins;
	USART_InitTypeDef uart2_init;

	//Enabling UART and GPIO peripheral port clocks
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	//PA2 is USART2_TX and PA3 is USART2_RX(from data-sheet(alternate pin section of data-sheet))
	memeset(&gpio_uart_pins,0,sizeof(gpio_uart_pins));
	gpio_uart_pins.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_1;
	gpio_uart_pins.GPIO_Mode = GPIO_Mode_AF;
	gpio_uart_pins.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &gpio_uart_pins);



}


static void prvSetupGPIO(void)
{

}
