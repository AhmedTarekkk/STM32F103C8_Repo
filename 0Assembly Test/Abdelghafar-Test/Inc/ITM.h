/*
 * ITM.h
 *
 *  Created on: Apr 29, 2023
 *      Author: Ahmed
 */

#ifndef ITM_H_
#define ITM_H_

#define DEMCR 			*((volatile uint32_t*) 0xE000EDFC)
#define ITM_TER			*((volatile uint32_t*) 0xE0000E00)
#define ITM_STIM0		*((volatile uint32_t*) 0xE0000000)

void Custom_ITM(uint8_t data);

#endif /* ITM_H_ */
