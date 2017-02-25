/**********************************************************************
 * bigintadd.c  - bigint method
 *
 * Version:	1.0
 * Author: 	Mark Fisher, CMP, UEA
 * Date:	03.11.16
 **********************************************************************/

#include "bigint.h"
#include "bigintprivate.h"
#include <assert.h>

enum {FALSE, TRUE};

/*--------------------------------------------------------------------*/

static int BigInt_larger(int iLength1, int iLength2)

/* Return the larger of iLength1 and iLength2. */

{
   int iLarger;
   if (iLength1 > iLength2)
      iLarger = iLength1;
   else
      iLarger = iLength2;
   return iLarger;
}

/*--------------------------------------------------------------------*/

int BigInt_add(BigInt_T oAddend1, BigInt_T oAddend2, BigInt_T oSum)

/* Assign the sum of oAddend1 and oAddend2 to oSum.  Return 0 (FALSE)
   if an overflow occurred, and 1 (TRUE) otherwise. */

{
   unsigned int uiCarry = 0;
   unsigned int uiSum;
   int i;
   int iSumLength;

   assert(oAddend1 != NULL);
   assert(oAddend2 != NULL);
   assert(oSum != NULL);

   iSumLength = BigInt_larger(oAddend1->iLength, oAddend2->iLength);

   for (i = 0; i < iSumLength; i++)
   {
      uiSum = uiCarry;
      uiCarry = 0;

      uiSum += oAddend1->auiDigits[i];
      if (uiSum < oAddend1->auiDigits[i]) /* Check for overflow. */
         uiCarry = 1;

      uiSum += oAddend2->auiDigits[i];
      if (uiSum < oAddend2->auiDigits[i]) /* Check for overflow. */
         uiCarry = 1;

      oSum->auiDigits[i] = uiSum;
   }

   if (uiCarry == 1)
   {
      if (iSumLength == MAX_DIGITS)
         return FALSE;
      oSum->auiDigits[iSumLength] = 1;
      iSumLength++;
   }

   oSum->iLength = iSumLength;

   return TRUE;
}
