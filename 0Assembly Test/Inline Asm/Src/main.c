/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

void ChangeToUnPriv(void)
{
	__asm volatile ("MRS R0,CONTROL");
	__asm volatile ("ORR R0,R0,#1");
	__asm volatile ("MSR CONTROL,R0");

}

void AccessPriv(void)
{
	unsigned long * ISER0Reg =(unsigned long *)0xE000E100;
	* ISER0Reg |= (1<<3);
}

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
//    /****************** EXAMPLE1 ******************/
//
//	/* save memory locations into GPRS */
//	__asm volatile ("LDR R0,=#0x20001000");
//	__asm volatile ("LDR R1,=#0x20001004");
//	/* Read its values */
//	__asm volatile ("LDR R2,[R0]");
//	__asm volatile ("LDR R3,[R1]");
//	/* Add the two variables */
//	__asm volatile ("ADD R4,R3,R2");
//	/* Store the result into address = 0x20001000 */
//	__asm volatile ("STR R4,[R0]");
//
//    /****************** EXAMPLE2 ******************/
//
//	int x = 50;
//	__asm volatile ("MOV R0,%0" : :"r"(x));
//
//    /****************** Labs Lec 9 ******************/

	/* Lab 1 */
	int ControlReg = 5;
	__asm volatile ("MRS %0, PRIMASK " : "=r"(ControlReg) : ); /* Save the primask register */

	__asm("CPSID i"); /* Disable Global Interrupt */

	__asm volatile ("MSR PRIMASK,%0" : :"r"(ControlReg));

//	__asm volatile("MRS %0 , CONTROL " : : );
//	__asm("CPSID I");
//	/* Lab 2 */
//	ChangeToUnPriv();
//	AccessPriv();
//
//	/* Lab 3 */
//	int var1 = 10 , var2;
//	__asm volatile("MOV %0,%1":"=r"(var2):"r"(var1));
//
//	/* Lab 4 */
//	int p, *p2 = (int * )0x20000008;
//	__asm volatile("LDR %0,[%1]" :"=r"(p):"r"(p2));

    /* Loop forever */
	for(;;);
}

void HardFault_Handler(void)
{
	while(1)
	{

	}
}