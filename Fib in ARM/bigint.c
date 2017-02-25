/**********************************************************************
 * bigint.c - An ADT for big integers
 *
 * Version:	1.0                                                          
 * Author:	Mark Fisher, CMP, UEA
 * Date:   	03.11.16             
 **********************************************************************/

#include "bigint.h"
#include "bigintprivate.h"
#include <assert.h>
#include <stdlib.h>

/*--------------------------------------------------------------------*/

BigInt_T BigInt_new(unsigned int uiValue)

/* Return a new BigInt_T object initialized to uiValue, or NULL if
   insufficient memory is available. */

{
   BigInt_T oBigInt;

   oBigInt = (BigInt_T)calloc(1, sizeof(struct BigInt));
   if (oBigInt == NULL)
      return NULL;

   if (uiValue > 0)
   {
      oBigInt->iLength = 1;
      oBigInt->auiDigits[0] = uiValue;
   }

   return oBigInt;
}

/*--------------------------------------------------------------------*/

void BigInt_free(BigInt_T oBigInt)

/* Free oBigInt.  Do nothing if oBigInt is NULL. */

{
   free(oBigInt);
   /* Note that free() does nothing if its parameter is NULL. */
}

/*--------------------------------------------------------------------*/

void BigInt_writeHex(FILE *psFile, BigInt_T oBigInt)

/* Write oBigInt to psFile in hexadecimal format. */

{
   int i;

   assert(psFile != NULL);
   assert(oBigInt != NULL);

   if (oBigInt->iLength == 0)
      fprintf(psFile, "%08x", 0);
   else
      for (i = oBigInt->iLength - 1; i >= 0; i--)
         fprintf(psFile, "%08x", oBigInt->auiDigits[i]);
}
