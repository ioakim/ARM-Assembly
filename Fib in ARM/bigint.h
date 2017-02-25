/**********************************************************************
 * bigint.h                               
 *
 *                           
 * Author: 	Mark Fisher, CMP, UEA                    
 * Date:	03.11.16
 **********************************************************************/

#ifndef BIGINT_INCLUDED
#define BIGINT_INCLUDED

#include <stdio.h>

typedef struct BigInt *BigInt_T;
/* A BigInt_T object is a high-precision integer. */

BigInt_T BigInt_new(unsigned int uiValue);
/* Return a new BigInt_T object initialized to uiValue, or NULL
   if insufficient memory is available. */

void BigInt_free(BigInt_T oBigInt);
/* Free oBigInt.  Do nothing if oBigInt is NULL. */

int BigInt_add(BigInt_T oAddend1, BigInt_T oAddend2, BigInt_T oSum);
/* Assign the sum of oAddend1 and oAddend2 to oSum.  Return 0 (FALSE)
   if an overflow occurred, and 1 (TRUE) otherwise. */

void BigInt_writeHex(FILE *psFile, BigInt_T oBigInt);
/* Write oBigInt to psFile in hexadecimal format. */

#endif

