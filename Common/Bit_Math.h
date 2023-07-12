/*
 * Bit_Math.h
 *
 *  Created on: Mar 22, 2023
 *      Author: Omar
 */

#ifndef COMMON_BIT_MATH_H_
#define COMMON_BIT_MATH_H_

#define SET_BIT(VAR,BIT)   ((VAR) |= (1 << (BIT)))
#define CLR_BIT(VAR,BIT)   (VAR &= ~(1 << BIT))
#define GET_BIT(VAR,BIT)   ((VAR >> BIT) & (1))
#define TOG_BIT(VAR,BIT)   ((VAR) ^= (1 <<(BIT)))

#define ASS_BIT(VAR,BIT,VALUE)   ((VAR) = (((VAR) & ( ~(1 << (BIT))))|(VALUE << BIT)))

#endif /* COMMON_BIT_MATH_H_ */
